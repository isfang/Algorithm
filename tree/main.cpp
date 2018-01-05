
#include <iostream>

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
};

int main () {

    return 0;
}
