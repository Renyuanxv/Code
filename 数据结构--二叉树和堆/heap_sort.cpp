//#include<iostream>
//#include<memory>
//using namespace std;
//typedef int HPDataType;
////��˳���ʵ�ֶ� (������ȫ������,�����ڿռ��˷�)
//typedef struct Heap {
//	HPDataType* _array;
//	size_t _size;
//	size_t _capacity;
//}Heap;
////��������
//void Swap(HPDataType* array, int size, int parent) {
//	int tmp = array[];
//	array[child] = array[parent];
//	array[parent] = tmp;
//}
//
//void AdJustDown2(HPDataType* array, int n, int size) {
//	int child = n * 2 + 1;
//	//�ж��Ƿ����к��ӣ������ǲ���Ҷ�ӽڵ�
//	while (child < size) {
//		//���������ӽڵ���ѡ��ϴ���Ǹ�
//		if (child + 1 < size && array[child + 1] > array[child])
//			child++;
//		//	//�Ƚ���ʼλ�ú͸��ڵ�λ�õĴ�С,�����ʼλ�ô��ڸ��ڵ�,����,������ʼλ��
//		if (array[child] > array[n]) {
//			Swap(array, child, n);
//			n = child;
//			child = 2 * n + 1;
//		}
//		else
//			break;
//	}
//}