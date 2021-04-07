#include "stdafx.h"

#include "StringArrayTable.h"
#include "util/coding.h"

StringArrayTable::StringArrayTable(int bufSize):
	layer(0), bufferSize(bufSize), data(nullptr), length(0), currLayer(0), cursor(0)
{
}

VOID StringArrayTable::InitWithData(int len, char* p)
{
	length = len;
	data = new char[length + bufferSize];
	memcpy(data, p, length);
	ReInitialize();
	layer = leveldb::DecodeFixed32(&data[cursor]);
}

void StringArrayTable::InitLayerAndBuffer(const vector<string>* const keys1, const vector<vector<string>>* const keys2, const vector<vector<vector<string>>>* const keys3)
{
	SAFE_DELETE_ARRAY(data);
	ReInitialize();
	layer = 1;
	length++; //add layer
	length += 4; //add num
	length += 4; //node size in layer 1;
	length += keys1->size(); //add name size bit
	for (int i = 0; i < keys1->size(); i++)
	{
		length += (*keys1)[i].size();
		if (keys2 != nullptr)
		{
			layer = 2;
			length += 4; //add num
			length += 4; //add node size
			length += (*keys2)[i].size(); //add name size bit
			for (int j = 0; j < (*keys2)[i].size(); j++)
			{
				length += (*keys2)[i][j].size();
				if (keys3 != nullptr)
				{
					layer = 3;
					length += 4; //add num
					length += 4; //add node size
					length += (*keys3)[i][j].size(); //add name size bit
					for (int k = 0; k < (*keys3)[i][j].size(); k++)
					{
						length += (*keys3)[i][j][k].size();
					}
				}
			}
		}
	}

	length += bufferSize;
	data = new char[length];
}

bool StringArrayTable::InitWithArrays(const vector<string>* const keys1, const vector<vector<string>>* const keys2, const vector<vector<vector<string>>>* const keys3)
{
	InitLayerAndBuffer(keys1, keys2, keys3);
	stack<int> nodeSize;
	int nameSize;

	data[cursor] = layer;
	cursor ++;
	currLayerStart.push(cursor);
	leveldb::EncodeFixed32(&data[cursor], (*keys1).size());
	cursor += 4;
	nodeSize.push(0);
	//skip for node size pos
	cursor += 4;
	for (int i = 0; i < keys1->size(); i++)
	{
		nameSize = (*keys1)[i].size();
		data[cursor++] = nameSize;
		memcpy(&data[cursor], (*keys1)[i].c_str(), nameSize);
		cursor += nameSize;
		if (keys2 != nullptr)
		{
			currLayerStart.push(cursor);
			leveldb::EncodeFixed32(&data[cursor], (*keys2)[i].size());
			cursor += 4;

			nodeSize.push(0);
			//skip for node size pos
			cursor += 4;
			

			for (int j = 0; j < (*keys2)[i].size(); j++)
			{
				nameSize = (*keys2)[i][j].size();
				data[cursor++] = nameSize;
				memcpy(&data[cursor], (*keys2)[i][j].c_str(), nameSize);
				cursor += nameSize;
				if (keys3 != nullptr)
				{
					currLayerStart.push(cursor);
					leveldb::EncodeFixed32(&data[cursor], (*keys3)[i][j].size());
					cursor += 4;

					nodeSize.push(0);
					//skip for node size pos
					cursor += 4;
					nodeSize.top() = cursor - currLayerStart.top();

					for (int k = 0; k < (*keys3)[i][j].size(); k++)
					{
						currLayerStart.push(cursor);
						nameSize = (*keys3)[i][j][k].size();
						data[cursor++] = nameSize;
						memcpy(&data[cursor], (*keys3)[i][j][k].c_str(), nameSize);
						cursor += nameSize;
						nodeSize.top() = cursor - currLayerStart.top();
					}
					int currentSize = cursor - currLayerStart.top();
					leveldb::EncodeFixed32(&data[currLayerStart.top() + 4], currentSize);
					currLayerStart.pop();
				}
			}
			int currentSize = cursor - currLayerStart.top();
			leveldb::EncodeFixed32(&data[currLayerStart.top() + 4], currentSize);
			currLayerStart.pop();
		}
	}
	int currentSize = cursor - currLayerStart.top();
	leveldb::EncodeFixed32(&data[currLayerStart.top() + 4], currentSize);
	currLayerStart.pop();
	return true;
}

VOID StringArrayTable::ReInitialize()
{
	currLayerStart.empty();
	cursor = 0;
	currLayer = 1;
}

bool StringArrayTable::GetArrayAtKeys(const vector<string>& keys, vector<string>& dataArray)
{
	ReInitialize();
	int nameSize;
	int currentLayerStart;
	uint32_t num;
	uint32_t currNodeSize;
	bool found = false;
	cursor++; //skip layer

	do
	{
		currentLayerStart = cursor;
		currLayerStart.push(currentLayerStart);
		num = leveldb::DecodeFixed32(&data[cursor]);
		cursor += 4;
		currNodeSize = leveldb::DecodeFixed32(&data[cursor]);
		cursor += 4;
		if (currLayer == layer)
		{
			for (int j = 0; j < num; j++)
			{
				nameSize = data[cursor++];
				string s(&data[cursor], nameSize);
				dataArray.push_back(s);
				cursor += nameSize;
			}
			return true;
		}
		else
		{
			found = false;
			for (int i = 0; i < num; i++)
			{	
				uint8_t nameSize = data[cursor++];
				string s(&data[cursor], nameSize);
				cursor += nameSize;
				uint32_t currNodeStart = cursor;
				if (s == keys[currLayer - 1])
				{
					currLayerStart.push(currentLayerStart);
					currLayer++;
					found = true;
					break;
				}
				else
				{
					cursor += 4; //skip num
					currNodeSize = leveldb::DecodeFixed32(&data[cursor]);
					cursor = currNodeStart + currNodeSize;
				}
			}
			if (!found)
			{
				return false;
			}
		}
	} 	while (cursor < length);
	return false;
}

StringArrayTable::~StringArrayTable() 
{
	SAFE_DELETE_ARRAY(data);
}
