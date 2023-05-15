#include <iostream>

using namespace std;

int main()
{
    int cur;
    cin >> cur;
    int base = cur, count = 0, count_max = 0;
    while (cur)
    {
        if (base == cur)
            count++;
        else
        {
            base = cur;
            count = 1;
        }
        count_max = max(count_max, count);
        cin >> cur;
    }

    cout << count_max;
    
}

