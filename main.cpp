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
	size_t	currentColumnCapacity;
	size_t	rowSize;
public:
	size_t	size;
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
			rowSize++;
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
			rowSize++;
		}
		size = _var.size;
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
	inline int	pushBack(const T& _var)
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
		headPtr = nullptr;

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

		if (tempIndex1 == 1)
			return	currentPtr->valsPtr[0];
		else if (tempIndex1 <= size)
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
		else
			throw	out_of_range("access error");
	}
};

int main()
{
	MiniIndexedList<int> indexedList1;

	for (int i = 1; i < 10000001; i++)
		indexedList1.pushBack(i);
	for (int i = 0; i < 10000000; i++)
		indexedList1[i];

	return	0;
}
