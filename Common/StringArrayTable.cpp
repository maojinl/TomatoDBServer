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
	currNodeStart.push(cursor);
	leveldb::EncodeFixed32(&data[cursor], (*keys1).size());
	cursor += 4;
	nodeSize.push(0);
	//skip for node size pos
	cursor += 4;
	int currStart;
	for (int i = 0; i < keys1->size(); i++)
	{
		currStart = cursor;
		nameSize = (*keys1)[i].size();
		data[cursor++] = nameSize;
		memcpy(&data[cursor], (*keys1)[i].c_str(), nameSize);
		cursor += nameSize;
		if (keys2 != nullptr)
		{
			currNodeStart.push(currStart);
			leveldb::EncodeFixed32(&data[cursor], (*keys2)[i].size());
			cursor += 4;

			nodeSize.push(0);
			//skip for node size pos
			cursor += 4;
			
			for (int j = 0; j < (*keys2)[i].size(); j++)
			{
				currStart = cursor;
				nameSize = (*keys2)[i][j].size();
				data[cursor++] = nameSize;
				memcpy(&data[cursor], (*keys2)[i][j].c_str(), nameSize);
				cursor += nameSize;
				if (keys3 != nullptr)
				{
					currNodeStart.push(currStart);
					leveldb::EncodeFixed32(&data[cursor], (*keys3)[i][j].size());
					cursor += 4;

					nodeSize.push(0);
					//skip for node size pos
					cursor += 4;
					nodeSize.top() = cursor - currNodeStart.top();

					for (int k = 0; k < (*keys3)[i][j].size(); k++)
					{
						nameSize = (*keys3)[i][j][k].size();
						data[cursor++] = nameSize;
						memcpy(&data[cursor], (*keys3)[i][j][k].c_str(), nameSize);
						cursor += nameSize;
						nodeSize.top() = cursor - currNodeStart.top();
					}
					int currentSize = cursor - currNodeStart.top();
					leveldb::EncodeFixed32(&data[GetCurrentNodeSizePos(currNodeStart.top())], currentSize);
					currNodeStart.pop();
				}
			}
			int currentSize = cursor - currNodeStart.top();
			leveldb::EncodeFixed32(&data[GetCurrentNodeSizePos(currNodeStart.top())], currentSize);
			currNodeStart.pop();
		}
	}
	int currentSize = cursor - currNodeStart.top();
	leveldb::EncodeFixed32(&data[GetCurrentNodeSizePos(currNodeStart.top())], currentSize);
	currNodeStart.pop();
	return true;
}

VOID StringArrayTable::ReInitialize()
{
	while (!currNodeStart.empty())
	{
		currNodeStart.pop();
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

bool StringArrayTable::DeleteArrayAtCurrentNode()
{
	if (CurrentNodeFound())
	{
		if (currNodeStart.size() == 1 && currNodeStart.top() == 1)
		{
			InitEmptyStruct(layer);
		}
		else
		{
			int currNodeSize;
			if (currLayer <= layer)
			{
				currNodeSize = leveldb::DecodeFixed32(&data[GetCurrentNodeSizePos(currNodeStart.top())]);
			}
			else
			{
				currNodeSize = (uint8_t)data[currNodeStart.top()] + 1;
			}

			MoveTheNodesAfterCurrent(currNodeSize, -currNodeSize);

			currNodeStart.pop();
			int parentNodeNum = leveldb::DecodeFixed32(&data[GetCurrentNodeNumPos(currNodeStart.top())]);
			leveldb::EncodeFixed32(&data[GetCurrentNodeNumPos(currNodeStart.top())], parentNodeNum - 1);
			int parentNodeSize = leveldb::DecodeFixed32(&data[GetCurrentNodeSizePos(currNodeStart.top())]);
			leveldb::EncodeFixed32(&data[GetCurrentNodeSizePos(currNodeStart.top())], parentNodeSize - currNodeSize);

			UpdateParentsSize(currNodeSize, -currNodeSize);
		}
		ReInitialize();
		return true;
	}
	return false;
}

bool StringArrayTable::WriteArrayAtCurrentNode(const vector<string>& dataToWrite)
{
	if (CurrentNodeFound())
	{
		int currNodeSize;
		int writeSize;
		if (currLayer <= layer)
		{
			currNodeSize = leveldb::DecodeFixed32(&data[GetCurrentNodeSizePos(currNodeStart.top())]);
			writeSize = dataToWrite.size() + 8; //add num pos and node size pos
		}
		else
		{
			currNodeSize = (uint8_t)data[GetCurrentNodeSizePos(currNodeStart.top())];
		}

		if (currNodeStart.top() > 1)
		{
			char nameSize = data[currNodeStart.top()];
			writeSize += 1 + nameSize;
		}
		for (int i = 0; i < dataToWrite.size(); i++)
		{
			writeSize += dataToWrite[i].size();
		}
		int diff = writeSize - currNodeSize;
		if (diff > bufferSize)
		{
			return false;
		}

		MoveTheNodesAfterCurrent(currNodeSize, diff);

		leveldb::EncodeFixed32(&data[GetCurrentNodeNumPos(currNodeStart.top())], dataToWrite.size());
		leveldb::EncodeFixed32(&data[GetCurrentNodeSizePos(currNodeStart.top())], writeSize);
		cursor = GetCurrentNodeSizePos(currNodeStart.top()) + 4;
		int nameSize;
		for (int i = 0; i < dataToWrite.size(); i++)
		{
			nameSize = dataToWrite[i].size();
			data[cursor++] = nameSize;
			memcpy(&data[cursor], dataToWrite[i].c_str(), nameSize);
			cursor += nameSize;
		}

		UpdateParentsSize(currNodeSize, diff);

		ReInitialize();
		return true;
	}
	return false;
}

void StringArrayTable::MoveTheNodesAfterCurrent(int currNodeSize, int moveSize)
{
	int nextNodeNewPos = 0;
	int remainningLength = 0;
	int nextNodeStart = currNodeStart.top() + currNodeSize;

	if (nextNodeStart < length && moveSize != 0)
	{
		nextNodeNewPos = nextNodeStart + moveSize;
		remainningLength = length - nextNodeStart;
		memmove(&data[nextNodeNewPos], &data[nextNodeStart], remainningLength);
	}
	AddLength(moveSize);
}

void StringArrayTable::UpdateParentsSize(int currNodeSize, int moveSize)
{
	int nextNodeNewPos = 0;
	int remainningLength = 0;
	int nextNodeStart = 0;
	if (moveSize != 0)
	{
		while (true)
		{
			int currNum = leveldb::DecodeFixed32(&data[GetCurrentNodeNumPos(currNodeStart.top())]);
			int numDiff = 0;
			if (currNum == 0)
			{
				if (currNodeStart.size() > 1)
				{
					currNodeSize = leveldb::DecodeFixed32(&data[GetCurrentNodeSizePos(currNodeStart.top())]);
					nextNodeStart = currNodeStart.top() + currNodeSize;
					int extraDiff = -currNodeSize;
					if (nextNodeStart < length)
					{
						nextNodeNewPos = nextNodeStart + extraDiff;
						remainningLength = length - nextNodeStart;
						memmove(&data[nextNodeNewPos], &data[nextNodeStart], remainningLength);
					}
					AddLength(extraDiff);
					moveSize += extraDiff;
					numDiff = -1;
				}
				else
				{
					leveldb::EncodeFixed32(&data[GetCurrentNodeNumPos(currNodeStart.top())], 0);
					leveldb::EncodeFixed32(&data[GetCurrentNodeSizePos(currNodeStart.top())], 8);
				}
			}

			currNodeStart.pop();
			if (!currNodeStart.empty())
			{
				if (numDiff != 0)
				{
					currNum = leveldb::DecodeFixed32(&data[GetCurrentNodeNumPos(currNodeStart.top())]);
					leveldb::EncodeFixed32(&data[GetCurrentNodeNumPos(currNodeStart.top())], currNum + numDiff);
				}
				currNodeSize = leveldb::DecodeFixed32(&data[GetCurrentNodeSizePos(currNodeStart.top())]);
				leveldb::EncodeFixed32(&data[GetCurrentNodeSizePos(currNodeStart.top())], currNodeSize + moveSize);
			}
			else
			{
				break;
			}
		}
	}
}

bool StringArrayTable::FindNodeAtKeys(const vector<string>& keys)
{
	return GetArrayAtKeys(keys);
}

bool StringArrayTable::GetArrayAtKeys(const vector<string>& keys, vector<string>& dataArray)
{
	return GetArrayAtKeys(keys, &dataArray);
}

bool StringArrayTable::GetArrayAtKeys(const vector<string>& keys, vector<string>* pArray)
{
	ReInitialize();
	int nameSize;
	int currentLayerStart;
	uint32_t num;
	uint32_t currNodeSize;
	bool found = false;
	cursor++; //skip layer
	currNodeStart.push(cursor);
	do
	{
		if (currLayer <= layer)
		{
			num = leveldb::DecodeFixed32(&data[GetCurrentNodeNumPos(currNodeStart.top())]);
			cursor += 4;
			currNodeSize = leveldb::DecodeFixed32(&data[GetCurrentNodeSizePos(currNodeStart.top())]);
			cursor += 4;
		}
		else
		{
			num = 1;
			cursor = currNodeStart.top();
			currNodeSize = (uint8_t)data[currNodeStart.top()];
		}
		if (keys.size() < currLayer)
		{
			if (currLayer < layer)
			{
				if (pArray != nullptr)
				{
					for (int j = 0; j < num; j++)
					{
						int currNodeStart = cursor;
						nameSize = data[cursor++];
						string s(&data[cursor], nameSize);
						(*pArray).push_back(s);
						cursor += nameSize;
						currNodeSize = leveldb::DecodeFixed32(&data[GetCurrentNodeSizePos(currNodeStart)]);
						cursor = currNodeStart + currNodeSize;
					}
				}
				return true;
			}
			else if (currLayer == layer)
			{
				if (pArray != nullptr)
				{
					for (int j = 0; j < num; j++)
					{
						nameSize = data[cursor++];
						string s(&data[cursor], nameSize);
						(*pArray).push_back(s);
						cursor += nameSize;
					}
				}
				return true;
			}
			else if (currLayer > layer)
			{
				if (pArray != nullptr)
				{
					nameSize = currNodeSize;
					cursor++;
					string s(&data[cursor], nameSize);
					(*pArray).push_back(s);
					cursor += nameSize;
				}
				return true;
			}
		}
		else
		{
			found = false;
			for (int i = 0; i < num; i++)
			{
				int currStart = cursor;
				uint8_t nameSize = data[cursor++];
				string s(&data[cursor], nameSize);
				cursor += nameSize;
				if (s == keys[currLayer - 1])
				{
					currNodeStart.push(currStart);
					currLayer++;
					found = true;
					break;
				}
				else
				{
					if (currLayer < layer)
					{
						currNodeSize = leveldb::DecodeFixed32(&data[GetCurrentNodeSizePos(currStart)]);
						cursor = currStart + currNodeSize;
					}
				}
			}
			if (!found)
			{
				ReInitialize();
				return false;
			}
		}
	} while (cursor < length);
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
