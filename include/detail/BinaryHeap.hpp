#pragma once
#include <functional>
//#include "Allocator.h"
#define ASSERT(X) (X)
#define HEAP_PARENT(_Node) ((_Node - 1) >> 1)
#define HEAP_RCHILD(_Node) ((_Node << 1) + 2)
#define HEAP_LCHILD(_Node) ((_Node << 1) + 1)
template<class _DataTy, class _Compare = std::less<_DataTy>, size_t _InitCapacity = 100>
class BinaryHeap
{
	_DataTy* __DataArray;
	_Compare __Compare;
	size_t __SIZE;
	size_t __CAPACITY;
	void __realloc(const size_t _NEWSIZE)
	{
		__DataArray = static_cast<_DataTy*>(std::realloc(__DataArray, _NEWSIZE * sizeof(_DataTy)));
		__CAPACITY = _NEWSIZE;
	}
public:
	BinaryHeap() :
		__DataArray(nullptr), __SIZE(0), __CAPACITY(_InitCapacity)
	{

		std::allocator<_DataTy> _Alloc;
		__DataArray = _Alloc.allocate(__CAPACITY);
	}
	virtual ~BinaryHeap()
	{
		if (__DataArray != nullptr)
		{
			std::free(__DataArray); __DataArray = nullptr;
		}
	}
	inline void swap(BinaryHeap& _Right)
	{
		if (this != _STD addressof(_Right)) {
			std::swap(this->__CAPACITY, _Right.__CAPACITY);
			std::swap(this->__SIZE, _Right.__SIZE);
			std::swap(this->__Compare, _Right.__Compare);
			std::swap(this->__DataArray, _Right.__DataArray);
		}
	}
	inline bool empty() { return __SIZE == 0; }
	inline size_t size() {
		return __SIZE;
	}

	_DataTy& front()
	{
		ASSERT(__SIZE > 0);
		return __DataArray[0];
	}
	_DataTy const& front()const
	{
		ASSERT(__SIZE > 0);
		return __DataArray[0];
	}
	void clear(void)
	{
		__SIZE = 0;
		memset(__DataArray, 0, sizeof(_DataTy) * __CAPACITY);
	}
	void push(_DataTy&& _Data)
	{
		if (__CAPACITY == __SIZE)
		{
			__realloc(__SIZE + (__SIZE >> 1));
		}
		size_t _Node = __SIZE++;
		size_t _Parent = HEAP_PARENT(_Node);
		while ((_Node != 0) && (__Compare(std::forward<_DataTy>(_Data), __DataArray[_Parent])))
		{
			__DataArray[_Node] = __DataArray[_Parent];
			_Node = _Parent;
			_Parent = HEAP_PARENT(_Node);
		}
		__DataArray[_Node] = std::forward<_DataTy>(_Data);
	}
	void push(_DataTy const& _Data)
	{
		if (__CAPACITY == __SIZE)
		{
			__realloc(__SIZE + (__SIZE >> 1));
		}
		size_t _Node = __SIZE++;
		size_t _Parent = HEAP_PARENT(_Node);
		while ((_Node != 0) && (__Compare((_Data), __DataArray[_Parent])))
		{
			__DataArray[_Node] = __DataArray[_Parent];
			_Node = _Parent;
			_Parent = HEAP_PARENT(_Node);
		}
		__DataArray[_Node] = (_Data);
	}


	void pop()
	{
		ASSERT(__SIZE > 0);
		--__SIZE;
		size_t _Parent = 0;
		while (true)
		{
			size_t _lChild = HEAP_LCHILD(_Parent);
			size_t _rChild = _lChild + 1;
			if (_rChild < __SIZE)
			{
				//�������ӽڵ���ѡһ����С/��Ľڵ㣬������С/��ڵ������_lChild
				if (__Compare(__DataArray[_rChild], __DataArray[_lChild]))
				{
					_lChild = _rChild;
				}
				//���_lChild����β�ڵ㣬��������
				else if (_lChild < __SIZE) {}
				else break;
				//�����ǰ_lChildֵ��β�ڵ��С/�󣬽�������
				if (__Compare(__DataArray[__SIZE], __DataArray[_lChild]))
					break;
				//����С/��Ľڵ���Ϊ���ڵ�
				__DataArray[_Parent] = std::move(__DataArray[_lChild]);
				//���Ÿ�С/��Ľڵ㷽���������
				_Parent = _lChild;
			}
			else if (_lChild < __SIZE)
			{
				//�����ǰ_lChildֵ��β�ڵ��С/�󣬽�������
				if (__Compare(__DataArray[__SIZE], __DataArray[_lChild]))
					break;
				//����С/��Ľڵ���Ϊ���ڵ�
				__DataArray[_Parent] = std::move(__DataArray[_lChild]);
				//���Ÿ�С/��Ľڵ㷽���������
				_Parent = _lChild;
			}
			else
			{
				break;
			}
		}
		//������ڵ���β�ڵ㲹��
		__DataArray[_Parent] = std::move(__DataArray[__SIZE]);


	}
private:

};
