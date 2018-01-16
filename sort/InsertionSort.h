#include <iostream>
#include <cassert>

using namespace std;

void insertionSort(int arr[], int n){

    for( int i = 1 ; i < n ; i ++ ) {

        // 寻找元素arr[i]合适的插入位置
        // 写法1
       for( int j = i ; j > 0 ; j-- )
           if( arr[j] < arr[j-1] )
               swap( arr[j] , arr[j-1] );
           else
               break;

        // 写法2
        // for( int j = i ; j > 0 && arr[j] < arr[j-1] ; j -- )
        //     swap( arr[j] , arr[j-1] );

    }

    return;
}

void insertionSort2(int arr[], int n){
    for( int i = 1 ; i < n ; i ++ ) {
        //先把将要被排序的元素备份一下
        int e = arr[i];
        //j代表元素 e 应该要插入的位置
        int j;
        //这个条件代表的是 arr[j-1] > e j的前一个元素比e要大,那么继续遍历,直到e>j的前一个元素
        for( j = i; j > 0 && arr[j-1] > e; j-- ) {
            //j的前一个元素比e要大,往后挪
            arr[j] = arr[j-1];
        }
        arr[j] = e;
    }
    return;
}