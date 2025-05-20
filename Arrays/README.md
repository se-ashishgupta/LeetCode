# Arrays Coding Problems Collection

## Table of Contents

- [1. Two Sum(1)](#two-sum)
- [2. Sort Colors(75)](#sort-colors)
- [3. Majority Element(169)](#majority-element)
- [4. Maximum Sum Subarray(53)](#maximum-sum-subarray)
- [5. Best Time to Buy and Sell Stock(121)](#best-time-to-buy-and-sell-stock)
- [6. Rearrange Array Elements by Sign(2149)](#rearrange-array-elements-by-sign)
- [7. Next Permutation(31)](#next-permutation)

##### Hash Table and Prefix Sum

- [8. Subarray Sum Equals K(560)](#subarray-sum-equals-k)
- [9. Contiguous Array(525)](#contiguous-array)
- [10. Count Number of Nice Subarrays(1248)](#count-number-of-nice-subarrays)

---

## Two Sum

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

## Sort Colors

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

## Rearrange Array Elements by Sign

### Problem Statement

Given an array `nums` containing **equal numbers of positive and negative integers**, rearrange them such that:

1. **Alternating sign order** (positive at even indices, negative at odd indices)
2. **Preserve the original relative order** of positives and negatives

### Example

```
Input: [3, 1, -2, -5, 2, -4]
Output: [3, -2, 1, -5, 2, -4]
```

### Approach 1: Using Extra Arrays

- **Time Complexity**: O(n)
- **Space Complexity**: O(n)

#### Logic

1. Separate positives and negatives into two separate arrays
2. Merge them back into the result in alternating order

```cpp
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
```

### Approach 2: Using Single Result Array (Optimal)

- **Time Complexity**: O(n)
- **Space Complexity**: O(n)

#### Logic

1. Create a result array of the same size as input
2. Maintain two pointers:
   - `pos`: points to even indices (0, 2, 4, ...) for positive numbers
   - `neg`: points to odd indices (1, 3, 5, ...) for negative numbers
3. In a single pass through the array, place positive and negative numbers at their respective positions

```cpp
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
```

---

## Next Permutation

### Problem Statement

Implement **nextPermutation**, which rearranges numbers into the **lexicographically next greater permutation** of numbers. If such an arrangement is not possible, it must rearrange it as the lowest possible order (i.e., sorted in ascending order). The replacement must be **in-place** and use only constant extra memory.

### Examples

```
Example 1:
Input: nums = [1,2,3]
Output: [1,3,2]

Example 2:
Input: nums = [3,2,1]
Output: [1,2,3]

Example 3:
Input: nums = [1,1,5]
Output: [1,5,1]
```

### Approach 1: Brute Force (Not Practical)

- **Time Complexity**: O(N!)
- **Space Complexity**: O(N)

#### Logic

1. Generate all permutations of the array
2. Sort them
3. Return the one that comes just after the current permutation

This approach is extremely inefficient for large arrays and not suitable for interviews.

### Approach 2: Optimal Algorithm

- **Time Complexity**: O(N)
- **Space Complexity**: O(1)

#### Logic

1. Traverse from the end and find the first index `idx` such that nums[idx] < nums[idx + 1] (This means the suffix after idx is in descending order)
2. If no such index is found, the entire array is the highest permutation — reverse to get lowest
3. Find the smallest element in the suffix that is greater than nums[idx]
4. Swap them
5. Reverse the suffix (to get the next smallest lexicographic permutation)

```cpp
void nextPermutation(vector<int> &nums)
{
    int n = nums.size();

    // Step 1: Find the first decreasing element from the end
    int idx = -1;
    for (int i = n - 1; i > 0; i--)
    {
        if (nums[i] > nums[i - 1])
        {
            idx = i - 1;
            break;
        }
    }

    // Step 2: If no such index is found, array is in descending order
    if (idx == -1)
    {
        reverse(begin(nums), end(nums));
        return;
    }

    // Step 3: Find element just greater than nums[idx] from the end
    int swap_idx = idx;
    for (int i = n - 1; i > idx; i--)
    {
        if (nums[i] > nums[idx])
        {
            swap_idx = i;
            break;
        }
    }

    // Step 4: Swap and reverse the suffix
    swap(nums[idx], nums[swap_idx]);
    reverse(nums.begin() + idx + 1, nums.end());
}
```

### Key Observations

1. **Descending Order Property**:

   - The suffix (rightmost part of the array) after `idx` is sorted in descending order
   - This means the largest values are at the end, and no next greater permutation is possible unless we swap

2. **Selecting the Smallest Larger Element**:
   - Since the suffix is in descending order, the first element (from right to left) that is greater than nums[idx] is the smallest such element — making it the ideal candidate for the next permutation

### Summary Table

| Approach           | Time Complexity | Space Complexity |
| ------------------ | --------------- | ---------------- |
| Brute Force        | O(N!)           | O(N)             |
| Optimal (In-Place) | O(N)            | O(1)             |

---

## Subarray Sum Equals K

### Problem Statement

Given an array `nums` and an integer `k`, return the total number of continuous subarrays whose sum equals to `k`.

### Example

```
Input: nums = [1, 2, 3, 4, 5], k = 5
Output: 2
Explanation: Subarrays [2, 3] and [5] have sum 5.
```

### Approach 1: Brute Force

- **Time Complexity**: O(N²)
- **Space Complexity**: O(1)

#### Logic

1. Use two nested loops to consider all possible subarrays
2. For each subarray, compute the sum and check if it equals `k`
3. Increment the counter if the sum equals `k`

```cpp
int subArraySumEqualsKNaive(vector<int> &nums, int k)
{
    int n = nums.size();
    int res = 0;
    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = i; j < n; j++)
        {
            sum += nums[j];
            if (sum == k)
            {
                res++; // Found a subarray with sum equal to k
            }
        }
    }
    return res;
}
```

### Approach 2: Prefix Sum with HashMap (Optimal)

- **Time Complexity**: O(N)
- **Space Complexity**: O(N)

#### Logic

1. Use a hashmap to store prefix sums and their frequencies
2. For each index, calculate the running prefix sum
3. Check if (prefix_sum - k) exists in the map, which indicates a subarray with sum k ending at the current index
4. Use the key insight: if the sum from index 0 to i is `sum`, and (sum - k) exists in the map, then there's a subarray ending at index i with sum k

```cpp
int subArraySumEqualsKEfficient(vector<int> &nums, int k)
{
    unordered_map<int, int> preSumMap; // Stores {prefix sum -> count of occurrences}
    int res = 0;
    int sum = 0;      // Running sum
    preSumMap[0] = 1; // To handle subarrays starting from index 0

    for (int i = 0; i < nums.size(); i++)
    {
        sum += nums[i]; // Update running sum

        int rem = sum - k; // Check if (sum - k) exists in the map

        if (preSumMap.find(rem) != preSumMap.end())
        {
            res += preSumMap[rem]; // Add the count of occurrences of (sum - k)
        }

        preSumMap[sum]++; // Increment the count of the current prefix sum
    }

    return res;
}
```

### Summary Table

| Approach            | Time Complexity | Space Complexity |
| ------------------- | --------------- | ---------------- |
| Brute Force (Naive) | O(N²)           | O(1)             |
| Optimal (Hashmap)   | O(N)            | O(N)             |

### Related Problems

- Contiguous Array (LeetCode)
- Subarrays with K Different Integers (LeetCode)
- Count Number of Nice Subarrays (LeetCode)
- Binary Subarrays With Sum (LeetCode)
- Subarray Product Less Than K (LeetCode)
- Count Subarrays Where Max Element Appears at Least K Times (LeetCode)

---

## Contiguous Array

### Problem Statement

Given a binary array `nums`, find the maximum length of a contiguous subarray with an equal number of 0s and 1s.

### Example

```
Input: nums = [0, 1, 1, 1, 1, 1, 0, 0, 0]
Output: 6
Explanation: The subarray [1, 1, 1, 0, 0, 0] has equal number of 0s and 1s.
```

### Approach 1: Naive Approach

- **Time Complexity**: O(N²)
- **Space Complexity**: O(1)

#### Logic

1. Check every possible subarray
2. Count 0s and 1s for each subarray
3. If counts are equal, update maximum length

```cpp
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
```

### Approach 2: Prefix Sum with Hashmap (Optimal)

- **Time Complexity**: O(N)
- **Space Complexity**: O(N)

#### Logic

1. Replace all 0s with -1s (key insight!)
2. Calculate running sum
3. If we see the same sum twice, it means the subarray between these positions has a sum of 0
4. A sum of 0 means equal numbers of -1s and 1s (which implies equal numbers of original 0s and 1s)
5. Use a hashmap to store the first occurrence of each sum

```cpp
int contiguousArrayEfficient(vector<int> &nums)
{
    int n = nums.size();
    int res = 0;

    // Step 1: Convert 0s to -1s
    vector<int> modifiedNums = nums; // Create a copy to avoid modifying original
    for (int i = 0; i < n; i++)
    {
        if (modifiedNums[i] == 0)
            modifiedNums[i] = -1;
    }

    int sum = 0;
    unordered_map<int, int> countMap;
    countMap[0] = -1; // To handle sum = 0 case at beginning

    for (int i = 0; i < n; i++)
    {
        sum += modifiedNums[i];

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
```

### Summary Table

| Approach        | Time Complexity | Space Complexity |
| --------------- | --------------- | ---------------- |
| Naive           | O(N²)           | O(1)             |
| Optimized (Map) | O(N)            | O(N)             |

### LeetCode Problem Link

[Contiguous Array](https://leetcode.com/problems/contiguous-array/)

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
