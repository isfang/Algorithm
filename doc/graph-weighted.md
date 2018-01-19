# 有权图

有权图跟无权图其实一样,差别是每条边 不再只是连接了两个顶点,而是在此基础上还有一个值放在那里,一条边不再像之前的稀疏图(邻接矩阵)用节点表示,稠密图(矩阵)用布尔值表示,要加上权重,于是我们可以定义一个对象或者是一个结构,如下模板Weight我们一般可以传递double进去表示权值大小

```
template<typename Weight>
class Edge{
private:
    int a,b;    // 边的两个端点
    Weight weight;  // 边的权值

public:
    // 构造函数
    Edge(int a, int b, Weight weight){
        this->a = a;
        this->b = b;
        this->weight = weight;
    }
    
    int v(){ return a;} // 返回第一个顶点
    int w(){ return b;} // 返回第二个顶点
    Weight wt(){ return weight;}    // 返回权值
    
    // 给定一个顶点, 返回另一个顶点
    int other(int x){
        assert( x == a || x == b );
        return x == a ? b : a;
    }
};

```

