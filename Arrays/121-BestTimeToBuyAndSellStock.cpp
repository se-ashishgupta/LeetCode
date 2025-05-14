#include <iostream>
#include <vector>
using namespace std;

// Problem: Given an array of stock prices where each element represents the price of a stock on a specific day,
//          find the maximum profit you can achieve by making a single buy and a single sell.
//          If no profit can be made, return 0.
// Example: For the array {7, 1, 5, 3, 6, 4}, the maximum profit is 5 (buy at 1 and sell at 6).
// Constraints: A single transaction is allowed (buy once, sell once).

// Naive Solution: Brute Force
// Approach:
// - Iterate through all pairs of days (i, j) where i < j.
// - Calculate the profit for every possible pair of buy (i) and sell (j).
// - Keep track of the maximum profit.
// Time Complexity: O(n^2) (Nested loops for all possible pairs)
// Space Complexity: O(1) (No extra space used)
int stockBuySellNaive(vector<int> &arr)
{
    int maxProfit = 0; // Initialize maxProfit to 0
    int n = arr.size();

    // Loop through all possible buy days
    for (int i = 0; i < n; i++)
    {
        // Loop through all possible sell days after the buy day
        for (int j = i + 1; j < n; j++)
        {
            // If selling on day j yields profit, calculate it
            if (arr[j] > arr[i])
            {
                int profit = arr[j] - arr[i];       // Calculate profit
                maxProfit = max(maxProfit, profit); // Update maxProfit if current profit is higher
            }
        }
    }

    return maxProfit; // Return the maximum profit found
}

// Efficient Solution: Single Pass
// Approach:
// - Maintain the minimum stock price encountered so far (minVal).
// - For each day, calculate the profit if the stock is sold on that day (price - minVal).
// - Update the maximum profit if the current profit is higher than maxProfit.
// - Update minVal as the minimum of the current stock price and minVal.
// Time Complexity: O(n) (Single traversal of the array)
// Space Complexity: O(1) (No extra space used)
int stockBuySellEfficient(vector<int> &arr)
{
    int maxProfit = 0;   // Initialize maxProfit to 0
    int minVal = arr[0]; // Initialize minVal as the price on the first day
    int n = arr.size();

    // Traverse the array from the second day
    for (int i = 1; i < n; i++)
    {
        // Update minVal to the smallest stock price so far
        minVal = min(minVal, arr[i]);

        // Calculate profit if stock is sold on day i
        maxProfit = max(arr[i] - minVal, maxProfit); // Update maxProfit if current profit is higher
    }

    return maxProfit; // Return the maximum profit found
}

int main()
{
    // Example stock prices array
    vector<int> stocks{7, 6, 4, 3, 10};

    // Call the naive solution and print the result
    cout << "Naive Solution: " << stockBuySellNaive(stocks) << endl;

    // Call the efficient solution and print the result
    cout << "Efficient Solution: " << stockBuySellEfficient(stocks) << endl;

    return 0;
}
