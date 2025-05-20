#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/*
Problem Statement:
------------------
Given an array of integers `nums` and an integer `k`, return the number of **nice subarrays**.

A subarray is called *nice* if it contains exactly `k` odd numbers.

Leetcode: https://leetcode.com/problems/count-number-of-nice-subarrays/

Example:
--------
Input: nums = [1,1,2,1,1], k = 3
Output: 2
Explanation: The nice subarrays are [1,1,2,1] and [1,2,1,1]
*/

/*
Naive Approach:
---------------
Try every subarray and count how many odd numbers it contains.
If it contains exactly `k` odd numbers, increase the count.

Time Complexity: O(N^2)
Space Complexity: O(1)
*/
int numberOfSubarraysNaive(vector<int> &nums, int k)
{
    int count = 0;
    int n = nums.size();

    for (int i = 0; i < n; i++)
    {
        int oddCount = 0;
        for (int j = i; j < n; j++)
        {
            if (nums[j] & 1) // Check if odd
                oddCount++;
            if (oddCount == k)
                count++;
        }
    }

    return count;
}

/*
Efficient Approach 1: Prefix Sum + Hash Map
-------------------------------------------
- Convert array into a binary array: 1 if odd, 0 if even.
- Maintain a running sum of the binary array.
- Count the number of subarrays with sum = k.

Time Complexity: O(N)
Space Complexity: O(N)
*/
int numberOfSubarraysEfficient(vector<int> &nums, int k)
{
    int count = 0;
    int sum = 0;
    unordered_map<int, int> prefSum;
    prefSum[0] = 1; // sum=0 appears once

    for (int x : nums)
    {
        sum += (x & 1); // Add 1 if odd

        int rem = sum - k;
        if (prefSum.find(rem) != prefSum.end())
            count += prefSum[rem];

        prefSum[sum]++;
    }

    return count;
}

/*
Efficient Approach 2: Sliding Window with AtMostK Trick
--------------------------------------------------------
- Count subarrays with at most k odd numbers.
- Subtract subarrays with at most (k-1) odd numbers.

Time Complexity: O(N)
Space Complexity: O(1)
*/
int atMostK(vector<int> &nums, int k)
{
    int count = 0;
    int n = nums.size();
    int i = 0, j = 0;
    int oddCount = 0;

    while (j < n)
    {
        if (nums[j] % 2 == 1)
            oddCount++;

        while (oddCount > k)
        {
            if (nums[i] % 2 == 1)
                oddCount--;
            i++;
        }

        count += (j - i + 1); // Subarrays ending at j
        j++;
    }

    return count;
}

int numberOfSubarraysEfficientSecond(vector<int> &nums, int k)
{
    return atMostK(nums, k) - atMostK(nums, k - 1);
}

int main()
{
    vector<int> nums = {1, 1, 2, 1, 1};
    int k = 3;

    cout << "Number of nice subarrays (naive): " << numberOfSubarraysNaive(nums, k) << endl;
    cout << "Number of nice subarrays (efficient - prefix sum): " << numberOfSubarraysEfficient(nums, k) << endl;
    cout << "Number of nice subarrays (efficient - sliding window): " << numberOfSubarraysEfficientSecond(nums, k) << endl;

    return 0;
}

/*
Complexity Table:
------------------------------------------------------------
| Approach                  | Time Complexity | Space Complexity |
|---------------------------|-----------------|------------------|
| Naive                     | O(N^2)          | O(1)             |
| Efficient (Prefix Sum)    | O(N)            | O(N)             |
| Efficient (Sliding Window)| O(N)            | O(1)             |
------------------------------------------------------------
*/
