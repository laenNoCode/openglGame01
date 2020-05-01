#include "VertexAndIndexBuffer.h"
unsigned int VertexAndIndexBuffer::boundVertexBuffer = 0;
unsigned int VertexAndIndexBuffer::boundIndexBuffer = 0;

void VertexAndIndexBuffer::actualizeBuffers()
{
	if (vertexBufferID == 0 && newData)
		GenerateBuffers();
	if (vertexBufferID != 0 && newData) {
#ifdef DEBUG 
		std::cout << "setting data to bufferV n°" << this->vertexBufferID << std::endl;
#endif
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, this->dataLength * sizeof(float), this->data, GL_DYNAMIC_DRAW));
	}
	if (indexID != 0 && newIndexes) {
#ifdef DEBUG 
		std::cout << "setting data to bufferI n°" << this->indexID << std::endl;
#endif
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->indexID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, this->indexesLength * sizeof(unsigned int), this->indexes, GL_DYNAMIC_DRAW));
	}
	newData = false;
	newIndexes = false;
}

void VertexAndIndexBuffer::GenerateBuffers()
{
	if (vertexBufferID == 0) {
		GLCall(glGenBuffers(1, &(this->vertexBufferID)));
#ifdef DEBUG
		std::cout << "generated bufferV n°" << (this->vertexBufferID) << std::endl;
#endif
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferID));
		GLCall(glBufferData(GL_ARRAY_BUFFER, this -> dataLength * sizeof(float), this -> data, this->bufferType));
		boundVertexBuffer = this->vertexBufferID;
		newData = false;
	}
	if (indexID == 0 && hasIndex) {
		GLCall(glGenBuffers(1, &(this->indexID)));
#ifdef DEBUG
		std::cout << "generated bufferI n°" << (this->indexID) << std::endl;
#endif
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexID));
		GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indexesLength * sizeof(unsigned int), this->indexes, this->bufferType));
		boundIndexBuffer = this->indexID;
		newIndexes = false;
	}
	newData = false;
	newIndexes = false;
}

int VertexAndIndexBuffer::getVertexID()
{
	return this -> dataLength;
}

int VertexAndIndexBuffer::getIndicesID()
{
	return indexesLength;
}

int VertexAndIndexBuffer::draw()
{
	this->bind();
	this->actualizeBuffers();
	if (vertexBufferID == 0)
		return -1;
	if (indexID == 0) {
		GLCall(glDrawArrays(GL_TRIANGLES, 0, dataLength / attribTotalSize));
		return 0;
	}
	else {
		GLCall(glDrawElements(GL_TRIANGLES, indexesLength, GL_UNSIGNED_INT, nullptr));
		return 1;
	}
}

void VertexAndIndexBuffer::bind()
{
	if (vertexBufferID != 0) {
		if (vertexBufferID != boundVertexBuffer) {
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferID));
			boundVertexBuffer = this->vertexBufferID;
#ifdef DEBUG
			std::cout << "binding Vertex Buffer :" << this->vertexBufferID;
#endif
		}
	}
	if (indexID != 0) {
		if (indexID != boundIndexBuffer) {
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indexID));
			boundIndexBuffer = this->indexID;
#ifdef DEBUG
			std::cout << "binding Index Buffer :" << this->indexID;
#endif
		}
		
	}
}

void VertexAndIndexBuffer::setData(float* data, int dataLength)
{
	if (this->dataLength == dataLength) {
		bool test = true;
		FORI(i, dataLength,
			if (data[i] != this->data[i]) {
				test = false;
				this->data[i] = data[i];
				this->newData = true;
			}
			)
			
#ifdef DEBUG
			if (test) {
				std::cout << "nothing changed" << std::endl;
			}
#endif // DEBUG

			return;
	}
	else {
		delete[] (this -> data);
		this->data = new float[dataLength];
		this->dataLength = dataLength;
		FORI(i, dataLength, this->data[i] = data[i];)
		this->newData = true;
	}
}


void VertexAndIndexBuffer::setData(float data, int dataIndex)
{
#ifdef CHECKARRAYOUTOFBOUND
	if (dataIndex < 0 || dataIndex >= dataLength) {
		std::cerr << "you tried to put data in a forbidden slot ! " << dataIndex << "length is only " << dataLength << std::endl;
		return;
	}
#endif
	if (this->data[dataIndex] != data)
	{
		newData = true;
		this->data[dataIndex] = data;
	}
}

void VertexAndIndexBuffer::setData(float* data, int dataLength, int* dataIndexes)
{
#ifdef CHECKARRAYOUTOFBOUND
	FORI(i, dataLength,
		if (dataIndexes[i] < 0 || dataIndexes[i] >= dataLength)
		{
			std::cerr << "you tried to put data in a forbidden slot ! " << dataIndexes[i] << "length is only " << dataLength << std::endl;
			return;
		}
			)
#endif
	FORI(i, dataLength, 
		if (this->data[dataIndexes[i]] != data[i]) {
			this->data[dataIndexes[i]] = data[i];
			newData = true;
		}
		)
		
}

void VertexAndIndexBuffer::setIndexes(unsigned int * data, int dataLength)
{
	if (this->indexesLength == dataLength) {
		bool test = true;
		FORI(i, dataLength,
			if (data[i] != this->indexes[i]) {
				test = false;
				this->indexes[i] = data[i];
				this->newIndexes = true;
			}
		)
			
#ifdef DEBUG
			if (test) {
				std::cout << "nothing changed" << std::endl;
			}
#endif // DEBUG
		return;
	}
	else {
		delete[](this->indexes);
		this->indexes = new unsigned int[dataLength];
		this->indexesLength = dataLength;
		FORI(i, dataLength, this->indexes[i] = data[i];)
			this->newIndexes = true;
	}
}

void VertexAndIndexBuffer::setIndexes(unsigned int data, int dataIndex)
{
#ifdef CHECKARRAYOUTOFBOUND
	if (dataIndex < 0 || dataIndex >= indexesLength) {
		std::cerr << "you tried to put data in a forbidden slot ! " << dataIndex << "length is only " << indexesLength << std::endl;
		return;
	}
#endif
	if (this->indexes[dataIndex] != data)
	{
		newIndexes = true;
		this->indexes[dataIndex] = data;
	}
}

void VertexAndIndexBuffer::setIndexes(unsigned int * data, int dataLength, int * dataIndexes)
{
#ifdef CHECKARRAYOUTOFBOUND
	FORI(i, dataLength,
		if (dataIndexes[i] < 0 || dataIndexes[i] >= indexesLength)
		{
			std::cerr << "you tried to put data in a forbidden slot ! " << dataIndexes[i] << "length is only " << indexesLength << std::endl;
			return;
		}
	)
#endif
		FORI(i, dataLength,
			if (this->indexes[dataIndexes[i]] != data[i]) {
				this->indexes[dataIndexes[i]] =  data[i];
				newIndexes = true;
			}
	)
}

float * VertexAndIndexBuffer::getData()
{
	return data;
}

float * VertexAndIndexBuffer::getDataAsCopy()
{
	float* toRet = new float[this->dataLength];
	FORI(i, dataLength, toRet[i] = data[i];)
	return data;
}

unsigned int * VertexAndIndexBuffer::getIndexes()
{
	return indexes;
}

unsigned int * VertexAndIndexBuffer::getIndexesAsCopy()
{
	unsigned int* toRet = new unsigned int[indexesLength];
	FORI(i, indexesLength, toRet[i] = indexes[i];)
	return toRet;
}




VertexAndIndexBuffer::VertexAndIndexBuffer(int* shape, int shapeLength, float* data, int dataLength, GLenum bufferType,unsigned int* indexes, int indexesLength)
{
	int sum = 0;
	FORI(i, shapeLength, sum += shape[i];)
	this->attribTotalSize = sum;
	this->shape = new unsigned int[shapeLength];
	this->data = new float[dataLength];
	this->shapeLength = shapeLength;
	this->dataLength = dataLength;
	this->indexesLength = indexesLength;
	this->bufferType = bufferType;
	FORI(i, shapeLength, this->shape[i] = shape[i];)
		FORI(i, dataLength,
		this->data[i] = data[i];
	)
	if (indexes != nullptr) {
		this ->indexes = new unsigned int[indexesLength];
		this->hasIndex = true;
		FORI(i, indexesLength, this->indexes[i] = indexes[i];)
	}
	this->GenerateBuffers();

	int accumulatedSum = 0;
	
		FORI(i, shapeLength,
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, shape[i], GL_FLOAT, GL_FALSE, sizeof(float) * sum,(void*) (sizeof(float) * accumulatedSum)));
		accumulatedSum += shape[i];
		)
}

VertexAndIndexBuffer::~VertexAndIndexBuffer()
{
#ifdef DEBUG
	std::cout << "deleting buffers" << std::endl;
#endif
	if (this->vertexBufferID != 0) {
#ifdef DEBUG
		std::cout << "deleting vertex buffer " << this ->vertexBufferID << std::endl;
#endif
		glDeleteBuffers(1, &(this->vertexBufferID));
	}
	if (this->indexID != 0) {
#ifdef DEBUG
		std::cout << "deleting array buffer " << this->indexID << std::endl;
#endif
		glDeleteBuffers(1, &(this->indexID));
	}
	DELETA(shape);
	DELETA(data);
	DELETA(indexes);
}
