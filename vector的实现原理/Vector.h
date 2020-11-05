#pragma once
#include<iostream>
#include<algorithm>
#include<assert.h>
#include<string>
using namespace std;
template<class T>
class Vector
{
public:
	//vector的迭代器是一个原生指针
	typedef T* Iterator;
	typedef const T* ConstIterator;

	//迭代器
	Iterator Begin() {
		return _start;
	}

	Iterator End() {
		return _finish;
	}

	ConstIterator CBegin()const {
		return _start;
	}

	ConstIterator CEnd()const {
		return _finish;
	}

	//vector.size()
	size_t Size()const {
		return _finish - _start;
	}

	//vector.capacity()
	size_t Capacity()const {
		return _endofstorage - _start;
	}

	//构造函数
	Vector()
		:_start(nullptr)
		, _finish(nullptr)
		, _endofstorage(nullptr)
	{}

	Vector(int n, const T& value)
		:_start(nullptr)
		, _finish(nullptr)
		, _endofstorage(nullptr)
	{
		Reserve(n);
		while (n--) {
			PushBack(value);
		}
	}

	//这里如果使用Iterator做迭代器，就会导致初始化的迭代器区间[first,last]只能是Vector的迭代器
	//这里重新声明迭代器，迭代器区间[first,last]可以是任意容器的迭代器区间。
	template<class InputIterator>
	Vector(InputIterator first, InputIterator last) {
		Reserve(last - first);
		while (first != last) {
			PushBack(*first);
			++first;
		}
	}

	//拷贝构造函数
	//Vector(Vector<T>& v) {
	//	_start = new T[v.Capacity];
	//	for (size_t i = 0; i < Size(); ++i) {
	//		_start[i] = v._start[i];
	//	}
	//	_finish = _start + v.Size();
	//	_endofstorage = _start + v.Capacity();
	//}

	Vector(const Vector<T>& v)
		:_start(nullptr)
		, _finish(nullptr)
		, _endofstorage(nullptr)
	{
		Reserve(v.Capacity());
		Iterator it = Begin();
		ConstIterator cit = v.CBegin();
		while (cit != v.CEnd()) {
			*it++ = *cit++;
		}
		_finish = _start + v.Size();
		_endofstorage = _start + v.Capacity();
	}

	//赋值运算符重载

	//Vector<T>& operator=(Vector<T>& v) {
	//	if (this != &v) {
	//		delete[] _start;
	//		_start = new T[sizeof(T) * v.Size()];
	//		memcpy(_start, v._start, sizeof(T) * v.Size());
	//		_finish = _start + v.Size();
	//		_endofstorage = _start + v.Capacity();
	//	}
	//	return *this;
	//}
	Vector<T>& operator=(Vector<T>& v) {
		Swap(v);
		return *this;
	}

	//析构函数
	~Vector() {
		delete[] _start;
		_start = _finish = _endofstorage = nullptr;
	}

	//vector.reserve()
	void Reserve(size_t n) {
		if (n > Capacity()) {
			size_t size = Size();
			T* tmp = new T[n];
			if (_start) {
				for (size_t i = 0; i < size; ++i)
					tmp[i] = _start[i];
			}
			_start = tmp;
			_finish = _start + size;
			_endofstorage = _start + n;
		}
	}

	//vector.resize()
	void Resize(size_t n, const T& value) {
		//1.如果n小于当前的size,则数据个数缩小到n
		if (n <= Size()) {
			_finish = _start + n;
			return;
		}
		//2.空间不够则增容
		if (n > Capacity()) {
			Reserve(n);
		}

		//3.将size扩大到n
		Iterator it = _finish;
		Iterator _finish = _start + n;
		while (it != _finish) {
			*it = value;
			++it;
		}
	}

	//vector.swap()
	void Swap(Vector<T>& v) {
		swap(_start, v._start);
		swap(_finish, v._finish);
		swap(_endofstorage, v._endofstorage);
	}

	//尾插vector.pushback()
	void PushBack(const T& x) {
		//if (_finish == _endofstorage) {
		//	size_t Newcapacity = Capacity() == 0 ? 2 : Capacity() * 2;
		//	Reserve(Newcapacity);
		//}
		//*_finish = x;
		//++_finish;
		Insert(End(), x);
	}

	//尾删vector.popback()
	void PopBack() {
		//assert(Size() > 0);
		//--_finish;
		Iterator it = End();
		Erase(--it);
	}

	//插入vector.insert()
	//返回插入位置的迭代器
	Iterator Insert(Iterator pos, const T& x) {
		assert(pos <= _finish);
		size_t posindex = pos - _start;
		//空间不够先增容
		if (_finish == _endofstorage) {
			size_t size = Size();
			size_t newCapacity = Capacity() == 0 ? 1 : Capacity() * 2;
			Reserve(newCapacity);
			//如果发生了增容，需要重置pos
			pos = _start + posindex;
		}

		Iterator end = _finish - 1;
		while (end >= pos) {
			*(end + 1) = *end;
			--end;
		}
		*pos = x;
		++_finish;
		return pos;
	}

	//删除vector.erase()
	//返回删除数据的下一个数据,方便解决一边遍历一边删除的迭代器失效问题
	Iterator Erase(Iterator pos) {
		Iterator begin = pos;
		while (pos!= _finish) {
			*pos=*(pos+1);
			++pos;
		}
		--_finish;
		return begin;
	}

	//随机访问 重载[]
	T& operator[](size_t pos) {
		assert(pos <= Size());
		return _start[pos];
	}

private:
	Iterator _start;//指向数据块的开始
	Iterator _finish;//指向有效数据的尾
	Iterator _endofstorage;//指向存储容量的尾
};

void PrintVector(const Vector<int>& v) {
	// 使用const迭代器进行遍历打印    
	Vector<int> ::ConstIterator it = v.CBegin();
	while (it != v.CEnd()) {
		cout << *it << " "; ++it;
	}
	cout << endl;
}

void TestVector01() {
	Vector<int> v;
	v.PushBack(1);
	v.PushBack(2);
	v.PushBack(3);
	v.PushBack(4);

	//拷贝构造
	Vector<int> V(v);

	// 使用迭代器进行遍历打印    
	Vector<int>::Iterator it = v.Begin();
	while (it != v.End()) {
		cout << *it << " ";
		++it;
	}
	cout << endl;

	// 使用迭代器进行修改    
	Vector<int>::Iterator It = V.Begin();
	while (It != V.End()) {
		*It *= 2;
		++It;
	}
	PrintVector(V);
	cout << endl;
}


void TestVector02() {
	Vector<int> v2;
	v2.PushBack(1);
	v2.PushBack(2);
	v2.PushBack(3);
	v2.PushBack(4);

	//赋值运算符重载
	Vector<int> v3 = v2;
	PrintVector(v2);
	cout << "v2.Size()=" << v2.Size() << endl;
	cout << "v2.Capacity()=" << v2.Capacity() << endl;
	//尾插
	cout << "尾插" << endl;
	v2.PushBack(5);
	PrintVector(v2);
	cout << "v2.Size()=" << v2.Size() << endl;
	cout << "v2.Capacity()=" << v2.Capacity() << endl;
	//尾删
	cout << "尾删" << endl;
	v2.PopBack();
	PrintVector(v2);
	cout << "v2.Size()=" << v2.Size() << endl;
	cout << "v2.Capacity()=" << v2.Capacity() << endl;

	//修改有效元素个数
	cout << "修改有效元素个数" << endl;
	v2.Resize(6, 2);
	cout << "v2.Size()=" << v2.Size() << endl;
	cout << "v2.Capacity()=" << v2.Capacity() << endl;
	//修改容量
	cout << "修改容量" << endl;
	v2.Reserve(10);
	cout << "v2.Size()=" << v2.Size() << endl;
	cout << "v2.Capacity()=" << v2.Capacity() << endl;

	PrintVector(v3);
	cout << endl;
}

void TestVector03() {
	Vector<int> v4;
	v4.PushBack(5);
	v4.PushBack(6);
	v4.PushBack(7);
	v4.PushBack(8);
	PrintVector(v4);
	Vector<int>::Iterator it = v4.Begin();
	//插入
	v4.Insert(it, 4);
	PrintVector(v4);
	//删除
	Vector<int>::Iterator it2 = v4.End();
	v4.Erase(it2);
	PrintVector(v4);
}


