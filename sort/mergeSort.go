package main

import (
	"fmt"
)

func main() {

	nums := []int{2, 7, 18, 4, 211, 44, 34, 56, 77, 78, 999, 11, 15, 3, 55, 6667, 12312, 1}

	fmt.Println(sort(nums))
}

func sort(nums []int) []int {

	merge(nums, 0, len(nums)-1)

	return nums
}

func merge(nums []int, l int, r int) {

	if l >= r {
		return
	}

	mid := (l + r) / 2

	merge(nums, l, mid)
	merge(nums, mid+1, r)

	__merge(nums, l, mid, r)
}

func __merge(nums []int, l int, mid int, r int) []int {

	aux := make([]int, r-l+1)

	copy(aux, nums[l:r+1])

	i := l
	j := mid + 1

	for k := l; k <= r; k++ {

		// 这里是i-l 跟 j - l的原因是程序是递归的 所以开始结束 只是一个指向 不一定是从0开始的
		// 相对于  相对于 ij来说 是需要要排序的数组的一半多以是这样的

		// 如果正常的情况,一会处理左边一会处理右边,那么就是判断 i j指向的值的大小
		// 但是还有一种可能是 左边或者右边一边已经处理完毕了, 所以还要考虑只有左边还是只有右边

		//左边处理完成
		if i > mid {
			nums[k] = aux[j-l]
			j++
		} else if j > r {
			nums[k] = aux[i-l]
			i++
		} else if aux[i-l] < aux[j-l] {
			nums[k] = aux[i-l]
			i++
		} else {
			nums[k] = aux[j-l]
			j++
		}
	}

	return nums
}
