//#include<iostream>
//#include<vector>
//using namespace std;
//void Print(vector<int>& v,int i) {
//	cout <<"��"<< i <<"��������"<< ":";
//	for (int j = 0; j<v.size(); ++j) {
//		cout << v[j] << " ";
//	}
//	cout << endl;
//}
//void InsertSort(vector<int>& v) {
//	for (int i = 1; i < v.size(); ++i) {
//		// //����i��Ԫ�ش���i-1Ԫ�أ�ֱ�Ӳ��롣С�ڵĻ����ƶ����������
//		if (v[i] < v[i - 1]) {
//			int end = i - 1;
//			int tmp = v[i];//��¼���洢Ԫ��
//			while(end>=0) {
//				////�����������Ĳ���λ��
//				if (tmp < v[end]) {
//					v[end + 1] = v[end];
//					end--;
//				}
//				else
//					break;
//			}
//			////���뵽��ȷλ��
//			v[end + 1] = tmp;
//		}
//		Print(v, i);
//	}
//}
//
//int main() {
//	vector<int> v;
//	v.push_back(10);
//	v.push_back(7);
//	v.push_back(9);
//	v.push_back(8);
//	v.push_back(4);
//	v.push_back(2);
//	InsertSort(v);
//	return 0;
//}
