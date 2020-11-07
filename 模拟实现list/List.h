#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

template<class T>
//��������ڵ�Ľṹ��
struct ListNode
{
	ListNode(const T& val=T())
		: _pre(nullptr)
		, _next(nullptr)
		, _val(val)
	{}
	ListNode<T>* _pre;
	ListNode<T>* _next;
	T _val;
};

/*    
List �ĵ�����������������ʵ�ַ�ʽ��      
1. ԭ��ָ̬�룬���磺vector      
2. ��ԭ��ָ̬����з�װ�����������ʹ����ʽ��ָ����ȫ��ͬ����ˣ����Զ�������б���ʵ�����·�����
1. ָ����Խ����ã������������б�������operator*()
2. ָ�����ͨ��->��������ָ�ռ��Ա�����������б�������oprator->()
3. ָ�����++����ƶ������������б�������operator++()��operator++(int)
����operator--()/operator--(int)�ͷ���Ҫ���أ����ݾ���Ľṹ������
˫�����������ǰ�ƶ���������Ҫ���أ������forward_list�Ͳ���Ҫ����--
4. ��������Ҫ�����Ƿ���ȵıȽϣ���˻���Ҫ����operator==()��operator!=()    
*/

//�����������ģ�����ΪT��T�����ã�T���͵�ָ��
template<class T,class Ref,class Ptr>
class ListIterator {
	typedef ListNode<T>* PNode;
	typedef ListIterator<T, Ref, Ptr> Self1;
public:
	PNode _pNode;
	ListIterator(PNode pNode=nullptr)
		: _pNode(pNode)
	{}

	ListIterator(const Self1&l)
		: _pNode(l._pNode)
	{}

	//���� *��->������
	Ref operator*() {
		return _pNode->_val;
	}

	Ptr operator->() {
		return &(_pNode->val);
	}

	//����++��--������
	Self1& operator++() {
		_pNode = _pNode->_next;
		return *this;
	}
	Self1 operator++(int) {
		Self1 temp(*this);
		_pNode = _pNode->_next;
		return temp;
	}

	Self1& operator--() {
		_pNode = _pNode->_pre;
		return *this;
	}
	Self1 operator--(int) {
		Self1 temp(*this);
		_pNode = _pNode->_pre;
		return temp;
	}

	//����!=��==������
	bool operator!=(const Self1& l) {
		return _pNode != l._pNode;
	}
	bool operator==(const Self1& l) {
		return _pNode == l._pNode;
	}
};

/*    
List �ķ�������������������������������պ����෴�ģ�
���������++����������ǰ�ƶ������������--�������������ƶ���
*/

template<class T,class Ref,class Ptr>
class ListReverseIterator {
	typedef ListNode<T>* PNode;
	typedef ListReverseIterator<T, Ref, Ptr> Self;
private:
	PNode _pNode;
public:
	ListReverseIterator(PNode pNode=nullptr)
		: _pNode(pNode)
	{}

	ListReverseIterator(const Self& s)
		: _pNode(s._pNode)
	{}

	//����*��->
	Ref operator*() {
		return _pNode->_val;
	}
	Ptr operator&(){
		return &(_pNode->_val);
	}

	//����++��--
	//���������++����������ǰ�ƶ������������--�������������ƶ�
	Self& operator++() {
		_pNode = _pNode->_pre;
		return *this;
	}
	Self operator++(int) {
		Self temp(*this);
		_pNode = _pNode->_pre;
		return temp;
	}

	Self& operator--() {
		_pNode = _pNode->_next;
		return *this;
	}
	Self operator--(int) {
		Self temp(*this);
		_pNode = _pNode->_next;
		return temp;
	}

	//����!=��==
	bool operator!=(const Self&s) {
		return _pNode != s._pNode;
	}
	bool operator==(const Self& s) {
		return _pNode == s._pNode;
	}
};

template<class T>
class List
{
	typedef ListNode<T> Node;
	typedef Node* PNode;
private:
	PNode _pHead;
	void CreatHead() {
		_pHead = new Node;
		_pHead->_pre = _pHead;
		_pHead->_next = _pHead;
	}
public:
	typedef ListIterator<T, T&, T*> Iterator;
	typedef ListIterator<T, const T&, const T*> Const_Iterator;
	typedef ListReverseIterator<T, T&, T*> ReverseIterator;
	typedef ListReverseIterator<T, const T&, const T*> Const_ReverseIterator;
	
	//List Iterator
	Iterator Begin() {
		return Iterator(_pHead->_next);
	}

	Iterator End() {
		return Iterator(_pHead);
	}

	ReverseIterator RBegin() {
		return ReverseIterator(End());
	}

	ReverseIterator REnd() {
		return ReverseIterator(Begin());
	}

	Const_Iterator CBegin()const {
		return Const_Iterator(_pHead->_next);
	}

	Const_Iterator CEnd()const {
		return Const_Iterator(_pHead);
	}

	Const_ReverseIterator CRBegin()const {
		return Const_ReverseIterator(CEnd());
	}

	Const_ReverseIterator CREnd()const {
		return Const_ReverseIterator(CBegin());
	}

	//List�Ĺ��캯��
	List() {
		CreatHead();
	}

	List(int n, const T&val) {
		CreatHead();
		for (int i = 0; i < n; ++i)
			PushBack(val);
	}

	template<class Iterator>
	List(Iterator first, Iterator last) {
		CreatHead();
		while (first != last) {
			PushBack(*first);
			++first;
		}
	}

	//��������
	List(const List<T>& l){
		CreatHead();
		//��l������ʱtemp,�뵱ǰ���󽻻�
		List<T> temp(l.CBegin(), l.CEnd());
		this->Swap(temp);
	}

	//��ֵ���������
	List<T>& operator=(const List<T>&l) {
		if (this != &l) {
			List<T> temp(l);
			this->Swap(temp);
		}
		return *this;
	}

	//��������
	~List() {
		Clear();
		delete _pHead;
		_pHead = nullptr;
	}

	//List Capacity
	size_t Size()const {
		size_t count = 0;
		PNode pCur = _pHead->_next;
		while (pCur != _pHead) {
			++count;
			pCur = pCur->_next;
		}
		return count;
	}

	bool Empty()const {
		return _pHead->_next == _pHead;
	}

	bool ReSize(size_t newSize, const T&val) {
		size_t oldSize = Size();
		if (oldSize <= newSize) {
			for (size_t i = oldSize; i < newSize; ++i)
				PushBack(val);
		}
		else {
			for (size_t i = newSize; i < oldSize; ++i)
				PopBack();
		}
	}

	//List�ķ���
	T& Front() {
		return _pHead->_next->_val;
	}

	const T& Front()const {
		return _pHead->_next->_val;
	}

	T& Back() {
		return _pHead->_pre->_val;
	}

	const T& Back()const{
		return _pHead->_pre->_val;
	}

	//List���޸�
	//β��
	void PushBack(const T& val) {
		PNode pNewNode = new Node(val);
		//�Ȱ��½ڵ�β���ȥ
		pNewNode->_next = _pHead;
		pNewNode->_pre = _pHead->_pre;
		//����ʣ�������ָ��
		_pHead->_pre = pNewNode;
		pNewNode->_pre->_next = pNewNode;
	}

	//βɾ
	void PopBack() {
		//�ҵ���ɾ�����
		PNode pDel = _pHead->_pre;
		if (pDel != _pHead) {
			_pHead->_pre = pDel->_pre;
			pDel->_pre->_next = _pHead;
			delete pDel;
		}
	}

	//ͷ��
	void PushFront(const T&val) {
		PNode pNewNode = new Node(val);
		//�Ȱ��½ڵ�ͷ���ȥ
		pNewNode->_pre = _pHead;
		pNewNode->_next = _pHead->_next;
		//����ʣ�������ָ��
		_pHead->_next = pNewNode;
		_pHead->_next->_pre = pNewNode;
	}

	//ͷɾ
	void PopFront() {
		//�ҵ���ɾ�����
		PNode pDel = _pHead->_next;
		if (pDel != _pHead) {
			_pHead->_next = pDel->_next;
			pDel->_next->_pre = _pHead;
			delete pDel;
		}
	}

	//���� ��posλ��ǰ����ֵΪval�Ľ��
	Iterator Insert(Iterator pos, const T& val) {
		PNode pNewNode = new Node(val);
		PNode pCur = pos._pNode;
		//�Ƚ��½ڵ����
		pNewNode->_pre = pCur->_pre;
		pNewNode->_next = pCur;
		pNewNode->_pre->_next = pNewNode;
		pCur->_pre = pNewNode;
		return Iterator(pNewNode);
	}
	//ɾ�� ɾ��posλ�õĽ�㣬������pos��һ��λ�õĽ��
	Iterator Erase(Iterator pos) {
		//�ҵ���ɾ�����
		PNode pDel = pos._pNode;
		PNode pRet = pDel->_next;
		//���ýڵ��������ȡ������ɾ��
		pDel->_pre->_next = pDel->_next;
		pDel->_next->_pre = pDel->_pre;
		delete pDel;

		return Iterator(pRet);
	}

	void Clear() {
		PNode pCur = _pHead->_next;
		while (pCur != _pHead) {
			pCur->_next->_pre = _pHead;
			_pHead->_next = pCur->_next;
			delete pCur;
			pCur = _pHead->_next;
		}
	}

	void Swap(List<T>& l){
		swap(_pHead, l._pHead);
	}
};
