package main

import "fmt"

func main() {
	nums := []int{2, 7, 11, 15, 3, 55, 6667, 12312}
	fmt.Println(sort(nums, len(nums)))
}

func sort(nums []int, num int) []int {
	for i := 0; i < num; i++ {
		minNum := i
		for j := i + 1; j < num; j++ {
			if nums[j] < nums[minNum] {
				minNum = j
			}
		}
		nums[i], nums[minNum] = nums[minNum], nums[i]
	}
	return nums
}
