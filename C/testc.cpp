#include <iostream>
using namespace std;

int sum(int a = 1, int b = 2) { return a + b; }

int main()
{
    cout << sum(4, 5) << endl
         << sum(5) << endl
         << sum();
}
