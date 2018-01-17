#include <iostream>
#include <cassert>


using namespace std;

// m指的是前半部分的最后一个元素
// 1 2 3 4 5 6 7 8
// l     m       r

//这个方法 处理的就是把 左右两块合成一个数组,也就是进行一次归并
//具体做法 就是
//1. 新开辟一个数组,就是一样的一个数组aux
//2. 有三个指向,1个指向aux的l 一个指向aux的m+1, 还有一个指的是原数组arr的index
//3. 接下去就是arr的index,每次都往后面挪一位, 去看l 跟 r 哪个应该放到这个位置
void __merge(int arr[], int l, int mid, int r){

    int aux[r-l+1];
    //T *aux = new T[r-l+1];

    //先开辟一段空间存储 当前整个数组,i-l 是因为数组有偏移,仔细想想就知道
    for( int i = l ; i <= r; i ++ )
        aux[i-l] = arr[i];

    //这两个索引ij是用在新开辟的aux数组中的
    // 初始化，i指向左半部分的起始索引位置l；j指向右半部分起始索引位置mid+1
    int i = l, j = mid+1;

    // 1 2 3 4 5 6 7 8
    // l     m       r
    // k
    // 1 2 3 4 5 6 7 8
    // i     m j      
    //遍历整个arr,看arr的每个位置应该放哪个位置, 每次都取较小的一个往前放
    //要取 aux的真实数据时,aux的索引位置 要减去l 这个初始偏移量,于是i-l j-l
    for( int k = l ; k <= r; k ++ ){

        // 如果左半部分元素已经全部处理完毕
        if( i > mid ){  
            arr[k] = aux[j-l]; j ++;
        }
        else if( j > r ){  // 如果右半部分元素已经全部处理完毕
            arr[k] = aux[i-l]; i ++;
        }
        else if( aux[i-l] < aux[j-l] ) {  // 左半部分所指元素 < 右半部分所指元素
            arr[k] = aux[i-l]; i ++;
        }
        else{  // 左半部分所指元素 >= 右半部分所指元素
            arr[k] = aux[j-l]; j ++;
        }
    }
}

// 递归使用归并排序,对arr[l...r]的范围进行排序
void __mergeSort(int arr[], int l, int r){

    //退出条件
    if( l >= r )
        return;

    int mid = (l+r)/2;
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid+1, r);
    
    //归并
    __merge(arr, l, mid, r);
}

void __mergeSort2(int arr[], int l, int r){

    // 优化2: 对于小规模数组, 使用插入排序
    if( r - l <= 15 ){
        //使用插入排序
        // insertionSort
        return;
    }

    int mid = (l+r)/2;
    __mergeSort2(arr, l, mid);
    __mergeSort2(arr, mid+1, r);

    // 优化1: 对于arr[mid] <= arr[mid+1]的情况,不进行merge
    // 对于近乎有序的数组非常有效,但是对于一般情况,有一定的性能损失
    if( arr[mid] > arr[mid+1] )
        __merge(arr, l, mid, r);
}


void mergeSort(int arr[], int n){
    __mergeSort(arr, 0, n-1);
}

void mergeSort2(int arr[], int n){
    __mergeSort2(arr, 0, n-1);
}