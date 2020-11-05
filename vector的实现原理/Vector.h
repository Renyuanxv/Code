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
	//vector�ĵ�������һ��ԭ��ָ��
	typedef T* Iterator;
	typedef const T* ConstIterator;

	//������
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

	//���캯��
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

	//�������ʹ��Iterator�����������ͻᵼ�³�ʼ���ĵ���������[first,last]ֻ����Vector�ĵ�����
	//������������������������������[first,last]���������������ĵ��������䡣
	template<class InputIterator>
	Vector(InputIterator first, InputIterator last) {
		Reserve(last - first);
		while (first != last) {
			PushBack(*first);
			++first;
		}
	}

	//�������캯��
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

	//��ֵ���������

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

	//��������
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
		//1.���nС�ڵ�ǰ��size,�����ݸ�����С��n
		if (n <= Size()) {
			_finish = _start + n;
			return;
		}
		//2.�ռ䲻��������
		if (n > Capacity()) {
			Reserve(n);
		}

		//3.��size����n
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

	//β��vector.pushback()
	void PushBack(const T& x) {
		//if (_finish == _endofstorage) {
		//	size_t Newcapacity = Capacity() == 0 ? 2 : Capacity() * 2;
		//	Reserve(Newcapacity);
		//}
		//*_finish = x;
		//++_finish;
		Insert(End(), x);
	}

	//βɾvector.popback()
	void PopBack() {
		//assert(Size() > 0);
		//--_finish;
		Iterator it = End();
		Erase(--it);
	}

	//����vector.insert()
	//���ز���λ�õĵ�����
	Iterator Insert(Iterator pos, const T& x) {
		assert(pos <= _finish);
		size_t posindex = pos - _start;
		//�ռ䲻��������
		if (_finish == _endofstorage) {
			size_t size = Size();
			size_t newCapacity = Capacity() == 0 ? 1 : Capacity() * 2;
			Reserve(newCapacity);
			//������������ݣ���Ҫ����pos
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

	//ɾ��vector.erase()
	//����ɾ�����ݵ���һ������,������һ�߱���һ��ɾ���ĵ�����ʧЧ����
	Iterator Erase(Iterator pos) {
		Iterator begin = pos;
		while (pos!= _finish) {
			*pos=*(pos+1);
			++pos;
		}
		--_finish;
		return begin;
	}

	//������� ����[]
	T& operator[](size_t pos) {
		assert(pos <= Size());
		return _start[pos];
	}

private:
	Iterator _start;//ָ�����ݿ�Ŀ�ʼ
	Iterator _finish;//ָ����Ч���ݵ�β
	Iterator _endofstorage;//ָ��洢������β
};

void PrintVector(const Vector<int>& v) {
	// ʹ��const���������б�����ӡ    
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

	//��������
	Vector<int> V(v);

	// ʹ�õ��������б�����ӡ    
	Vector<int>::Iterator it = v.Begin();
	while (it != v.End()) {
		cout << *it << " ";
		++it;
	}
	cout << endl;

	// ʹ�õ����������޸�    
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

	//��ֵ���������
	Vector<int> v3 = v2;
	PrintVector(v2);
	cout << "v2.Size()=" << v2.Size() << endl;
	cout << "v2.Capacity()=" << v2.Capacity() << endl;
	//β��
	cout << "β��" << endl;
	v2.PushBack(5);
	PrintVector(v2);
	cout << "v2.Size()=" << v2.Size() << endl;
	cout << "v2.Capacity()=" << v2.Capacity() << endl;
	//βɾ
	cout << "βɾ" << endl;
	v2.PopBack();
	PrintVector(v2);
	cout << "v2.Size()=" << v2.Size() << endl;
	cout << "v2.Capacity()=" << v2.Capacity() << endl;

	//�޸���ЧԪ�ظ���
	cout << "�޸���ЧԪ�ظ���" << endl;
	v2.Resize(6, 2);
	cout << "v2.Size()=" << v2.Size() << endl;
	cout << "v2.Capacity()=" << v2.Capacity() << endl;
	//�޸�����
	cout << "�޸�����" << endl;
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
	//����
	v4.Insert(it, 4);
	PrintVector(v4);
	//ɾ��
	Vector<int>::Iterator it2 = v4.End();
	v4.Erase(it2);
	PrintVector(v4);
}


