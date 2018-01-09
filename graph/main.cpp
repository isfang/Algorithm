#include <iostream>

#include "DenseGraph.h"
#include "SparseGraph.h"
#include "ReadGraph.h"

int main(){

//    vector<int> arr({1,2,3,4});
//    vector<int>::iterator iter;
//    for (int iter  = arr.begin; iter != arr.end ; ++iter ) {
//        cout<<iter<<endl;
//    }

    int N = 20;
    int M = 100;

    srand(time(NULL));

    SparseGraph g1(N, false);
    for( int i = 0 ; i < M ; i ++ ){
        int a = rand()%N;
        int b = rand()%N;
        g1.addEdge( a , b );
    }

    // O(E)
    for( int v = 0 ; v < N ; v ++ ){
        cout<<v<<" : ";
        SparseGraph::adjIterator adj(g1, v);
        for (int w = adj.begin(); !adj.end(); w=adj.next()){
            cout<<w<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    cout<<endl;

    // Dense Graph
    DenseGraph g2(N , false);
    for( int i = 0 ; i < M ; i ++ ){
        int a = rand()%N;
        int b = rand()%N;
        g2.addEdge( a , b );
    }

    // O(V^2)
    for( int v = 0 ; v < N ; v ++ ){
        cout<<v<<" : ";
        DenseGraph::adjIterator adj( g2 , v );
        for( int w = adj.begin() ; !adj.end() ; w = adj.next() )
            cout<<w<<" ";
        cout<<endl;
    }

    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout<<endl;

    // 使用两种图的存储方式读取testG1.txt文件
    string filename = "testG1.txt";
    SparseGraph g3( 13 , false );
    ReadGraph<SparseGraph> readGraph1( g3 , filename );
    cout<<"test G1 in Sparse Graph:" << endl;
    g3.show();

    cout<<endl;

    DenseGraph g4( 13 , false );
    ReadGraph<DenseGraph> readGraph2( g4 , filename );
    cout<<"test G1 in Dense Graph:" << endl;
    g4.show();

    cout<<endl;

    // 使用两种图的存储方式读取testG2.txt文件
    filename = "testG2.txt";
    SparseGraph g5( 6 , false );
    ReadGraph<SparseGraph> readGraph3( g5 , filename );
    cout<<"test G2 in Sparse Graph:" << endl;
    g5.show();

    cout<<endl;

    DenseGraph g6( 6 , false );
    ReadGraph<DenseGraph> readGraph4( g6 , filename );
    cout<<"test G2 in Dense Graph:" << endl;
    g6.show();

    return 0;
}