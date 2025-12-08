// 声明一个Shape基类，在此基础上公有派生出矩形Rectangle类和圆Circle类，
// 二者都有函数GetArea()计算对象的面积，利用矩形类公有派生一个正方形Square类。
// （1）Shape基类的公有成员为：
// Shape()：构造函数
// float GetArea()：其返回值为-1
// void Print()：输出，函数体为空
// （2）Rectangle类的公有成员为：
// Rectangle(float l, float w)：构造函数
// GetArea()：计算矩形的面积
// Print()： 输出矩形的长、宽和面积
// 私有成员为：
// float width：矩形的宽
// float length：矩形的长
// （3）Circle类的公有成员为：
// Circle(float r)：构造函数
// GetArea()：计算圆的面积
// Print()：输出圆的半径和面积
// 私有成员为：
// float radius：圆的半径
// （4）Square类的公有成员为：
// Square(float l)：构造函数
// （5）主函数中通过Shape指针sp来实现对其他派生类对象的操作。
// 矩形输出成员函数为：
// void Print()
// {
//     cout << "矩形的长为: " << length << endl;
//     cout << "矩形的宽为: " << width << endl;
//     cout << "矩形的面积为: " << GetArea() << endl;
// }
// 圆输出成员函数为：
// void Print()
// {
//     cout << "圆的半径为: " << radius << endl;
//     cout << "圆的面积为: " << GetArea() << endl;
// }
// 正方形输出成员函数为：
// void Print()
// {
//     cout << "正方形的半径为: " << R << endl;
//     cout << "正方形的面积为: " << GetArea() << endl;
// }
#include <iostream>
using namespace std;

class Shape
{
public:
    Shape() {}
    virtual float GetArea() { return -1; }
    virtual void Print() {}
};

class Rectangle : public Shape
{
private:
    float width;
    float length;

public:
    Rectangle(float l, float w) : width(w), length(l) {}
    float GetArea() { return width * length; }
    void Print()
    {
        cout << "矩形的长为: " << length << endl;
        cout << "矩形的宽为: " << width << endl;
        cout << "矩形的面积为: " << GetArea() << endl;
    }
};

class Circle : public Shape
{
private:
    float radius;

public:
    Circle(float r) : radius(r) {}
    float GetArea() { return radius * radius * 3.14159; }
    void Print()
    {
        cout << "圆的半径为: " << radius << endl;
        cout << "圆的面积为: " << GetArea() << endl;
    }
};

class Square : public Rectangle
{
private:
    float R;

public:
    Square(float l) : Rectangle(l, l), R(l) {}
    float GetArea() { return R * R; }
    void Print()
    {
        cout << "正方形的半径为: " << R << endl;
        cout << "正方形的面积为: " << GetArea() << endl;
    }
};

int main()
{
    Shape *sp1, *sp2, *sp3; // Shape类的指针
    sp1 = new Rectangle(3, 4);
    sp2 = new Circle(5);
    sp3 = new Square(2);
    cout << sp1->GetArea() << endl;
    sp1->Print();
    cout << sp2->GetArea() << endl;
    sp2->Print();
    cout << sp3->GetArea() << endl;
    sp3->Print();
    return 0;
}