#include <iostream>

#include "DenseGraph.h"
#include "SparseGraph.h"
#include "ReadGraph.h"
#include "Components.h"
#include "Path.h"
#include "ShortestPath.h"

void _test() {
    string filename1 = "testG1.txt";
    SparseGraph g1 = SparseGraph(13, false);

    ReadGraph<SparseGraph> readGraph1(g1, filename1);
    Component<SparseGraph> component1(g1);
    cout<<"TestG1.txt, Component Count: "<<component1.count()<<endl;

    cout<<endl;

    // TestG2.txt
    string filename2 = "testG2.txt";
    SparseGraph g2 = SparseGraph(7, false);
    ReadGraph<SparseGraph> readGraph2(g2, filename2);
    Component<SparseGraph> component2(g2);
    cout<<"TestG2.txt, Component Count: "<<component2.count()<<endl;
}

void test(){
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
    SparseGraph g5( 7 , false );
    ReadGraph<SparseGraph> readGraph3( g5 , filename );
    cout<<"test G2 in Sparse Graph:" << endl;
    g5.show();

    cout<<endl;

    DenseGraph g6( 7 , false );
    ReadGraph<DenseGraph> readGraph4( g6 , filename );
    cout<<"test G2 in Dense Graph:" << endl;
    g6.show();

    cout<<endl;
    cout<<endl;
    cout<<endl;
}

void testPath(){
    string filename = "testG.txt";
    SparseGraph g = SparseGraph(7, false);
    ReadGraph<SparseGraph> readGraph(g, filename);
    g.show();
    cout<<endl;

    Path<SparseGraph> path(g,0);
    cout<<"Path from 0 to 6 : " << endl;
    path.showPath(6);
}

void testShortest(){
    string filename = "testG.txt";
    SparseGraph g = SparseGraph(7, false);
    ReadGraph<SparseGraph> readGraph(g, filename);
    g.show();
    cout<<endl;

    // 比较使用深度优先遍历和广度优先遍历获得路径的不同
    // 广度优先遍历获得的是无权图的最短路径
    Path<SparseGraph> dfs(g,0);
    cout<<"DFS : ";
    dfs.showPath(6);

    ShortestPath<SparseGraph> bfs(g,0);
    cout<<"BFS : ";
    bfs.showPath(6);

}

int main(){

    test();
    _test();
    testPath();
    cout<<endl;
    testShortest();
    return 0;
}
