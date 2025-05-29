#include <iostream>
#include <vector>
using namespace std;

/*
Problem Statement:
------------------
Given a binary array `nums`, you can flip at most `k` 0s to 1s. Return the maximum number of consecutive 1s in the array.

Example:
---------
Input: nums = [1,1,0,0,1,1,1,0,1], k = 2
Output: 8
Explanation: Flip two 0s to get maximum 8 consecutive 1s.

Naive Approach:
---------------
- Try all subarrays and count 0s and 1s in each.
- If the number of 0s is <= k, update the max length.
- Time Complexity: O(n^2), Space: O(1)

Optimized Approach (Sliding Window):
------------------------------------
- Maintain a window [i...j] with at most `k` zeroes.
- Expand `j`, count zeros and ones.
- If zeros > k, shrink from the left (i++) until zeros <= k.
- Track max window size.

Time: O(n), Space: O(1)
*/

int maxConsecutiveOnesIIINaive(vector<int> &nums, int k)
{
    int n = nums.size();
    int res = 0;

    // Try every subarray
    for (int i = 0; i < n; i++)
    {
        int ones = 0, zeros = 0;

        for (int j = i; j < n; j++)
        {
            nums[j] == 0 ? zeros++ : ones++;

            // Only consider subarrays with at most k zeroes
            if (zeros <= k)
            {
                res = max(res, ones + zeros);
            }
        }
    }

    return res;
}

int maxConsecutiveOnesIIIEfficient(vector<int> &nums, int k)
{
    int n = nums.size();
    int i = 0, j = 0; // window boundaries
    int ones = 0, zeros = 0;
    int res = 0;

    // Sliding window
    while (j < n)
    {
        nums[j] == 0 ? zeros++ : ones++;

        // Shrink window until zeros <= k
        while (zeros > k)
        {
            nums[i] == 0 ? zeros-- : ones--;
            i++;
        }

        // Update max window size
        res = max(res, ones + zeros);
        j++;
    }

    return res;
}

int main()
{
    vector<int> nums = {0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1};
    int k = 3;

    cout << "Max Consecutive 1s (with at most " << k << " flips): "
         << maxConsecutiveOnesIIIEfficient(nums, k) << endl;
    return 0;
}

/*
Summary Table:
----------------------------------------------------------
| Approach              | Time Complexity | Space Complexity |
|-----------------------|-----------------|------------------|
| Naive (Brute Force)   | O(n^2)          | O(1)             |
| Sliding Window (Optimal) | O(n)        | O(1)             |
----------------------------------------------------------
*/

// Note
// Do by Binary Search and Prefix Sum also