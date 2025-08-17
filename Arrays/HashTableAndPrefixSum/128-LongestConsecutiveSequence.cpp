#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;

/*
Problem Statement:
-------------------
Given an unsorted array of integers `nums`, return the length of the longest consecutive elements sequence.

Consecutive sequence means numbers that follow each other in increasing order without gaps.

Example 1:
----------
Input: nums = [100, 4, 200, 1, 3, 2]
Output: 4
Explanation: The longest consecutive sequence is [1, 2, 3, 4].

Example 2:
----------
Input: nums = [1, 2, 0, 1]
Output: 3
Explanation: The longest consecutive sequence is [0, 1, 2].

Example 3:
----------
Input: nums = []
Output: 0
Explanation: Empty array → no sequence.
*/

/*
Naive Approach:
---------------
1. Sort the array.
2. Traverse the sorted array and count consecutive sequences:
   - If current element = previous element + 1 → increase count.
   - If current element = previous element → skip (to handle duplicates).
   - Else → reset count to 1.
3. Keep track of the maximum count found.

Time Complexity: O(N log N) (due to sorting)
Space Complexity: O(1)      (ignoring sorting space)
*/

int longestConsecutiveSequenceNaive(vector<int> &nums)
{
    int n = nums.size();
    if (n == 0)
        return 0;

    sort(nums.begin(), nums.end());

    int res = 1;
    int count = 1;

    for (int i = 1; i < n; i++)
    {
        if (nums[i] == nums[i - 1] + 1)
        {
            // Consecutive element found → increase count
            count++;
            res = max(res, count);
        }
        else if (nums[i] == nums[i - 1])
        {
            // Duplicate element → skip
            continue;
        }
        else
        {
            // Sequence breaks → reset count
            count = 1;
        }
    }

    return res;
}

/*
Optimized Approach:
-------------------
1. Store all numbers in a hash set for O(1) lookup.
2. Iterate through each number `x`:
   - If `x - 1` exists in the set, skip (because `x` is not the start of a sequence).
   - Otherwise, treat `x` as the start of a new sequence.
3. From `x`, keep checking for `x+1`, `x+2`, ... while they exist in the set.
4. Count the length of this sequence and update the result.

Time Complexity: O(N) (each number is processed once)
Space Complexity: O(N) (for the hash set)
*/

int longestConsecutiveSequence(vector<int> &nums)
{
    int n = nums.size();
    if (n == 0)
        return 0;

    unordered_set<int> st(nums.begin(), nums.end());

    int res = 0;
    for (int x : st)
    {
        // Check if 'x' is the start of a sequence
        if (st.find(x - 1) == st.end())
        {
            int currNo = x;
            int count = 1;

            // Expand the sequence
            while (st.find(currNo + 1) != st.end())
            {
                currNo++;
                count++;
            }
            res = max(res, count);
        }
    }

    return res;
}

int main()
{
    vector<int> nums = {1, 0, 1, 2};

    cout << "Naive Solution: " << longestConsecutiveSequenceNaive(nums) << endl;
    cout << "Efficient Solution: " << longestConsecutiveSequence(nums) << endl;

    return 0;
}

/*
Summary Table:
------------------------------------------------------
| Approach           | Time Complexity | Space Complexity |
|--------------------|-----------------|------------------|
| Naive (Sorting)    | O(N log N)      | O(1)             |
| Efficient (Hashing)| O(N)            | O(N)             |
------------------------------------------------------
*/
