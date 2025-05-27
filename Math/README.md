# Maths Coding Problems Collection

## Table of Contents

### Problems

- [1. Divisibility Difference(2894)](#divisibility-difference)

---

# Problems

## Divisibility Difference

### Problem Statement

Given two integers n and m, return the difference between:

- The sum of all positive integers less than or equal to n that are **not divisible by m**, and
- The sum of all positive integers less than or equal to n that **are divisible by m**.

Mathematically:

```
Result = (Sum of i for i in 1..n if i % m != 0) - (Sum of i for i in 1..n if i % m == 0)
```

### Example

```
Input: n = 10, m = 3
All numbers ≤ 10: 1 2 3 4 5 6 7 8 9 10
Divisible by 3: 3, 6, 9 → sum = 18
Not divisible by 3: 1, 2, 4, 5, 7, 8, 10 → sum = 37
Output = 37 - 18 = 19
```

### Approach 1: Naive Solution

- **Time Complexity**: O(n)
- **Space Complexity**: O(1)

#### Logic

1. Iterate from 1 to n
2. Add to one sum if divisible by m, otherwise to the other sum
3. Return the difference between non-divisible sum and divisible sum

```cpp
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
```

### Approach 2: Mathematical Formula (Optimal)

- **Time Complexity**: O(1)
- **Space Complexity**: O(1)

#### Logic

1. Calculate total sum of first n natural numbers = n \* (n + 1) / 2
2. Calculate sum of numbers divisible by m:
   - Count of multiples of m up to n = floor(n / m)
   - Sum = m _ (count _ (count + 1)) / 2 (arithmetic progression formula)
3. Non-divisible sum = total sum - divisible sum
4. Return non-divisible sum - divisible sum

```cpp
int differenceOfSumsEfficient(int n, int m)
{
    int totalSumOfN = (n * (n + 1)) / 2;

    int divisibleCount = n / m;

    int divisibleSum = m * ((divisibleCount * (divisibleCount + 1)) / 2);
    int nonDivisibleSum = totalSumOfN - divisibleSum;

    return nonDivisibleSum - divisibleSum;
}
```

### Summary Table

| Approach            | Time Complexity | Space Complexity |
| ------------------- | --------------- | ---------------- |
| Naive               | O(n)            | O(1)             |
| Optimized (Formula) | O(1)            | O(1)             |

---
