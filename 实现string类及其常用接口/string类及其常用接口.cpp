#define _CRT_SECURE_NO_WARNINGS
#include"teststring.h"
#include<iostream>
#include<string>
#include<cstring>
#include<cassert>



//����յ�string����� �����յ��ַ���
String::String()
	:_size(0)
	,_capacity(15)
	,_str(new char[_capacity]){

}

////��C-string������string�����
String::String(const char* s)
	:_size(0)
	,_capacity(15)
	,_str(new char[_capacity]){
	if (s == nullptr) {
		assert(false);
	}
	size_t _size = strlen(s);
	_capacity = _size;
	strcpy(_str, s);
}
//
////string������а���n���ַ�c
//String::String(size_t n, char c)
//	:_size(0)
//	,_capacity(15)
//	,_str(new char[_capacity]) {
//	_size = n;
//	_capacity = _size;
//	memset(_str, c, n);
//}
//
////�������캯��
//String::String(const String& s)
//	:_size(0)
//	, _capacity(15)
//	, _str(new char[_capacity]) {
//	if (this == &s) {
//		return;
//	}
//	_size = s._size;
//	_capacity = s._capacity;
//	strncpy(_str, s._str, s._size);
//}
//
////��s�е�ǰn���ַ������µ�string�����
//String::String(const String& s, size_t n)
//	:_size(0)
//	, _capacity(15)
//	, _str(new char[_capacity]) {
//	_size = n;
//	_capacity = _size;
//	strncpy(_str, s._str, n);
//}
//String::~String() {
//	if (_str) {
//		delete[]_str;
//	}
//	_str = nullptr;
//	_size = 0;
//	_capacity = 0;
//}

//s1=s2;
String& String::operator=(const String& s) {
	if (this != &s) {
		char* pstr = new char[s._capacity];
		strcpy(pstr, s._str);
		delete[] _str;
		_size = s._size;
		_capacity = s._capacity;
		_str = pstr;
	}
	return *this;
}

String& String::operator=(const char* s) {
	if (s == nullptr) {
		assert(false);
	}
	_size = strlen(s);
	_capacity = _size;
	strcpy(_str, s);

	return *this;
}

////�����ַ�������Ч�ַ�����
//size_t String::Size()const {
//	return _size;
//}
//
////�����ַ�������Ч�ַ�����
//size_t String::Length()const {
//	return _size;
//}
//
////�����ַ����ռ��ܴ�С
//size_t String::Capacity()const {
//	return _capacity;
//}
//
////����ַ����Ƿ�Ϊ�մ� �Ƿ���true,���򷵻�false
//bool String::Empty()const {
//	return 0 == _size;
//}
//
////�����Ч�ַ���
//void String::Clean() {
//	_size = 0;
//	_str[_size] = '\0';
//}
//
////����Ч�ַ��ĸ����ĳ�n��������Ŀռ����ַ�c���
//void String::Resize(size_t n, char c) {
//	if (n > _size) {
//		if (n > _capacity)
//			Reserve(n);
//		memset(_str + _size, c, n - _size);
//		_size = n;
//		_str[n] = '\0';
//	}
//}
//
////����Ч�ַ��ĸ����ĳ�n��������Ŀռ���0���
//void String::Resize(size_t n) {
//	if (n > _size) {
//		if (n > _capacity)
//			Reserve(n);
//		memset(_str + _size, '\0', n - _size);
//		_size = n;
//		_str[n] = '\0';
//	}
//}
////Ϊ�ַ���Ԥ���ռ�
//void String::Reserve(size_t newcapacity) {
//	if (newcapacity > _capacity) {
//		char* str = new char[newcapacity];
//		strcpy(str, _str);
//		delete[] _str;
//		_str = str;
//		_capacity = newcapacity;
//	}
//}
//
////����posλ�õ��ַ�����const string��������
//char& String:: operator[](size_t pos)const {
//	assert(pos < _size);
//	return _str[pos];
//}
//
////����posλ�õ��ַ���const string��������
//char& String:: operator[](size_t pos) {
//	assert(pos < _size);
//	return _str[pos];
//}
//
//void String::Push_back(char c) {//abcd _size=4
//	if (_size == _capacity) {
//		Reserve(_capacity * 2);
//	}
//	_str[_size] = 'c';
//	_size++;
//	_str[_size] = '\0';
//}
//
////βɾ
//void String::Pop_back(char c) {
//	if (_size)
//		--_size;
//}
//
//String& String::Append(const char* s) {
//	if (s == nullptr) {
//		assert(false);
//	}
//	int size = _size + strlen(s);
//	Reserve(size);
//	strcat(_str, s);
//	_size = size;
//	return *this;
//}
//
//String& String::Append(size_t n, const char c) {
//	while (n--) {
//		Push_back(c);
//	}
//	return *this;
//}
//
//String& String::Append(const String& s) {
//	int size = _size + s._size;
//	Reserve(size);
//	strcpy(_str, s._str);
//	_size = size;
//	return *this;
//}
//
////����C��ʽ�ַ���
//const char* String::c_str()const {
//	return _str;	
//}
//
//// �����ַ�c/�ַ���s��string�е�һ�γ��ֵ�λ��
//size_t String::Find(const char c, size_t pos)const {
//	if (pos < 0 || pos >= _size) {
//		return -1;
//	}
//	char* ptr = strchr(_str + pos, c);
//	if (ptr) {
//		return ptr - _str;
//	}
//	else {
//		return -1;
//	}
//}
//size_t String::Find(const char* s, size_t pos)const {
//	if (s == nullptr) {
//		assert(false);
//	}
//	if (pos < 0 || pos >= _size) {
//		return -1;
//	}
//	char* ptr = strstr(_str + pos, s);
//	if (ptr) {
//		return ptr - _str;
//	}
//	else {
//		return -1;
//	}
//}
//size_t String::Find(const String& s, size_t pos)const {
//	if (pos < 0 || pos >= _size) {
//		return -1;
//	}
//	char* ptr = strstr(_str + pos, s._str);
//	if (ptr) {
//		return ptr - _str;
//	}
//	else {
//		return -1;
//	}
//}
//
//size_t String::Rfind(const char c, size_t pos)const {
//	char* ptr = nullptr;
//	strncpy(ptr, _str, pos);
//	char* m = nullptr;
//	if (ptr) {
//		m = strchr(ptr, c);
//	}
//	if (m) {
//			return m - ptr;
//	}
//	else {
//		return -1;
//	}
//}
//size_t String::Rfind(const char* s, size_t pos)const {
//	if (s == nullptr) {
//		assert(false);
//	}
//	char* ptr = nullptr;
//	strncpy(ptr, _str, pos);
//	char* m = nullptr;
//	if (ptr) {
//		m = strstr(ptr, s);
//	}
//	if (m) {
//		return m - ptr;
//	}
//	else{
//		return -1;
//	}
//}
//size_t String::Rfind(const String& s, size_t pos)const {
//	char* ptr = new char[pos + 1];
//	ptr[pos] = 0;
//    strncpy(ptr, _str, pos);
//	char* m = nullptr;
//	if (ptr) {
//		m = strstr(ptr, _str);
//	}
//	if (m) {
//		return m - ptr;
//		delete[] ptr;
//	}
//	else {
//		return -1;
//		delete[] ptr;
//	}
//}
//
//// ��ȡstring��posλ�ÿ�ʼ��n���ַ�
//String String::Substr(size_t pos, size_t n) {
//	String str;
//	if (pos > _size)
//		return str;
//	if (pos + n > _size)
//		n = _size - pos;//���ܳ���_str;
//	str.Reserve(n);
//	str._size = n;
//	strncpy(str._str,_str+pos,n);
//	return str;
//}
//
//String& String::operator+=(const char c) {
//	Push_back(c);
//	return *this;
//}
//
//String& String::operator+=(const String& s) {
//	int size = _size + s._size;
//	Reserve(size);
//	strncpy(_str + _size, s._str, s._size);
//	_size = size;
//	return *this;
//
//}
//String& String::operator+=(const char* s) {
//	if (s == nullptr) {
//		assert(false);
//	}
//	int size = strlen(s) + _size;
//	Reserve(size);
//	strcpy(_str + _size, s);
//	_size = size;
//	return *this;
//
//}