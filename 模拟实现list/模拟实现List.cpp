#include<iostream>
#include"List.h"
using namespace std;


//�����ӡ����
template<class T>
void PrintList(List<T>& l) {
	auto it = l.Begin();
	while (it != l.End()) {
		cout << *it <<" ";
		++it;
	}
	cout << endl;
}
//�����ӡ����
template<class T>
void PrintListReverse(const List<T>& l) {
	auto it = l.RBegin();
	while (it != l.CEnd()) {
		cout << *it < " ";
		++it;
	}
	cout << endl;
}

int main() {
	List<int> mylist1;
	List<int> mylist2(5, 10);
	for (int i = 0; i < 10; i++) {
		mylist2.PushBack(i + 1);
	}
	cout << "mylist2:";
	PrintList(mylist2);
	cout << "��ֵ���������mylist1:";
	mylist1 = mylist2;
	PrintList(mylist1);
	cout << "��������mylist3:";
	List<int> mylist3(mylist1);
	PrintList(mylist3);
	cout << endl;
	cout << "βɾ���mylist3:";
	mylist3.PopBack();
	PrintList(mylist3);
	cout << "5��ͷɾ���mylist3:";
	mylist3.PopFront();
	mylist3.PopFront();
	mylist3.PopFront();
	mylist3.PopFront();
	mylist3.PopFront();
	PrintList(mylist3);
	cout << "ͷ����mylist3:";
	mylist3.PushFront(0);
	PrintList(mylist3);
	cout << "β����mylist3:";
	mylist3.PushBack(10);
	PrintList(mylist3);
	cout << "��posλ�ò���Ԫ�غ��mylist3:";
	auto pos = mylist3.Begin();
	pos++;
	mylist3.Insert(pos, 2);
	PrintList(mylist3);
	cout << "��posλ��ɾ��Ԫ�غ��mylist3:";
	mylist3.Erase(pos);
	PrintList(mylist3);
	cout << "mylist3.Size()=";
	cout<<mylist3.Size()<<endl;
	cout << "mylist2.Swap(mylist3):  mylist3=";
	mylist2.Swap(mylist3);
	PrintList(mylist3);
	cout << "mylist3.Clern():  mylist3=";
	mylist3.Clear();
	PrintList(mylist3);
	cout << "mylist3.Size()=";
	cout<<mylist3.Size()<<endl;




	



}
