# Algorithm

## 排序
### 最简单的选择排序
找当前数组中最小的一个放到最前面,然后继续寻找,思路很简单

```
void selectionSort(int arr[], int n){
    for(int i = 0 ; i < n ; i ++){
        // 寻找[i, n)区间里的最小值
        int minIndex = i;
        for( int j = i + 1 ; j < n ; j ++ )
            if( arr[j] < arr[minIndex] )
                minIndex = j;
        swap( arr[i] , arr[minIndex] );
    }
}

```

### 插入排序

* 普通写法

  就跟我们打牌一样, 把牌一张一张的放到合适的位置 

  也就是选择一个元素,一个一个跟前面的有序数组比大小,直到找到合适的位置,代码如下

  ```
  void insertionSort(int arr[], int n){

      for( int i = 1 ; i < n ; i ++ ) {

          // 寻找元素arr[i]合适的插入位置
          // 写法1
         for( int j = i ; j > 0 ; j-- )
             if( arr[j] < arr[j-1] )
                 swap( arr[j] , arr[j-1] );
             else
                 break;

      }

      return;
  }
  ```

* 优化改进的写法
  上面的这种方式要交换多次元素,所以减少交换次数的优化,去寻找最适合当前元素的位置,找到后 再进行交互

  ```
  void insertionSort2(int arr[], int n){
      for( int i = 1 ; i < n ; i ++ ) {
          //先把将要被排序的元素备份一下
          int e = arr[i];
          //j代表元素 e 应该要插入的位置
          int j;
          //这个条件代表的是 arr[j-1] > e j的前一个元素比e要大,那么继续遍历,直到e>j的前一个元素
          for( j = i; j > 0 && arr[j-1] > e; j-- ) {
              //j的前一个元素比e要大,往后挪
              arr[j] = arr[j-1];
          }
          arr[j] = e;
      }
      return;
  }
  ```



## 归并排序

* 基本实现

  O(nlogn)的复杂度

  其基本思路就是将数组分成二组A，B，如果这二组组内的数据都是有序的，那么就可以很方便的将这二组数据进行排序。

  如何让这二组组内数据有序

  可以将A，B组各自再分成二组。依次类推，当分出来的小组只有一个数据时，可以认为这个小组组内已经达到了有序，然后再合并相邻的二个小组就可以了。这样通过先递归的分解数列，再合并数列就完成了归并排序.

  ```
  // m指的是前半部分的最后一个元素
  // 1 2 3 4 5 6 7 8
  // l     m       r

  //这个方法 处理的就是把 左右两块合成一个数组,也就是进行一次归并
  //具体做法 就是
  //1. 新开辟一个数组,就是一样的一个数组aux
  //2. 有三个指向,1个指向aux的l 一个指向aux的m+1, 还有一个指的是原数组arr的index
  //3. 接下去就是arr的index,每次都往后面挪一位, 去看l 跟 r 哪个应该放到这个位置
  void __merge(int arr[], int l, int mid, int r){

      int aux[r-l+1];
      //T *aux = new T[r-l+1];

      //先开辟一段空间存储 当前整个数组,i-l 是因为数组有偏移,仔细想想就知道
      for( int i = l ; i <= r; i ++ )
          aux[i-l] = arr[i];

      //这两个索引ij是用在新开辟的aux数组中的
      // 初始化，i指向左半部分的起始索引位置l；j指向右半部分起始索引位置mid+1
      int i = l, j = mid+1;

      // 1 2 3 4 5 6 7 8
      // l     m       r
      // k
      // 1 2 3 4 5 6 7 8
      // i     m j      
      //遍历整个arr,看arr的每个位置应该放哪个位置, 每次都取较小的一个往前放
      //要取 aux的真实数据时,aux的索引位置 要减去l 这个初始偏移量,于是i-l j-l
      for( int k = l ; k <= r; k ++ ){

          // 如果左半部分元素已经全部处理完毕
          if( i > mid ){  
              arr[k] = aux[j-l]; j ++;
          }
          else if( j > r ){  // 如果右半部分元素已经全部处理完毕
              arr[k] = aux[i-l]; i ++;
          }
          else if( aux[i-l] < aux[j-l] ) {  // 左半部分所指元素 < 右半部分所指元素
              arr[k] = aux[i-l]; i ++;
          }
          else{  // 左半部分所指元素 >= 右半部分所指元素
              arr[k] = aux[j-l]; j ++;
          }
      }
  }

  // 递归使用归并排序,对arr[l...r]的范围进行排序
  void __mergeSort(int arr[], int l, int r){

      //退出条件
      if( l >= r )
          return;

      int mid = (l+r)/2;
      __mergeSort(arr, l, mid);
      __mergeSort(arr, mid+1, r);
      
      //归并
      __merge(arr, l, mid, r);
  }

  void mergeSort(int arr[], int n){
      __mergeSort(arr, 0, n-1);
  }
  ```

* 归并排序的优化

  * 在归并过程中, 数组如果很小,使用插入排序就行排序,因为插入排序对数组量小的时候速度较快

    ```
    // 优化2: 对于小规模数组, 使用插入排序
    if( r - l <= 15 ){
        //使用插入排序
        // insertionSort
        return;
    }
    ```

  * 在进行归并前,可以判断下 当前数组是不是已经是有序的了,只要mid < mid+1 就代表已经有序了

    ```
    int mid = (l+r)/2;
    __mergeSort2(arr, l, mid);
    __mergeSort2(arr, mid+1, r);

    // 优化1: 对于arr[mid] <= arr[mid+1]的情况,不进行merge
    // 对于近乎有序的数组非常有效,但是对于一般情况,有一定的性能损失
    if( arr[mid] > arr[mid+1] )
        __merge(arr, l, mid, r);

    ```




## 快速排序

* 基础写法

  一个分治思想. 找第一个元素v,然后把数组分成两部分,第一部分都 < v,另外一部分就 > v, 然后再去递归 这两部分,直到只有一个元素的时候

  ```
  // 对arr[l...r]部分进行partition操作
  // 返回p, 使得arr[l...p-1] < arr[p] ; arr[p+1...r] > arr[p]
  int __partiton(int arr[], int l, int r) {

      //取第一个元素去找适合他的位置
      int v = arr[l];

      //初始化第一个元素应该在的位置 为第一个
      int j = l;
      //开始遍历剩下的元素
      for (int i = l + 1; i <= r; i++ ){
          //遇到比v小的元素,放到j的当前位置,j++就继续往后移一位
          if(arr[i] < v){
              j++;
              swap(arr[i], arr[j]);
          } 
          else {
          //如果遇到比j位置还要大的元素,其实就不用动 因为每次遍历的元素大的都是放在大的区域的最后一个的
          //所以不存在这个else
          }        
      }

      //上面遍历结束后,已经找到j的位置,把原来的第一个元素也就是v 放到j位置
      swap(arr[l], arr[j]);

      return j;
  }

  void __quickSort1(int arr[], int l, int r) {
      if (l >= r) {
          return;
      }

      //3 9 7 6 8 4 5 2 1
      int p = __partiton(arr, l , r);

      __quickSort1(arr, l, p -1);
      __quickSort1(arr, p + 1, r);
  }

  //快速排序的方式就是,取数组的第一个元素,找到这个元素合适的位置,
  //找到合适的位置也就是说,这个元素合适位置的前面都是<这个元素的 后面都是大于这个元素的,这个操作我们称呼为partiton操作
  //找到后,继续递归前后两个数组,知道找到每个数组只有一个的时候 也就已经排好序了
  void quickSort1 (int arr[], int n) {
      __quickSort1(arr, 0, n-1);
  }
  ```

  ​

## heap

堆可以实现一个优先队列, 可以用一颗树表示,``子节点都不能大于其根节点``,最简单的堆可以使用数组存放,然后在插入书时按照子节点都不能大于其根节的要求插入

* insert操作

  每一次插入都是把元素插入到数组的最后,然后对这个数据进行shift up操

  ```markdown
  shift up

  //向上移动元素
  //新的数据总是加在最后一个,所以就是外面传进来的k这个元素
  //调整这个新加入的元素,调整到合适的位置,每次都跟父节点比大小,如果比父节点大就交换位置
  //直到调整到合适的位置,父节点的位置就是当前index/2
  void shiftUp(int k) {
      while(k > 1 && data[k/2] < data[k]) {
          swap(data[k/2], data[k]);
          k /= 2;
      }
  }
  ```

* 取出堆中,权重最大的值,并且调整堆,也就是取出第一个元素,然后把最后一个元素放到第一个元素的位置,count -- ,然后再针对,第一个元素做shift down 的操作

  堆排序也是同样的道理,不停的取出第一个元素, 调整堆再取第一个元素

  ```
  shift down

  //向下移动元素
  //下一个元素的index值为2*index,所以只需要比较index 与2*index 还有 2*index + 1的大小就可以了
  //如果index<2*index,那么交换位置,继续比较
  //跟左右孩子比,谁大跟谁换

  void shiftDown(int k) {

      //k这个元素有左孩子的话
      while(count >= 2*k) {
          //j与j+1表示将要被比较的元素的位置,就是k元素的左右孩子
          int j = 2*k;

          //j+1就是右孩子,j+1 <= count 说明有右孩子
          //先看右孩子跟左孩子谁大
          //如果是右孩子大的话,把j更新成j+1
          if(j+1 <= count && data[j+1] > data[j]){
              ++j;
          }

          //目前 j就是左右孩子中最大的一个

          //如果k本来就比左右孩子都大,那么啥都不干就可以
          if(data[k]>=data[j]) {
              break;
          }

          swap(data[k], data[j]);
          k=j;
      }
  }
  ```

* heapify操作

  用于生成一个堆的时候,区别于最简单的方式, 直接针对一个数组执行heapify操作生成堆,而不是一个一个的shiftup操作

  除去全部的没有孩子的叶子节点,然后遍历,挨个执行shiftdown的操作,heapify全部的数据,也就是都进行一遍shiftdown的操作

  ```
  //执行heapify操作
  //count/2; 这个值正好是除去全部的叶子节点,剩下的最大的一个不是节点的堆
  //然后遍历,执行shiftdown的操作就可以将全部的数据都进行一遍shiftdown的操作
  for (int i = count/2; i >=1 ; --i) {
      shiftDown(i);
  }
  ```

* 索引堆

  不直接交换数组,交换数组的索引,在创建堆的时候,创建一个数组存放索引,这样就可以,操作索引,而不是数组本身,避免交换产生的消耗



## tree-二分搜索树

每个节点值大于左孩子,小于右孩子这样的一颗完全二叉树,经常可以用来处理key-value类型,类似字典的实现

* 定义,BST对象

```
class BST{
    //二分搜索树的结构体
    //每个节点值大于左孩子,小于右孩子
    struct Node {
        Key key;
        Value value;
        Node *right;
        Node *left;
    };
    Node *root;
    int count;//维护这个属性可以记录有多少节点
}
```

* 插入,递归插入,一直插到最后

```
//插入从根节点开始
//比当前节点小就插入到左孩子,大就插入到右孩子,一直插到底(即下一个左孩子或者右孩子为空的时候)
//如果跟某个节点一样的话就更新这个值
Node* insert(Node *node, Key key, Value value) {
    //递归退出的情况,代表已经找到了
    if(node == NULL) {
        count++;
        return new Node(key, value);
    }
    //更新当前key值
    if (node->key == key) {
        node->value = value;
    }
    else if(key < node->key) {
        //先理解等号右边
        node->left = insert(node->left, key, value);
    }
    else {
        node->right = insert(node->right, key, value);
    }
    return node;
}
```

* 遍历

  * 深度遍历,也就是一直遍历到底

  ```
  //前序遍历-深度遍历
  void preOrder(Node *node) {
    if(node != NULL) {
        cout<<node->key<<" ";
        preOrder(node->left);
        preOrder(node->right);
    }
  }
  //中序遍历-深度遍历
  void inOrder(Node *node) {
    if(node != NULL) {
        inOrder(node->left);
        cout<<node->key<<endl;
        inOrder(node->right);
    }
  }
  //后序遍历-深度遍历
  void postOrder(Node *node) {
    if(node != NULL) {
        postOrder(node->left);
        postOrder(node->right);
        cout<<node->key<<endl;
    }
  }
  ```

  * 广度遍历,通过一个队列的协助来进行层次的遍历

  ```
  //层序遍历,也就是广度遍历
  void levelOrder(){
      queue<Node*> q;
      q.push(root);
      while(!q.empty()) {
          Node *node = q.front();
          q.pop();
          cout<<node->key<<" ";
          
          if(node->left) {
              q.push(node->left);
          }
          if(node->right) {
              q.push(node->right);
          }
      }
      cout<<endl;
  }
  ```

  ​

* 删除最大最小节点,很简单递归,左节点或者右节点

  ```
  Node* removeMin(Node *node) {
      //如果没有左节点
      if (node->left == NULL) {
          Node *rightNode = node->right;
          delete node;
          count --;
          return rightNode;
      }

      node->left = removeMin(node->left);

      return node;
  }

  Node* removeMax(Node *node) {
      //如果没有左节点
      if (node->right == NULL) {
          Node *leftNode = node->left;
          delete node;
          count --;
          return leftNode;
      }

      node->right = removeMax(node->right);

      return node;
  }
  ```

* 删除某个节点 

  根据待删除的key先找到(递归)对应的节点,如果找不到就返回空

  找到后需要删除当前节点,然后维护这颗树也就是补全要分几种情况

  ​	只有左或者右子树的时候,直接把left/right 替换为当前被删除的节点

  ​	当前节点有左右子树的时候, 寻找右子树中最小的/左子树中最大的节点 替换当前节点

  ```
  // 删除掉以node为根的二分搜索树中键值为key的节点, 递归算法
  // 返回删除节点后新的二分搜索树的根
  Node *remove(Node* node, Key key) {
      if(node == NULL) {
          return NULL;
      }
      if (key < node->key) {
          node->left = remove(node->left, key);
          return node;
      }
      else if (key > node->key) {
          node->right = remove(node->right, key);
          return node;
      }
      //key == node.key
      else {

          //待删除节点左子树为空的情况
          if( node->left == NULL ){
              Node *rightNode = node->right;
              delete node;
              count --;
              return rightNode;
          }

          // 待删除节点右子树为空的情况
          if( node->right == NULL ){
              Node *leftNode = node->left;
              delete node;
              count--;
              return leftNode;
          }

          // 待删除节点左右子树均不为空的情况
          // 找到比待删除节点大的最小节点, 即待删除节点右子树的最小节点
          // 用这个节点顶替待删除节点的位置

  		//有点错误不想改了
          Node *successor = new Node(minNode(node->right));
          //因为新生成了一个节点所以要++一下
          count ++;

          //寻找右子树中最小的跟左子树中最大的效果是一样的
          successor->right = removeMin(node->right);
          successor->left = node->left;

          //跟上面的两行一样
          // successor->left = removeMax(node->left);
          // successor->right = node->right;

          delete node;
          count --;
    
          return successor;
      }
  }
  ```

## 图-无权图

无权图 根据每个节点有多少边可以分为稀疏图(SparseGraph)跟稠密图(DenseGraph),都可以用一个二维数组表示,不同的是稀疏图不需要按钮节点个数全部初始化二维数组,有多少条边就放多少内容(节点),而稠密图不一样稠密图利用二维数组创建一个矩阵存放是否有相对应的边, 存放需要初始化全部的二维数组为false

* 基本结构
  * 稀疏图(SparseGraph),可以使用一个邻接表来表示,数据结构与构造方法如下

    ```
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
    }
    ```


  * 稠密图(DenseGraph),可以使用一个矩阵来表示,数据结构与构造方法如下

    ```
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
     }
    ```

    ​

* 插入一条边,建立一条边也就是建立两个点的关系

  * 稀疏图(SparseGraph)

    因为是邻接表的结构,所以,增加一条边就是新增一个元素到数组中

    ```
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
    ```

  * 稠密图(DenseGraph)

    矩阵的结构,就是改变矩阵中原来的布尔值, 暂时不处理自环边

    因为判断vw两者原本有没有边存在要进行一次遍历,所以添加一条新边的时候暂时不判断

    ```
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
    ```

* 图的遍历

  图的遍历,可以分别遍历稀疏图与稠密图的二维数组,但是这样就不能统一使用接口,所以可以分别通过迭代器进行迭代

  ```
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

  // O(V^2)
  for( int v = 0 ; v < N ; v ++ ){
      cout<<v<<" : ";
      DenseGraph::adjIterator adj( g2 , v );
      for( int w = adj.begin() ; !adj.end() ; w = adj.next() )
          cout<<w<<" ";
      cout<<endl;
  }
  ```

  迭代器生成具体规则如下

  - 稀疏图(SparseGraph)

    ```
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
    ```

    ​

  - 稠密图(DenseGraph)

    ```
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
    ```

* 图的路径

  求路径的思路极其简单, 在查找某个起始点的只要把s这个点的访问是来自哪个节点的(from[s]),然后在遍历完成后,只需要反过来遍历一遍from数组即可

  图的结构迭代器接口已经统一,所以只需要专注路径算法就好

  * 深度遍历求求s-w图的路径 (寻路算法通过递归实现)

    这样求出来的路径只是一条路径但是,不一定是最短的路径,最短的路径其实只需要进行广度遍历即可实现

    ```
    class Path {
    private:
        Graph &G;   // 图的引用
        int s;      // 起始点
        bool* visited;  // 记录dfs的过程中节点是否被访问
        int * from;     // 记录路径, from[i]表示查找的路径上i的上一个节点

        // 图的深度优先遍历
        void dfs( int v ){

            visited[v] = true;

            typename Graph::adjIterator adj(G, v);
            for( int i = adj.begin() ; !adj.end() ; i = adj.next() ){
                if( !visited[i] ){
                    from[i] = v;
                    dfs(i);
                }
            }
        }

    public:
        // 构造函数, 寻路算法, 寻找图graph从s点到其他点的路径
        Path(Graph &graph, int s):G(graph){

            // 算法初始化
            assert( s >= 0 && s < G.V() );

            visited = new bool[G.V()];
            from = new int[G.V()];
            for( int i = 0 ; i < G.V() ; i ++ ){
                visited[i] = false;
                from[i] = -1;
            }
            this->s = s;

            // 寻路算法
            dfs(s);
        }

        // 查询从s点到w点是否有路径
        bool hasPath(int w){
            assert( w >= 0 && w < G.V() );
            return visited[w];
        }

        // 查询从s点到w点的路径, 存放在vec中
        void path(int w, vector<int> &vec){

            assert( hasPath(w) );

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
    };
    ```

  * 广度遍历求最短路径

    广度遍历通过一个队列的辅助,进行遍历,基本元素跟其他需要的元素差不多 因为广度遍历本身得到的路径就是最短的

    ```
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
    ```