#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*
Problem Statement:
-------------------
Given an array nums, determine if it is sorted in ascending order
and then possibly rotated at some pivot.

A sorted and rotated array means:
- The array is originally sorted in ascending order.
- It is then rotated at some pivot index.
- Example: [3, 4, 5, 1, 2] is a rotation of [1, 2, 3, 4, 5].

Example 1:
----------
Input: nums = [3,4,5,1,2]
Output: true
Explanation: Rotated at index 2 (value 5).

Example 2:
----------
Input: nums = [2,1,3,4]
Output: false
Explanation: Not sorted after any rotation.

Example 3:
----------
Input: nums = [1,2,3]
Output: true
Explanation: Already sorted without rotation.
*/

/*
Naive Approach:
---------------
1. Try all possible rotations of the array.
2. For each rotation, check if it is sorted.
3. If any rotation is sorted, return true.
   Otherwise, return false.

Time Complexity: O(N^2)  (because we check N rotations and each check takes O(N))
Space Complexity: O(N)   (for storing rotated arrays)
*/

/*
Optimized Approach:
-------------------
1. Traverse the array and count how many times an element is greater than its next element.
   - This count is called `countPivot`.
   - In a sorted and rotated array, this happens at most once.
2. Additionally, compare the last element with the first element.
   - If the last element is greater than the first element, increment `countPivot`.
3. If `countPivot` <= 1, return true; otherwise false.

Time Complexity: O(N)
Space Complexity: O(1)
*/

bool CheckIfArrayIsSortedAndRotated(vector<int> &nums)
{
    int n = nums.size();
    int countPivot = 0;

    // Step 1: Count places where the order is broken
    for (int i = 1; i < n; i++)
    {
        if (nums[i] < nums[i - 1])
        {
            countPivot++;
        }
    }

    // Step 2: Check last element with first element
    if (nums[n - 1] > nums[0])
    {
        countPivot++;
    }

    // Step 3: At most one pivot allowed for sorted-rotated array
    return countPivot <= 1;
}

int main()
{
    vector<int> arr = {3, 4, 5, 1, 2};
    bool res = CheckIfArrayIsSortedAndRotated(arr);

    cout << (res ? "true" : "false") << endl;

    return 0;
}

/*
Summary Table:
------------------------------------------------------
| Approach           | Time Complexity | Space Complexity |
|--------------------|-----------------|------------------|
| Brute Force        | O(N^2)          | O(N)             |
| Optimal (In-Place) | O(N)            | O(1)             |
------------------------------------------------------
*/
