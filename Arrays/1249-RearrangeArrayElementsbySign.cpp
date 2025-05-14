#include <bits/stdc++.h>
using namespace std;

/*
Problem Statement:
------------------
Given an array `nums` containing **equal numbers of positive and negative integers**,
rearrange them such that:
1. **Alternating sign order** (positive at even indices, negative at odd indices).
2. **Preserve the original relative order** of positives and negatives.

Example:
---------
Input:  [3, 1, -2, -5, 2, -4]
Output: [3, -2, 1, -5, 2, -4]

---

Approach 1: Naive Solution (Using Extra Arrays)
-----------------------------------------------
1. Separate positives and negatives into two arrays.
2. Merge them back in alternating order.
3. **Time Complexity:** O(n) (traversing input twice).
4. **Space Complexity:** O(n) (extra arrays for positives & negatives).
*/

vector<int> rearrangeArrayNaive(vector<int> &nums)
{
    vector<int> pos, neg;

    // Separate positive and negative numbers
    for (int x : nums)
    {
        if (x >= 0)
            pos.push_back(x);
        else
            neg.push_back(x);
    }

    // Merge in alternating order
    vector<int> res;
    for (int i = 0; i < nums.size() / 2; i++)
    {
        res.push_back(pos[i]); // Place positive at even index
        res.push_back(neg[i]); // Place negative at odd index
    }

    return res;
}

/*
Approach 2: Efficient Approach (Using Single Result Array)
-----------------------------------------------------------
1. Maintain two pointers:
   - `pos`: points to even indices for positives.
   - `neg`: points to odd indices for negatives.
2. Traverse the array:
   - Place positives at `res[pos]`, then increment `pos` by 2.
   - Place negatives at `res[neg]`, then increment `neg` by 2.
3. **Time Complexity:** O(n) (single pass).
4. **Space Complexity:** O(n) (output array).
*/

vector<int> rearrangeArray(vector<int> &nums)
{
    int n = nums.size();
    vector<int> res(n);   // Output array
    int pos = 0, neg = 1; // Even index for positives, odd for negatives

    for (int i = 0; i < n; i++)
    {
        if (nums[i] < 0)
        {
            res[neg] = nums[i];
            neg += 2;
        }
        else
        {
            res[pos] = nums[i];
            pos += 2;
        }
    }
    return res;
}

int main()
{
    vector<int> arr{3, 1, -2, -5, 2, -4};
    vector<int> result = rearrangeArray(arr);

    for (int x : result)
    {
        cout << x << " ";
    }
    cout << endl;

    return 0;
}
