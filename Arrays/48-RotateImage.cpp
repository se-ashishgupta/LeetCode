#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
Problem Statement:
-------------------
Given a square matrix (2D vector) `nums`, rotate the image by 90 degrees clockwise.

Rules:
- You must rotate the matrix in place (without using another matrix).
- The operation should be done by transforming the matrix step by step.

Example 1:
----------
Input:
nums = [[1,2,3],
        [4,5,6],
        [7,8,9]]

Output:
nums = [[7,4,1],
        [8,5,2],
        [9,6,3]]

Example 2:
----------
Input:
nums = [[5,1,9,11],
        [2,4,8,10],
        [13,3,6,7],
        [15,14,12,16]]

Output:
nums = [[15,13,2,5],
        [14,3,4,1],
        [12,6,8,9],
        [16,7,10,11]]
*/

/*
Naive Approach:
---------------
1. Create a new matrix `rotated` of the same size.
2. For each element nums[i][j], place it at position rotated[j][n-1-i].
   - This directly gives the rotated image.
3. Copy rotated back into nums.

Time Complexity: O(N^2)
Space Complexity: O(N^2) (extra matrix used)
*/

/*
Optimized Approach (In-place):
-------------------------------
1. **Transpose the matrix**:
   - Swap elements across the diagonal (nums[i][j] ↔ nums[j][i]).
   - This converts rows into columns.
2. **Reverse each row**:
   - Reversing rows after transpose gives the final 90° rotated matrix.
3. This avoids using extra space.

Time Complexity: O(N^2)
Space Complexity: O(1)
*/

void rotateImage(vector<vector<int>> &nums)
{
    int row = nums.size();

    // Step 1: Transpose the matrix
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < i; j++)
        {
            swap(nums[i][j], nums[j][i]);
        }
    }

    // Step 2: Reverse each row
    for (auto &it : nums)
    {
        // &it is important: modifies the actual row in nums
        reverse(it.begin(), it.end());
    }
}

int main()
{
    vector<vector<int>> nums = {{1, 2, 3},
                                {4, 5, 6},
                                {7, 8, 9}};

    rotateImage(nums);

    // Print rotated matrix
    for (auto it : nums)
    {
        for (int x : it)
        {
            cout << x << " ";
        }
        cout << endl;
    }

    return 0;
}

/*
Summary Table:
------------------------------------------------------
| Approach           | Time Complexity | Space Complexity |
|--------------------|-----------------|------------------|
| Naive (Extra Mat)  | O(N^2)          | O(N^2)           |
| Optimized (In-Place)| O(N^2)         | O(1)             |
------------------------------------------------------
*/
