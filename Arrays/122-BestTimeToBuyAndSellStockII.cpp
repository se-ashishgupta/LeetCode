#include <iostream>
#include <vector>
using namespace std;

/*
Problem Statement:
-------------------
You are given an array `arr` where each element represents the stock price on a given day.
You may complete as many transactions as you like (buy one and sell one share of the stock multiple times).
However, you must sell the stock before you buy again.

Your task is to find the maximum profit that can be made.

Example 1:
----------
Input: arr = [1, 5, 3, 8, 12]
Output: 13
Explanation:
- Buy at 1, sell at 5 → Profit = 4
- Buy at 3, sell at 12 → Profit = 9
- Total Profit = 4 + 9 = 13

Example 2:
----------
Input: arr = [7, 6, 4, 3, 1]
Output: 0
Explanation: Prices are always decreasing, so no transaction is done.

Example 3:
----------
Input: arr = [7, 6, 4, 3, 10]
Output: 7
Explanation:
- Buy at 3, sell at 10 → Profit = 7
*/

/*
Naive Approach:
---------------
1. Consider all possible buy-sell pairs (i < j) and calculate the profit for each.
2. Use recursion to explore:
   - Not doing any transaction
   - Doing a transaction from i to j and then solving the remaining subarray
3. Return the maximum of all possibilities.

Time Complexity: O(N^2)  (because we check all pairs and recursively process)
Space Complexity: O(1)   (no extra space used, ignoring recursion stack)
*/

int stockBuySellIINaive(const vector<int> &arr)
{
    int n = arr.size();
    int profit = 0;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] > arr[i])
            {
                int curr_profit = arr[j] - arr[i] + stockBuySellIINaive(vector<int>(arr.begin() + j + 1, arr.end()));
                profit = max(profit, curr_profit);
            }
        }
    }
    return profit;
}

/*
Optimized Approach:
-------------------
1. Traverse the array from day 1 to day n-1.
2. If the current day's price is higher than the previous day's price,
   add the difference to the result (this simulates buying at previous day's price and selling at current day's price).
3. Continue until the end to accumulate profit from all increasing segments.

Time Complexity: O(N)
Space Complexity: O(1)
*/

int stockBuySellIIEfficient(vector<int> &arr)
{
    int n = arr.size();
    int res = 0;

    // Step 1: Accumulate profit from all increasing segments
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > arr[i - 1])
        {
            res += arr[i] - arr[i - 1];
        }
    }

    return res;
}

int main()
{
    // Example stock prices array
    vector<int> stocks{7, 6, 4, 3, 10};

    // Call the naive solution and print the result
    cout << "Naive Solution: " << stockBuySellIINaive(stocks) << endl;

    // Call the efficient solution and print the result
    cout << "Efficient Solution: " << stockBuySellIIEfficient(stocks) << endl;

    return 0;
}

/*
Summary Table:
------------------------------------------------------
| Approach           | Time Complexity | Space Complexity |
|--------------------|-----------------|------------------|
| Naive              | O(N^2)          | O(1)*            |
| Efficient          | O(N)            | O(1)             |
------------------------------------------------------
*Recursion stack space may add extra memory usage for Naive.
*/
