#include <iostream>
using namespace std;

/*
Problem Statement:
------------------
Given two integers n and m, return the difference between:
- The sum of all positive integers less than or equal to n that are **not divisible by m**, and
- The sum of all positive integers less than or equal to n that **are divisible by m**.

Mathematically:
    Result = (Sum of i for i in 1..n if i % m != 0) - (Sum of i for i in 1..n if i % m == 0)

Example:
--------
Input: n = 10, m = 3
All numbers ≤ 10: 1 2 3 4 5 6 7 8 9 10
Divisible by 3: 3, 6, 9 → sum = 18
Not divisible by 3: 1, 2, 4, 5, 7, 8, 10 → sum = 37
Output = 37 - 18 = 19
*/

/*
Naive Approach:
---------------
- Iterate from 1 to n.
- Add to one sum if divisible by m, otherwise to the other.
- Return the difference.

Time Complexity: O(n)
Space Complexity: O(1)
*/
int differenceOfSumsNaive(int n, int m)
{
    int divSum = 0, nonDivSum = 0;
    for (int i = 1; i <= n; i++)
    {
        if (i % m == 0)
        {
            divSum += i;
        }
        else
        {
            nonDivSum += i;
        }
    }
    return nonDivSum - divSum;
}

/*
Optimized Approach:
-------------------
1. Total sum of first n natural numbers = n * (n + 1) / 2
2. Sum of numbers divisible by m up to n is:
    - Let count = floor(n / m)
    - Sum = m * (count * (count + 1)) / 2 (Sum of AP with common difference m)
3. Non-divisible sum = total sum - divisible sum
4. Return non-divisible sum - divisible sum

Time Complexity: O(1)
Space Complexity: O(1)
*/
int differenceOfSumsEfficient(int n, int m)
{
    int totalSumOfN = (n * (n + 1)) / 2;

    int divisibleCount = n / m;

    int divisibleSum = m * ((divisibleCount * (divisibleCount + 1)) / 2);
    int nonDivisibleSum = totalSumOfN - divisibleSum;

    return nonDivisibleSum - divisibleSum;
}

int main()
{
    int n = 10, m = 3;

    int res = differenceOfSumsEfficient(n, m);
    cout << "Result: " << res << endl; // Expected: 19

    return 0;
}

/*
Summary Table:
-------------------------------------------------------
| Approach           | Time Complexity | Space Complexity |
|--------------------|-----------------|------------------|
| Naive              | O(n)            | O(1)             |
| Optimized (Formula)| O(1)            | O(1)             |
-------------------------------------------------------
*/
