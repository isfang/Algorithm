#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>
#include <cmath>
#include <cassert>

using namespace std;


template<typename Item>
class MaxHeap {
    private:
        Item *data;
        int count;
        int capacity;

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
        MaxHeap(int capacity) {
            data = new Item[capacity+1];
            count = 0;
            this->capacity = capacity;
        }

        ~MaxHeap(){
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


        // 以树状打印整个堆结构
        void testPrint(){

            // 我们的testPrint只能打印100个元素以内的堆的树状信息
            if( size() >= 100 ){
                cout<<"This print function can only work for less than 100 int";
                return;
            }

            // 我们的testPrint只能处理整数信息
            if( typeid(Item) != typeid(int) ){
                cout <<"This print function can only work for int item";
                return;
            }

            cout<<"The max heap size is: "<<size()<<endl;
            cout<<"Data in the max heap: ";
            for( int i = 1 ; i <= size() ; i ++ ){
                // 我们的testPrint要求堆中的所有整数在[0, 100)的范围内
                assert( data[i] >= 0 && data[i] < 100 );
                cout<<data[i]<<" ";
            }
            cout<<endl;
            cout<<endl;

            int n = size();
            int max_level = 0;
            int number_per_level = 1;
            while( n > 0 ) {
                max_level += 1;
                n -= number_per_level;
                number_per_level *= 2;
            }

            int max_level_number = int(pow(2, max_level-1));
            int cur_tree_max_level_number = max_level_number;
            int index = 1;
            for( int level = 0 ; level < max_level ; level ++ ){
                string line1 = string(max_level_number*3-1, ' ');

                int cur_level_number = min(count-int(pow(2,level))+1,int(pow(2,level)));
                bool isLeft = true;
                for( int index_cur_level = 0 ; index_cur_level < cur_level_number ; index ++ , index_cur_level ++ ){
                    putNumberInLine( data[index] , line1 , index_cur_level , cur_tree_max_level_number*3-1 , isLeft );
                    isLeft = !isLeft;
                }
                cout<<line1<<endl;

                if( level == max_level - 1 )
                    break;

                string line2 = string(max_level_number*3-1, ' ');
                for( int index_cur_level = 0 ; index_cur_level < cur_level_number ; index_cur_level ++ )
                    putBranchInLine( line2 , index_cur_level , cur_tree_max_level_number*3-1 );
                cout<<line2<<endl;

                cur_tree_max_level_number /= 2;
            }
        }

    private:
        void putNumberInLine( int num, string &line, int index_cur_level, int cur_tree_width, bool isLeft){

            int sub_tree_width = (cur_tree_width - 1) / 2;
            int offset = index_cur_level * (cur_tree_width+1) + sub_tree_width;
            assert(offset + 1 < line.size());
            if( num >= 10 ) {
                line[offset + 0] = '0' + num / 10;
                line[offset + 1] = '0' + num % 10;
            }
            else{
                if( isLeft)
                    line[offset + 0] = '0' + num;
                else
                    line[offset + 1] = '0' + num;
            }
        }

        void putBranchInLine( string &line, int index_cur_level, int cur_tree_width){

            int sub_tree_width = (cur_tree_width - 1) / 2;
            int sub_sub_tree_width = (sub_tree_width - 1) / 2;
            int offset_left = index_cur_level * (cur_tree_width+1) + sub_sub_tree_width;
            assert( offset_left + 1 < line.size() );
            int offset_right = index_cur_level * (cur_tree_width+1) + sub_tree_width + 1 + sub_sub_tree_width;
            assert( offset_right < line.size() );

            line[offset_left + 1] = '/';
            line[offset_right + 0] = '\\';
        }

};

int main() {
    MaxHeap<int> heap = MaxHeap<int>(10000);

    //插入生成一个堆
    srand(time(NULL));
    for(int i = 0; i < 99; i++) {
        heap.insert(rand()%100);
    }
    heap.testPrint();

    cout<<endl;
    cout<<endl;
    cout<<endl;
    //当堆不空的时候,取出最大并打印
    while (!heap.isEmpty()){
        //取出最大值,并且打印
        cout<<heap.extractMax()<<" ";
    }

    cout<<endl;

    return 0;
}
