#include "stdafx.h"

#include "StringArrayTable.h"
#include "util/coding.h"

StringArrayTable::StringArrayTable(int bufSize):
	layer(0), bufferSize(bufSize), data(nullptr), length(0), currLayer(0), cursor(0)
{
}

VOID StringArrayTable::InitWithData(int len, const char* p)
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

	data = new char[length + bufferSize];
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
	while (!currLayerStart.empty())
	{
		currLayerStart.pop();
	}
	cursor = 0;
	currLayer = 1;
}

bool StringArrayTable::Append(const StringArrayTable& sat)
{
	int addingLen = sat.GetLength();
	if (addingLen > bufferSize)
	{
		return false;
	}
	if (layer != sat.GetLayer())
	{
		return false;
	}

	int startPosAdding = 1 + 4 + 4; //skip layer, num, size
	addingLen -= startPosAdding;

	memcpy(&data[length], &sat.GetData()[startPosAdding], addingLen);
	int currNum = leveldb::DecodeFixed32(&data[1]) + leveldb::DecodeFixed32(&sat.GetData()[1]);
	int currSize = leveldb::DecodeFixed32(&data[5]) + leveldb::DecodeFixed32(&sat.GetData()[5]) - 8; //skip num pos and size pos
	leveldb::EncodeFixed32(&data[1], currNum);
	leveldb::EncodeFixed32(&data[5], currSize);
	AddLength(addingLen);
	return true;
}

bool StringArrayTable::WriteArrayAtCurrentNode(const vector<string>& dataToWrite)
{
	if (CurrentNodeFound())
	{
		int currNodeSize = leveldb::DecodeFixed32(&data[currLayerStart.top() + 4]);
		int writeSize = dataToWrite.size() + 8; //add num pos and node size pos
		for (int i = 0; i < dataToWrite.size(); i++)
		{
			writeSize += dataToWrite[i].size();
		}
		int diff = writeSize - currNodeSize;
		if (diff > bufferSize)
		{
			return false;
		}
		int nextNodeNewPos = 0;
		int remainningLength = 0;
		int nextNodeStart = currLayerStart.top() + currNodeSize;
		
		if (nextNodeStart < length && diff != 0)
		{
			nextNodeNewPos = nextNodeStart + diff;
			remainningLength = length - nextNodeStart;
			memmove(&data[nextNodeNewPos], &data[nextNodeStart], remainningLength);
		}
		AddLength(diff);

		cursor = currLayerStart.top();
		leveldb::EncodeFixed32(&data[cursor], dataToWrite.size());
		cursor += 4;
		leveldb::EncodeFixed32(&data[cursor], writeSize);
		cursor += 4;
		int nameSize;
		for (int i = 0; i < dataToWrite.size(); i++)
		{
			nameSize = dataToWrite[i].size();
			data[cursor++] = nameSize;
			memcpy(&data[cursor], dataToWrite[i].c_str(), nameSize);
			cursor += nameSize;
		}

		if (diff != 0)
		{
			while (true)
			{
				int currNum = leveldb::DecodeFixed32(&data[currLayerStart.top()]);
				int numDiff = 0;
				if (currNum == 0)
				{
					if (currLayerStart.size() > 1)
					{
						currNodeSize = leveldb::DecodeFixed32(&data[currLayerStart.top() + 4]);
						nextNodeStart = currLayerStart.top() + currNodeSize;
						int extraDiff = -currNodeSize;
						if (nextNodeStart < length)
						{
							nextNodeNewPos = nextNodeStart + extraDiff;
							remainningLength = length - nextNodeStart;
							memmove(&data[nextNodeNewPos], &data[nextNodeStart], remainningLength);
						}
						AddLength(extraDiff);
						diff += extraDiff;
						numDiff = -1;
					}
					else
					{
						leveldb::EncodeFixed32(&data[currLayerStart.top()], 0);
						leveldb::EncodeFixed32(&data[currLayerStart.top() + 4], 8);
					}
				}			

				currLayerStart.pop();
				if (!currLayerStart.empty())
				{
					if (numDiff != 0)
					{
						currNum = leveldb::DecodeFixed32(&data[currLayerStart.top()]);
						leveldb::EncodeFixed32(&data[currLayerStart.top()], currNum + numDiff);
					}
					currNodeSize = leveldb::DecodeFixed32(&data[currLayerStart.top() + 4]);
					leveldb::EncodeFixed32(&data[currLayerStart.top() + 4], currNodeSize + diff);
				}
				else
				{
					break;
				}
			}
		}
		ReInitialize();
		return true;
	}
	return false;
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
	currLayerStart.push(cursor);

	do
	{
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
					currLayerStart.push(cursor);
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
				ReInitialize();
				return false;
			}
		}
	} 	while (cursor < length);
	return false;
}

void StringArrayTable::InitEmptyStruct(unsigned char nlayer)
{
	layer = nlayer;
	length = 1 + 4 + 4;
	data = new char[length + bufferSize];
	data[0] = layer;
	leveldb::EncodeFixed32(&data[1], 0);
	leveldb::EncodeFixed32(&data[5], length - 1);
}

StringArrayTable::~StringArrayTable() 
{
	SAFE_DELETE_ARRAY(data);
}
