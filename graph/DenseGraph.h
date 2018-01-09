#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

//稠密图-邻接矩阵
class DenseGraph {
private:
    //节点数,变数
    int n,m;
    //是不是有向图
    bool directed;

    // 图的具体数据
    vector<vector<bool> > g;

public:
    DenseGraph(int n, bool directed){
        assert(n >= 0);
        this->n = n;

        //初始化没有边
        this->m = 0;

        this->directed =directed;

        // g初始化为n*n的布尔矩阵, 每一个g[i][j]均为false, 表示没有任和边
        g = vector<vector<bool> >(n, vector<bool>(n, false));
    }

    ~DenseGraph(){}


    //节点数
    int V(){
        return n;
    }

    //边数
    int E(){
        return m;
    }

    void addEdge (int v, int w) {
        assert( v >= 0 && v < n );
        assert( w >= 0 && w < n );

        //如果已经有了
        if(hasEdge(v,w)) {
            return;
        }

        g[v][w] = true;

        if(!directed) {
            g[w][v] = true;
        }

        m ++;
    }

    bool hasEdge(int v, int w){
        assert( v >= 0 && v < n );
        assert( w >= 0 && w < n );
        return g[v][w];
    }

    // 矩阵迭代器, 传入一个图和一个顶点,
    // 迭代在这个图中和这个顶点向连的所有顶点
    class adjIterator {
    private:
        DenseGraph &G;
        int v;
        //迭代到哪里了
        int index;
    public:
        //:G(graph),因为传的是一个引用,所以可以这样去初始化
        adjIterator(DenseGraph &graph, int v):G(graph) {
            this->v = v;
            this->index = -1;
        }

        ~adjIterator(){}

        // 返回图G中与顶点v相连接的第一个顶点
        int begin(){
            index = -1;
            return next();
        }
 
        // 返回图G中与顶点v相连接的下一个顶点
        int next(){
            // 若没有顶点和v相连接, 则返回-1
            for ( index +=1; index < G.V() ; index++) {
                if(G.g[v][index]){
                    return index;
                }
            }
            return -1;
        }

        // 查看是否已经迭代完了图G中与顶点v相连接的所有顶点
        int end() {
            return index >= G.V();
        }
    };
};