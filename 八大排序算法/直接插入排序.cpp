//#include<iostream>
//#include<vector>
//using namespace std;
//void Print(vector<int>& v,int i) {
//	cout <<"第"<< i <<"次排序结果"<< ":";
//	for (int j = 0; j<v.size(); ++j) {
//		cout << v[j] << " ";
//	}
//	cout << endl;
//}
//void InsertSort(vector<int>& v) {
//	for (int i = 1; i < v.size(); ++i) {
//		// //若第i个元素大于i-1元素，直接插入。小于的话，移动有序表后插入
//		if (v[i] < v[i - 1]) {
//			int end = i - 1;
//			int tmp = v[i];//记录带存储元素
//			while(end>=0) {
//				////查找在有序表的插入位置
//				if (tmp < v[end]) {
//					v[end + 1] = v[end];
//					end--;
//				}
//				else
//					break;
//			}
//			////插入到正确位置
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
