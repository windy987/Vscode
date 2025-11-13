#include <iostream>
using namespace std;

void push(int a[], int c, int n, int *rear)
{
    a[*rear] = c;
    *rear = (*rear + 1) % n;
}

void pop(int a[], int n, int *front)
{
    *front = (*front + 1) % n;
}

void output(int a[], int n, int front, int rear)
{
    while (front != rear)
    {
        cout << a[front] << " ";
        front = (front + 1) % n;
    }
}

int main()
{
    int n = 7;
    int a[n];
    int front = 0;
    int rear = 0;

    push(a, 7, n, &rear);
    push(a, 5, n, &rear);
    push(a, 3, n, &rear);
    push(a, 9, n, &rear);
    push(a, 2, n, &rear);
    push(a, 4, n, &rear);

    for (int i = 1; i <= 3; i++)
        pop(a, n, &front);

    push(a, 15, n, &rear);
    push(a, 18, n, &rear);

    output(a, n, front, rear);
}
