#include<iostream>
#include<memory>
using namespace std;
typedef int HPDataType;
//用顺序表实现堆 (堆是完全二叉树,不存在空间浪费)
typedef struct Heap {
	HPDataType* _array;
	size_t _size;
	size_t _capacity;
}Heap;
//交换函数
void Swap(HPDataType* array, int child, int parent) {
	int tmp = array[child];
	array[child] = array[parent];
	array[parent] = tmp;
}

//堆向下调整算法建小堆
void AdJustDown1(HPDataType* array, int n, int size) {
	int child = n * 2 + 1;
	//判断是否有有孩子，即它是不是叶子节点
	while (child < size) {
		//从两个孩子节点中选择较小的那个
		if (child + 1 < size && array[child + 1] < array[child])
			child++;
		//比较起始位置和父节点位置的大小,如果起始位置小于父节点,交换,更新起始位置,
		if (array[child] < array[n]) {
			Swap(array, child, n);
			n = child;
			child = 2 * n + 1;
		}
		else
			break;
	}
}

//堆向下调整算法建大堆
void AdJustDown2(HPDataType* array, int n, int size) {
	int child = n * 2 + 1;
	//判断是否有有孩子，即它是不是叶子节点
	while (child < size) {
		//从两个孩子节点中选择较大的那个
		if (child+1< size && array[child+1] > array[child])
			child++;
		//	//比较起始位置和父节点位置的大小,如果起始位置大于父节点,交换,更新起始位置
		if (array[child]>array[n]) {
			Swap(array, child, n);
			n = child;
			child = 2 * n + 1;
		}
		else
			break;
	}
}

//堆向上调整算法建小堆
void AdJustUp1(HPDataType* array, int child) {
	int parent = (child - 1) / 2;
	////前提是小根堆已经建好
	while (child > 0) {
		//比较起始位置和父节点位置的大小,如果起始位置小于父节点,交换,更新
		if (array[child] < array[parent]) {
			Swap(array, child, parent);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
			break;
	}
}

//堆向上调整算法建大堆	
void AdJustUp2(HPDataType* array, int child) {
	int parent = (child - 1) / 2;
	//前提是大根堆已经建好
	while (child > 0) {
		//比较起始位置和父节点位置的大小,如果起始位置大于父节点,交换,更新
		if (array[child] > array[parent]) {
			Swap(array, child, parent);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
			break;
	}
}

//建堆

//小堆
void HeapCreat(Heap* hp, HPDataType* array, int size) {
	hp->_array = (HPDataType*)malloc(sizeof(HPDataType) * size);
	memcpy(hp->_array, array, sizeof(HPDataType) * size);
	hp->_capacity = size * 2;
	hp->_size = size;
	for (int parent = (size - 2) / 2; parent >= 0; parent--) {
		//从最后一个非叶子结点开始，调整到 0 结束
		//最后一个非叶子结点就是最后一个结点的双亲结点
		AdJustDown1(hp->_array,parent,size);//向下调整算法建小堆
	}
}

//大堆
void HeapCreat2(Heap* hp, HPDataType* array, int size) {
	hp->_array = (HPDataType*)malloc(sizeof(HPDataType) * size);
	memcpy(hp->_array, array, sizeof(HPDataType) * size);
	hp->_capacity = size * 2;
	hp->_size = size;
	for (int parent = (size - 2) / 2; parent >= 0; parent--) {
		//从最后一个非叶子结点开始，调整到 0 结束
		//最后一个非叶子结点就是最后一个结点的双亲结点
		AdJustDown2(hp->_array, parent,size);//向下调整算法建大堆
	}
}


//插入
void HeapInsert(Heap* hp, HPDataType data) {
	//检查容量是否增容
	if (hp->_size == hp->_capacity) {
		hp->_capacity *= 2;
		hp->_array = (HPDataType*)realloc(hp->_array, sizeof(HPDataType) * hp->_capacity);
	}
	//尾插

	hp->_array[hp->_size] = data;
	(hp->_size)++;
	//向上调整
	AdJustUp2(hp->_array, hp->_size - 1);
}
//删除堆顶元素
void HeapPop(Heap* hp) {
	if (hp->_size > 0){
		//交换:堆顶和最后一个叶子
		Swap(hp->_array, 0, hp->_size - 1);
		//尾删:实际删除的是堆顶元素

		//删除效率高:O(1)
		hp->_size--;
		//向下调整
		AdJustDown2(hp->_array, 0,hp->_size);
	}
}
//获取堆顶元素
HPDataType HeapTop(Heap* hp) {
	return hp->_array[0];
}
//判空
bool HeapEmpty(Heap* hp) {
	if (hp->_size == 0)
		return 1;
	return 0;
}
//堆打印
void HeapPrint(Heap* hp) {
	for (size_t i = 0; i < hp->_size; i++) {
		printf("%d ", hp->_array[i]);
	}
	printf("\n");
}

int main() {
	Heap hp;
	int array[6] = {1,5,2,8,3,7};
	cout << "数组:";
	for (int i = 0; i < 6; ++i) {
		cout << array[i] << " ";
	}
	cout << endl;
	HeapCreat(&hp, array, 6);
	cout << "大根堆：";
	HeapPrint(&hp);
	HeapCreat2(&hp, array, 6);
	cout << "小根堆：";
	HeapPrint(&hp);

	HeapInsert(&hp, 9);
	cout << "插入元素后的大根堆为：";
	HeapPrint(&hp);
	cout << "堆顶元素为：" << HeapTop(&hp) << endl;
	HeapPop(&hp);
	cout << "删除堆顶元素后的大根堆为：";
	HeapPrint(&hp);

	return 0;
}