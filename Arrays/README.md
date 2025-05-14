# Coding Problems Collection

## Table of Contents

- [1. Two Sum(1)](#1-two-sum)
- [2. Sort Colors(75)](#2-sort-colors)
- [3. Majority Element(169)](#majority-element)
- [4. Maximum Sum Subarray(53)](#maximum-sum-subarray)
- [5. Best Time to Buy and Sell Stock(121)](#best-time-to-buy-and-sell-stock)
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

## Majority Element

### Problem Statement

Find the majority element in an array. A majority element in an array is an element that appears more than n/2 times, where n is the size of the array.

### Example

```
Input: arr = [8, 3, 4, 8, 8]
Output: 8
Explanation: 8 appears 3 times which is more than 5/2 = 2.5 times.
```

### Approach 1: Brute Force

- **Time Complexity**: O(n²)
- **Space Complexity**: O(1)

#### Logic

1. For each element, count its occurrences in the array using a nested loop
2. If any element appears more than n/2 times, return it as the majority element
3. If no such element exists, return -1

```cpp
int majorityElementNaive(vector<int> &arr)
{
    int n = arr.size(); // Size of the array

    for (int i = 0; i < n; i++) // Traverse each element
    {
        int count = 1; // Initialize count of current element

        // Count occurrences of arr[i] in the array
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] == arr[j])
            {
                count++;
            }
        }

        // If count is more than n/2, return this element
        if (count > n / 2)
        {
            return arr[i];
        }
    }

    return -1; // No majority element found
}
```

### Approach 2: Boyer-Moore Majority Voting Algorithm (Optimal)

- **Time Complexity**: O(n)
- **Space Complexity**: O(1)

#### Logic

1. **Find a Candidate**:
   - Assume the first element is the majority candidate
   - Traverse the array and keep track of a count
   - If the count reaches zero, reset the candidate to the current element
2. **Verify the Candidate**:
   - Check if the candidate actually appears more than n/2 times
   - If yes, return the candidate; otherwise, return -1

```cpp
int majorityElementEfficient(vector<int> &arr)
{
    int n = arr.size();
    int count = 1;          // Initialize count for potential majority element
    int candidate = arr[0]; // Assume first element is the majority candidate

    // Step 1: Find a candidate for the majority element
    for (int i = 1; i < n; i++)
    {
        if (arr[i] == candidate)
        {
            count++; // Increment count if same as candidate
        }
        else
        {
            count--; // Decrease count if different

            if (count == 0) // If count reaches zero, choose a new candidate
            {
                candidate = arr[i];
                count = 1;
            }
        }
    }

    // Step 2: Verify if the candidate is actually the majority element
    count = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == candidate)
        {
            count++;
        }
    }

    // If count is greater than n/2, return the candidate
    if (count > n / 2)
    {
        return candidate;
    }

    return -1; // No majority element found
}
```

---

## Maximum Sum Subarray

### Problem Statement

Given an array of integers (potentially including negative numbers), find the contiguous subarray with the largest sum.

### Examples

```
Example 1:
Input: arr = [1, 2, 3]
Output: 6
Explanation: The entire array forms the maximum sum subarray.

Example 2:
Input: arr = [-2, 1, -3, 4, -1, 2, 1, -5, 4]
Output: 6
Explanation: The subarray [4, -1, 2, 1] has the largest sum = 6.
```

### Approach 1: Naive (Brute Force)

- **Time Complexity**: O(n²)
- **Space Complexity**: O(1)

#### Logic

1. Use two nested loops to consider all possible subarrays
2. The outer loop selects the starting position
3. The inner loop calculates the sum from the starting position to each possible ending position
4. Keep track of the maximum sum encountered

```cpp
int maximumSumSubarrayNaive(vector<int> &arr)
{
    int n = arr.size(); // Size of the array
    int res = 0;        // Initialize result to 0

    // Outer loop: Start from every index
    for (int i = 0; i < n; i++)
    {
        int sum = 0; // Sum of the current subarray

        // Inner loop: Calculate the sum of subarrays starting from index i
        for (int j = i; j < n; j++)
        {
            sum += arr[j];       // Add current element to the sum
            res = max(res, sum); // Update the result if a larger sum is found
        }
    }

    return res; // Return the maximum sum
}
```

### Approach 2: Kadane's Algorithm (Optimal)

- **Time Complexity**: O(n)
- **Space Complexity**: O(1)

#### Logic

1. Use a single pass through the array
2. Maintain two variables:
   - `maxEnding`: Maximum sum of subarray ending at current position
   - `res`: Overall maximum sum found so far
3. For each element, decide whether to:
   - Extend the previous subarray by adding the current element
   - Start a new subarray beginning with the current element
4. Take the maximum of these two options

```cpp
int kadneAlgorithm(vector<int> &arr)
{
    int n = arr.size();     // Size of the array
    int maxEnding = arr[0]; // Maximum sum of subarray ending at the first element
    int res = maxEnding;    // Initialize result with the first element's value

    // Traverse the array starting from the second element
    for (int i = 1; i < n; i++)
    {
        // Update maxEnding:
        // - Either extend the previous subarray or start a new subarray with the current element.
        maxEnding = max(arr[i], maxEnding + arr[i]);

        // Update the result if a larger sum is found
        res = max(res, maxEnding);
    }

    return res; // Return the maximum sum
}
```

### Summary Table

| Approach            | Time Complexity | Space Complexity |
| ------------------- | --------------- | ---------------- |
| Naive (Brute Force) | O(n²)           | O(1)             |
| Kadane's Algorithm  | O(n)            | O(1)             |

---

## Best Time to Buy and Sell Stock

### Problem Statement

Given an array of stock prices where each element represents the price of a stock on a specific day, find the maximum profit you can achieve by making a single buy and a single sell. If no profit can be made, return 0.

### Examples

```
Example 1:
Input: prices = [7, 1, 5, 3, 6, 4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.

Example 2:
Input: prices = [7, 6, 4, 3, 1]
Output: 0
Explanation: No transactions are done as the price keeps decreasing.
```

### Approach 1: Brute Force

- **Time Complexity**: O(n²)
- **Space Complexity**: O(1)

#### Logic

1. Consider all possible pairs of buy and sell days where the buy day is before the sell day
2. Calculate profit for each pair and keep track of the maximum profit

```cpp
int stockBuySellNaive(vector<int> &arr)
{
    int maxProfit = 0; // Initialize maxProfit to 0
    int n = arr.size();

    // Loop through all possible buy days
    for (int i = 0; i < n; i++)
    {
        // Loop through all possible sell days after the buy day
        for (int j = i + 1; j < n; j++)
        {
            // If selling on day j yields profit, calculate it
            if (arr[j] > arr[i])
            {
                int profit = arr[j] - arr[i];       // Calculate profit
                maxProfit = max(maxProfit, profit); // Update maxProfit if current profit is higher
            }
        }
    }

    return maxProfit; // Return the maximum profit found
}
```

### Approach 2: Single Pass (Optimal)

- **Time Complexity**: O(n)
- **Space Complexity**: O(1)

#### Logic

1. Track the minimum price seen so far
2. For each day, calculate potential profit if selling on that day (current price - minimum price seen)
3. Update the maximum profit if the current profit is greater than the tracked maximum

```cpp
int stockBuySellEfficient(vector<int> &arr)
{
    int maxProfit = 0;   // Initialize maxProfit to 0
    int minVal = arr[0]; // Initialize minVal as the price on the first day
    int n = arr.size();

    // Traverse the array from the second day
    for (int i = 1; i < n; i++)
    {
        // Update minVal to the smallest stock price so far
        minVal = min(minVal, arr[i]);

        // Calculate profit if stock is sold on day i
        maxProfit = max(arr[i] - minVal, maxProfit); // Update maxProfit if current profit is higher
    }

    return maxProfit; // Return the maximum profit found
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
