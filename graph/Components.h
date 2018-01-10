#include <iostream>
#include <cassert>

using namespace std;

template<typename Graph>
class Component {
    private:
        Graph &G;

        //记录dfs的过程节点是否有被访问过
        bool *visited;

        //联通分量个数
        int ccount;

        //每个节点所对应的联通分量的标记
        int *id;


        //深度遍历一个图
        void dfs(int v){

            //这个位置代表第一次访问这个节点
            visited[v] = true;
            id[v] = ccount;

            typename Graph::adjIterator adj(G,v);
            for(int i = adj.begin(); !adj.end(); i = adj.next()){
                if(!visited[i]){
                    dfs(i);
                }
            }
        }
    public:
        Component (Graph &graph): G(graph){
            visited = new bool[G.V()];

            id = new int [G.V()];

            ccount = 0;

            //将visited初始化为都没有访问过
            for(int i = 0; i < G.V(); i++){
                visited[i] = false;

                id[i] = -1;
            }

            //深度遍历整个图,顺便求出联通分量
            for(int i = 0; i < G.V(); i ++){
                if(!visited[i]){
                    //遍历执行dfs操作
                    dfs(i);

                    ccount++;
                }
            }
        }

        ~Component(){
            delete[] visited;
        }

        // 返回图的联通分量个数
        int count(){
            return ccount;
        }

        // 查询点v和点w是否联通
        bool isConnected( int v , int w ){
            assert( v >= 0 && v < G.V() );
            assert( w >= 0 && w < G.V() );
            return id[v] == id[w];
        }

};
