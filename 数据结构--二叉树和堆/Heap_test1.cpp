#include<iostream>
#include<memory>
using namespace std;
typedef int HPDataType;
//��˳���ʵ�ֶ� (������ȫ������,�����ڿռ��˷�)
typedef struct Heap {
	HPDataType* _array;
	size_t _size;
	size_t _capacity;
}Heap;
//��������
void Swap(HPDataType* array, int child, int parent) {
	int tmp = array[child];
	array[child] = array[parent];
	array[parent] = tmp;
}

//�����µ����㷨��С��
void AdJustDown1(HPDataType* array, int n, int size) {
	int child = n * 2 + 1;
	//�ж��Ƿ����к��ӣ������ǲ���Ҷ�ӽڵ�
	while (child < size) {
		//���������ӽڵ���ѡ���С���Ǹ�
		if (child + 1 < size && array[child + 1] < array[child])
			child++;
		//�Ƚ���ʼλ�ú͸��ڵ�λ�õĴ�С,�����ʼλ��С�ڸ��ڵ�,����,������ʼλ��,
		if (array[child] < array[n]) {
			Swap(array, child, n);
			n = child;
			child = 2 * n + 1;
		}
		else
			break;
	}
}

//�����µ����㷨�����
void AdJustDown2(HPDataType* array, int n, int size) {
	int child = n * 2 + 1;
	//�ж��Ƿ����к��ӣ������ǲ���Ҷ�ӽڵ�
	while (child < size) {
		//���������ӽڵ���ѡ��ϴ���Ǹ�
		if (child+1< size && array[child+1] > array[child])
			child++;
		//	//�Ƚ���ʼλ�ú͸��ڵ�λ�õĴ�С,�����ʼλ�ô��ڸ��ڵ�,����,������ʼλ��
		if (array[child]>array[n]) {
			Swap(array, child, n);
			n = child;
			child = 2 * n + 1;
		}
		else
			break;
	}
}

//�����ϵ����㷨��С��
void AdJustUp1(HPDataType* array, int child) {
	int parent = (child - 1) / 2;
	////ǰ����С�����Ѿ�����
	while (child > 0) {
		//�Ƚ���ʼλ�ú͸��ڵ�λ�õĴ�С,�����ʼλ��С�ڸ��ڵ�,����,����
		if (array[child] < array[parent]) {
			Swap(array, child, parent);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
			break;
	}
}

//�����ϵ����㷨�����	
void AdJustUp2(HPDataType* array, int child) {
	int parent = (child - 1) / 2;
	//ǰ���Ǵ�����Ѿ�����
	while (child > 0) {
		//�Ƚ���ʼλ�ú͸��ڵ�λ�õĴ�С,�����ʼλ�ô��ڸ��ڵ�,����,����
		if (array[child] > array[parent]) {
			Swap(array, child, parent);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
			break;
	}
}

//����

//С��
void HeapCreat(Heap* hp, HPDataType* array, int size) {
	hp->_array = (HPDataType*)malloc(sizeof(HPDataType) * size);
	memcpy(hp->_array, array, sizeof(HPDataType) * size);
	hp->_capacity = size * 2;
	hp->_size = size;
	for (int parent = (size - 2) / 2; parent >= 0; parent--) {
		//�����һ����Ҷ�ӽ�㿪ʼ�������� 0 ����
		//���һ����Ҷ�ӽ��������һ������˫�׽��
		AdJustDown1(hp->_array,parent,size);//���µ����㷨��С��
	}
}

//���
void HeapCreat2(Heap* hp, HPDataType* array, int size) {
	hp->_array = (HPDataType*)malloc(sizeof(HPDataType) * size);
	memcpy(hp->_array, array, sizeof(HPDataType) * size);
	hp->_capacity = size * 2;
	hp->_size = size;
	for (int parent = (size - 2) / 2; parent >= 0; parent--) {
		//�����һ����Ҷ�ӽ�㿪ʼ�������� 0 ����
		//���һ����Ҷ�ӽ��������һ������˫�׽��
		AdJustDown2(hp->_array, parent,size);//���µ����㷨�����
	}
}


//����
void HeapInsert(Heap* hp, HPDataType data) {
	//��������Ƿ�����
	if (hp->_size == hp->_capacity) {
		hp->_capacity *= 2;
		hp->_array = (HPDataType*)realloc(hp->_array, sizeof(HPDataType) * hp->_capacity);
	}
	//β��

	hp->_array[hp->_size] = data;
	(hp->_size)++;
	//���ϵ���
	AdJustUp2(hp->_array, hp->_size - 1);
}
//ɾ���Ѷ�Ԫ��
void HeapPop(Heap* hp) {
	if (hp->_size > 0){
		//����:�Ѷ������һ��Ҷ��
		Swap(hp->_array, 0, hp->_size - 1);
		//βɾ:ʵ��ɾ�����ǶѶ�Ԫ��

		//ɾ��Ч�ʸ�:O(1)
		hp->_size--;
		//���µ���
		AdJustDown2(hp->_array, 0,hp->_size);
	}
}
//��ȡ�Ѷ�Ԫ��
HPDataType HeapTop(Heap* hp) {
	return hp->_array[0];
}
//�п�
bool HeapEmpty(Heap* hp) {
	if (hp->_size == 0)
		return 1;
	return 0;
}
//�Ѵ�ӡ
void HeapPrint(Heap* hp) {
	for (size_t i = 0; i < hp->_size; i++) {
		printf("%d ", hp->_array[i]);
	}
	printf("\n");
}

int main() {
	Heap hp;
	int array[6] = {1,5,2,8,3,7};
	cout << "����:";
	for (int i = 0; i < 6; ++i) {
		cout << array[i] << " ";
	}
	cout << endl;
	HeapCreat(&hp, array, 6);
	cout << "����ѣ�";
	HeapPrint(&hp);
	HeapCreat2(&hp, array, 6);
	cout << "С���ѣ�";
	HeapPrint(&hp);

	HeapInsert(&hp, 9);
	cout << "����Ԫ�غ�Ĵ����Ϊ��";
	HeapPrint(&hp);
	cout << "�Ѷ�Ԫ��Ϊ��" << HeapTop(&hp) << endl;
	HeapPop(&hp);
	cout << "ɾ���Ѷ�Ԫ�غ�Ĵ����Ϊ��";
	HeapPrint(&hp);

	return 0;
}