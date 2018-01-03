#include "HeapIndexClass.h"
#include "HeapSort.h"

// 原始的shiftDown过程
template<typename T>
void __shiftDown_(T arr[], int n, int k){

    while( 2*k+1 < n ){
        int j = 2*k+1;
        if( j+1 < n && arr[j+1] > arr[j] )
            j += 1;

        if( arr[k] >= arr[j] )break;

        swap( arr[k] , arr[j] );
        k = j;
    }
}

// 优化的shiftDown过程, 使用赋值的方式取代不断的swap,
// 该优化思想和我们之前对插入排序进行优化的思路是一致的
template<typename T>
void __shiftDown(T arr[], int n, int k){

    T e = arr[k];
    while( 2*k+1 < n ){
        int j = 2*k+1;
        if( j+1 < n && arr[j+1] > arr[j] )
            j += 1;

        if( e >= arr[j] ) break;

        arr[k] = arr[j];
        k = j;
    }

    arr[k] = e;
}

template <typename T>
void heapsort3(T arr[], int n) {
    //heapify操作, 构建一个堆
    //最后一个非叶子节点的索引,index从0开始
    for (int i = (n-1)/2; i >=0; --i) {
        //执行一个shiftdown的操作
        __shiftDown_(arr, n, i);
    }

    //遍历整个数组,从末尾开始,遍历到index=1
    for (int i = n-1; i > 0 ; --i) {
        //将堆中最大元素的值放到正确的位置就是i的位置
        swap(arr[0], arr[i]);

        //对arr 中前i个元素的 第0个元素进行shiftDown
        __shiftDown_(arr, i, 0);
    }

    //打印当前排好序的数组
    for (int k = 0; k < n ; ++k) {
        cout<<arr[k]<<" ";
    }
    cout<<endl;
}

int main() {

    cout<<"---普通堆-----"<<endl;
    MaxHeap<int> heap = MaxHeap<int>(10000);

    //插入生成一个堆
    srand(time(NULL));
    for(int i = 0; i < 99; i++) {
        heap.insert(rand()%100);
    }

    //当堆不空的时候,取出最大并打印
    while (!heap.isEmpty()){
        //取出最大值,并且打印
        cout<<heap.extractMax()<<" ";
    }

    cout<<endl;


    cout<<"---排序1, --普通堆index从1开始-----"<<endl;
    int *arr1 = new int[100];
    for (int j = 0; j < 100 ; ++j) {
        arr1[j] = rand()%100;
    }
    heapsort1(arr1, 100);

    cout<<"---堆排序2,--heapify index从1开始------"<<endl;
    int *arr2 = new int[100];
    for (int j = 0; j < 100 ; ++j) {
        arr2[j] = rand()%100;
    }
    heapsort2(arr2, 100);

    cout<<"---排序3,heapify原地堆 index从0开始------"<<endl;
    arr2 = new int[100];
    for (int j = 0; j < 100 ; ++j) {
        arr2[j] = rand()%100;
    }
    heapsort3(arr2, 100);

    cout<<"---index堆-----"<<endl;
    IndexMaxHeap<int> indexHeap = IndexMaxHeap<int>(1000);

    //插入生成一个堆
    srand(time(NULL));
    for(int i = 0; i < 99; i++) {
        indexHeap.insert(rand()%50);
    }

    //当堆不空的时候,取出最大并打印
    while (!indexHeap.isEmpty()){
        //取出最大值,并且打印
        cout<<indexHeap.extractMax()<<" ";
    }

    cout<<endl;

    return 0;
}
