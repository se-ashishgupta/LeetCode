#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
Problem Statement:
-------------------
Given an array, write a function to move all zeros to the end of the array
while maintaining the relative order of the non-zero elements.

Example:
--------
Input:  [8, 5, 0, 10, 0, 20]
Output: [8, 5, 10, 20, 0, 0]

Approach:
---------
Naive Approach:
1. Create a temporary array and store all non-zero elements in it.
2. Append zeros at the end of the temp array.
3. Copy it back to the original array.
- Time: O(n)
- Space: O(n)

Optimized Approach (In-place, no extra space):
1. Use a pointer `idx` to track the position of the next non-zero element.
2. Traverse the array.
   - If current element is non-zero, swap it with `arr[idx]` and increment `idx`.
3. By the end, all non-zeros are at the start, and zeros at the end.
- Time: O(n)
- Space: O(1)
*/

// Function to move all zeros in the array to the end (in-place)
void moveZerosToEnd(vector<int> &arr)
{
    int n = arr.size(); // Get the size of the array
    int idx = 0;        // Pointer to track the position of the next non-zero element

    // Step 1: Loop through the array
    for (int i = 0; i < n; i++)
    {
        // Step 2: If the current element is non-zero, move it to the front
        if (arr[i] != 0)
        {
            swap(arr[idx++], arr[i]); // Swap the element at 'idx' with the current element
        }
    }
    // After the loop, all non-zero elements will be moved to the front of the array
    // The zeros will naturally be pushed to the end due to the swaps
}

int main()
{
    // Example input array (with zeros in between)
    vector<int> arr = {8, 5, 0, 10, 0, 20};

    // Call the function to move zeros to the end of the array
    moveZerosToEnd(arr);

    // Step 3: Print the array after moving the zeros to the end
    for (int x : arr) // Loop through the modified array and print each element
    {
        cout << x << " "; // Print each element followed by a space
    }

    return 0; // Exit the program successfully
}

/*
Summary Table:
------------------------------------------------------
| Approach           | Time Complexity | Space Complexity |
|--------------------|-----------------|------------------|
| Naive (Extra array)| O(n)            | O(n)             |
| Optimized (In-place)| O(n)           | O(1)             |
------------------------------------------------------
*/
