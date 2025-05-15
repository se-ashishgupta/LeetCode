#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
Problem Statement:
-------------------
Implement **nextPermutation**, which rearranges numbers into the **lexicographically next greater permutation** of numbers.

If such an arrangement is not possible, it must rearrange it as the lowest possible order (i.e., sorted in ascending order).
The replacement must be **in-place** and use only constant extra memory.

Example 1:
----------
Input: nums = [1,2,3]
Output: [1,3,2]

Example 2:
----------
Input: nums = [3,2,1]
Output: [1,2,3]

Example 3:
----------
Input: nums = [1,1,5]
Output: [1,5,1]
*/

/*
Naive Approach:
---------------
- Generate all permutations of the array.
- Sort them.
- Return the one that comes just after the current permutation.
This is extremely inefficient for large arrays (O(N!)) and not suitable.

Optimized Approach:
-------------------
1. Traverse from the end and find the first index `idx` such that nums[idx] < nums[idx + 1].
   (This means the suffix after idx is in descending order.)
2. If no such index is found, the entire array is the highest permutation — reverse to get lowest.
3. Otherwise, find the smallest element in the suffix that is greater than nums[idx].
4. Swap them.
5. Reverse the suffix (to get the next smallest lexicographic permutation).

Time Complexity: O(N)
Space Complexity: O(1)
*/

class Solution
{
public:
    void nextPermutation(vector<int> &nums)
    {
        int n = nums.size();

        // Step 1: Find the first decreasing element from the end
        int idx = -1;
        for (int i = n - 1; i > 0; i--)
        {
            if (nums[i] > nums[i - 1])
            {
                idx = i - 1;
                break;
            }
        }

        // Step 2: If no such index is found, array is in descending order
        if (idx == -1)
        {
            reverse(begin(nums), end(nums));
            return;
        }

        /*
        Key Observations:
        -----------------
        1. Descending Order Property:
           - The suffix (rightmost part of the array) after `idx` is sorted in descending order.
           - This means the largest values are at the end, and no next greater permutation is possible unless we swap.

        2. Selecting the Smallest Larger Element:
           - Since the suffix is in descending order, the first element (from right to left) that is greater than nums[idx]
             is the smallest such element — making it the ideal candidate for the next permutation.
        */

        // Step 3: Find element just greater than nums[idx] from the end
        int swap_idx = idx;
        for (int i = n - 1; i > idx; i--)
        {
            if (nums[i] > nums[idx])
            {
                swap_idx = i;
                break;
            }
        }

        // Step 4: Swap and reverse the suffix
        swap(nums[idx], nums[swap_idx]);
        reverse(nums.begin() + idx + 1, nums.end());
    }
};

int main()
{
    vector<int> nums = {1, 2, 3};
    Solution().nextPermutation(nums);

    cout << "Next Permutation: ";
    for (int x : nums)
        cout << x << " ";
    cout << endl;

    return 0;
}

/*
Summary Table:
------------------------------------------------------
| Approach           | Time Complexity | Space Complexity |
|--------------------|-----------------|------------------|
| Brute Force        | O(N!)           | O(N)             |
| Optimal (In-Place) | O(N)            | O(1)             |
------------------------------------------------------
*/
