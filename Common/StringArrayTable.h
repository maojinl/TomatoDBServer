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
	stack<int> currNodeStart;
	int currLayer;
	int cursor;
	void ReInitialize();
	void MoveTheNodesAfterCurrent(int currNodeSize, int moveSize);
	void UpdateParentsSize(int currNodeSize, int moveSize);
	bool GetArrayAtKeys(const vector<string>& keys, vector<string>* pArray = nullptr);
	uint GetCurrentNodeNumPos(uint nodeStart) const
	{
		uint cur;
		if (nodeStart > 1)
		{
			cur = nodeStart + 1;
			char nameSize = data[nodeStart];
			cur += nameSize;
		}
		else
		{
			cur = 1;
		}
		return cur;
	}

	uint GetCurrentNodeSizePos(uint nodeStart) const
	{
		uint cur;
		if (nodeStart > 1)
		{ 
			cur = nodeStart + 1;
			char nameSize = data[nodeStart];
			cur += nameSize + 4;
		}
		else
		{
			cur = 5;
		}
		return cur;
	}

public:
	StringArrayTable(int bufSize = 1024);
	virtual ~StringArrayTable();
	VOID InitWithData(int len, const char* p);
	bool InitWithArrays(const vector<string>* const keys1, const vector<vector<string>>* const keys2 = nullptr, const vector<vector<vector<string>>>* const keys3 = nullptr);
	void InitLayerAndBuffer(const vector<string>* const keys1, const vector<vector<string>>* const keys2 = nullptr, const vector<vector<vector<string>>>* const keys3 = nullptr);
	bool GetArrayAtKeys(const vector<string>& keys, vector<string>& dataArray);
	bool WriteArrayAtCurrentNode(const vector<string>& dataToWrite);
	bool Append(const StringArrayTable& sat);
	void InitEmptyStruct(unsigned char nlayer);
	bool DeleteArrayAtCurrentNode();
	bool FindNodeAtKeys(const vector<string>& keys);
	void AddLength(int diff)
	{
		length += diff;
		bufferSize -= diff;
	}
	bool CurrentNodeFound() const
	{
		return currNodeStart.size() > 0;
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

	string dump()
	{
		string s(data, length);
		return s;
	}
};

#endif