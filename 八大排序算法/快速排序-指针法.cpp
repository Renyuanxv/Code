#include<iostream>
#include<vector>
#include<stack>
using namespace std;

//左右指针法	
int Partsort1(int* a, int left, int right) {
	int begin = left;
	int end = right;
	int key = right;
	while (begin < end) {
		while (begin < end && a[begin] <= a[key])
			begin++;
		while (begin < end && a[end] >= a[key])
			end--;
		swap(a[begin], a[end]);
	}
	swap(a[begin], a[right]);
	return begin;//返回中间位置
}

//挖坑法
int Partsort2(int* a, int left, int right) {
	int key = a[right];//初始坑
	while (left < right) {
		while (left < right && a[left] <= key)
			left++;
		a[right] = a[left];//left作为新坑
		while (left < right && a[right] >= key)
			right--;
		a[left] = a[right];//right作为新坑
	}
	a[left] = key;////将key赋值给left和right的相遇点，保持key的左边都是比key小的数，key的右边都是比key大的数
	return left;//最终返回中间位置
}

//前后指针法
int Partsort3(int* a, int left, int right) {
	int cur = left;
	int prev = left - 1;
	int key = a[right];
	while (cur < right) {
		if (a[cur] < key && ++prev!=cur) {
			swap(a[cur], a[prev]);
		}
		++cur;
	}
	swap(a[++prev], a[right]);//++prev左边比key小 右边比key大
	return prev;//返回中间位置
}

//递归
void Quicksort(int* a, int left, int right) {
	if (left >= right)
		return;
	int mid = Partsort1(a, left, right);
	Quicksort(a, left, mid - 1);
	Quicksort(a, mid + 1, right);
}
//非递归
void QuicksortNOR(int* a, int left, int right){
	stack<int> s;
	if (left < right){
		s.push(left);
		s.push(right);
	}
	while (!s.empty()){
		int right = s.top();
		s.pop();
		int left = s.top();
		s.pop();
		int div = Partsort1(a, left, right);
		if (left < div - 1){
			s.push(left);
			s.push(div - 1);
		}
		if (div + 1 < right){
			s.push(div + 1);
			s.push(right);
		}
	}
}


int main() {
	int a[] = { 2,5,1,7,9,8,3,6 };
	int n = (sizeof(a)) / sizeof(int);
	//Quicksort(a, 0, n - 1);
	QuicksortNOR(a, 0, n - 1);
	for (int i = 0; i < n; ++i) {
		cout << a[i] << " " ;
	}
	return 0;
}