#pragma once
#include<iostream>
#include<string>
#include<cstring>
using namespace std;
class String {
public:
	typedef char* Iterator;
	String();//����յ�string����� �����յ��ַ���
	String(const char* s);//��C-string������string�����
	//String(size_t n, char c);//string������а���n���ַ�c
	//String(const String& s);//�������캯��
	//String(const String& s, size_t n);//��s�е�ǰn���ַ������µ�string�����

	String& operator=(const String& s);//s1=s2;
	String& operator=(const char* s);

	//~String();
	//size_t Size()const; //�����ַ�������Ч�ַ�����
	//size_t Length()const;//�����ַ�������Ч�ַ�����
	//size_t Capacity()const;//�����ַ����ռ��ܴ�С
	//bool Empty()const;//����ַ����Ƿ�Ϊ�մ� �Ƿ���true,���򷵻�false
	//void Clean();//�����Ч�ַ���
	//void Resize(size_t n, char c);//����Ч�ַ��ĸ����ĳ�n��������Ŀռ����ַ�c���
	//void Resize(size_t);//����Ч�ַ��ĸ����ĳ�n��������Ŀռ���0���
	//void Reserve(size_t newcapacity);//Ϊ�ַ���Ԥ���ռ�

	//char& operator[](size_t pos)const;//����posλ�õ��ַ�����const string��������
	//char& operator[](size_t pos);//����posλ�õ��ַ���const string��������

	//void Push_back(char c);
	//void Pop_back(char c);
	//String& Append(const char* s);
	//String& Append(size_t,const char c);
	//String& Append(const String& s);

	////����C��ʽ�ַ���
	//const char* c_str()const;

	//// �����ַ�c/�ַ���s��string�е�һ�γ��ֵ�λ��
	//size_t Find(const char c, size_t pos)const;
	//size_t Find(const char* s, size_t pos)const;
	//size_t Find(const String& s, size_t pos)const;

	//size_t Rfind(const char c, size_t pos)const;
	//size_t Rfind(const char* s, size_t pos)const;
	//size_t Rfind(const String& s, size_t pos)const;

	//// ��ȡstring��posλ�ÿ�ʼ��n���ַ�
	//String Substr(size_t pos, size_t n);
	//
	//// ��posλ���ϲ����ַ�c/�ַ���str�������ظ��ַ���λ��
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
