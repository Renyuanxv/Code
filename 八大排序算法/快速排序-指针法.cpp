#include<iostream>
#include<vector>
#include<stack>
using namespace std;

//����ָ�뷨	
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
	return begin;//�����м�λ��
}

//�ڿӷ�
int Partsort2(int* a, int left, int right) {
	int key = a[right];//��ʼ��
	while (left < right) {
		while (left < right && a[left] <= key)
			left++;
		a[right] = a[left];//left��Ϊ�¿�
		while (left < right && a[right] >= key)
			right--;
		a[left] = a[right];//right��Ϊ�¿�
	}
	a[left] = key;////��key��ֵ��left��right�������㣬����key����߶��Ǳ�keyС������key���ұ߶��Ǳ�key�����
	return left;//���շ����м�λ��
}

//ǰ��ָ�뷨
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
	swap(a[++prev], a[right]);//++prev��߱�keyС �ұ߱�key��
	return prev;//�����м�λ��
}

//�ݹ�
void Quicksort(int* a, int left, int right) {
	if (left >= right)
		return;
	int mid = Partsort1(a, left, right);
	Quicksort(a, left, mid - 1);
	Quicksort(a, mid + 1, right);
}
//�ǵݹ�
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