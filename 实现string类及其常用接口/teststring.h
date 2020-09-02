#pragma once
#include<iostream>
#include<string>
#include<cstring>
using namespace std;
class String {
public:
	typedef char* Iterator;
	String();//构造空的string类对象 ，即空的字符串
	String(const char* s);//用C-string来构造string类对象
	//String(size_t n, char c);//string类对象中包含n个字符c
	//String(const String& s);//拷贝构造函数
	//String(const String& s, size_t n);//用s中的前n个字符构造新的string类对象

	String& operator=(const String& s);//s1=s2;
	String& operator=(const char* s);

	//~String();
	//size_t Size()const; //返回字符串的有效字符长度
	//size_t Length()const;//返回字符串的有效字符长度
	//size_t Capacity()const;//返回字符串空间总大小
	//bool Empty()const;//检测字符串是否为空串 是返回true,否则返回false
	//void Clean();//清空有效字符串
	//void Resize(size_t n, char c);//将有效字符的个数改成n个，多出的空间用字符c填充
	//void Resize(size_t);//将有效字符的个数改成n个，多出的空间用0填充
	//void Reserve(size_t newcapacity);//为字符串预留空间

	//char& operator[](size_t pos)const;//返回pos位置的字符，非const string类对象调用
	//char& operator[](size_t pos);//返回pos位置的字符，const string类对象调用

	//void Push_back(char c);
	//void Pop_back(char c);
	//String& Append(const char* s);
	//String& Append(size_t,const char c);
	//String& Append(const String& s);

	////返回C格式字符串
	//const char* c_str()const;

	//// 返回字符c/字符串s在string中第一次出现的位置
	//size_t Find(const char c, size_t pos)const;
	//size_t Find(const char* s, size_t pos)const;
	//size_t Find(const String& s, size_t pos)const;

	//size_t Rfind(const char c, size_t pos)const;
	//size_t Rfind(const char* s, size_t pos)const;
	//size_t Rfind(const String& s, size_t pos)const;

	//// 截取string从pos位置开始的n个字符
	//String Substr(size_t pos, size_t n);
	//
	//// 在pos位置上插入字符c/字符串str，并返回该字符的位置
	//String& operator+=(const char c);
	//String& operator+=(const String& s);
	//String& operator+=(const char* s);


private:
	char* _str;
	size_t _size;
	size_t _capacity;
};

int main() {
	String s1("abcd");
	String s2;
	s2 = s1;
	cout << s1 << " " << s2 << endl;
	return 0;
}
