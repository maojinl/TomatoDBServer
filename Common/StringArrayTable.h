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
	StringArrayTable(int bufSize = 1024);
	virtual ~StringArrayTable();
	VOID InitWithData(int len, char* p);
	bool InitWithArrays(const vector<string>* const keys1, const vector<vector<string>>* const keys2 = nullptr, const vector<vector<vector<string>>>* const keys3 = nullptr);
	void InitLayerAndBuffer(const vector<string>* const keys1, const vector<vector<string>>* const keys2 = nullptr, const vector<vector<vector<string>>>* const keys3 = nullptr);
	bool GetArrayAtKeys(const vector<string>& keys, vector<string>& dataArray);
	bool WriteArrayAtCurrentNode(const vector<string>& dataToWrite);
	bool Append(const StringArrayTable& sat);
	void AddLength(int diff)
	{
		length += diff;
		bufferSize -= diff;
	}
	bool CurrentNodeFound() const
	{
		return currLayerStart.size() > 0;
	}

	int GetLength() const
	{
		return length;
	}
	unsigned char GetLayer() const
	{
		return layer;
	}
	char* const GetData() const
	{
		return data;
	}
};

#endif