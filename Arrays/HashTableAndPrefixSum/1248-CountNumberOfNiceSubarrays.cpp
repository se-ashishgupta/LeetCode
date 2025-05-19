#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/*
Problem Statement:
------------------
Given an array of integers `nums` and an integer `k`, return the number of nice subarrays.

A nice subarray is a subarray that contains exactly `k` odd numbers.

Leetcode: https://leetcode.com/problems/count-number-of-nice-subarrays/

Example:
--------
Input: nums = [1,1,2,1,1], k = 3
Output: 2

Explanation:
The nice subarrays are [1,1,2,1] and [1,2,1,1]
*/

/*
Naive Approach:
---------------
- Try all possible subarrays
- Count the number of odd numbers in each subarray
- If the count is equal to k, increment the result

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
            if (nums[j] & 1)
                oddCount++; // Check if odd
            if (oddCount == k)
                count++;
        }
    }

    return count;
}

/*
Optimized Approach (Prefix Sum + HashMap):
------------------------------------------
- Convert array elements to 0 (even) and 1 (odd)
- Maintain prefix sum of odd counts
- Use hashmap to count how many times each prefix sum occurred

Let:
- sum = current total count of odd numbers
- (sum - k) = number of subarrays ending at current index with exactly k odd numbers

Time Complexity: O(N)
Space Complexity: O(N)
*/

int numberOfSubarraysEfficient(vector<int> &nums, int k)
{
    int count = 0;
    int sum = 0;
    unordered_map<int, int> prefSum;
    prefSum[0] = 1; // to handle the case where sum == k directly

    for (int x : nums)
    {
        sum += (x & 1); // add 1 if x is odd, else 0

        int rem = sum - k;

        if (prefSum.find(rem) != prefSum.end())
            count += prefSum[rem];

        prefSum[sum]++;
    }

    return count;
}

int main()
{
    vector<int> nums = {1, 1, 2, 1, 1};
    int k = 3;

    cout << "Number of nice subarrays (naive): " << numberOfSubarraysNaive(nums, k) << endl;
    cout << "Number of nice subarrays (efficient): " << numberOfSubarraysEfficient(nums, k) << endl;

    return 0;
}

/*
Complexity Table:
-----------------------------------------------------
| Approach        | Time Complexity | Space Complexity |
|----------------|-----------------|------------------|
| Naive          | O(N^2)          | O(1)             |
| Efficient      | O(N)            | O(N)             |
-----------------------------------------------------
*/
