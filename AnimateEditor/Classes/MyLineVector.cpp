#include "MyLineVector.h"
#include "MyConfig.h"

MyLineVector::MyLineVector()
{
}


MyLineVector::~MyLineVector()
{
	int i = 0;
	int j = 0;
	for (i = 0; i < _lineButton.size(); i ++)
	{
		for (j = 0; j < _lineButton.at(i).size(); j ++)
		{
			DEL_FREE_OBJ(_lineButton.at(i).at(j));
		}
	}
}
