# Sliding Window Coding Problems Collection

## Table of Contents

### Patterns

- [1. At Most K Subarrays](#at-most-k-subarrays)

### Problems

- [1. Subarrays with K Different Integers(992)](#subarrays-with-k-different-integers)
- [2. Count Number of Nice Subarrays(1248)](#count-number-of-nice-subarrays)
- [3. Max Consecutive Ones III(1004)](#max-consecutive-ones-iii)
- [4. Binary Subarrays With Sum(930)](#binary-subarrays-with-sum)

---

# Patterns

## At Most K Subarrays

**"At Most K" Subarrays** (also called the **Variable Sliding Window** or **Prefix Inclusion-Exclusion Technique**)

🔹 **Core Idea:**
To count subarrays with **exactly** `K` distinct properties (like odd numbers, distinct elements, etc.), you compute:
ExactlyK(k) = AtMost(k) − AtMost(k−1)

This transforms a difficult **exact count** problem into two simpler **at-most** problems.

🔹 **Where This Pattern Applies:**

- Counting subarrays with **exactly K odd numbers**
- Counting subarrays with **exactly K distinct integers**
- Problems where **"exactly K"** conditions are hard to maintain in one pass

🔹 **Famous Leetcode Examples:**

- Leetcode 1248: Count Number of Nice Subarrays
- Leetcode 992: Subarrays with K Different Integers
- Leetcode 340: Longest Substring with At Most K Distinct Characters

---

# Problems

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

## Count Number of Nice Subarrays

### Problem Statement

Given an array of integers `nums` and an integer `k`, return the number of **nice subarrays**.

A subarray is called _nice_ if it contains exactly `k` odd numbers.

**Leetcode:** https://leetcode.com/problems/count-number-of-nice-subarrays/

### Example

```
Input: nums = [1, 1, 2, 1, 1], k = 3
Output: 2
Explanation: The nice subarrays are [1, 1, 2, 1] and [1, 2, 1, 1]
```

### Approach 1: Naive (Brute Force)

- **Time Complexity**: O(N²)
- **Space Complexity**: O(1)

#### Logic

1. Check every possible subarray
2. Count the number of odd integers in each subarray
3. If the count equals k, increment the result counter

```cpp
int numberOfSubarraysNaive(vector<int> &nums, int k) {
    int count = 0;
    int n = nums.size();

    for (int i = 0; i < n; i++) {
        int oddCount = 0;
        for (int j = i; j < n; j++) {
            if (nums[j] & 1) // Check if odd
                oddCount++;
            if (oddCount == k)
                count++;
        }
    }

    return count;
}
```

### Approach 2: Prefix Sum + Hash Map

- **Time Complexity**: O(N)
- **Space Complexity**: O(N)

#### Logic

1. Convert array into a binary array: 1 if odd, 0 if even
2. Maintain a running sum of the binary array
3. Use a hash map to count prefix sums
4. For each current sum, check if (sum - k) exists in the map

```cpp
int numberOfSubarraysEfficient(vector<int> &nums, int k) {
    int count = 0;
    int sum = 0;
    unordered_map<int, int> prefSum;
    prefSum[0] = 1; // sum=0 appears once

    for (int x : nums) {
        sum += (x & 1); // Add 1 if odd

        int rem = sum - k;
        if (prefSum.find(rem) != prefSum.end())
            count += prefSum[rem];

        prefSum[sum]++;
    }

    return count;
}
```

### Approach 3: Sliding Window with AtMostK Trick

- **Time Complexity**: O(N)
- **Space Complexity**: O(1)

#### Logic

1. Count subarrays with at most k odd numbers
2. Subtract subarrays with at most (k-1) odd numbers
3. The difference gives the count of subarrays with exactly k odd numbers

```cpp
int atMostK(vector<int> &nums, int k) {
    int count = 0;
    int n = nums.size();
    int i = 0, j = 0;
    int oddCount = 0;

    while (j < n) {
        if (nums[j] % 2 == 1)
            oddCount++;

        while (oddCount > k) {
            if (nums[i] % 2 == 1)
                oddCount--;
            i++;
        }

        count += (j - i + 1); // Subarrays ending at j
        j++;
    }

    return count;
}

int numberOfSubarraysEfficientSecond(vector<int> &nums, int k) {
    return atMostK(nums, k) - atMostK(nums, k - 1);
}
```

### Summary Table

| Approach                   | Time Complexity | Space Complexity |
| -------------------------- | --------------- | ---------------- |
| Naive                      | O(N²)           | O(1)             |
| Efficient (Prefix Sum)     | O(N)            | O(N)             |
| Efficient (Sliding Window) | O(N)            | O(1)             |

---

## Max Consecutive Ones III

### Problem Statement

Given a binary array `nums`, you can flip at most `k` 0s to 1s. Return the maximum number of consecutive 1s in the array.

### Example

```
Input: nums = [1,1,0,0,1,1,1,0,1], k = 2
Output: 8
Explanation: Flip two 0s to get maximum 8 consecutive 1s.
```

### Approach 1: Brute Force

- **Time Complexity**: O(n²)
- **Space Complexity**: O(1)

#### Logic

1. Try all possible subarrays
2. Count zeros and ones in each subarray
3. If the number of zeros is ≤ k, update the maximum length
4. Return the maximum length found

```cpp
int maxConsecutiveOnesIIINaive(vector<int> &nums, int k) {
    int n = nums.size();
    int res = 0;

    // Try every subarray
    for (int i = 0; i < n; i++) {
        int ones = 0, zeros = 0;

        for (int j = i; j < n; j++) {
            nums[j] == 0 ? zeros++ : ones++;

            // Only consider subarrays with at most k zeroes
            if (zeros <= k) {
                res = max(res, ones + zeros);
            }
        }
    }

    return res;
}
```

### Approach 2: Sliding Window (Optimal)

- **Time Complexity**: O(n)
- **Space Complexity**: O(1)

#### Logic

1. Maintain a sliding window [i...j] with at most `k` zeros
2. Expand the right boundary (j), count zeros and ones
3. If zeros exceed k, shrink from the left (i++) until zeros ≤ k
4. Track the maximum window size throughout the process

```cpp
int maxConsecutiveOnesIIIEfficient(vector<int> &nums, int k) {
    int n = nums.size();
    int i = 0, j = 0;  // window boundaries
    int ones = 0, zeros = 0;
    int res = 0;

    // Sliding window
    while (j < n) {
        nums[j] == 0 ? zeros++ : ones++;

        // Shrink window until zeros <= k
        while (zeros > k) {
            nums[i] == 0 ? zeros-- : ones--;
            i++;
        }

        // Update max window size
        res = max(res, ones + zeros);
        j++;
    }

    return res;
}
```

### Summary Table

| Approach                 | Time Complexity | Space Complexity |
| ------------------------ | --------------- | ---------------- |
| Naive (Brute Force)      | O(n²)           | O(1)             |
| Sliding Window (Optimal) | O(n)            | O(1)             |

---

## Binary Subarrays With Sum

### Problem Statement

Given a binary array `nums` and an integer `goal`, return the number of non-empty subarrays with a sum equal to `goal`. A subarray is a contiguous part of the array.

### Examples

```
Example 1:
Input: nums = [1,0,1,0,1], goal = 2
Output: 4

Example 2:
Input: nums = [0,0,0,0,0], goal = 0
Output: 15
```

### Approach 1: Brute Force

- **Time Complexity**: O(N²)
- **Space Complexity**: O(1)

#### Logic

Use two nested loops to calculate sum of all subarrays and count how many are equal to `goal`.

```cpp
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
```

### Approach 2: Prefix Sum + HashMap

- **Time Complexity**: O(N)
- **Space Complexity**: O(N)

#### Logic

1. Use prefix sum technique with a hashmap to store frequencies of prefix sums
2. For each position, if `sum - goal` was seen before, we found subarrays that sum to `goal`
3. Initialize hashmap with `mp[0] = 1` to handle exact matches from index 0

```cpp
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
```

### Approach 3: Sliding Window (Binary Arrays Only)

- **Time Complexity**: O(N)
- **Space Complexity**: O(1)

#### Logic

1. For binary arrays only: Number of subarrays with exact sum `goal` = Number of subarrays with at most `goal` 1s - Number of subarrays with at most `goal - 1` 1s
2. Use sliding window to count subarrays with at most K ones
3. Handle edge case when goal = 0

```cpp
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

// Main function usage for sliding window approach
int numSubarraysWithSum(vector<int> &nums, int goal)
{
    if (goal == 0)
    {
        return numSubarraysWithSumAtMost(nums, goal);
    }
    else
    {
        return numSubarraysWithSumAtMost(nums, goal) - numSubarraysWithSumAtMost(nums, goal - 1);
    }
}
```

### Summary Table

| Approach                       | Time Complexity | Space Complexity | Notes                |
| ------------------------------ | --------------- | ---------------- | -------------------- |
| Brute Force                    | O(N²)           | O(1)             | Checks all subarrays |
| Prefix Sum + HashMap           | O(N)            | O(N)             | General case         |
| Sliding Window (Binary Arrays) | O(N)            | O(1)             | Only for binary nums |

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
