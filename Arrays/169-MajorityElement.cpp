#include <iostream>
#include <vector>
using namespace std;

/*
Problem: Majority Element in an Array
- A majority element in an array is an element that appears more than n/2 times.
- Example: In the array {8, 3, 4, 8, 8}, the majority element is 8 because it appears 3 times (which is more than 5/2 = 2.5).
*/

/*
Naive Approach:
1. Iterate through each element in the array.
2. Count how many times the current element appears in the array using a nested loop.
3. If an element appears more than n/2 times, return it as the majority element.
4. If no majority element is found, return -1.

Complexity:
- **Time**: O(n²) due to nested loops (each element's count is checked against all others).
- **Space**: O(1) since no extra space is used.
*/
int majorityElementNaive(vector<int> &arr)
{
    int n = arr.size(); // Size of the array

    for (int i = 0; i < n; i++) // Traverse each element
    {
        int count = 1; // Initialize count of current element

        // Count occurrences of arr[i] in the array
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] == arr[j])
            {
                count++;
            }
        }

        // If count is more than n/2, return this element
        if (count > n / 2)
        {
            return arr[i];
        }
    }

    return -1; // No majority element found
}

/*
Efficient Approach: Boyer-Moore Majority Voting Algorithm
1. **Find a Candidate**:
   - Assume the first element is the majority candidate.
   - Traverse the array and keep track of a count.
   - If the count reaches zero, reset the candidate to the current element.
2. **Verify the Candidate**:
   - Check if the candidate actually appears more than n/2 times.
   - If yes, return the candidate; otherwise, return -1.

Complexity:
- **Time**: O(n) (First loop finds a candidate, second loop verifies it).
- **Space**: O(1) (Only a few integer variables are used).
*/
int majorityElementEfficient(vector<int> &arr)
{
    int n = arr.size();
    int count = 1;          // Initialize count for potential majority element
    int candidate = arr[0]; // Assume first element is the majority candidate

    // Step 1: Find a candidate for the majority element
    for (int i = 1; i < n; i++)
    {
        if (arr[i] == candidate)
        {
            count++; // Increment count if same as candidate
        }
        else
        {
            count--; // Decrease count if different

            if (count == 0) // If count reaches zero, choose a new candidate
            {
                candidate = arr[i];
                count = 1;
            }
        }
    }

    // Step 2: Verify if the candidate is actually the majority element
    count = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == candidate)
        {
            count++;
        }
    }

    // If count is greater than n/2, return the candidate
    if (count > n / 2)
    {
        return candidate;
    }

    return -1; // No majority element found
}

int main()
{
    vector<int> arr{8, 3, 4, 8, 8};

    cout << "Majority Element (Efficient): " << majorityElementEfficient(arr) << endl;

    return 0;
}
