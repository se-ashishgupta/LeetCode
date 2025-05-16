#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/*
Problem Statement:
------------------
Given an array `nums` and an integer `k`, return the total number of continuous subarrays
whose sum equals to `k`.

Example:
--------
Input: nums = [1, 2, 3, 4, 5], k = 5
Output: 2
Explanation: Subarrays [2, 3] and [5] have sum 5.
*/

/*
Naive Approach:
---------------
- Traverse all possible subarrays.
- For each subarray, compute the sum and compare it with `k`.
- Time Complexity: O(N^2)
*/

int subArraySumEqualsKNaive(vector<int> &nums, int k)
{
    int n = nums.size();
    int res = 0;
    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = i; j < n; j++)
        {
            sum += nums[j];
            if (sum == k)
            {
                res++; // Found a subarray with sum equal to k
            }
        }
    }
    return res;
}

/*
Optimized Approach using Prefix Sum and Hashmap:
------------------------------------------------
- Use a hashmap to store the count of prefix sums.
- For each index, calculate the running prefix sum.
- If (prefix_sum - k) exists in the map, we found a subarray that ends at this index with sum = k.

Key Insight:
------------
If the sum from index 0 to i is `sum`, and (sum - k) is present in the map,
then there exists a subarray that sums to k ending at index `i`.

Time Complexity: O(N)
Space Complexity: O(N)
*/

int subArraySumEqualsKEfficient(vector<int> &nums, int k)
{
    unordered_map<int, int> preSumMap; // Stores {prefix sum -> count of occurrences}
    int res = 0;
    int sum = 0;      // Running sum
    preSumMap[0] = 1; // To handle subarrays starting from index 0

    for (int i = 0; i < nums.size(); i++)
    {
        sum += nums[i]; // Update running sum

        int rem = sum - k; // Check if (sum - k) exists in the map

        if (preSumMap.find(rem) != preSumMap.end())
        {
            res += preSumMap[rem]; // Add the count of occurrences of (sum - k)
        }

        preSumMap[sum]++; // Increment the count of the current prefix sum
    }

    return res;
}

int main()
{
    vector<int> nums = {1, 2, 3, 4, 5};
    int k = 5;

    int result = subArraySumEqualsKEfficient(nums, k);
    cout << "Number of subarrays with sum equal to " << k << ": " << result << endl;

    return 0;
}

/*
Summary Table:
----------------------------------------------------------
| Approach           | Time Complexity | Space Complexity |
|--------------------|-----------------|------------------|
| Brute Force (Naive)| O(N^2)          | O(1)             |
| Optimal (Hashmap)  | O(N)            | O(N)             |
----------------------------------------------------------
*/

/*
Related Leetcode Problems (Prefix Sum Variants):
------------------------------------------------
1. Subarray Sum Equals K
   https://leetcode.com/problems/subarray-sum-equals-k/

2. Contiguous Array
   https://leetcode.com/problems/contiguous-array/

3. Subarrays with K Different Integers
   https://leetcode.com/problems/subarrays-with-k-different-integers/

4. Count Number of Nice Subarrays
   https://leetcode.com/problems/count-number-of-nice-subarrays/

5. Binary Subarrays With Sum
   https://leetcode.com/problems/binary-subarrays-with-sum/

6. Subarray Product Less Than K
   https://leetcode.com/problems/subarray-product-less-than-k/

7. Count Subarrays Where Max Element Appears at Least K Times
   https://leetcode.com/problems/count-subarrays-where-max-element-appears-at-least-k-times/
*/
