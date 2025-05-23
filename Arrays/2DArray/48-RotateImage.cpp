#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
Problem Statement:
------------------
Given an N x N 2D matrix representing an image, rotate the image by 90 degrees (clockwise) **in-place**.

Example:
--------
Input:
[
 [1, 2, 3],
 [4, 5, 6],
 [7, 8, 9]
]

Output:
[
 [7, 4, 1],
 [8, 5, 2],
 [9, 6, 3]
]
*/

/*
Naive Approach:
---------------
- Create a new matrix of same size.
- Fill elements from original matrix such that: result[j][n - i - 1] = matrix[i][j]
- This requires extra space.

Time Complexity: O(N^2)
Space Complexity: O(N^2)
*/

vector<vector<int>> RotateImageNaive(vector<vector<int>> &matrix)
{
    int n = matrix.size();
    vector<vector<int>> rotated(n, vector<int>(n));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            rotated[j][n - 1 - i] = matrix[i][j];
        }
    }

    return rotated;
}

/*
Efficient Approach (In-place):
------------------------------
1. Transpose the matrix: matrix[i][j] ↔ matrix[j][i]
2. Reverse every row to get the final rotated matrix.

Time Complexity: O(N^2)
Space Complexity: O(1)
*/

void RotateImageEfficient(vector<vector<int>> &matrix)
{
    int n = matrix.size();

    // Step 1: Transpose the matrix (swap across diagonal)
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            swap(matrix[i][j], matrix[j][i]);
        }
    }

    // Step 2: Reverse each row
    for (int i = 0; i < n; i++)
    {
        reverse(matrix[i].begin(), matrix[i].end());
    }
}

int main()
{
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    // Efficient in-place rotation
    RotateImageEfficient(matrix);

    cout << "Rotated Matrix:" << endl;
    for (const auto &row : matrix)
    {
        for (const auto &elem : row)
        {
            cout << elem << " ";
        }
        cout << endl;
    }

    // Optional: Output naive approach result (if needed)
    // vector<vector<int>> rotatedMatrix = RotateImageNaive(matrix);
    // Print rotatedMatrix if you wish

    return 0;
}

/*
Complexity Table:
---------------------------------------------------
| Approach        | Time Complexity | Space Complexity |
|----------------|-----------------|------------------|
| Naive          | O(N^2)          | O(N^2)           |
| Efficient (In-place) | O(N^2)     | O(1)             |
---------------------------------------------------
*/
