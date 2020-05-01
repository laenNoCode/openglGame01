#pragma once
#include "util.hpp"
class VertexAndIndexBuffer
{
	

private:
	unsigned int* shape = nullptr;//must contains the shape of the vertex
	int shapeLength;
	bool hasIndex = false;
	bool newData = false;
	bool newIndexes = false;
	float* data = nullptr;
	unsigned int vertexBufferID = 0;
	unsigned int indexID = 0;
	int attribTotalSize = 0;
	int dataLength;
	unsigned int* indexes = nullptr;
	int indexesLength;
	GLenum bufferType;
	void actualizeBuffers();
public:
	static unsigned int boundVertexBuffer;
	static unsigned int boundIndexBuffer;
	void GenerateBuffers();
	int getVertexID();
	int getIndicesID();
	int draw();
	void bind();
	void setData(float* data, int dataLength);
	void setData(float  data, int dataIndex);
	void setData(float* data, int dataLength, int* dataIndexes);
	void setIndexes(unsigned int* data, int dataLength);
	void setIndexes(unsigned int  data, int dataIndex);
	void setIndexes(unsigned int* data, int dataLength, int* dataIndexes);
	float* getData();
	float* getDataAsCopy();
	unsigned int* getIndexes();
	unsigned int* getIndexesAsCopy();
	void reportDataChangedOutside();
	void reportIndexesChangedOutside();
	VertexAndIndexBuffer(int* shape, int shapeLength, float* data, int dataLength,GLenum bufferType= GL_DYNAMIC_DRAW,unsigned int* indexes=nullptr, int indexesLength = 0);
	~VertexAndIndexBuffer();
};

