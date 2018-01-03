#include "HeapClass.h"

using namespace std;
// template<typename T>
class HeapPrint {

    public:
        HeapPrint(int count);
        HeapPrint(MaxHeap<int> *heap);
    private:
        int count;
        MaxHeap<int> heap;

    // private:
        // void putNumberInLine( int num, string &line, int index_cur_level, int cur_tree_width, bool isLeft){

        //     int sub_tree_width = (cur_tree_width - 1) / 2;
        //     int offset = index_cur_level * (cur_tree_width+1) + sub_tree_width;
        //     assert(offset + 1 < line.size());
        //     if( num >= 10 ) {
        //         line[offset + 0] = '0' + num / 10;
        //         line[offset + 1] = '0' + num % 10;
        //     }
        //     else{
        //         if( isLeft)
        //             line[offset + 0] = '0' + num;
        //         else
        //             line[offset + 1] = '0' + num;
        //     }
        // }

        // void putBranchInLine( string &line, int index_cur_level, int cur_tree_width){

        //     int sub_tree_width = (cur_tree_width - 1) / 2;
        //     int sub_sub_tree_width = (sub_tree_width - 1) / 2;
        //     int offset_left = index_cur_level * (cur_tree_width+1) + sub_sub_tree_width;
        //     assert( offset_left + 1 < line.size() );
        //     int offset_right = index_cur_level * (cur_tree_width+1) + sub_tree_width + 1 + sub_sub_tree_width;
        //     assert( offset_right < line.size() );

        //     line[offset_left + 1] = '/';
        //     line[offset_right + 0] = '\\';
        // }

    // public:

        //  HeapPrint(int count) {
        //      this.count = count;
        //  }
         
        //  HeapPrint(){
        //     cout << "Constructors" << endl;
        //  }

        //  void testPrint() {
        //     cout << "testPrint" << endl;
        //  }
    
         // 以树状打印整个堆结构
    //     void testPrint(MaxHeap<int> heap)
    //     {

    //         // 我们的testPrint只能打印100个元素以内的堆的树状信息
    //         if( heap.size() >= 100 ){
    //             cout<<"This print function can only work for less than 100 int";
    //             return;
    //         }

    //         // 我们的testPrint只能处理整数信息
    //         if( typeid(T) != typeid(int) ){
    //             cout <<"This print function can only work for int item";
    //             return;
    //         }

    //         cout<<"The max heap size is: "<<heap.size()<<endl;
    //         cout<<"Data in the max heap: ";
    //         for( int i = 1 ; i <= heap.size() ; i ++ ){
    //             // 我们的testPrint要求堆中的所有整数在[0, 100)的范围内
    //             assert( heap.data[i] >= 0 && heap.data[i] < 100 );
    //             cout<<heap.data[i]<<" ";
            
    //         cout<<endl;
    //         cout<<endl;

    //         int n = heap.size();
    //         int max_level = 0;
    //         int number_per_level = 1;
    //         while( n > 0 ) {
    //             max_level += 1;
    //             n -= number_per_level;
    //             number_per_level *= 2;
    //         }

    //         int max_level_number = int(pow(2, max_level-1));
    //         int cur_tree_max_level_number = max_level_number;
    //         int index = 1;
    //         for( int level = 0 ; level < max_level ; level ++ ){
    //             string line1 = string(max_level_number*3-1, ' ');

    //             int cur_level_number = min(heap.count-int(pow(2,level))+1,int(pow(2,level)));
    //             bool isLeft = true;
    //             for( int index_cur_level = 0 ; index_cur_level < cur_level_number ; index ++ , index_cur_level ++ ){
    //                 putNumberInLine( heap.data[index] , line1 , index_cur_level , cur_tree_max_level_number*3-1 , isLeft );
    //                 isLeft = !isLeft;
    //             }
    //             cout<<line1<<endl;

    //             if( level == max_level - 1 )
    //                 break;

    //             string line2 = string(max_level_number*3-1, ' ');
    //             for( int index_cur_level = 0 ; index_cur_level < cur_level_number ; index_cur_level ++ )
    //                 putBranchInLine( line2 , index_cur_level , cur_tree_max_level_number*3-1 );
    //             cout<<line2<<endl;

    //             cur_tree_max_level_number /= 2;
    //         }
    //     }
    // }
};

HeapPrint::HeapPrint(int _count) {
    count = _count;
    cout << "count is  " << count <<endl;
}

HeapPrint::HeapPrint(MaxHeap<int> *_heap) {
    // heap = _heap;
    cout << "count is  " << count <<endl;
}