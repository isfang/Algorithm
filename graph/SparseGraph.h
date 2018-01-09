#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

//稀疏图-邻接表
class SparseGraph {
private:
    //节点数,变数
    int n,m;
    //是不是有向图
    bool directed;

    // 图的具体数据
    vector<vector<int> > g;
public:
    SparseGraph(int n, bool directed) {
        assert(n >= 0);
        this->n = n;

        //初始化没有边
        this->m = 0;

        this->directed =directed;

        // g初始化为n个空的vector, 表示每一个g[i]都为空, 即没有任和边
        g = vector<vector<int> >(n, vector<int>());
    }

    ~SparseGraph(){}
    int V(){ return n;} // 返回节点个数
    int E(){ return m;} // 返回边的个数

    void addEdge(int v, int w) {
        assert( v >= 0 && v < n );
        assert( w >= 0 && w < n );

        g[v].push_back(w);

        //v w不一样就处理了自环边
        if( v!= w && !directed) {
            g[w].push_back(v);
        }
        m++;
    }
    // 验证图中是否有从v到w的边
    bool hasEdge( int v , int w ){

        assert( v >= 0 && v < n );
        assert( w >= 0 && w < n );

        for( int i = 0 ; i < g[v].size() ; i ++ )
            if( g[v][i] == w )
                return true;
        return false;
    }

    // 显示图的信息
    void show(){

        for( int i = 0 ; i < n ; i ++ ){
            cout<<"vertex "<<i<<":\t";
            for( int j = 0 ; j < g[i].size() ; j ++ )
                cout<<g[i][j]<<"\t";
            cout<<endl;
        }
    }

    // 邻边迭代器, 传入一个图和一个顶点,
    // 迭代在这个图中和这个顶点向连的所有顶点
    class adjIterator {
    private:
        SparseGraph &G;
        int v;
        //迭代到哪里了
        int index;
    public:
        //:G(graph),因为传的是一个引用,所以可以这样去初始化
        adjIterator(SparseGraph &graph, int v):G(graph) {
            this->v = v;
            this->index = 0;
        }

        ~adjIterator(){}

        // 返回图G中与顶点v相连接的第一个顶点
        int begin(){
            index = 0;
            if(G.g[v].size() > 0){
                return G.g[v][index];
            }
            // 若没有顶点和v相连接, 则返回-1
            return -1;
        }

        // 返回图G中与顶点v相连接的下一个顶点
        int next(){
            index ++;
            if(G.g[v].size() > index) {
                return G.g[v][index];
            }
            // 若没有顶点和v相连接, 则返回-1
            return -1;
        }

        // 查看是否已经迭代完了图G中与顶点v相连接的所有顶点
        int end() {
            return G.g[v].size() <= index;
        }
    };

};