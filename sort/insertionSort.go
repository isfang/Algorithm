package main

import "fmt"

func main() {
	nums := []int{2, 7, 18, 4, 211, 44, 34, 56, 77, 78, 999, 11, 15, 3, 55, 6667, 12312}
	fmt.Println(sort(nums, len(nums)))
	fmt.Println(betterSort(nums, len(nums)))
}

func sort(nums []int, num int) []int {
	for i := 1; i < num; i++ {
		for j := i; j > 0 && nums[i] < nums[j-1]; j-- {
			nums[j] = nums[j-1]
		}
	}
	return nums
}

func betterSort(nums []int, num int) []int {
	for i := 1; i < num; i++ {
		e := nums[i]
		for j := i; j > 0 && nums[j-1] > e; j-- {
			nums[j] = nums[j-1]
		}
		nums[i] = e
	}
	return nums
}
