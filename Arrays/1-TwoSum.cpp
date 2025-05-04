#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

/*
Problem Statement:
------------------
Given an array of integers `arr` and an integer `target`, return the **indices** of the two numbers
that add up to `target`. Assume that there is exactly one solution, and each input has unique elements.

Approach 1: Naive Solution (Brute Force)
----------------------------------------
1. Use two nested loops to check all possible pairs.
2. If the sum of `arr[i] + arr[j]` equals `target`, return `{i, j}`.
3. **Time Complexity:** O(n²) (quadratic due to nested loops).
4. **Space Complexity:** O(1) (no extra space used).
*/

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
    return {-1, -1}; // Return -1, -1 if no valid pair is found (though problem guarantees a solution)
}

/*
Approach 2: Hash Map (Efficient Solution)
------------------------------------------
1. Use an **unordered_map** to store elements and their corresponding indices.
2. Traverse the array:
   - Compute `remaining = target - arr[i]`
   - Check if `remaining` is in the map:
     - If found, return `{index of remaining, current index i}`
   - Otherwise, store `arr[i]` in the map.
3. **Time Complexity:** O(n) (each element is processed once).
4. **Space Complexity:** O(n) (hash map stores up to n elements).
*/

vector<int> twoSum(vector<int> &arr, int target)
{
    int n = arr.size();
    unordered_map<int, int> mp; // Map stores {value -> index}

    for (int i = 0; i < n; i++)
    {
        int remaining = target - arr[i]; // Calculate the value needed to reach the target

        // Check if the required value exists in the map
        if (mp.find(remaining) != mp.end())
        {
            return {mp[remaining], i}; // Found the pair, return indices
        }

        // Store the current value and its index in the map
        mp[arr[i]] = i;
    }

    return {-1, -1}; // This should never execute (as per the problem assumption)
}

int main()
{
    vector<int> arr{2, 7, 11, 15}; // Example array
    int target = 9;                // Target sum
    vector<int> result = twoSum(arr, target);

    cout << "Indices: " << result[0] << " " << result[1] << endl;

    return 0;
}
