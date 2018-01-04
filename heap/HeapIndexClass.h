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

        //存放索引
        int *indexes;

        //存放反向索引
        //reverse[i] 表示 索引i在indexes堆中的位置
        int *reverse;

    private:
        //向上移动元素
        //新的数据总是加在最后一个,所以就是外面传进来的k这个元素
        //调整这个新加入的元素,调整到合适的位置,每次都跟父节点比大小,如果比父节点大就交换位置
        //直到调整到合适的位置,父节点的位置就是当前index/2
        
        // 索引堆中, 数据之间的比较根据data的大小进行比较, 但实际操作的是索引
        void shiftUp(int k) {
            while(k > 1 && data[indexes[k/2]] < data[indexes[k]]) {
                swap(indexes[k/2], indexes[k]);

                reverse[indexes[k/2]] = k/2;
                reverse[indexes[k]] = k;

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
                if(j+1 <= count && data[indexes[j+1]] > data[indexes[j]]){
                    ++j;
                }

                //目前 j就是左右孩子中最大的一个


                //如果k本来就比左右孩子都大,那么啥都不干就可以
                if(data[indexes[k]]>=data[indexes[j]]) {
                    break;
                }

                swap(indexes[k], indexes[j]);

                reverse[indexes[k]] = k;
                reverse[indexes[j]] = j;

                k=j;
            }
        }
    public:
        //构造一个可以容纳capacity个元素的空堆
        IndexMaxHeap(int capacity) {
            data = new Item[capacity+1];
            indexes = new int[capacity+1];
            reverse = new int[capacity +1];
            
            //初始化reverse 数组,0 在堆中没有数据的,正好作为初始化用
            for( int i = 0 ; i <= capacity ; i ++ )
                reverse[i] = 0;


            count = 0;
            this->capacity = capacity;
        }

        IndexMaxHeap() {

        }

        ~IndexMaxHeap(){
            delete[] data;
            delete[] indexes;
            delete[] reverse;
        }

        int size(){
            return count;
        }

        bool isEmpty(){
            return count == 0;
        }

        //元素插入到数组的最后,然后对这个数据进行shift up操作
        //i 是指插入的索引,一般来说从0开始比较好
        void insert(int i, Item t) {
            
            assert( count + 1 <= capacity );
            assert(i+1 >= 1 && i+1 <= capacity);

            //需要保证i这个位子是没有元素在堆中的
            assert( !contain(i) );

            //因为是从0开始索引,堆是1开始,所以要先加1
            i += 1;

            //data存放数据,根据索引值存放即可
            data[i] = t;

            //存放索引
            indexes[count+1] = i;
            reverse[i] = count+1;
            count ++;

            shiftUp(count);
        }

        //取出堆中,权重最大的值,也就是取出第一个元素
        //然后把最后一个元素放到,第一个元素的位置count -- ,然后再针对
        //第一个元素做shift down 的操作
        Item extractMax(){
            assert(count > 0);
            //取出第一个元素,最大的
            Item result = data[indexes[1]];

            //把最后一个元素跟第一个元素交换
            swap(indexes[count], indexes[1]);

             //这个地方 不=count是因为,取出操作就是删除操作,所以要等于0,0是不存放数据的
             reverse[indexes[count]] = 0;
             reverse[indexes[1]] = 1;


             count--;

            //对第一个元素执行shift down 的操作

            shiftDown(1);

            return result;
        }

        int extractMaxIndex(){

            assert(count > 0);

            //从0开始所以要-1
            int result = indexes[1] - 1;

            swap(indexes[count], indexes[1]);

            //这个地方 不=count是因为,取出操作就是删除操作,所以要等于0,0是不存放数据的
            reverse[indexes[count]] = 0;
            reverse[indexes[1]] = 1;

            count --;

            shiftDown(1);

            return result;
        }

        // 看索引i所在的位置是否存在元素
        bool contain( int i ){
            assert( i + 1 >= 1 && i + 1 <= capacity );
            return reverse[i+1] != 0;
        }


        // 获取最大索引堆中索引为i的元素
        Item getItem( int i ){
            // assert( i + 1 >= 1 && i + 1 <= capacity );
            //需要保证i这个元素在堆中,不是说是容量够不够放i
            assert( contain(i) );
            return data[i+1];
        }

        // 将最大索引堆中索引为i的元素修改为newItem
        void change(int i, Item newItem) {

            //需要保证i这个元素在堆中,不是说是容量够不够放i
            assert( contain(i) );

            //i 是从0开始计数的, 所以要+1
            i += 1;

            //修改i位置的数据
            data[i] = newItem;

            //调整数据
            // 找到indexes[j] = i, j表示data[i]在堆中的位置
            // 之后shiftUp(j), 再shiftDown(j)
            
            //1. 这种是没有reverse数组,通过遍历的方式查找j的位置
            // for( int j = 1 ; j <= count ; j ++ )
            //     if( indexes[j] == i ){
            //         shiftUp(j);
            //         shiftDown(j);
            //         return;
            //     }

            //2. 有了reverse之后就很简单了

            int j = reverse[i];
            shiftUp(j);
            shiftDown(j);
        }
};
