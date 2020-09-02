//#include<iostream>
//#include<memory>
//using namespace std;
//typedef int HPDataType;
////用顺序表实现堆 (堆是完全二叉树,不存在空间浪费)
//typedef struct Heap {
//	HPDataType* _array;
//	size_t _size;
//	size_t _capacity;
//}Heap;
////交换函数
//void Swap(HPDataType* array, int size, int parent) {
//	int tmp = array[];
//	array[child] = array[parent];
//	array[parent] = tmp;
//}
//
//void AdJustDown2(HPDataType* array, int n, int size) {
//	int child = n * 2 + 1;
//	//判断是否有有孩子，即它是不是叶子节点
//	while (child < size) {
//		//从两个孩子节点中选择较大的那个
//		if (child + 1 < size && array[child + 1] > array[child])
//			child++;
//		//	//比较起始位置和父节点位置的大小,如果起始位置大于父节点,交换,更新起始位置
//		if (array[child] > array[n]) {
//			Swap(array, child, n);
//			n = child;
//			child = 2 * n + 1;
//		}
//		else
//			break;
//	}
//}