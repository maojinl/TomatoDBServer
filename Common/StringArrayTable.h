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
	VOID StringArrayTable::ReInitialize();
public:
	StringArrayTable(int bufSize = 128);
	virtual ~StringArrayTable();
	VOID InitWithData(int len, char* p);
	bool InitWithArrays(const vector<string>* const keys1, const vector<vector<string>>* const keys2 = nullptr, const vector<vector<vector<string>>>* const keys3 = nullptr);
	void InitLayerAndBuffer(const vector<string>* const keys1, const vector<vector<string>>* const keys2 = nullptr, const vector<vector<vector<string>>>* const keys3 = nullptr);
	bool GetArrayAtKeys(const vector<string>& keys, vector<string>& dataArray);
	int GetLength()
	{
		return length;
	}
	int GetLayer()
	{
		return layer;
	}
	char* GetData()
	{
		return data;
	}
};

#endif