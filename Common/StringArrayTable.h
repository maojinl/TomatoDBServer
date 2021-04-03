#ifndef		__STRING_ARRAY_TABLE_H__
#define		__STRING_ARRAY_TABLE_H__

#include <stack>

#include "Type.h"


class StringArrayTable
{
private:
	int layer;
	int bufferSize;
	int length;
	char* data;
	stack<int> currLayerStart;
	int currLayer;
	int cursor;
public:
	StringArrayTable(int l, int bufSize);
	virtual ~StringArrayTable();
	VOID InitWithData(int len, char* p);
	bool GetArrayAtKeys(const vector<string>& keys, vector<string>& dataArray);
};

#endif