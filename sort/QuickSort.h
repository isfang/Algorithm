#include <iostream>
#include <cassert>

using namespace std;

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