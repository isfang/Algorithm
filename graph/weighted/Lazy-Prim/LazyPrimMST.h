#include <iostream>
#include <vector>
#include <cassert>
#include "Edge.h"
#include "MinHeap.h"

using namespace std;

template<typename Graph, typename Weight>
class LazyPrimMST {

private:

    Graph &G;

    // 最小堆, 用于算法在找到当前横切分钟横切边的最小权重值
    MinHeap<Edge<Weight> > pq;

    //标记节点i是否被访问过了
    //在这个数组里,全部为true的值可以理解为 切分的一块,全部为false的值可以理解为切分的另外一块
    bool *marked;

    //存放最小生成树的全部边
    vector<Edge<Weight> > mst;

    //最小生成树的全部权值
    Weight mstWeight;

    //访问一个节点v,并且把全部横切边放到最小堆里去,这里放进去的某条边就有可能是横切边
    void visit(int v) {
        assert( !marked[v] );
        marked[v] = true;
        // 将和节点v相连接的所有未访问的边放入最小堆中
        typename Graph::adjIterator adj(G,v);

        for (Edge<Weight>* e = adj.begin(); !adj.end(); e = adj.next()) {

            //找到一个没有被遍历过的边,丢到最小堆里去,这些边里有可能是横切边
            //marked[e->other(v)代表相邻节点有没有被访问过
            if (!marked[e->other(v)]) {
                pq.insert(*e);
            }
        }
    }

public:

    LazyPrimMST() {}
    //构造方法传递一张图进来
    LazyPrimMST(Graph &graph) : G(graph), pq(MinHeap<Edge<Weight> >(graph.E())){
        // G = graph;
        // //初始化一个最小堆,开辟空间为边数的一个最小堆
        // pq = MinHeap<Edge<Weight> >(graph.E());

        //初始化节点访问标记 为图的节点个数
        marked = new bool[G.V()];

        for( int i = 0 ; i < G.V() ; i ++ ) {
            marked[i] = false;
        }

        mst.clear();

        // 开始Lazy Prim算法, 把新的最小横切边加到最小堆中去

        //先访问起始节点
        visit(0);

        //只要最小堆不空
        while( !pq.isEmpty() ) {

            //取出最小堆中的最小权重边
            Edge<Weight> e = pq.extractMin();

            // 如果这条边的两端都已经访问过了, 则扔掉这条边
            //e 这条边的 两个顶点可能都访问过,可能都没有访问过,
            //一个顶点访问过,另外一个没有访问过代表这个边是一个横切边
            //所以两个顶点在marked中的值一样的话可以判断肯定不是横切边
            if(marked[e.v()] == marked[e.w()]) {
                //丢弃这条边
                continue;
            }

            //把这个横切边丢到最小生成树里去
            //因为是从最小生成树里取出来的, 所以肯定是权重最小的边了,肯定是最小生成树的一条边
            mst.push_back(e);

            //这个时候,e这条边肯定是一个顶点是红色,一个顶点是蓝色,也就是这两个点肯定是在不同的切分中的
            //找到没有访问过的节点
            int nv = e.v();
            if(marked[nv]) {
                nv = e.w();
            }

            //访问那个蓝色的点,继续寻找下一个最小横切边
            visit(nv);
        }

                // 计算最小生成树的权值
        mstWeight = mst[0].wt();
        for( int i = 1 ; i < mst.size() ; i ++ ) {
            mstWeight += mst[i].wt();
        }

    }

        // 析构函数
    ~LazyPrimMST(){
        delete[] marked;
    }

        // 返回最小生成树的所有边
    vector<Edge<Weight> > mstEdges(){
        return mst;
    };

    // 返回最小生成树的权值
    Weight result(){
        return mstWeight;
    };

};