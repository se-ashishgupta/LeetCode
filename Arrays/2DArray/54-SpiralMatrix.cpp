#include <iostream>
#include <vector>
using namespace std;

/*
Problem Statement:
-------------------
Print a given 2D matrix in a spiral order.

Example:
--------
Input:
[
 [1, 2, 3],
 [4, 5, 6],
 [7, 8, 9]
]

Output:
1 2 3 6 9 8 7 4 5

Naive Approach:
---------------
You could use a visited matrix and simulate directions manually — but it's inefficient (O(N^2) time and space).

Efficient Approach:
-------------------
Use four pointers to represent the current boundaries: top, bottom, left, and right.
- Traverse the matrix in 4 directions:
  - Left to Right → (top row)
  - Top to Bottom ↓ (rightmost column)
  - Right to Left ← (bottom row)
  - Bottom to Top ↑ (leftmost column)
- After completing each direction, adjust the boundaries accordingly.
- Use a direction variable (0 to 3) to keep track of the current traversal direction.

Time Complexity: O(N * M)
Space Complexity: O(1) extra (excluding result)
*/

vector<int> SpiralMatrixEfficient(vector<vector<int>> &matrix)
{
    int rows = matrix.size();
    int cols = matrix[0].size();
    vector<int> res;

    int top = 0, left = 0;
    int bottom = rows - 1, right = cols - 1;

    int dir = 0;

    // dir = 0 -- left -> right
    // dir = 1 -- top -> down
    // dir = 2 -- right -> left
    // dir = 3 -- down -> top

    while (top <= bottom && left <= right)
    {
        if (dir == 0)
        {
            // Left to Right
            for (int i = left; i <= right; i++)
            {
                res.push_back(matrix[top][i]);
            }
            top++;
        }
        else if (dir == 1)
        {
            // Top to Bottom
            for (int i = top; i <= bottom; i++)
            {
                res.push_back(matrix[i][right]);
            }
            right--;
        }
        else if (dir == 2)
        {
            // Right to Left
            for (int i = right; i >= left; i--)
            {
                res.push_back(matrix[bottom][i]);
            }
            bottom--;
        }
        else if (dir == 3)
        {
            // Bottom to Top
            for (int i = bottom; i >= top; i--)
            {
                res.push_back(matrix[i][left]);
            }
            left++;
        }

        // Move to next direction
        dir = (dir + 1) % 4;
    }

    return res;
}

int main()
{
    vector<vector<int>> matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    vector<int> res = SpiralMatrixEfficient(matrix);

    cout << "Spiral Order: ";
    for (int x : res)
    {
        cout << x << " ";
    }

    return 0;
}

/*
Summary Table:
------------------------------------------------------
| Approach            | Time Complexity | Space Complexity |
|---------------------|-----------------|------------------|
| Naive (visited)     | O(N * M)        | O(N * M)         |
| Efficient (4 Pointers) | O(N * M)    | O(1) extra        |
------------------------------------------------------
*/
