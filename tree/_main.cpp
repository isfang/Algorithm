#include <iostream>
#include <queue>
#include <cassert>
#include <ctime>
#include "main.cpp"

using namespace std;


int main2 () {
    srand(time(NULL));

    BST<int, int> bst = BST<int, int>();
    int N = 10;
    int M = 100;

    for (int i = 0; i < N; i++){
        int key = rand()%M;

        int value = key;

        cout<<key<< " ";

        bst.insert(key, value);

    }

    cout<<endl;

    // 测试二分搜索树的size()
    cout<<"size: "<<bst.size()<<endl<<endl;


    //preOrder
    cout<<"preOrder:"<<endl;
    bst.preOrder();

    //levelOrder 
    cout<<endl<<"levelOrder:"<<endl;
    bst.levelOrder();
    
     // 测试 removeMin
    // 输出的元素应该是从小到大排列的
    cout<<"Test removeMin: "<<endl;
    while( !bst.isEmpty() ){
        cout<<"min: "<<bst.minNode()<<" , ";
        bst.removeMin();
        cout<<"After removeMin, size = "<<bst.size()<<endl;
    }
    cout << endl;


    int n = 100;
    int m = 100;
 
    for( int i = 0 ; i < n ; i ++ ){
        int key = rand()%n;
        // 为了后续测试方便,这里value值取和key值一样
        int value = key;
        //cout<<key<<" ";
        bst.insert(key,value);
    }
    // 注意, 由于随机生成的数据有重复, 所以bst中的数据数量大概率是小于n的

    // 测试 removeMax
    // 输出的元素应该是从大到小排列的
    cout<<"Test removeMax: "<<endl;
    while( !bst.isEmpty() ){
        cout<<"max: "<<bst.maxNode()<<" , ";
        bst.removeMax();
        cout<<"After removeMax, size = "<<bst.size()<<endl;
    }


    cout<<"测试移除节点 "<<endl;
    BST<int,int> bst2 = BST<int,int>();

    // 取n个取值范围在[0...n)的随机整数放进二分搜索树中
    int nn = 10;
    for( int i = 0 ; i < nn ; i ++ ){
        int key = rand()%nn;
        // 为了后续测试方便,这里value值取和key值一样
        int value = key;
        bst2.insert(key,value);
    }
    // 注意, 由于随机生成的数据有重复, 所以bst中的数据数量大概率是小于n的

    // order数组中存放[0...n)的所有元素
    int order[nn];
    for( int i = 0 ; i < nn ; i ++ )
        order[i] = i;
    // 打乱order数组的顺序
    shuffle( order , nn );

    // 乱序删除[0...n)范围里的所有元素
    for( int i = 0 ; i < nn ; i ++ )
        if( bst2.contain( order[i] )){
            bst2.remove( order[i] );
            cout<<"After remove "<<order[i]<<" size = "<<bst2.size()<<endl;
        }

    // 最终整个二分搜索树应该为空
    cout << bst2.size() << endl;



    return 0;
}