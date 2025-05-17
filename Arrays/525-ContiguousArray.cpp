#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/*
Problem Statement:
------------------
Given a binary array `nums`, find the maximum length of a contiguous subarray with an equal number of 0s and 1s.

Example:
--------
Input: nums = [0, 1, 1, 1, 1, 1, 0, 0, 0]
Output: 6
Explanation: The subarray [1, 1, 1, 0, 0, 0] has equal number of 0s and 1s.
*/

/*
Naive Approach:
---------------
- Check every subarray.
- Count 0s and 1s for each subarray.
- If they are equal, update max length.

Time Complexity: O(N^2)
Space Complexity: O(1)
*/

int contiguousArrayNaive(vector<int> &nums)
{
    int n = nums.size();
    int res = 0;

    for (int i = 0; i < n; i++)
    {
        int oneCount = 0;
        int zeroCount = 0;

        for (int j = i; j < n; j++)
        {
            if (nums[j] == 0)
                zeroCount++;
            else
                oneCount++;

            if (oneCount == zeroCount)
            {
                res = max(res, j - i + 1);
            }
        }
    }

    return res;
}

/*
Optimized Approach:
-------------------
- Replace 0s with -1s to use prefix sum.
- If sum from index 0 to i is 0, then subarray from 0 to i has equal 0s and 1s.
- Use a hashmap to store first occurrence of each prefix sum.

Trick:
------
0 is replaced with -1 so:
   - 0s → -1, 1s → +1
   - Now, equal number of 0s and 1s → sum = 0

Time Complexity: O(N)
Space Complexity: O(N)
*/

int contiguousArrayEfficient(vector<int> &nums)
{
    int n = nums.size();
    int res = 0;

    // Step 1: Convert 0s to -1s
    for (int i = 0; i < n; i++)
    {
        if (nums[i] == 0)
            nums[i] = -1;
    }

    int sum = 0;
    unordered_map<int, int> countMap;
    countMap[0] = -1; // To handle sum = 0 case at beginning

    for (int i = 0; i < n; i++)
    {
        sum += nums[i];

        if (countMap.find(sum) != countMap.end())
        {
            res = max(res, i - countMap[sum]); // Subarray with sum = 0 found
        }
        else
        {
            countMap[sum] = i; // Store first occurrence
        }
    }

    return res;
}

int main()
{
    vector<int> nums = {0, 1, 1, 1, 1, 1, 0, 0, 0};
    cout << "Length of the longest contiguous subarray: "
         << contiguousArrayEfficient(nums) << endl;

    return 0;
}

/*
Complexity Table:
-----------------------------------------------------
| Approach        | Time Complexity | Space Complexity |
|----------------|-----------------|------------------|
| Naive          | O(N^2)          | O(1)             |
| Optimized (Map)| O(N)            | O(N)             |
-----------------------------------------------------
*/

/*
Leetcode Link:
--------------
https://leetcode.com/problems/contiguous-array/
*/
