#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

/*
Problem Statement:
-------------------
Given an array `arr` containing only 0s, 1s, and 2s,
sort the array **in-place** in linear time and constant space such that
all 0s come first, followed by all 1s, then all 2s.

This is also known as the **Dutch National Flag problem**.

Example 1:
----------
Input: arr = [2, 0, 2, 1, 1, 0]
Output: [0, 0, 1, 1, 2, 2]

Example 2:
----------
Input: arr = [2, 0, 1]
Output: [0, 1, 2]
*/

/*
Naive Approach 1 (Using sort()):
-------------------------------
- Just use the built-in sort function.
- Not optimal for interview purposes.

Time Complexity: O(N log N)
Space Complexity: O(1)
*/
void sortColorsNaive(vector<int> &arr)
{
    sort(arr.begin(), arr.end());
}

/*
Naive Approach 2 (Counting 0s, 1s, 2s):
---------------------------------------
1. Count the number of 0s, 1s, and 2s.
2. Overwrite the array using the counts.

Time Complexity: O(N)
Space Complexity: O(1)
*/
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

/*
Optimal Approach (Dutch National Flag Algorithm):
-------------------------------------------------
- Use three pointers: low, mid, high.
- Traverse the array once and place 0s to the left, 2s to the right,
  and leave 1s in the middle.

Time Complexity: O(N)
Space Complexity: O(1)
*/
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

int main()
{
    vector<int> arr = {2, 0, 2, 1, 1, 0};
    sortColorsOptimal(arr);

    cout << "Sorted Colors: ";
    for (int x : arr)
    {
        cout << x << " ";
    }

    return 0;
}

/*
Summary Table:
---------------------------------------------------
| Approach               | Time Complexity | Space Complexity |
|------------------------|-----------------|------------------|
| Naive (Built-in sort)  | O(N log N)      | O(1)             |
| Naive (Counting)       | O(N)            | O(1)             |
| Optimal (Dutch Flag)   | O(N)            | O(1)             |
---------------------------------------------------
*/
