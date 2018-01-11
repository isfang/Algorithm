#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <cassert>

using namespace std;


// 寻找无权图的最短路径
template <typename Graph>
class ShortestPath {

private:
    Graph &G;       // 图的引用
    int s;          // 起始点
    bool *visited;  // 记录dfs的过程中节点是否被访问
    int *from;      // 记录路径, from[i]表示查找的路径上i的上一个节点
    //就是距离第一个节点的层数也就是第几个节点
    int *ord;       // 记录路径中节点的次序。ord[i]表示i节点在路径中的次序。

public:
    // 构造函数, 寻找无权图graph从s点到其他点的最短路径
    ShortestPath(Graph &graph, int s):G(graph){

        // 算法初始化
        assert( s >= 0 && s < graph.V() );

        visited = new bool[graph.V()];
        from = new int[graph.V()];
        ord = new int[graph.V()];
        for( int i = 0 ; i < graph.V() ; i ++ ){
            visited[i] = false;
            from[i] = -1;
            ord[i] = -1;
        }
        this->s = s;

        // 无向图最短路径算法, 从s开始广度优先遍历整张图
        queue<int> q;

        //把原点入队
        q.push( s );
        //标记原点已经访问过
        visited[s] = true;

        //原点s自己到自己距离为0
        ord[s] = 0;

        while( !q.empty() ){

            //取出队首元素
            int v = q.front();
            //因为已经取出来了,所以可以出队了
            q.pop();

            //遍历一遍,首元素相邻的全部元素
            typename Graph::adjIterator adj(G, v);
            for( int i = adj.begin() ; !adj.end() ; i = adj.next() )
                //是否已经访问过,是不是已经加入到队列里过了
                if( !visited[i] ){
                    //入队
                    q.push(i);
                    visited[i] = true;

                    //i这个节点是从v那边来的
                    from[i] = v;
                    //过来的节点的距离再+1
                    ord[i] = ord[v] + 1;
                }
        }

    }

    // 析构函数
    ~ShortestPath(){

        delete [] visited;
        delete [] from;
        delete [] ord;
    }

    // 查询从s点到w点是否有路径
    bool hasPath(int w){
        assert( w >= 0 && w < G.V() );
        return visited[w];
    }

    // 查询从s点到w点的路径, 存放在vec中
    void path(int w, vector<int> &vec){

        assert( w >= 0 && w < G.V() );

        stack<int> s;
        // 通过from数组逆向查找到从s到w的路径, 存放到栈中
        int p = w;
        while( p != -1 ){
            s.push(p);
            p = from[p];
        }

        // 从栈中依次取出元素, 获得顺序的从s到w的路径
        vec.clear();
        while( !s.empty() ){
            vec.push_back( s.top() );
            s.pop();
        }
    }

    // 打印出从s点到w点的路径
    void showPath(int w){

        assert( w >= 0 && w < G.V() );

        vector<int> vec;
        path(w, vec);
        for( int i = 0 ; i < vec.size() ; i ++ ){
            cout<<vec[i];
            if( i == vec.size()-1 )
                cout<<endl;
            else
                cout<<" -> ";
        }
    }

    // 查看从s点到w点的最短路径长度
    int length(int w){
        assert( w >= 0 && w < G.V() );
        return ord[w];
    }
};