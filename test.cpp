#include <iostream>
using namespace std;

int main()
{

    int arr[] = {10, 15, 78, 96, 46};
    int first = -1, second = -1;

    for (int x : arr)
    {
        if (x > first)
        {
            second = first;
            first = x;
        }
        else
        {
            if (x > second && x < first)
            {
                second = x;
            }
        }
    }

    cout << first << second;

    return 0;
}