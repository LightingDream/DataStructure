class Solution:
    def nextPermutation(self, nums):
        size = len(nums)
        maxPos = -1
        for i in range(size - 1):
            for j in range(i + 1, size):
                if nums[i] < nums[j]:
                    maxPos = i
        if maxPos != -1:
            minValue = nums[maxPos]
            minPos = -1
            for j in range(maxPos, size):
                if nums[j] > nums[maxPos] and (nums[j] < minValue if minPos != -1 else True):
                    #print(j, ' ', maxPos)
                    minValue = nums[j]
                    minPos = j
            tmp = nums[maxPos]
            nums[maxPos] = nums[minPos]
            nums[minPos] = tmp
        l = nums[maxPos+1:size]
        l.reverse()
        nums[maxPos+1:size] = l
        return nums

if __name__ == '__main__':
    l = Solution().nextPermutation([1,3,2])
    print(l)
