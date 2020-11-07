#pragma once
#include<iostream>
#include<assert.h>
using namespace std;

template<class T>
//定义链表节点的结构体
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
List 的迭代器迭代器有两种实现方式：      
1. 原生态指针，比如：vector      
2. 将原生态指针进行封装，因迭代器的使用形式与指针完全相同，因此，在自定义的类中必须实现以下方法：
1. 指针可以解引用，迭代器的类中必须重载operator*()
2. 指针可以通过->访问其所指空间成员，迭代器类中必须重载oprator->()
3. 指针可以++向后移动，迭代器类中必须重载operator++()与operator++(int)
至于operator--()/operator--(int)释放需要重载，根据具体的结构来抉择，
双向链表可以向前移动，所以需要重载，如果是forward_list就不需要重载--
4. 迭代器需要进行是否相等的比较，因此还需要重载operator==()与operator!=()    
*/

//定义迭代器，模板参数为T，T的引用，T类型的指针
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

	//重载 *、->操作符
	Ref operator*() {
		return _pNode->_val;
	}

	Ptr operator->() {
		return &(_pNode->val);
	}

	//重载++、--操作符
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

	//重载!=、==操作符
	bool operator!=(const Self1& l) {
		return _pNode != l._pNode;
	}
	bool operator==(const Self1& l) {
		return _pNode == l._pNode;
	}
};

/*    
List 的反向迭代器，反向迭代器与正向迭代器刚好是相反的，
反向迭代器++，迭代器往前移动，反向迭代器--，迭代器往后移动，
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

	//重载*、->
	Ref operator*() {
		return _pNode->_val;
	}
	Ptr operator&(){
		return &(_pNode->_val);
	}

	//重载++、--
	//反向迭代器++，迭代器往前移动，反向迭代器--，迭代器往后移动
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

	//重载!=、==
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

	//List的构造函数
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

	//拷贝构造
	List(const List<T>& l){
		CreatHead();
		//用l构造临时temp,与当前对象交换
		List<T> temp(l.CBegin(), l.CEnd());
		this->Swap(temp);
	}

	//赋值运算符重载
	List<T>& operator=(const List<T>&l) {
		if (this != &l) {
			List<T> temp(l);
			this->Swap(temp);
		}
		return *this;
	}

	//析构函数
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

	//List的访问
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

	//List的修改
	//尾插
	void PushBack(const T& val) {
		PNode pNewNode = new Node(val);
		//先把新节点尾插进去
		pNewNode->_next = _pHead;
		pNewNode->_pre = _pHead->_pre;
		//链接剩余的两个指针
		_pHead->_pre = pNewNode;
		pNewNode->_pre->_next = pNewNode;
	}

	//尾删
	void PopBack() {
		//找到待删除结点
		PNode pDel = _pHead->_pre;
		if (pDel != _pHead) {
			_pHead->_pre = pDel->_pre;
			pDel->_pre->_next = _pHead;
			delete pDel;
		}
	}

	//头插
	void PushFront(const T&val) {
		PNode pNewNode = new Node(val);
		//先把新节点头插进去
		pNewNode->_pre = _pHead;
		pNewNode->_next = _pHead->_next;
		//链接剩余的两个指针
		_pHead->_next = pNewNode;
		_pHead->_next->_pre = pNewNode;
	}

	//头删
	void PopFront() {
		//找到待删除结点
		PNode pDel = _pHead->_next;
		if (pDel != _pHead) {
			_pHead->_next = pDel->_next;
			pDel->_next->_pre = _pHead;
			delete pDel;
		}
	}

	//插入 在pos位置前插入值为val的结点
	Iterator Insert(Iterator pos, const T& val) {
		PNode pNewNode = new Node(val);
		PNode pCur = pos._pNode;
		//先将新节点插入
		pNewNode->_pre = pCur->_pre;
		pNewNode->_next = pCur;
		pNewNode->_pre->_next = pNewNode;
		pCur->_pre = pNewNode;
		return Iterator(pNewNode);
	}
	//删除 删除pos位置的结点，并返回pos下一个位置的结点
	Iterator Erase(Iterator pos) {
		//找到待删除结点
		PNode pDel = pos._pNode;
		PNode pRet = pDel->_next;
		//将该节点从链表中取下来并删除
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
