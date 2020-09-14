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
//void Selectsort(vector<int>& v) {
//	size_t size = v.size();
//	int begin = 0;
//	int end = size - 1;
//	int j = 0;
//	while (begin < end) {
//		int min = begin,max = begin;
//		//选择每一轮的最值元素
//		for (int i = begin; i <=end; ++i) {
//			if (v[min]>v[i])
//				min = i;
//			if (v[max]<v[i])
//				max = i;
//		}
//		//最前面的元素和min交换，最后面的元素和max交换
//		swap(v[min], v[begin]);
//		//
//		if (max==begin) {
//			max = min;
//		}
//		swap(v[max], v[end]);
//		++j;
//		++begin;
//		--end;
//		Print(v, j);
//	}
//}
//int main() {
//	vector<int> v;
//	v.push_back(10);
//	v.push_back(7);
//	v.push_back(9);
//	v.push_back(8);
//	v.push_back(4);
//	v.push_back(2);
//	Selectsort(v);
//	return 0;
//}