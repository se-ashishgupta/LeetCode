#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/*
Problem Statement:
-------------------
Given a binary array `nums` and an integer `goal`, return the number of non-empty subarrays with a sum equal to `goal`.

A subarray is a contiguous part of the array.

Examples:
---------
Input: nums = [1,0,1,0,1], goal = 2
Output: 4

Input: nums = [0,0,0,0,0], goal = 0
Output: 15
*/

/*
Naive Approach:
---------------
Use two nested loops to calculate sum of all subarrays and count how many are equal to `goal`.

Time Complexity: O(N^2)
Space Complexity: O(1)
*/
int numSubarraysWithSumNaive(vector<int> &nums, int goal)
{
    int res = 0;
    int n = nums.size();

    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = i; j < n; j++)
        {
            sum += nums[j];
            if (sum == goal)
            {
                res++;
            }
        }
    }

    return res;
}

/*
Efficient Approach 1: Prefix Sum + HashMap
------------------------------------------
Let `sum` be the prefix sum at current index. If `sum - goal` was seen before,
then we found a subarray that sums to `goal`.

Use hashmap to store frequencies of prefix sums.

Time Complexity: O(N)
Space Complexity: O(N)
*/
int numSubarraysWithSumEfficient(vector<int> &nums, int goal)
{
    int res = 0, sum = 0;
    unordered_map<int, int> mp;
    mp[0] = 1; // to handle exact match from index 0

    for (int num : nums)
    {
        sum += num;
        int rem = sum - goal;

        if (mp.find(rem) != mp.end())
        {
            res += mp[rem];
        }

        mp[sum]++;
    }

    return res;
}

/*
Efficient Approach 2: Sliding Window for Binary Array (when goal >= 0)
----------------------------------------------------------------------
Number of subarrays with exact sum `goal` =
    Number of subarrays with at most `goal` 1s
  - Number of subarrays with at most `goal - 1` 1s

Only works for binary arrays.

Time Complexity: O(N)
Space Complexity: O(1)
*/
int numSubarraysWithSumAtMost(vector<int> &nums, int goal)
{
    if (goal < 0)
        return 0;

    int res = 0, countOne = 0, i = 0;

    for (int j = 0; j < nums.size(); j++)
    {
        if (nums[j] == 1)
            countOne++;

        while (countOne > goal)
        {
            if (nums[i] == 1)
                countOne--;
            i++;
        }

        res += j - i + 1;
    }

    return res;
}

int main()
{
    vector<int> nums = {0, 0, 0, 0, 0};
    int goal = 0;

    int result;

    // When goal is 0, use only atMost(goal) to avoid goal-1 being negative
    if (goal == 0)
    {
        result = numSubarraysWithSumAtMost(nums, goal);
    }
    else
    {
        result = numSubarraysWithSumAtMost(nums, goal) - numSubarraysWithSumAtMost(nums, goal - 1);
    }

    cout << "Number of subarrays with sum " << goal << ": " << result << endl;

    return 0;
}

/*
Summary Table:
--------------------------------------------------------------------------------
| Approach                         | Time Complexity | Space Complexity | Notes                |
|----------------------------------|------------------|------------------|----------------------|
| Brute Force                     | O(N^2)           | O(1)             | Checks all subarrays |
| Prefix Sum + HashMap            | O(N)             | O(N)             | General case         |
| Sliding Window (Binary Arrays)  | O(N)             | O(1)             | Only for binary nums |
--------------------------------------------------------------------------------
*/
