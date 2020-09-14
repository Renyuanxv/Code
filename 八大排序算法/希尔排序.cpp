//#include<iostream>
//#include<vector>
//using namespace std;
//void Print(vector<int>& v, int i) {
//	cout << "第" << i << "次排序结果" << ":";
//	for (int j = 0; j < v.size(); ++j) {
//		cout << v[j] << " ";
//	}
//	cout << endl;
//}
//void ShellSort(vector<int>& v) {
//	int size = v.size();
//	int gap = size;
//	while (gap > 1) {
//		gap = gap / 3 + 1;
//		for (int i = 0; i < size - gap; ++i) {
//			int end = i;
//			int tmp = v[end + gap];
//			while (end >= 0 && tmp < v[end]) {
//				v[end+gap] = v[end];
//				end -= gap;
//			}
//			v[end + gap] = tmp;
//			cout << "gap为" << gap << "时";
//			Print(v,i);
//		}
//		cout << endl;
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
//	ShellSort(v);
//	return 0;
//}
