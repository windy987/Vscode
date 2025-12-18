// 定义Point类，有成员变量X、Y，为其定义友元函数实现重载+。
// 要求重载 Point + int、int + Point、Point + Point三种加法和输出<<运算符，
// 无输入
// 程序的输出：
// Point(10, 10)
// Point(15, 15)
// Point(25, 25)
// Point(50, 50)
// 并且包含以下代码：
#include <iostream>
using namespace std;

class Point
{
private:
    int X, Y;

public:
    Point(int x, int y) : X(x), Y(y) {}
    friend Point operator+(Point p, int a)
    {
        return Point(p.X + a, p.Y + a);
    }
    friend Point operator+(int a, Point p)
    {
        return Point(p.X + a, p.Y + a);
    }
    friend Point operator+(Point a, Point b)
    {
        return Point(a.X + b.X, a.Y + b.Y);
    }
    friend ostream &operator<<(ostream &os, const Point &p)
    {
        os << "(" << p.X << ", " << p.Y << ")";
        return os;
    };
};
int main()
{
    Point pt(10, 10);
    // pt.Print();
    cout << "Point" << pt << endl;
    pt = pt + 5; // Point + int
    cout << "Point" << pt << endl;
    pt = 10 + pt; // int + Point
    cout << "Point" << pt << endl;
    pt = pt + pt;                  // Point + Point
    cout << "Point" << pt << endl; //<<运算符重载
}
