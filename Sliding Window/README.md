# Sliding Window Coding Problems Collection

## Table of Contents

- [1. Subarrays with K Different Integers(992)](#subarrays-with-k-different-integers)

---

## Subarrays with K Different Integers

### Problem Statement

Given an integer array `nums` and an integer `k`, return the number of **good subarrays** of `nums`. A good subarray is a subarray where the number of distinct integers is exactly `k`.

### Example

```
Input: nums = [1,2,1,2,3], k = 2
Output: 7

Explanation:
Subarrays with exactly 2 distinct integers:
[1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,3]
```

### Approach 1: Naive (Check All Subarrays)

- **Time Complexity**: O(N²)
- **Space Complexity**: O(N)

#### Logic

1. Iterate through all possible subarrays using two nested loops
2. Use a set to track unique elements in each subarray
3. If the set size equals k, increment the count

```cpp
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
```

### Approach 2: Sliding Window (Optimal)

- **Time Complexity**: O(N)
- **Space Complexity**: O(N)

#### Logic

1. The key insight: number of subarrays with exactly k distinct elements = (subarrays with at most k distinct) - (subarrays with at most k-1 distinct)
2. Implement a helper function to count subarrays with at most K distinct elements using sliding window
3. Calculate the final result as: atMostKDistinct(nums, k) - atMostKDistinct(nums, k-1)

```cpp
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
```

### Summary Table

| Approach       | Time Complexity | Space Complexity |
| -------------- | --------------- | ---------------- |
| Naive          | O(N²)           | O(N)             |
| Sliding Window | O(N)            | O(N)             |

---

### Forget the fear of sliding window now. Practice these and you will have one less topic to worry about.

- Count Number of Nice Subarrays
- Longest Substring with At Most K Distinct Characters
- Number of Substrings Containing All Three Characters
- Replace the Substring for Balanced String
- Max Consecutive Ones III
- Binary Subarrays With Sum
- Subarrays with K Different Integers
- Fruit Into Baskets
- Shortest Subarray with Sum at Least K
- Minimum Size Subarray Sum
