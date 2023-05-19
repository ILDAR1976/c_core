#include <iostream>

using namespace std;

void main()
{
    int cur = 8;
    cout << cur % 100 << endl;
    cout << ~5 << endl;
    cout << (cur & 1) << endl;
    cout << (cur |= (1<<0)) << endl;
    cout << (cur & (1 << 3)) << endl;
    cout << (15 & (~7)) << endl;
}
