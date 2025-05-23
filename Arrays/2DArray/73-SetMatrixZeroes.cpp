#include <iostream>
#include <vector>
using namespace std;

/*
Problem Statement:
------------------
Given an m x n matrix, if an element is 0, set its entire row and column to 0 in-place.

Example:
Input:
[
 [0,1,2,0],
 [3,4,5,2],
 [1,3,1,5]
]
Output:
[
 [0,0,0,0],
 [0,4,5,0],
 [0,3,1,0]
]

Leetcode: https://leetcode.com/problems/set-matrix-zeroes/
*/

/*
Approach 1: Brute Force (Extra matrix copy)
- Copy the matrix
- If matrix[i][j] == 0, set all cells in row i and column j of the copy to 0

Time: O(m*n)
Space: O(m*n)
*/
vector<vector<int>> setMatrixZeroesNaive(vector<vector<int>> &matrix)
{
    int rows = matrix.size();
    int cols = matrix[0].size();
    vector<vector<int>> result = matrix;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] == 0)
            {
                for (int k = 0; k < rows; k++)
                    result[k][j] = 0;
                for (int k = 0; k < cols; k++)
                    result[i][k] = 0;
            }
        }
    }

    return result;
}

/*
Approach 2: Better (Use 2 arrays to mark zero rows/columns)

Time: O(m*n)
Space: O(m+n)
*/
vector<vector<int>> setMatrixZeroesNaiveSecond(vector<vector<int>> &matrix)
{
    int rows = matrix.size();
    int cols = matrix[0].size();

    vector<int> row(rows, 1);
    vector<int> col(cols, 1);

    // Mark the rows and columns that should be zero
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (matrix[i][j] == 0)
            {
                row[i] = 0;
                col[j] = 0;
            }
        }
    }

    // Apply the zeroing
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (row[i] == 0 || col[j] == 0)
            {
                matrix[i][j] = 0;
            }
        }
    }

    return matrix;
}

/*
Approach 3: Optimal (In-place using first row and column as markers)
- Use matrix itself to store flags (in first row and column)
- Use two flags to check whether first row and column need to be zeroed

Time: O(m*n)
Space: O(1)
*/

void setMatrixZeroesOptimal(vector<vector<int>> &matrix)
{
    int rows = matrix.size();
    int cols = matrix[0].size();
    bool firstRowZero = false, firstColZero = false;

    // Check if first row needs to be zero
    for (int j = 0; j < cols; j++)
    {
        if (matrix[0][j] == 0)
        {
            firstRowZero = true;
            break;
        }
    }

    // Check if first column needs to be zero
    for (int i = 0; i < rows; i++)
    {
        if (matrix[i][0] == 0)
        {
            firstColZero = true;
            break;
        }
    }

    // Use first row and column as flags
    for (int i = 1; i < rows; i++)
    {
        for (int j = 1; j < cols; j++)
        {
            if (matrix[i][j] == 0)
            {
                matrix[i][0] = 0;
                matrix[0][j] = 0;
            }
        }
    }

    // Zero cells based on flags
    for (int i = 1; i < rows; i++)
    {
        for (int j = 1; j < cols; j++)
        {
            if (matrix[i][0] == 0 || matrix[0][j] == 0)
            {
                matrix[i][j] = 0;
            }
        }
    }

    // Zero the first row if needed
    if (firstRowZero)
    {
        for (int j = 0; j < cols; j++)
            matrix[0][j] = 0;
    }

    // Zero the first column if needed
    if (firstColZero)
    {
        for (int i = 0; i < rows; i++)
            matrix[i][0] = 0;
    }
}

int main()
{
    vector<vector<int>> matrix = {
        {0, 1, 2, 0},
        {3, 4, 5, 2},
        {1, 3, 1, 5},
    };

    setMatrixZeroesOptimal(matrix);

    cout << "Matrix after setting zeroes:\n";
    for (const auto &row : matrix)
    {
        for (const auto &elem : row)
        {
            cout << elem << " ";
        }
        cout << endl;
    }

    return 0;
}

/*
Complexity Table:
--------------------------------------------------------
| Approach               | Time Complexity | Space Complexity |
|------------------------|-----------------|------------------|
| Naive (copy matrix)    | O(m*n)          | O(m*n)           |
| Better (2 arrays)      | O(m*n)          | O(m+n)           |
| Optimal (in-place)     | O(m*n)          | O(1)             |
--------------------------------------------------------
*/
