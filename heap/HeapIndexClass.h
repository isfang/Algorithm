#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>
#include <cmath>
#include <cassert>

using namespace std;

template<typename Item>
class IndexMaxHeap {
    public:
        Item *data;
        int count;
        int capacity;

    private:
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
    public:
        //构造一个可以容纳capacity个元素的空堆
        IndexMaxHeap(int capacity) {
            data = new Item[capacity+1];
            count = 0;
            this->capacity = capacity;
        }

        IndexMaxHeap() {

        }

        ~IndexMaxHeap(){
            delete[] data;
        }

        int size(){
            return count;
        }

        bool isEmpty(){
            return count == 0;
        }

        //元素插入到数组的最后,然后对这个数据进行shift up操作
        void insert(Item t) {
            assert( count + 1 <= capacity );
            data[count + 1] = t;
            shiftUp(count + 1);
            count ++;
        }

        //取出堆中,权重最大的值,也就是取出第一个元素
        //然后把最后一个元素放到,第一个元素的位置count -- ,然后再针对
        //第一个元素做shift down 的操作
        Item extractMax(){
            assert(count > 0);
            //取出第一个元素,最大的
            Item result = data[1];

            //把最后一个元素跟第一个元素交换
            swap(data[count], data[1]);

            count--;

            //对第一个元素执行shift down 的操作

            shiftDown(1);


            return result;
        }
};
