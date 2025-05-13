#include <iostream>
#include <vector>
using namespace std;

/*
Problem: Maximum Sum Subarray
- You are given an array of integers, which may include both positive and negative numbers.
- The goal is to find the maximum possible sum of a contiguous subarray.
- Example: For the array {1, 2, 3}, the maximum sum is 6 (entire array).

---

Naive Approach:
1. Use two nested loops:
   - The outer loop selects a starting index for a subarray.
   - The inner loop calculates the sum of elements from the current starting index to the end of the subarray.
2. Keep track of the maximum sum encountered (`res`).
3. Complexity:
   - **Time**: O(n²), as every possible subarray is considered.
   - **Space**: O(1), no extra space is used.
*/

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

/*
Efficient Approach: Kadane's Algorithm
1. Use a single traversal of the array to calculate the maximum sum of a subarray:
   - Maintain `maxEnding`, which represents the maximum sum of subarrays ending at the current index.
   - Update `res`, which stores the overall maximum sum encountered so far.
2. At each step:
   - Either extend the previous subarray by adding the current element, or start a new subarray with the current element.
   - Compare these two options and update `maxEnding`.
3. Complexity:
   - **Time**: O(n), as the array is traversed once.
   - **Space**: O(1), no extra space is used.
*/

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

int main()
{
    // Example array
    vector<int> arr{1, 2, 3};

    // Print the result using Kadane's algorithm
    cout << "Maximum Sum Subarray: " << kadneAlgorithm(arr) << endl;

    return 0;
}
