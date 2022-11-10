#include <gui/screen3_screen/Screen3View.hpp>
#include <gui/screen3_screen/Screen3Presenter.hpp>

Screen3Presenter::Screen3Presenter(Screen3View &v) :
		view(v) {

}

void Screen3Presenter::activate() {

}

void Screen3Presenter::deactivate() {

}

void Screen3Presenter::setIndicatorPresenter(int value1, int value2) {
	view.setIndicator(value1, value2);
}

