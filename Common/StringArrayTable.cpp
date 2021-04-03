#include "stdafx.h"

#include "StringArrayTable.h"
#include "coding.h"

StringArrayTable::StringArrayTable(int l, int bufSize):
	layer(l), bufferSize(bufSize), data(nullptr), length(0), currLayer(0), cursor(0)
{
}

VOID StringArrayTable::InitWithData(int len, char* p)
{
	length = len;
	data = new char[length + bufferSize];
	memcpy(data, p, length);
}

bool StringArrayTable::GetArrayAtKeys(const vector<string>& keys, vector<string>& dataArray)
{
	currLayerStart.empty();
	cursor = 0;
	currLayer = 0;
	do
	{
		uint32_t num = leveldb::DecodeFixed32(&data[cursor]);
		cursor += 4;
		for (int i = 0; i < num; i++)
		{
			uint32_t currNodeSize = leveldb::DecodeFixed32(&data[cursor]);
			cursor += 4;
			uint8_t nameSize = data[cursor++];
			string s(&data[cursor], nameSize);
			cursor += nameSize;
			if (s == keys[currLayer])
			{
				if (currLayer < layer)
				{
					currLayer++;
					break;
				}
				else
				{

				}
			}
		}
	} 	while (true);

}

StringArrayTable::~StringArrayTable() 
{
	SAFE_DELETE(data);
}
