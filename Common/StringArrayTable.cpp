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
	length += 4; //add layer
	length += 4; //add num
	length += 4; //node size in layer 1;
	length += keys1->size(); //add name size
	if (keys2 != nullptr)
	{
		length += 4 * keys2->size(); //add num
		length += keys2->size(); //add name size
		layer++;
		if (keys3 != nullptr)
		{
			length += 4; //node size in layer 2;
			length += 4 * keys3->size(); //add num
			length += keys3->size(); //add name size
			for (int i = 0; i < keys3->size(); i++)
			{
				length += (*keys3)[i].size();
			}
			layer++;
		}
		for (int i = 0; i < keys2->size(); i++)
		{
			length += (*keys2)[i].size();
		}
	}
	for (int i = 0; i < keys1->size(); i++)
	{
		length += (*keys1)[i].size();
	}
	length += bufferSize;
	data = new char[length];

}

bool StringArrayTable::InitWithArrays(const vector<string>* const keys1, const vector<vector<string>>* const keys2, const vector<vector<vector<string>>>* const keys3)
{
	InitLayerAndBuffer(keys1, keys2, keys3);
	stack<int> nodeSize;
	
	leveldb::EncodeFixed32(&data[cursor], layer);
	cursor += 4;
	leveldb::EncodeFixed32(&data[cursor], (*keys1).size());
	cursor += 4;
	currLayerStart.push(cursor);
	nodeSize.push(0);
	//skip for node size pos
	cursor += 4;
	for (int i = 0; i < keys1->size(); i++)
	{
		int nameSize = (*keys1)[i].size();
		leveldb::EncodeFixed32(&data[cursor++], nameSize);
		memcpy(&data[cursor], (*keys1)[i].c_str(), nameSize);
		cursor += nameSize;
		if (keys2 != nullptr)
		{
			currLayerStart.push(cursor);
			nodeSize.push(0);
			//skip for node size pos
			cursor += 4;
			nodeSize.top() = cursor - currLayerStart.top();
			for (int j = 0; j < (*keys2)[i].size(); j++)
			{
				leveldb::EncodeFixed32(&data[cursor], (*keys2)[i].size());
				cursor += 4;
				nameSize = (*keys1)[i].size();
				leveldb::EncodeFixed32(&data[cursor++], nameSize);
				memcpy(&data[cursor], (*keys1)[i].c_str(), nameSize);
				cursor += nameSize;
			
				if (keys3 != nullptr)
				{
					currLayerStart.push(cursor);
					nodeSize.push(0);
					//skip for node size pos
					cursor += 4;
					nodeSize.top() = cursor - currLayerStart.top();

					leveldb::EncodeFixed32(&data[cursor], (*keys3)[i][j].size());
					nodeSize.push(0);
					cursor += 4;
					for (int k = 0; k < (*keys3)[i][j].size(); k++)
					{
						currLayerStart.push(cursor);
						nameSize = (*keys1)[i].size();
						leveldb::EncodeFixed32(&data[cursor++], nameSize);
						memcpy(&data[cursor], (*keys1)[i].c_str(), nameSize);
						cursor += nameSize;
						nodeSize.top() = cursor - currLayerStart.top();
					}
					int currentSize = nodeSize.top();
					nodeSize.pop();
					nodeSize.top() += currentSize;
					leveldb::EncodeFixed32(&data[currLayerStart.top()], nodeSize.top());
					currLayerStart.pop();
				}
			}
			int currentSize = nodeSize.top();
			nodeSize.pop();
			nodeSize.top() += currentSize;
			leveldb::EncodeFixed32(&data[currLayerStart.top()], nodeSize.top());
			currLayerStart.pop();
		}
	}
	nodeSize.top() = cursor - currLayerStart.top();
	leveldb::EncodeFixed32(&data[currLayerStart.top()], nodeSize.top());
	currLayerStart.pop();
	nodeSize.pop();
	return true;
}

VOID StringArrayTable::ReInitialize()
{
	currLayerStart.empty();
	cursor = 0;
	currLayer = 0;
}

bool StringArrayTable::GetArrayAtKeys(const vector<string>& keys, vector<string>& dataArray)
{
	ReInitialize();
	do
	{
		cursor += 4;
		uint32_t num = leveldb::DecodeFixed32(&data[cursor]);
		cursor += 4;
		for (int i = 0; i < num; i++)
		{
			int currentLayerS = cursor;
			uint32_t currNodeSize = leveldb::DecodeFixed32(&data[cursor]);
			cursor += 4;
			uint8_t nameSize = data[cursor++];
			string s(&data[cursor], nameSize);
			cursor += nameSize;
			if (s == keys[currLayer])
			{
				if (currLayer < layer)
				{
					currLayerStart.push(currentLayerS);
					currLayer++;
					break;
				}
				else
				{
					uint32_t arraySize = leveldb::DecodeFixed32(&data[cursor]);
					cursor += 4;
					for (int j = 0; j < arraySize; j++)
					{
						nameSize = data[cursor++];
						string s(&data[cursor], nameSize);
						dataArray.push_back(s);
					}
					return true;
				}
			}
			currLayer--;
		}
	} 	while (cursor < length);
	return false;
}

StringArrayTable::~StringArrayTable() 
{
	SAFE_DELETE_ARRAY(data);
}
