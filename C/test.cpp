/*
点（Point）类成员如下：
（1）公有成员：
Point(float xx, float yy)   // 构造函数，初始化点的x, y坐标
float getX() const  // 返回横坐标x
float getY() const  // 返回纵坐标y
void setX(float newX)  // 重设横坐标为newX
void setY(float newY)  // 重设纵坐标为newY
（2）私有成员：
float x, y   // 点的横坐标，纵坐标
由Point类公有派生出矩形（Rectangle）类，基类Point的x,y成员作为矩形左下角的坐标，新增成员如下：
（1）公有成员：
Rectangle(float x=0.0, float y=0.0, float w=1.0, float h=1.0) // 构造函数，初始化矩形左下角坐标x, y，以及宽w和高h
void reset(float newX, float newY, float newW, float newH) // 重置矩形左下角坐标x, y，以及宽w和高h
double getCircumference() const  // 返回矩形的周长
bool isSquare() const  // 判断是否为正方形
bool isEqual(Rectangle &r) const // 判断与另一个矩形的面积是否相等
（2）私有成员：
float w, h    // 矩形的宽和高
double area, circumference  // 矩形的面积，周长

请根据上述说明，完成Point, Rectangle两个类的定义。
程序运行时，若依次输入：
0 0 2 8
1 2 4 4
则依次输出：
rect1 位置: 0, 0
周长: 20
是否正方形: 0
rect2 位置: 0, 0
周长: 4
是否正方形: 1
面积是否相等: 0
重置后:
rect2 位置: 1, 2
周长: 16
是否正方形: 1
面积是否相等: 1

注意：部分源程序已给出，仅允许在注释“Begin”和“End”之间填写内容，不得改动其他已有的任何内容。
试题程序：
*/
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

/*********Begin*********/
class Point
{
private:
    float x, y;

public:
    Point(float xx = 0.0, float yy = 0.0) : x(xx), y(yy) {}
    float getX() const { return x; }
    float getY() const { return y; }
    void setX(float newX) { x = newX; }
    void setY(float newY) { y = newY; }
};

class Rectangle : public Point
{
private:
    float w, h;
    double area, circumference;

public:
    Rectangle(float x = 0.0f, float y = 0.0f, float w = 1.0f, float h = 1.0f)
        : Point(x, y), w(w), h(h)
    {
        area = w * h;
        circumference = 2 * (w + h);
    }

    void reset(float newX, float newY, float newW, float newH)
    {
        setX(newX);
        setY(newY);
        w = newW;
        h = newH;
        area = w * h;
        circumference = 2 * (w + h);
    }

    double getCircumference() const { return circumference; }
    bool isSquare() const { return w == h; }
    bool isEqual(Rectangle &r) const { return area == r.area; }
};
/**********End**********/

int main()
{
    float x, y, w, h;
    cin >> x >> y >> w >> h;
    Rectangle rect1(x, y, w, h), rect2;
    cout << endl;
    cout << "rect1 位置: " << rect1.getX() << ", " << rect1.getY() << endl;
    cout << "周长: " << rect1.getCircumference() << endl;
    cout << "是否正方形: " << rect1.isSquare() << endl;
    cout << "rect2 位置: " << rect2.getX() << ", " << rect2.getY() << endl;
    cout << "周长: " << rect2.getCircumference() << endl;
    cout << "是否正方形: " << rect2.isSquare() << endl;
    cout << "面积是否相等: " << rect2.isEqual(rect1) << endl;
    cin >> x >> y >> w >> h;
    rect2.reset(x, y, w, h);
    cout << endl;
    cout << "重置后:" << endl;
    cout << "rect2 位置: " << rect2.getX() << ", " << rect2.getY() << endl;
    cout << "周长: " << rect2.getCircumference() << endl;
    cout << "是否正方形: " << rect2.isSquare() << endl;
    cout << "面积是否相等: " << rect2.isEqual(rect1) << endl;
    ifstream in1("7.6.1_2-1.in");
    ofstream out1("7.6.1_2-1.out");
    while (in1 >> x >> y >> w >> h)
    {
        Rectangle rect1(x, y, w, h), rect2;
        out1 << "rect1 位置: " << rect1.getX() << ", " << rect1.getY() << endl;
        out1 << "周长: " << rect1.getCircumference() << endl;
        out1 << "是否正方形: " << rect1.isSquare() << endl;
        out1 << "rect2 位置: " << rect2.getX() << ", " << rect2.getY() << endl;
        out1 << "周长: " << rect2.getCircumference() << endl;
        out1 << "是否正方形: " << rect2.isSquare() << endl;
        out1 << "面积是否相等: " << rect2.isEqual(rect1) << endl;
        in1 >> x >> y >> w >> h;
        rect2.reset(x, y, w, h);
        out1 << "重置后:" << endl;
        out1 << "rect2 位置: " << rect2.getX() << ", " << rect2.getY() << endl;
        out1 << "周长: " << rect2.getCircumference() << endl;
        out1 << "是否正方形: " << rect2.isSquare() << endl;
        out1 << "面积是否相等: " << rect2.isEqual(rect1) << endl
             << endl;
    }
    in1.close();
    out1.close();
    return 0;
}