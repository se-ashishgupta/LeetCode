# LeetoCode Coding Problems Collection

## Table of Contents

- [1. Two Sum](#1-two-sum)
  <!-- Add more problems here as you solve them -->
  <!-- - [2. Problem Name](#2-problem-name) -->
  <!-- - [3. Problem Name](#3-problem-name) -->

---

## 1. Two Sum

### Problem Statement

Given an array of integers `arr` and an integer `target`, return the **indices** of the two numbers that add up to `target`. Assume that there is exactly one solution, and each input has unique elements.

### Example

```
Input: nums = [2, 7, 11, 15], target = 9
Output: [0, 1]
Explanation: Because nums[0] + nums[1] == 9, we return [0, 1].
```

### Approach 1: Brute Force

- **Time Complexity**: O(n²)
- **Space Complexity**: O(1)

#### Logic

1. Use two nested loops to check all possible pairs
2. If the sum of `arr[i] + arr[j]` equals `target`, return `{i, j}`

```cpp
vector<int> twoSumNaive(vector<int> &arr, int target)
{
    int n = arr.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] + arr[j] == target)
            {
                return {i, j}; // Return indices of the two numbers
            }
        }
    }
    return {-1, -1}; // Return -1, -1 if no valid pair is found
}
```

### Approach 2: Hash Map (Optimal)

- **Time Complexity**: O(n)
- **Space Complexity**: O(n)

#### Logic

1. Use a hash map to store elements and their corresponding indices
2. For each element:
   - Calculate the remaining value needed (`target - current value`)
   - Check if this remaining value exists in the hash map
   - If found, return the indices of both numbers
   - Otherwise, add the current element to the hash map

```cpp
vector<int> twoSum(vector<int> &arr, int target)
{
    int n = arr.size();
    unordered_map<int, int> mp; // Map stores {value -> index}

    for (int i = 0; i < n; i++)
    {
        int remaining = target - arr[i]; // Calculate the value needed

        // Check if the required value exists in the map
        if (mp.find(remaining) != mp.end())
        {
            return {mp[remaining], i}; // Found the pair, return indices
        }

        // Store the current value and its index in the map
        mp[arr[i]] = i;
    }

    return {-1, -1}; // This should never execute (problem assumes solution exists)
}
```

---

<!-- Template for adding new problems -->
<!--
## [Problem Number]. [Problem Name]

### Problem Statement
[Describe the problem here]

### Example
```
Input:
Output:
Explanation:
```

### Approach 1: [Approach Name]
- **Time Complexity**:
- **Space Complexity**:

#### Logic
1.
2.

```cpp
// Code here
```

### Approach 2: [Approach Name]
- **Time Complexity**:
- **Space Complexity**:

#### Logic
1.
2.

```cpp
// Code here
```
-->
