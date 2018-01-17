#include <iostream>
#include "selectionSort.h"
#include "insertionSort.h"

void testSelectionSort () {
    int a[10] = {10,9,8,7,6,5,4,3,2,1};
    selectionSort(a,10);
    for( int i = 0 ; i < 10 ; i ++ )
        cout<<a[i]<<" ";
    cout<<endl;
}

void testInsertionSort () {
    int a[10] = {10,9,8,7,6,5,4,3,2,1};
    insertionSort(a,10);
    for( int i = 0 ; i < 10 ; i ++ )
        cout<<a[i]<<" ";
    cout<<endl;
}

void testInsertionSort2 () {
    int a[10] = {10,9,8,7,6,5,4,3,2,1};
    insertionSort2(a,10);
    for( int i = 0 ; i < 10 ; i ++ )
        cout<<a[i]<<" ";
    cout<<endl;
}

int main () {

    //测试选择排序
    testSelectionSort();

    //测试插入排序
    testInsertionSort();

    //测试插入排序优化
    testInsertionSort2();
    
    return 0;
}