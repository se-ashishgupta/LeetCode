#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/*
Problem Statement:
-------------------
Given an array `nums` and an integer `k`, return the total number of subarrays
whose sum is exactly equal to `k`.

A subarray is a contiguous non-empty sequence of elements within the array.

Example 1:
----------
Input: nums = [1, 2, 3], k = 3
Output: 2
Explanation:
- Subarray [1, 2] → sum = 3
- Subarray [3] → sum = 3

Example 2:
----------
Input: nums = [1, 1, 1], k = 2
Output: 2
Explanation:
- Subarray [1, 1] at indices (0,1) → sum = 2
- Subarray [1, 1] at indices (1,2) → sum = 2

Example 3:
----------
Input: nums = [3, 4, 7, 2, -3, 1, 4, 2], k = 7
Output: 4
Explanation:
- Subarrays are: [3,4], [7], [7,2,-3,1], [1,4,2]
*/

/*
Naive Approach:
---------------
1. Iterate over all possible starting points `i` of the subarray.
2. For each `i`, expand the subarray ending at `j` (where j ≥ i).
3. Keep a running sum of the subarray from i to j.
4. If the sum equals k, increment the result count.
5. Return the count after checking all subarrays.

Time Complexity: O(N^2)  (since we check all subarrays)
Space Complexity: O(1)   (only uses variables for counting and sum)
*/

int subarraySumEqualKNaive(vector<int> &nums, int k)
{
    int n = nums.size();
    int res = 0;

    for (int i = 0; i < n; i++)
    {
        int temp = 0;
        for (int j = i; j < n; j++)
        {
            temp += nums[j]; // subarray sum from i to j
            if (temp == k)
            {
                res++;
            }
        }
    }

    return res;
}

/*
Optimized Approach (Prefix Sum + HashMap):
------------------------------------------
1. Maintain a running prefix sum while traversing the array.
2. For each prefix sum, check if there exists a previous prefix sum such that:
      current_sum - previous_sum = k
   → This means the subarray between them sums to k.
3. Use a hashmap (mp) to store frequencies of prefix sums seen so far.
   - mp[sum] = number of times this sum has occurred.
4. Initialize mp[0] = 1 (to handle cases where prefix sum itself equals k).
5. For each new prefix sum:
   - Check if (sum - k) exists in mp → add its frequency to result.
   - Increment frequency of current sum in mp.

Time Complexity: O(N)
Space Complexity: O(N)  (for hashmap storing prefix sums)
*/

int subarraySumEqualK(vector<int> &nums, int k)
{
    int n = nums.size();
    int res = 0;
    unordered_map<int, int> mp;
    mp[0] = 1; // base case: prefix sum = k

    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += nums[i];    // update prefix sum
        int rem = sum - k; // check if there exists a prefix sum with this value

        if (mp.find(rem) != mp.end())
        {
            res += mp[rem]; // add frequency of that prefix sum
        }
        mp[sum]++; // record the current prefix sum
    }

    return res;
}

int main()
{
    vector<int> arr{1, 2, 3};
    int k = 3;

    cout << "Naive Solution: " << subarraySumEqualKNaive(arr, k) << endl;
    cout << "Efficient Solution: " << subarraySumEqualK(arr, k) << endl;

    return 0;
}

/*
Summary Table:
------------------------------------------------------
| Approach           | Time Complexity | Space Complexity |
|--------------------|-----------------|------------------|
| Naive              | O(N^2)          | O(1)             |
| Efficient (Prefix) | O(N)            | O(N)             |
------------------------------------------------------
*/
