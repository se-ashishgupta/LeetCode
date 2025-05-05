# Coding Problems Collection

## Table of Contents

- [1. Two Sum(1)](#1-two-sum)
- [2. Sort Colors(75)](#2-sort-colors)
  <!-- Add more problems here as you solve them -->
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

## 2. Sort Colors

### Problem Statement

Given an array `arr` containing only 0s, 1s, and 2s, sort the array **in-place** in linear time and constant space such that all 0s come first, followed by all 1s, then all 2s. This is also known as the **Dutch National Flag problem**.

### Examples

```
Example 1:
Input: arr = [2, 0, 2, 1, 1, 0]
Output: [0, 0, 1, 1, 2, 2]

Example 2:
Input: arr = [2, 0, 1]
Output: [0, 1, 2]
```

### Approach 1: Built-in Sort

- **Time Complexity**: O(N log N)
- **Space Complexity**: O(1)

#### Logic

Use the built-in sort function to sort the array. This is not optimal for interview purposes.

```cpp
void sortColorsNaive(vector<int> &arr)
{
    sort(arr.begin(), arr.end());
}
```

### Approach 2: Counting Sort

- **Time Complexity**: O(N)
- **Space Complexity**: O(1)

#### Logic

1. Count the number of 0s, 1s, and 2s
2. Overwrite the array using the counts

```cpp
void sortColorsNaiveSecond(vector<int> &arr)
{
    int zero = 0, one = 0, two = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] == 0)
            zero++;
        else if (arr[i] == 1)
            one++;
        else
            two++;
    }

    for (int i = 0; i < arr.size(); i++)
    {
        if (zero > 0)
        {
            arr[i] = 0;
            zero--;
        }
        else if (one > 0)
        {
            arr[i] = 1;
            one--;
        }
        else
        {
            arr[i] = 2;
            two--;
        }
    }
}
```

### Approach 3: Dutch National Flag Algorithm (Optimal)

- **Time Complexity**: O(N)
- **Space Complexity**: O(1)

#### Logic

1. Use three pointers: low, mid, high
2. low to mid-1 segment contains all 0s
3. mid to high segment contains all 1s
4. high+1 to end segment contains all 2s
5. Traverse the array once and place elements accordingly:
   - If current element is 0, swap with low pointer element and increment both low and mid
   - If current element is 1, just increment mid
   - If current element is 2, swap with high pointer element and decrement high

```cpp
void sortColorsOptimal(vector<int> &arr)
{
    int low = 0, mid = 0, high = arr.size() - 1;

    while (mid <= high)
    {
        if (arr[mid] == 0)
        {
            swap(arr[low], arr[mid]);
            low++;
            mid++;
        }
        else if (arr[mid] == 1)
        {
            mid++;
        }
        else
        {
            swap(arr[mid], arr[high]);
            high--;
        }
    }
}
```

### Summary Table

| Approach              | Time Complexity | Space Complexity |
| --------------------- | --------------- | ---------------- |
| Naive (Built-in sort) | O(N log N)      | O(1)             |
| Naive (Counting)      | O(N)            | O(1)             |
| Optimal (Dutch Flag)  | O(N)            | O(1)             |

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
