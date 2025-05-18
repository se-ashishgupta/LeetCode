#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

/*
Problem Statement:
------------------
Given an integer array `nums` and an integer `k`, return the number of **good subarrays** of `nums`.

A good subarray is a subarray where the number of distinct integers is exactly `k`.

Leetcode: https://leetcode.com/problems/subarrays-with-k-different-integers/

Example:
--------
Input: nums = [1,2,1,2,3], k = 2
Output: 7

Explanation:
Subarrays with exactly 2 distinct integers:
[1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,3]
*/

/*
Naive Approach:
---------------
- Iterate through all possible subarrays
- Use a set to track unique elements
- If the number of unique elements is exactly k, count it

Time Complexity: O(N^2)
Space Complexity: O(N)
*/

int subarraysWithKDistinctNaive(vector<int> &nums, int k)
{
    int n = nums.size();
    int res = 0;

    for (int i = 0; i < n; i++)
    {
        unordered_set<int> st;
        for (int j = i; j < n; j++)
        {
            st.insert(nums[j]);
            if (st.size() == k)
            {
                res++;
            }
        }
    }

    return res;
}

/*
Optimized Approach:
-------------------
- Let F(k) = number of subarrays with at most k distinct elements
- Then number of subarrays with **exactly k** distinct elements is:
  F(k) - F(k-1)

We compute F(k) using sliding window:
- Expand window to the right
- Shrink from left if the number of unique elements exceeds k

Time Complexity: O(N)
Space Complexity: O(N)
*/

int atMostKDistinct(vector<int> &nums, int k)
{
    int n = nums.size();
    unordered_map<int, int> mp;
    int i = 0, j = 0, res = 0;

    while (j < n)
    {
        mp[nums[j]]++;

        // If number of distinct elements exceeds k, shrink the window
        while (mp.size() > k)
        {
            mp[nums[i]]--;
            if (mp[nums[i]] == 0)
            {
                mp.erase(nums[i]);
            }
            i++;
        }

        res += (j - i + 1); // Count subarrays ending at j
        j++;
    }

    return res;
}

int subarraysWithKDistinctEfficient(vector<int> &nums, int k)
{
    return atMostKDistinct(nums, k) - atMostKDistinct(nums, k - 1);
}

int main()
{
    vector<int> nums = {1, 2, 1, 2, 3};
    int k = 2;

    cout << "Number of subarrays with exactly " << k << " distinct elements: ";
    cout << subarraysWithKDistinctEfficient(nums, k) << endl;

    return 0;
}

/*
Complexity Table:
-----------------------------------------------------
| Approach        | Time Complexity | Space Complexity |
|----------------|-----------------|------------------|
| Naive          | O(N^2)          | O(N)             |
| Optimized (2-Pass Sliding Window) | O(N)   | O(N)   |
-----------------------------------------------------
*/
