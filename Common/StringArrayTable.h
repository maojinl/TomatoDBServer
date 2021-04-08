#ifndef		__STRING_ARRAY_TABLE_H__
#define		__STRING_ARRAY_TABLE_H__

#include <stack>

#include "Type.h"


class StringArrayTable
{
private:
	unsigned char layer;
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
	bool WriteArrayAtCurrentNode(const vector<string>& dataToWrite);
	bool CurrentNodeFound()
	{
		return currLayerStart.size() > 0;
	}

	int GetLength()
	{
		return length;
	}
	unsigned char GetLayer()
	{
		return layer;
	}
	char* GetData()
	{
		return data;
	}
};

#endif