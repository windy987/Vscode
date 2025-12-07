#include <iostream>
#include <string.h>
using namespace std;
class Date
{
public:
    Date(int y, int m, int d) : year(y), month(m), day(d) {}
    Date(const Date &d)
    {
        year = d.year;
        month = d.month;
        day = d.day;
    }
    void display()
    {
        cout << " 出生日期为" << year << '-' << month << '-' << day << endl;
    }

private:
    int year;
    int month;
    int day;
};

class People
{
public:
    People(char na[], char nu[], char s, char i[], int y, int m, int d) : birthday(y, m, d)
    {
        strcpy(name, na);
        strcpy(number, nu);
        sex = s;
        strcpy(id, i);
    }
    People(const People &p) : birthday(p.birthday)
    {
        strcpy(name, p.name);
        strcpy(number, p.number);
        sex = p.sex;
        strcpy(id, p.id);
    }
    ~People() {}
    inline void show()
    {
        cout << "姓名：" << name << " 编号：" << number << " 性别：" << sex << " 身份证号：" << id;
        birthday.display();
    }

private:
    char name[11];
    char number[7];
    char sex;
    Date birthday;
    char id[16];
};

class Student : virtual public People
{
public:
    Student(char na[], char nu[], char s, char i[], int y, int m, int d, char cNo[])
        : People(na, nu, s, i, y, m, d)
    {
        strcpy(classNo, cNo);
    }

    void show()
    {
        People::show();
        cout << "班号：" << classNo << endl;
    }

private:
    char classNo[7];
};

class Teacher : virtual public People
{
public:
    Teacher(char na[], char nu[], char s, char i[], int y, int m, int d, char prin[], char dept[])
        : People(na, nu, s, i, y, m, d)
    {
        strcpy(principalship, prin);
        strcpy(department, dept);
    }

    void show()
    {
        People::show();
        cout << "职务：" << principalship << " 部门：" << department << endl;
    }

private:
    char principalship[11];
    char department[21];
};

class Graduate : public Student
{
public:
    Graduate(char na[], char nu[], char s, char i[], int y, int m, int d, char cNo[], char sub[], Teacher adv)
        : People(na, nu, s, i, y, m, d), Student(na, nu, s, i, y, m, d, cNo), adviser(adv)
    {
        strcpy(subject, sub);
    }

    void show()
    {
        cout << "研究生信息" << endl;
        Student::show();
        cout << "专业：" << subject << endl;
        cout << "导师信息：" << endl;
        adviser.show();
    }

private:
    char subject[21];
    Teacher adviser;
};

class TA : public Graduate, public Teacher
{
public:
    TA(char na[], char nu[], char s, char i[], int y, int m, int d,
       char cNo[], char sub[], Teacher adv,
       char prin[], char dept[])
        : People(na, nu, s, i, y, m, d),
          Graduate(na, nu, s, i, y, m, d, cNo, sub, adv),
          Teacher(na, nu, s, i, y, m, d, prin, dept)
    {
    }

    void show()
    {
        cout << "助教详细信息" << endl;
        Graduate::show();
        cout << "助教工作信息" << endl;
        Teacher::show();
    }
};

int main()
{
    // 1. 创建一个导师对象
    char t_na[] = "Prof.Wang";
    char t_nu[] = "T001";
    char t_s = 'M';
    char t_id[] = "11010119800101";
    char t_job[] = "Professor";
    char t_dept[] = "ComputerScience";
    Teacher adviser(t_na, t_nu, t_s, t_id, 1980, 1, 1, t_job, t_dept);

    // 2. 创建一个助教对象
    char ta_na[] = "LiMing";
    char ta_nu[] = "S2023";
    char ta_s = 'M';
    char ta_id[] = "11010120000505";
    char ta_class[] = "CS2301";
    char ta_sub[] = "AI_Research";
    char ta_job[] = "Assistant";
    char ta_dept[] = "ComputerScience";

    TA ta(ta_na, ta_nu, ta_s, ta_id, 2000, 5, 5,
          ta_class, ta_sub, adviser,
          ta_job, ta_dept);

    ta.show();

    return 0;
}