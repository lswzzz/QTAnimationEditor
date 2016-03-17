#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

//#include "cocos2d.h"
#include "CocosQtPort/CCQApplication.h"
#include "qtedit.h"

class  AppDelegate : private cocos2d::CCQApplication
{
public:
	AppDelegate(int argc, char *argv[]) : cocos2d::CCQApplication(argc, argv) {};
	virtual ~AppDelegate();

    virtual void initGLContextAttrs();

    /**
    @brief    Implement Director and Scene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();

	void setParent(HWND hwnd, RECT rect);

protected:
	HWND m_ParentHwnd;
	RECT m_ParentRect;
};

#endif // _APP_DELEGATE_H_

