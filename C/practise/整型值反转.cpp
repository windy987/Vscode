#include <iostream>
using namespace std;

// long long reverse(int n)
// {
// 	long long r = n % 10;
// 	while (n /= 10) r = 10 * r + n % 10;
// 	return r;
// }

// bool is_palin_num(int n)
// {
//     return reverse(n) == (long long)n;
// }

long long reverse(int n)
{
    long long r = n % 10;
    while (n /= 10)
        r = 10 * r + n % 10;
    return r;
}

int main()
{
    cout << reverse(98437);
}