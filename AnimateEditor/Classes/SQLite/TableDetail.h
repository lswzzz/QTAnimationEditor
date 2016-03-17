#pragma once
#include "iostream"
using namespace std;
class TableDetail
{
public:
	TableDetail(void);
	~TableDetail(void);
	string name;
	bool is_Can_null;
	string type;
	bool primarykey;
	bool is_auto;
	bool foreginkey;
	string for_from;
};

