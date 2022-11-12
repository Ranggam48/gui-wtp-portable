/*
 * com_can.c
 *
 *  Created on: Apr 27, 2022
 *      Author: rangga
 */

#include "main.h"
#include "com_can.h"
#include "string.h"

#define RX_BUFFER_SIZE 256

extern CAN_HandleTypeDef hcan;
extern uint8_t 			  selfID;
extern uint8_t 			  bldcID;
extern float current, erpm;
uint8_t                   hvrdf_status = 0;

CAN_RxHeaderTypeDef   RxHeader;
CAN_TxHeaderTypeDef   TxHeader;

uint8_t               TxData[8];
uint8_t               RxData[8];

uint32_t              TxMailbox;

static uint8_t rx_buffer[RX_BUFFER_SIZE];

// Callback untuk penerimaan data can bus
void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO1, &RxHeader, RxData);
    if (RxHeader.IDE == CAN_ID_EXT) return;

    int32_t ind = 0;
    unsigned int rxbuf_len;
    unsigned int rxbuf_ind;
    uint8_t crc_low;
    uint8_t crc_high;
    uint8_t commands_send;

    uint8_t id = RxHeader.ExtId & 0xFF;
    uint8_t cmd = RxHeader.ExtId >> 8;
    uint8_t *data8 = RxData;
    uint8_t len = RxHeader.DLC;

    if (id == bldcID && cmd == CAN_PACKET_SET_HVRDF) {
        hvrdf_status = buffer_get_int32(data8, &ind);
        return;
    }

    if (id != selfID) return;

    switch (cmd) {
        case CAN_PACKET_FILL_RX_BUFFER:
            memcpy(rx_buffer + data8[0], data8 + 1, len - 1);
            break;

        case CAN_PACKET_FILL_RX_BUFFER_LONG:
            rxbuf_ind = (unsigned int) data8[0] << 8;
            rxbuf_ind |= data8[1];
            if (rxbuf_ind < RX_BUFFER_SIZE) {
                memcpy(rx_buffer + rxbuf_ind, data8 + 2, len - 2);
            }
            break;

        case CAN_PACKET_PROCESS_RX_BUFFER:
            ind = 0;
            commands_send = data8[ind++];
            rxbuf_len = (unsigned int) data8[ind++] << 8;
            rxbuf_len |= (unsigned int) data8[ind++];

            if (rxbuf_len > RX_BUFFER_SIZE) {
                break;
            }

            crc_high = data8[ind++];
            crc_low = data8[ind++];

            if (crc16(rx_buffer, rxbuf_len)
                == ((unsigned short) crc_high << 8
                    | (unsigned short) crc_low)) {
                commands_process_packet(rx_buffer, rxbuf_len, 0);
            }
            break;

        case CAN_PACKET_PROCESS_SHORT_BUFFER:
            ind = 0;
            commands_send = data8[ind++];
            commands_process_packet(data8 + ind, len - ind, 0);
            break;

        default:
            break;
    }
}

void comm_can_transmit_eid(uint32_t id, const uint8_t *data, uint8_t len) {
    if (len > 8) {
        len = 8;
    }

    TxHeader.IDE = CAN_ID_EXT;
    TxHeader.ExtId = id;
    TxHeader.RTR = CAN_RTR_DATA;
    TxHeader.DLC = len;
    memcpy(TxData, data, len);
    HAL_CAN_AddTxMessage(&hcan, &TxHeader, TxData, &TxMailbox);
}

/**
 * Send a buffer up to RX_BUFFER_SIZE bytes as fragments. If the buffer is 6 bytes or less
 * it will be sent in a single CAN frame, otherwise it will be split into
 * several frames.
 *
 * @param controller_id
 * The controller id to send to.
 *
 * @param data
 * The payload.
 *
 * @param len
 * The payload length.
 *
 * @param send
 * 0: Packet goes to commands_process_packet of receiver
 * 1: Packet goes to commiveands_send_packet of recer
 * 2: Packet goes to commands_process and send function is set to null
 *    so that no reply is sent back.
 */
void comm_can_send_buffer(uint8_t controller_id, uint8_t *data, unsigned int len, uint8_t send) {
    uint8_t send_buffer[8];

    if (len <= 6) {
        uint32_t ind = 0;
        send_buffer[ind++] = selfID;
        send_buffer[ind++] = send;
        memcpy(send_buffer + ind, data, len);
        ind += len;
        comm_can_transmit_eid(controller_id |
                              ((uint32_t)CAN_PACKET_PROCESS_SHORT_BUFFER << 8), send_buffer, ind);
    } else {
        unsigned int end_a = 0;
        for (unsigned int i = 0;i < len;i += 7) {
            if (i > 255) {
                break;
            }

            end_a = i + 7;

            uint8_t send_len = 7;
            send_buffer[0] = i;

            if ((i + 7) <= len) {
                memcpy(send_buffer + 1, data + i, send_len);
            } else {
                send_len = len - i;
                memcpy(send_buffer + 1, data + i, send_len);
            }

            comm_can_transmit_eid(controller_id |
                                  ((uint32_t)CAN_PACKET_FILL_RX_BUFFER << 8), send_buffer, send_len + 1);
        }

        for (unsigned int i = end_a;i < len;i += 6) {
            uint8_t send_len = 6;
            send_buffer[0] = i >> 8;
            send_buffer[1] = i & 0xFF;

            if ((i + 6) <= len) {
                memcpy(send_buffer + 2, data + i, send_len);
            } else {
                send_len = len - i;
                memcpy(send_buffer + 2, data + i, send_len);
            }

            comm_can_transmit_eid(controller_id |
                                  ((uint32_t)CAN_PACKET_FILL_RX_BUFFER_LONG << 8), send_buffer, send_len + 2);
        }

        uint32_t ind = 0;
        send_buffer[ind++] = selfID;
        send_buffer[ind++] = send;
        send_buffer[ind++] = len >> 8;
        send_buffer[ind++] = len & 0xFF;
        unsigned short crc = crc16(data, len);
        send_buffer[ind++] = (uint8_t)(crc >> 8);
        send_buffer[ind++] = (uint8_t)(crc & 0xFF);

        comm_can_transmit_eid(controller_id |
                              ((uint32_t)CAN_PACKET_PROCESS_RX_BUFFER << 8), send_buffer, ind++);
    }
}


void comm_can_set_mode(uint8_t controller_id , int command){
    int32_t send_index = 0;
    uint8_t buffer[4];
    buffer_append_int32(buffer, (int32_t)command, &send_index);
    comm_can_transmit_eid(controller_id |
                          ((uint32_t)CAN_PACKET_SET_HVRDF << 8), buffer, send_index);
}

void comm_can_get_values(uint8_t controller_id) {
    static uint8_t data = COMM_GET_VALUES;
    comm_can_send_buffer(controller_id, &data, 1, 0);
}

void comm_can_set_duty(uint8_t controller_id, float duty) {
    int32_t send_index = 0;
    uint8_t buffer[4];
    buffer_append_int32(buffer, (int32_t)(duty * 100000.0), &send_index);
    comm_can_transmit_eid(controller_id |
                          ((uint32_t)CAN_PACKET_SET_DUTY << 8), buffer, send_index);
}

void comm_can_set_current(uint8_t controller_id, float current) {
    int32_t send_index = 0;
    uint8_t buffer[4];
    buffer_append_int32(buffer, (int32_t)(current * 1000.0), &send_index);
    comm_can_transmit_eid(controller_id |
                          ((uint32_t)CAN_PACKET_SET_CURRENT << 8), buffer, send_index);
}

/**
 * Process a received buffer with commands and data.
 *
 * @param data
 * The buffer to process.
 *
 * @param len
 * The length of the buffer.
 */
void commands_process_packet(unsigned char *data, unsigned int len,
                             void(*reply_func)(unsigned char *data, unsigned int len)) {

    if (!len) return;

    COMM_PACKET_ID packet_id;
    packet_id = data[0];
    data++;
    len--;

    switch (packet_id) {
        case COMM_GET_VALUES:
        case COMM_GET_VALUES_SELECTIVE: {
            int32_t ind = 0;

            uint32_t mask = 0xFFFFFFFF;
            if (packet_id == COMM_GET_VALUES_SELECTIVE) {
                mask = buffer_get_uint32(data, &ind);
            }

            if (mask & ((uint32_t)1 << 0)) {
                float temp_fet = buffer_get_float16(data, 1e1, &ind);
//			buffer_append_float16(send_buffer, mc_interface_temp_fet_filtered(), 1e1, &ind);
            }
            if (mask & ((uint32_t)1 << 1)) {
                float temp_motor = buffer_get_float16(data, 1e1, &ind);
//			buffer_append_float16(send_buffer, mc_interface_temp_motor_filtered(), 1e1, &ind);
            }
            if (mask & ((uint32_t)1 << 2)) {
                float temp_motor = buffer_get_float32(data, 1e2, &ind);
//			buffer_append_float32(send_buffer, mc_interface_read_reset_avg_motor_current(), 1e2, &ind);
            }
            if (mask & ((uint32_t)1 << 3)) {
                current = buffer_get_float32(data, 1e2, &ind);
//			buffer_append_float32(send_buffer, mc_interface_read_reset_avg_input_current(), 1e2, &ind);
            }
            if (mask & ((uint32_t)1 << 4)) {
                float current_d = buffer_get_float32(data, 1e2, &ind);
//			buffer_append_float32(send_buffer, mc_interface_read_reset_avg_id(), 1e2, &ind);
            }
            if (mask & ((uint32_t)1 << 5)) {
                float current_q = buffer_get_float32(data, 1e2, &ind);
//			buffer_append_float32(send_buffer, mc_interface_read_reset_avg_iq(), 1e2, &ind);
            }
            if (mask & ((uint32_t)1 << 6)) {
                float duty_cycle = buffer_get_float32(data, 1e3, &ind);
//			buffer_append_float16(send_buffer, mc_interface_get_duty_cycle_now(), 1e3, &ind);
            }
            if (mask & ((uint32_t)1 << 7)) {
                erpm = buffer_get_float32(data, 1e0, &ind);
//			buffer_append_float32(send_buffer, mc_interface_get_rpm(), 1e0, &ind);
            }
            if (mask & ((uint32_t)1 << 8)) {
                float voltage_input = buffer_get_float16(data, 1e1, &ind);
//			buffer_append_float16(send_buffer, mc_interface_get_input_voltage_filtered(), 1e1, &ind);
            }
            if (mask & ((uint32_t)1 << 9)) {
                float amp_hours = buffer_get_float32(data, 1e4, &ind);
//			buffer_append_float32(send_buffer, mc_interface_get_amp_hours(false), 1e4, &ind);
            }
            if (mask & ((uint32_t)1 << 10)) {
                float amp_hours_charged = buffer_get_float32(data, 1e4, &ind);
//			buffer_append_float32(send_buffer, mc_interface_get_amp_hours_charged(false), 1e4, &ind);
            }
            if (mask & ((uint32_t)1 << 11)) {
                float watt_hours = buffer_get_float32(data, 1e4, &ind);
//			buffer_append_float32(send_buffer, mc_interface_get_watt_hours(false), 1e4, &ind);
            }
            if (mask & ((uint32_t)1 << 12)) {
                float watt_hours_charged = buffer_get_float32(data, 1e4, &ind);
//			buffer_append_float32(send_buffer, mc_interface_get_watt_hours_charged(false), 1e4, &ind);
            }
            if (mask & ((uint32_t)1 << 13)) {
                int32_t tachometer = buffer_get_int32(data, &ind);
//			buffer_append_int32(send_buffer, mc_interface_get_tachometer_value(false), &ind);
            }
            if (mask & ((uint32_t)1 << 14)) {
                int32_t tachometer_abs = buffer_get_int32(data, &ind);
//			buffer_append_int32(send_buffer, mc_interface_get_tachometer_abs_value(false), &ind);
            }
            if (mask & ((uint32_t)1 << 15)) {
                uint8_t is_fault = data[ind++];
//			send_buffer[ind++] = mc_interface_get_fault();
            }
            if (mask & ((uint32_t)1 << 16)) {
                float pid_pos = buffer_get_float32(data, 1e6, &ind);
//			buffer_append_float32(send_buffer, mc_interface_get_pid_pos_now(), 1e6, &ind);
            }
            if (mask & ((uint32_t)1 << 17)) {
                uint8_t controller_id = data[ind++];
//			uint8_t current_controller_id = app_get_configuration()->controller_id;
//#ifdef HW_HAS_DUAL_MOTORS
//			if (mc_interface_get_motor_thread() == 2) {
//				current_controller_id = utils_second_motor_id();
//			}
//#endif
//			send_buffer[ind++] = current_controller_id;
            }
            if (mask & ((uint32_t)1 << 18)) {
                float temp_ntc_mos1 = buffer_get_float16(data, 1e1, &ind);
                float temp_ntc_mos2 = buffer_get_float16(data, 1e1, &ind);
                float temp_ntc_mos3 = buffer_get_float16(data, 1e1, &ind);
//			buffer_append_float16(send_buffer, NTC_TEMP_MOS1(), 1e1, &ind);
//			buffer_append_float16(send_buffer, NTC_TEMP_MOS2(), 1e1, &ind);
//			buffer_append_float16(send_buffer, NTC_TEMP_MOS3(), 1e1, &ind);
            }
            if (mask & ((uint32_t)1 << 19)) {
                float voltage_d = buffer_get_float32(data, 1e3, &ind);
//			buffer_append_float32(send_buffer, mc_interface_read_reset_avg_vd(), 1e3, &ind);
            }
            if (mask & ((uint32_t)1 << 20)) {
                float voltage_q = buffer_get_float32(data, 1e3, &ind);
//			buffer_append_float32(send_buffer, mc_interface_read_reset_avg_vq(), 1e3, &ind);
            }
//		if (mask & ((uint32_t)1 << 21)) {
//			uint8_t status = 0;
//			status |= timeout_has_timeout();
//			status |= timeout_kill_sw_active() << 1;
//			send_buffer[ind++] = status;
//		}
        } break;

        default:
            break;
    }
}


// CRC Table
const unsigned short crc16_tab[] = { 0x0000, 0x1021, 0x2042, 0x3063, 0x4084,
                                     0x50a5, 0x60c6, 0x70e7, 0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad,
                                     0xe1ce, 0xf1ef, 0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7,
                                     0x62d6, 0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
                                     0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485, 0xa56a,
                                     0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d, 0x3653, 0x2672,
                                     0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4, 0xb75b, 0xa77a, 0x9719,
                                     0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc, 0x48c4, 0x58e5, 0x6886, 0x78a7,
                                     0x0840, 0x1861, 0x2802, 0x3823, 0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948,
                                     0x9969, 0xa90a, 0xb92b, 0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50,
                                     0x3a33, 0x2a12, 0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b,
                                     0xab1a, 0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
                                     0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49, 0x7e97,
                                     0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70, 0xff9f, 0xefbe,
                                     0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78, 0x9188, 0x81a9, 0xb1ca,
                                     0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f, 0x1080, 0x00a1, 0x30c2, 0x20e3,
                                     0x5004, 0x4025, 0x7046, 0x6067, 0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d,
                                     0xd31c, 0xe37f, 0xf35e, 0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214,
                                     0x6277, 0x7256, 0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c,
                                     0xc50d, 0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
                                     0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c, 0x26d3,
                                     0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634, 0xd94c, 0xc96d,
                                     0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab, 0x5844, 0x4865, 0x7806,
                                     0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3, 0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e,
                                     0x8bf9, 0x9bd8, 0xabbb, 0xbb9a, 0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1,
                                     0x1ad0, 0x2ab3, 0x3a92, 0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b,
                                     0x9de8, 0x8dc9, 0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0,
                                     0x0cc1, 0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
                                     0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0 };

unsigned short crc16(unsigned char *buf, unsigned int len) {
    unsigned int i;
    unsigned short cksum = 0;
    for (i = 0; i < len; i++) {
        cksum = crc16_tab[(((cksum >> 8) ^ *buf++) & 0xFF)] ^ (cksum << 8);
    }
    return cksum;
}

void buffer_append_int16(uint8_t* buffer, int16_t number, int32_t *index) {
    buffer[(*index)++] = number >> 8;
    buffer[(*index)++] = number;
}

void buffer_append_uint16(uint8_t* buffer, uint16_t number, int32_t *index) {
    buffer[(*index)++] = number >> 8;
    buffer[(*index)++] = number;
}

void buffer_append_int32(uint8_t* buffer, int32_t number, int32_t *index) {
    buffer[(*index)++] = number >> 24;
    buffer[(*index)++] = number >> 16;
    buffer[(*index)++] = number >> 8;
    buffer[(*index)++] = number;
}

void buffer_append_uint32(uint8_t* buffer, uint32_t number, int32_t *index) {
    buffer[(*index)++] = number >> 24;
    buffer[(*index)++] = number >> 16;
    buffer[(*index)++] = number >> 8;
    buffer[(*index)++] = number;
}

void buffer_append_float16(uint8_t* buffer, float number, float scale, int32_t *index) {
    buffer_append_int16(buffer, (int16_t)(number * scale), index);
}

void buffer_append_float32(uint8_t* buffer, float number, float scale, int32_t *index) {
    buffer_append_int32(buffer, (int32_t)(number * scale), index);
}