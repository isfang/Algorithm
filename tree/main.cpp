
using namespace std;

template<typename Key, typename Value>

class BST{
private:
    //二分搜索树的结构体
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
};

int main () {

    return 0;
}
