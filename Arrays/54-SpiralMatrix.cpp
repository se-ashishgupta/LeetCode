#include <iostream>
#include <vector>
using namespace std;

/*
Problem Statement:
-------------------
Given a 2D matrix `nums`, return all elements of the matrix in spiral order.

Spiral order means:
- Traverse from left to right across the top row,
- Then move down the right column,
- Then traverse from right to left across the bottom row,
- Then move up the left column,
- Repeat until all elements are visited.

Example 1:
----------
Input: nums = [[1,2,3],
               [4,5,6],
               [7,8,9]]
Output: [1,2,3,6,9,8,7,4,5]

Example 2:
----------
Input: nums = [[1,2,3,4],
               [5,6,7,8],
               [9,10,11,12]]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]

*/

/*
Naive Approach:
---------------
1. Keep track of visited cells using a boolean matrix.
2. Start from (0,0) and move right → down → left → up in a loop.
3. At each step, mark visited and change direction when hitting boundary or visited cell.
4. Continue until all elements are visited.

Time Complexity: O(M*N)   (each element visited once)
Space Complexity: O(M*N)  (extra visited matrix)
*/

/*
Optimized Approach:
-------------------
1. Use four boundaries: top, bottom, left, right.
2. Traverse in four directions:
   - Left to Right (top row)
   - Top to Bottom (right column)
   - Right to Left (bottom row)
   - Bottom to Top (left column)
3. After completing one direction, shrink the corresponding boundary.
4. Repeat until boundaries overlap.

Time Complexity: O(M*N)   (each element visited once)
Space Complexity: O(1)    (excluding output array)
*/

vector<int> spiralMatrix(vector<vector<int>> &nums)
{
    int row = nums.size();
    int col = nums[0].size();

    vector<int> res;

    int top = 0, bottom = row - 1;
    int left = 0, right = col - 1;

    int dir = 0;
    // dir = 0 -> left to right
    // dir = 1 -> top to bottom
    // dir = 2 -> right to left
    // dir = 3 -> bottom to top

    while (left <= right && top <= bottom)
    {
        if (dir == 0)
        {
            // Traverse top row
            for (int i = left; i <= right; i++)
                res.push_back(nums[top][i]);
            top++;
        }
        else if (dir == 1)
        {
            // Traverse right column
            for (int i = top; i <= bottom; i++)
                res.push_back(nums[i][right]);
            right--;
        }
        else if (dir == 2)
        {
            // Traverse bottom row
            for (int i = right; i >= left; i--)
                res.push_back(nums[bottom][i]);
            bottom--;
        }
        else if (dir == 3)
        {
            // Traverse left column
            for (int i = bottom; i >= top; i--)
                res.push_back(nums[i][left]);
            left++;
        }

        // Cycle direction (0 → 1 → 2 → 3 → 0)
        dir = (dir + 1) % 4;
    }

    return res;
}

int main()
{
    vector<vector<int>> nums = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    vector<int> res = spiralMatrix(nums);

    for (int x : res)
        cout << x << " ";

    return 0;
}

/*
Summary Table:
------------------------------------------------------
| Approach           | Time Complexity | Space Complexity |
|--------------------|-----------------|------------------|
| Naive (Visited)    | O(M*N)          | O(M*N)           |
| Optimized (Bounds) | O(M*N)          | O(1)             |
------------------------------------------------------
*/
