//
// Created by dong on 18/1/3.
//

#include "HeapClass.h"

#ifndef ALGORITHMSSTUDY_HEAPSORT_H
#define ALGORITHMSSTUDY_HEAPSORT_H
template<typename T>
//从小到大排序
void heapsort1(T arr[], int n) {
    //创建一个堆
    MaxHeap<T> heap = MaxHeap<T>(n);
    //插入每一个元素
    for (int i = 0; i < n; ++i) {
        heap.insert(arr[i]);
    }

    //从小到大排序
    for (int j = n - 1; j >= 0 ; j--) {
        arr[j] = heap.extractMax();
    }

    //打印当前排好序的数组
    for (int k = 0; k < n ; ++k) {
        cout<<arr[k]<<" ";
    }
    cout<<endl;
}

template<typename T>
//从小到大排序
void heapsort2(T arr[], int n) {
    //创建堆的过程在构造函数中完成,跟排序方法1 不一样,排序方法1是直接插入完成的
    MaxHeap<T> heap = MaxHeap<T>(arr, n);

    //从小到大排序
    for (int j = n - 1; j >= 0 ; j--) {
        arr[j] = heap.extractMax();
    }

    //打印当前排好序的数组
    for (int k = 0; k < n ; ++k) {
        cout<<arr[k]<<" ";
    }
    cout<<endl;
}
#endif //ALGORITHMSSTUDY_HEAPSORT_H
