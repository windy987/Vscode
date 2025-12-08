#include <iostream>
using namespace std;

// 1. Shape 基类
class Shape
{
public:
    Shape() {}

    // 必须声明为 virtual 才能实现多态，题目要求返回 -1
    virtual float GetArea()
    {
        return -1;
    }

    // 必须声明为 virtual，题目要求函数体为空
    virtual void Print()
    {
    }

    // 虚析构函数（虽然题目未提，但为了代码安全性通常需要）
    virtual ~Shape() {}
};

// 2. Rectangle 类
class Rectangle : public Shape
{
private:
    float width;  // 矩形的宽
    float length; // 矩形的长

public:
    // 构造函数
    Rectangle(float l, float w) : length(l), width(w) {}

    // 计算矩形面积
    float GetArea()
    {
        return length * width;
    }

    // 题目要求的输出函数
    void Print()
    {
        cout << "矩形的长为: " << length << endl;
        cout << "矩形的宽为: " << width << endl;
        cout << "矩形的面积为: " << GetArea() << endl;
    }

    // 辅助函数：供派生类 Square 获取长度（因为 length 是 private 的）
    float GetLength()
    {
        return length;
    }
};

// 3. Circle 类
class Circle : public Shape
{
private:
    float radius; // 圆的半径

public:
    // 构造函数
    Circle(float r) : radius(r) {}

    // 计算圆的面积
    float GetArea()
    {
        return 3.14 * radius * radius;
    }

    // 题目要求的输出函数
    void Print()
    {
        cout << "圆的半径为: " << radius << endl;
        cout << "圆的面积为: " << GetArea() << endl;
    }
};

// 4. Square 类
// 利用矩形类公有派生
class Square : public Rectangle
{
public:
    // 构造函数：正方形长宽相等，传给基类 Rectangle
    Square(float l) : Rectangle(l, l) {}

    // 题目要求的输出函数
    void Print()
    {
        // 为了支持题目代码中出现的未定义变量 R，这里定义 R 为边长
        float R = GetLength();

        // 以下完全照抄题目给出的代码
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