/*
点（Point）类成员如下：
（1）公有成员：
Point(float xx, float yy)   // 构造函数，初始化点的x, y坐标
void setX(float newX)  // 重设横坐标为newX
void setY(float newY)  // 重设纵坐标为newY
（2）私有成员：
float x, y   // 点的横坐标，纵坐标
在此基础上，定义正方形（Square）类，其成员如下：
（1）公有成员：
Square(float x=0.0,float y=0.0,float len=1.0)  // 构造函数，初始化所有数据成员，其中(x,y)为左下角位置，len为边长
void moveTo(float newX, float newY) // 平移操作，将左下角移动到(newX, newY)
double getLen() // 返回正方形的边长
double getCircumference() // 返回正方形的周长
bool isEqual(Square &s) // 判断与另一个正方形是否大小相等
（2）私有成员：
Point p   // 正方形左下角位置
float length  // 正方形的边长
请根据上述说明，完成Point，Square两个类的定义。

注意：部分源程序给出，仅允许在注释“Begin”和“End”之间填写内容，不得改动main函数和其他已有的任何内容。
试题程序：
*/
#include <iostream>
#include <fstream>
using namespace std;

/*******Begin*******/
class Point
{
public:
	Point(float xx, float yy)
	{
		x = xx;
		y = yy;
	}; // 构造函数，初始化点的x, y坐标
	void setX(float newX) { x = newX; }; // 重设横坐标为newX
	void setY(float newY) { y = newY; }; // 重设纵坐标为newY
private:
	float x, y; // 点的横坐标，纵坐标
};
class Square
{
public:
	Square(float x = 0.0, float y = 0.0, float len = 1.0) : p(x, y), length(len) {}; // 构造函数，初始化所有数据成员，其中(x,y)为左下角位置，len为边长
	void moveTo(float newX, float newY)
	{
		p.setX(newX);
		p.setY(newY);
	}; // 平移操作，将左下角移动到(newX, newY)
	double getLen() { return length; };				  // 返回正方形的边长
	double getCircumference() { return 4 * length; }; // 返回正方形的周长
	bool isEqual(Square &s)
	{
		return length == s.length;
	}; // 判断与另一个正方形是否大小相等
private:
	Point p;	  // 正方形左下角位置
	float length; // 正方形的边长
};

/*******End*********/

int main()
{
	float x, y, len;
	cin >> x >> y >> len;
	Square s1(x, y, len), s2;
	cout << "s1 边长: " << s1.getLen() << ", 周长: " << s1.getCircumference() << endl;
	cout << "s2 边长: " << s2.getLen() << ", 周长: " << s2.getCircumference() << endl;
	cout << "是否相等: " << s2.isEqual(s1) << endl;
	cin >> x >> y;
	s2.moveTo(x, y);
	cout << "平移后:\ns1 边长: " << s1.getLen() << ", 周长: " << s1.getCircumference() << endl;
	cout << "s2 边长: " << s2.getLen() << ", 周长: " << s2.getCircumference() << endl;
	cout << "是否相等: " << s2.isEqual(s1) << endl;
	ifstream in1("4.2.3_1-1_in.dat");
	ofstream out1("4.2.3_1-1_out.dat");
	while (in1 >> x >> y >> len)
	{
		Square s1(x, y, len), s2;
		out1 << "s1 边长: " << s1.getLen() << ", 周长: " << s1.getCircumference() << endl;
		out1 << "s2 边长: " << s2.getLen() << ", 周长: " << s2.getCircumference() << endl;
		out1 << "是否相等: " << s2.isEqual(s1) << endl;
		in1 >> x >> y;
		s2.moveTo(x, y);
		out1 << "平移后:\ns1 边长: " << s1.getLen() << ", 周长: " << s1.getCircumference() << endl;
		out1 << "s2 边长: " << s2.getLen() << ", 周长: " << s2.getCircumference() << endl;
		out1 << "是否相等: " << s2.isEqual(s1) << endl
			 << endl;
	}
	in1.close();
	out1.close();
	return 0;
}