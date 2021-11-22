#include	<iostream>


using namespace std;

template<typename T>
struct indexBox
{
	size_t	index;
	T* valsPtr;
	indexBox* next;
};

template<typename T>
class MiniIndexedList
{
private:
	indexBox<T>* headPtr, * currentPtr;
	size_t	size;
	size_t	currentColumnCapacity;
	size_t	rowSize;
public:
	MiniIndexedList()
	{
		headPtr = nullptr;
		currentPtr = nullptr;
		size = 0;
		currentColumnCapacity = 1;
		rowSize = 0;
	};
	MiniIndexedList(MiniIndexedList& _var)
	{
		indexBox<T>* tempIndexBox = new indexBox<T>();
		
		currentPtr = headPtr = nullptr;
		_var.currentPtr = _var.headPtr;
		size = 0;
		currentColumnCapacity = 1;
		rowSize = 0;

		if (_var.headPtr != nullptr)
		{
			currentPtr = headPtr = new indexBox<T>();
			currentPtr->valsPtr = new T[currentColumnCapacity];
			*currentPtr->valsPtr = *_var.currentPtr->valsPtr;
			currentPtr->index = _var.currentPtr->index;
			_var.currentPtr = _var.currentPtr->next;
			currentColumnCapacity <<= 1;
		}
		while (_var.currentPtr != nullptr)
		{
			currentPtr->next = new indexBox<T>();
			currentPtr = currentPtr->next;
			currentPtr->valsPtr = new T[currentColumnCapacity];
			currentPtr->index = _var.currentPtr->index;
			copy(_var.currentPtr->valsPtr, _var.currentPtr->valsPtr + currentColumnCapacity, currentPtr->valsPtr);
			_var.currentPtr = _var.currentPtr->next;
			currentColumnCapacity <<= 1;
		}
	};
	~MiniIndexedList() 
	{
		indexBox<T>* tempCurrentPtr = nullptr;
		currentPtr = headPtr;

		while (currentPtr != nullptr)
		{
			tempCurrentPtr = currentPtr;
			currentPtr = currentPtr->next;
			delete[]	tempCurrentPtr->valsPtr;
			delete	tempCurrentPtr;
		}
	};
	inline size_t	getSize()
	{
		return	size;
	};
	inline int	pushBack(const T&& _var)
	{
		if (size >= currentColumnCapacity - 1)
		{
			indexBox<T>* newBoxPtr = new indexBox<T>();

			if (headPtr == nullptr)
			{
				currentPtr = headPtr = newBoxPtr;
				headPtr->valsPtr = new T[1];
				headPtr->next = nullptr;
			}
			else
			{
				newBoxPtr->next = nullptr;
				newBoxPtr->index = size;
				newBoxPtr->valsPtr = new T[currentColumnCapacity];
				currentPtr->next = newBoxPtr;
				currentPtr = newBoxPtr;
			}
			currentColumnCapacity <<= 1;
			rowSize++;
		}
		currentPtr->valsPtr[++size - (currentColumnCapacity >> 1)] = _var;

		return	0;
	};
	inline int	clear()
	{
		indexBox<T>* tempCurrentPtr;
		currentPtr = headPtr;

		while (currentPtr != nullptr)
		{
			tempCurrentPtr = currentPtr;
			currentPtr = currentPtr->next;
			delete[]	tempCurrentPtr->valsPtr;
			delete	tempCurrentPtr;
			rowSize--;
		}

		if (rowSize != 0)
			return	1;
		else
		{
			size = 0;
			currentColumnCapacity = 1;
			return	0;
		}
	};
	inline T& operator[](const size_t index)
	{
		size_t	tempIndex1 = index, tempIndex2 = 1;
		unsigned int	rowSize = 0U;

		tempIndex1++;

		if (tempIndex1 > currentColumnCapacity * 2 - 1)
			throw	out_of_range("Access outside the allocated area.");
		else if (tempIndex1 > size)
			throw	out_of_range("Access is greater than size.");
		else if (tempIndex1 == 1)
			return	headPtr->valsPtr[0];
		else
		{
			while (tempIndex1 != 1)
			{
				tempIndex1 >>= 1;
				tempIndex2 <<= 1;
				rowSize++;
			}
			currentPtr = headPtr;
			for (size_t i = 0; i < rowSize; i++)
				currentPtr = currentPtr->next;
			return	currentPtr->valsPtr[index - tempIndex2 + 1];
		}
	}
};

int main()
{
	MiniIndexedList<unsigned int> indexedList1;

	indexedList1.pushBack(1U);
	indexedList1.pushBack(2U);
	indexedList1.pushBack(3U);
	indexedList1.pushBack(4U);
	indexedList1.pushBack(5U);
	indexedList1.pushBack(6U);
	indexedList1.pushBack(7U);
	indexedList1.pushBack(8U);
	indexedList1.pushBack(9U);
	indexedList1.pushBack(10U);

	MiniIndexedList<unsigned int>	indexedList2(indexedList1);

	return	0;
}