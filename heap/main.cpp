#include "HeapClass.h"
#include "HeapIndexClass.h"

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
