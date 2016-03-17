#include "qtedit.h"
#include "AppDelegate.h"
#include <QtWidgets/QApplication>

USING_NS_CC;
int main(int argc, char *argv[])
{
	CCQApplication::addLibraryPath("./plugins");
	AppDelegate app(argc, argv);
	QtEdit w;
	w.show();
	RECT t;
	auto widget = w.getUI().MainWidget;
	t.left = widget->rect().left();
	t.right = widget->rect().right() + 1;
	t.top = widget->rect().top();
	t.bottom = widget->rect().bottom() + 1;
	app.setParent((HWND)widget->winId(), t);

	return cocos2d::CCQApplication::getInstance()->run();
}
