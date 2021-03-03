package main

import (
	"fmt"
)

func main() {

	nums := []int{2, 7, 18, 4, 211, 44, 34, 56, 77, 78, 999, 11, 15, 3, 55, 6667, 12312, 1}

	fmt.Println(sort(nums))
}

func sort(nums []int) []int {

	quickSort(nums, 0, len(nums)-1)

	return nums
}

func quickSort(nums []int, l int, r int) {
	if l > r {
		return
	}
	p := partition(nums, l, r)

	quickSort(nums, l, p-1)
	quickSort(nums, p+1, r)
}

func partition(nums []int, l int, r int) int {
	v := nums[l]
	j := l
	for i := l + 1; i <= r; i++ {
		if nums[i] < v {
			nums[i], nums[j] = nums[j], nums[i]
		}
	}
	nums[l], nums[j] = nums[j], nums[l]
	return j
}
