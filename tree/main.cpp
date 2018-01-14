#include <iostream>
#include <queue>
#include <cassert>
#include <ctime>

using namespace std;

template<typename Key, typename Value>

class BST{
private:
    //二分搜索树的结构体
    //每个节点值大于左孩子,小于右孩子
    struct Node {
        Key key;
        Value value;
        Node *right;
        Node *left;

        Node(Key key, Value value) {
            this->key = key;
            this->value = value;
            this->left = this->right = NULL;
        }

        Node(Node *node){
            this->key = node->key;
            this->value = node->value;
            this->left = node->left;
            this->right = node->right;
        }

    };

    Node *root;
    int count;

public:
    BST(){
        root = NULL;
        count = 0;
    }

    ~BST(){

    }

    int size(){
        return count;
    }

    bool isEmpty (){
        return count == 0;
    }

    //插入一个节点
    void insert(Key key, Value value) {
        root = insert(root, key, value);
    }

    bool contain(Key key) {
        return contain(root, key);
    }

    Value *search(Key key) {
        return search(root, key);
    }

    //前序遍历
    void preOrder() {
        preOrder(root);
    }
    //中序遍历
    void inOrder() {
        inOrder(root);
    }
    //后序遍历
    void postOrder() {
        postOrder(root);
    }

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
    
    
    // 寻找二分搜索树的最小的键值
    Key minNode(){
        assert( count != 0 );
        Node* min = minNode( root );
        return min->key;
    }

    // 寻找二分搜索树的最大的键值
    Key maxNode(){
        assert( count != 0 );
        Node* max = maxNode(root);
        return max->key;
    }

    // 从二分搜索树中删除最小值所在节点
    void removeMin(){
        if( root )
            root = removeMin( root );
    }

    // 从二分搜索树中删除最大值所在节点
    void removeMax(){
        if( root )
            root = removeMax( root );
    }

    // 从二分搜索树中删除键值为key的节点
    void remove(Key key){
        root = remove(root, key);
    }

private:
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

    bool contain(Node *node, Key key){

        if(node == NULL){
            return false;
        }

        if(key == node->key) {
            return true;
        }
        else if (key < node->key) {
            return contain(node->left, key);
        }
        else {
            return contain(node->right, key);
        }
    }

    Value* search(Node *node, Key key) {
        
        // assert(contain(key));

        if(node == NULL) {
            return NULL;
        }

        if(node->key == key) {
            return &(node->value);
        }
        else if(key < node->key) {
            return search(node->left, key);
        }
        else {
            return search(node->right, key);
        }
    }


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

    //返回最大节点,就是没有右节点的节点
    Node* maxNode(Node *node) {
        if(node->right == NULL){
            return node;
        }

        return maxNode(node->right);
    }

    //返回最小节点,就是没有左节点的节点
    Node* minNode(Node *node) {
        if(node->left == NULL){
            return node;
        }

        return minNode(node->left);
    }

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


    //释放node 与其下面的全部节点,使用后序遍历
    void destory(Node *node) {
        if (node != NULL) {
            destory(node->left);
            destory(node->right);

            delete node;

            count --;
        }
    }

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
};

void shuffle( int arr[], int n ){

    srand( time(NULL) );
    for( int i = n-1 ; i >= 0 ; i -- ){
        int x = rand()%(i+1);
        swap( arr[i] , arr[x] );
    }
}



int main () {
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
