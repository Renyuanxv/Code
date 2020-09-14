//#include<iostream>
//#include<vector>
//using namespace std;
//
//void Adjustdown(int* a, int root, int n) {
//	int child = root * 2 + 1;//左孩子
//	while (child < n) {
//		if ((child + 1 )< n && a[child + 1] > a[child])
//			child++;
//		if (a[child] > a[root]) {
//			swap(a[child], a[root]);
//			root = child;
//			child = root * 2 + 1;
//		}
//		else
//			break;
//	}
//}
//
//int* Heapsort(int* a, int n) {
//	for (int i = (n - 1) / 2; i >= 0; i--) {
//		Adjustdown(a, i, n);
//
//		for (int i = 0; i < n; ++i) {
//			cout << a[i] << " ";
//		}
//		cout << endl;
//	}
//
//	int end = n - 1;
//	while (end > 0) {
//		swap(a[0], a[end]);
//		Adjustdown(a, 0, end); // end其实就是不算后面的一个元素，原因是最后一个节点已经是最大的
//		for (int i = 0; i < n; ++i) {
//			cout << a[i] << " ";
//		}
//		cout << endl;
//		end--;
//	}
//	return a;
//}
//
//int main() {
//	int a[] = { 2,5,1,7,9,8,3,6 };
//	int n = (sizeof(a)) / sizeof(int);
//	Heapsort(a, n);
//	for (int i = 0; i < n; ++i) {
//		cout << a[i] << " " ;
//	}
//	return 0;
//
//}