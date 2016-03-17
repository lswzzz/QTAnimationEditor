#include "Global.h"
#include "qtedit.h"

void ShowMessage(std::string str)
{
	QtEdit::getInstance()->ShowMsg(str);
}

int layerColorGlobalZ = -1;
int C3DSpriteGlobalZ = 0;