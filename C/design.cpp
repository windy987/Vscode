// 设某企业，主要有四类人员：经理、兼职技术人员、销售经理和兼职推销员。
// 现在，需要存储这些人员的档案信息（如：姓名、编号、级别、当月薪水等信息）
// 计算公司月薪总额、利润以及个人业绩排名等信息。
// 系统要求功能：
// 1.能从屏幕上读取员工信息并将其写入数据文件中，人员编号在生成员工信息时同时生成，
// 每输入一个人员，人员信息编号顺序加 1。
// 2.能将指定信息从文件中删除。
// 3.能按姓名或者编号显示、查找、增加、删除和保存各类人员的信息。
// 4.可以统计全部员工总工资及各类员工工资占比。
// 5.程序对所有人员有提升级别的功能。
// 6.要求有错误提示功能，如性别只能输入“男”“女”，输入错误需重新输入；
// 如果检索不到相应信息应提示用户。
// 7.月薪计算方法：
// -经理拿固定月薪；
// -兼职技术人员按工作小时数领取月薪；
// -兼职推销员的报酬按推销员当月销售额度提成；
// -销售经理既拿固定月薪也领取销售提成。
// 8.根据需要添加的其他功能，如：用户管理、员工生日提醒、员工转正提醒等功能。

// 输错职务、性别后重新输入
// 用户输入内容前加上>符号用于区分，加一些换行是交互界面更整洁
// 加一个退出程序的选项
// 添加成功删除成员信息

#include <iostream>
using namespace std;

// 员工基类
class Employee
{
private:
    string name;
    static int id;
    int idVal;
    string sex;
    int grade;

public:
    Employee(string name, string sex, int grade)
    {
        idVal = ++id;
        this->name = name;
        this->sex = sex;
        this->grade = grade;
    }
    virtual ~Employee() = default;
    string get_name() { return name; }
    int get_id() { return idVal; }
    string get_sex() { return sex; }
    int get_grade() { return grade; }
    virtual int get_salary() = 0;
    virtual string get_role() = 0;
    virtual void promote() = 0;
    virtual void printInfo()
    {
        cout << "姓名：" << name << "\n"
             << "id：" << idVal << "\n"
             << "性别：" << sex << "\n"
             << "级别：" << grade << endl;
    }
};

int Employee::id = 1000;

// 技术人员
class Technician : public Employee
{
private:
    int workHours;
    int hourRate;

public:
    Technician(string name, string sex, int grade, int workHours, int hourRate)
        : Employee(name, sex, grade)
    {
        this->workHours = workHours;
        this->hourRate = hourRate;
    }
    int get_workHours() { return workHours; }
    int get_hourRate() { return hourRate; }
    int get_salary() override { return workHours * hourRate; }
    string get_role() override { return "Technician"; }
    void printInfo() override
    {
        cout << "职务：技术人员" << endl;
        Employee::printInfo();
        cout << "工作时间：" << get_workHours() << "\n"
             << "每小时薪水：" << get_hourRate() << "\n"
             << "总薪水：" << get_salary() << endl;
    }
};

// 经理
class Manager : virtual public Employee
{
private:
    int fixedSalary;

public:
    Manager(string name, string sex, int grade, int fixedSalary)
        : Employee(name, sex, grade)
    {
        this->fixedSalary = fixedSalary;
    }
    int get_fixedSalary() { return fixedSalary; }
    int get_salary() override { return fixedSalary; }
    string get_role() override { return "Manager"; }
    void printInfo() override
    {
        cout << "职务：经理" << endl;
        Employee::printInfo();
        cout << "薪水：" << get_salary() << endl;
    }
};

// 销售
class Salesman : virtual public Employee
{
private:
    int salesAmount;
    float commissionRate;

public:
    Salesman(string name, string sex, int grade, int salesAmount, float commissionRate)
        : Employee(name, sex, grade)
    {
        this->salesAmount = salesAmount;
        this->commissionRate = commissionRate;
    }
    int get_salesAmount() { return salesAmount; }
    float get_commissionRate() { return commissionRate; }
    int get_salary() override { return salesAmount * commissionRate; }
    string get_role() override { return "Salesman"; }
    void printInfo() override
    {
        cout << "职务：销售" << endl;
        Employee::printInfo();
        cout << "当月销售额：" << salesAmount << "\n"
             << "提成比例：" << commissionRate << "\n"
             << "总工资：" << get_salary() << endl;
    }
};

// 销售经理
class Salesmanager : public Manager, public Salesman
{
public:
    Salesmanager(string name, string sex, int grade, int fixedSalary, int salesAmount, float commissionRate)
        : Employee(name, sex, grade),
          Manager(name, sex, grade, fixedSalary),
          Salesman(name, sex, grade, salesAmount, commissionRate) {}
    int get_salary() override { return get_fixedSalary() + get_salesAmount() * get_commissionRate(); }
    string get_role() override { return "Salesmanager"; }
    void printInfo() override
    {
        cout << "职务：销售经理" << endl;
        Employee::printInfo();
        cout << "固定薪水：" << get_fixedSalary() << "\n"
             << "当月销售额：" << get_salesAmount() << "\n"
             << "提成比例：" << get_commissionRate() << "\n"
             << "总工资：" << get_salary() << endl;
    }
};

// 动态数组类，存指针，指向各个员工对象
class EmployeeArray
{
private:
    Employee **data; // data数组存基类指针，在构造函数中动态分配内存
    int capacity;    // 容量大小
    int size;        // 数组索引

public:
    EmployeeArray(int c) : capacity(c)
    {
        data = new Employee *[capacity];
        size = 0;
    }
    ~EmployeeArray()
    {
        delete[] data;
    }
    void push()
    {
        string role; // 员工职位
        string name;
        string sex;
        int grade;
        int workHours;
        int hourRate;
        int fixedSalary;
        int salesAmount;
        float commissionRate;
        // 扩容
        if (size == capacity)
        {
            int newCap = capacity > 0 ? capacity * 2 : 1;
            Employee **newData = new Employee *[newCap];
            for (int k = 0; k < size; ++k)
                newData[k] = data[k];
            delete[] data;
            data = newData;
            capacity = newCap;
        }
        cout << "员工的职位是：";
        cin >> role;
        // 录入技术人员信息
        if (role == "技术人员" || role == "技术" || role == "jishu")
        {
            cout << "请依次输入姓名、性别、级别(1-5)、每日工作时长、每小时薪水" << endl;
            cin >> name >> sex >> grade >> workHours >> hourRate;
            Employee *p = new Technician(name, sex, grade, workHours, hourRate);
            data[size++] = p;
            // if (sex == "男" || sex == "女")
            // {
            //     Employee *p = new Technician(name, sex, grade, workHours, hourRate);
            //     data[size++] = p;
            // }
            // else
            //     cout << "性别输入错误" << endl;
        }
        // 录入经理信息
        else if (role == "经理" || role == "jingli")
        {
            cout << "请依次输入姓名、性别、级别(1-5)、固定月薪" << endl;
            cin >> name >> sex >> grade >> fixedSalary;
            Employee *p = new Manager(name, sex, grade, fixedSalary);
            data[size++] = p;
            // if (sex == "男" || sex == "女")
            // {
            //     Employee *p = new Manager(name, sex, grade, fixedSalary);
            //     data[size++] = p;
            // }
            // else
            //     cout << "性别输入错误" << endl;
        }
        // 录入销售信息
        else if (role == "销售" || role == "销售员" || role == "销售人员" || role == "xiaoshou")
        {
            cout << "请依次输入姓名、性别、级别(1-5)、当月销售额、提成比例" << endl;
            cin >> name >> sex >> grade >> salesAmount >> commissionRate;
            Employee *p = new Salesman(name, sex, grade, salesAmount, commissionRate);
            data[size++] = p;
            // if (sex == "男" || sex == "女")
            // {
            //     Employee *p = new Salesman(name, sex, grade, salesAmount, commissionRate);
            //     data[size++] = p;
            // }
            // else
            //     cout << "性别输入错误" << endl;
        }
        // 录入销售经理信息
        else if (role == "销售经理" || role == "xiaoshoujingli")
        {
            cout << "请依次输入姓名、性别、级别(1-5)、固定月薪、当月销售额、提成比例" << endl;
            cin >> name >> sex >> grade >> fixedSalary >> salesAmount >> commissionRate;
            Employee *p = new Salesmanager(name, sex, grade, fixedSalary, salesAmount, commissionRate);
            data[size++] = p;
            // if (sex == "男" || sex == "女")
            // {
            //     Employee *p = new Salesmanager(name, sex, grade, fixedSalary, salesAmount, commissionRate);
            //     data[size++] = p;
            // }
            // else
            //     cout << "性别输入错误" << endl;
        }
        else
            cout << "职位输入错误" << endl;
    }
    void lookup_name()
    {
        string name;
        cout << "请输入要查询的员工的姓名：";
        cin >> name;
        int idx = -1;
        for (int k = 0; k < size; k++)
        {
            if (data[k]->get_name() == name)
            {
                idx = k;
                break;
            }
        }
        if (idx == -1)
        {
            cout << "未找到此员工" << endl;
            return;
        }
        data[idx]->printInfo();
    }
    void lookup_id()
    {
        int id;
        cout << "请输入要查询的员工的id：";
        cin >> id;
        int idx = -1;
        for (int k = 0; k < size; k++)
        {
            if (data[k]->get_id() == id)
            {
                idx = k;
                break;
            }
        }
        if (idx == -1)
        {
            cout << "未找到此员工" << endl;
            return;
        }
        data[idx]->printInfo();
    }
    void remove_by_name()
    {
        string name;
        cout << "请输入要删除的员工的名字：";
        cin >> name;
        int idx = -1;
        for (int k = 0; k < size; k++)
        {
            if (data[k]->get_name() == name)
            {
                idx = k;
                delete data[idx];
                for (int i = idx; i < size - 1; i++)
                    data[i] = data[i + 1];
                size--;
            }
        }
        if (idx == -1)
        {
            cout << "未找到此员工" << endl;
            return;
        }
    }
    void remove_by_id()
    {
        int id;
        cout << "请输入要删除的员工的id：";
        cin >> id;
        int idx = -1;
        for (int k = 0; k < size; k++)
        {
            if (data[k]->get_id() == id)
            {
                idx = k;
                delete data[idx];
                for (int i = idx; i < size - 1; i++)
                    data[i] = data[i + 1];
                size--;
            }
        }
        if (idx == -1)
        {
            cout << "未找到此员工" << endl;
            return;
        }
    }
    void list_all_employees()
    {
        cout << "所有员工罗列如下：" << endl;
        for (int i = 0; i < size; i++)
        {
            data[i]->printInfo();
            cout << "\n";
        }
    }
    void salary_count_display()
    {
        int salary_amount = 0;
        float salary_Technician = 0;
        float salary_Manager = 0;
        float salary_Salesman = 0;
        float salary_Salesmanager = 0;
        for (int i = 0; i < size; i++)
        {
            salary_amount += data[i]->get_salary();
            if (data[i]->get_role() == "Technician")
                salary_Technician += data[i]->get_salary();
            else if (data[i]->get_role() == "Manager")
                salary_Manager += data[i]->get_salary();
            else if (data[i]->get_role() == "Salesman")
                salary_Salesman += data[i]->get_salary();
            else if (data[i]->get_role() == "Salesmanager")
                salary_Salesmanager += data[i]->get_salary();
        }
        cout << "所有员工的总工资为：" << salary_amount << "\n"
             << "技术人员的总工资占比为：" << salary_Technician / salary_amount << "\n"
             << "所有经理的总工资占比为：" << salary_Manager / salary_amount << "\n"
             << "所有销售的总工资占比为：" << salary_Salesman / salary_amount << "\n"
             << "所有销售经理的总工资占比为：" << salary_Salesmanager / salary_amount << endl;
    }
};

int main()
{
    EmployeeArray e(1);
    while (1)
    {
        int i;
        cout << "要录入员工信息请按1" << endl;
        cout << "按名字查询员工信息请按2" << endl;
        cout << "按id查询员工信息请按3" << endl;
        cout << "按名字删除员工信息请按4" << endl;
        cout << "按id删除员工信息请按5" << endl;
        cout << "罗列所有员工信息请按6" << endl;
        cout << "计算并展示工资占比情况请按7" << endl;
        cin >> i;
        switch (i)
        {
        case 1:
            int i;
            cout << "要录入几个员工？";
            cin >> i;
            while (i--)
                e.push();
            break;
        case 2:
            e.lookup_name();
            break;
        case 3:
            e.lookup_id();
            break;
        case 4:
            e.remove_by_name();
            break;
        case 5:
            e.remove_by_id();
            break;
        case 6:
            e.list_all_employees();
            break;
        case 7:
            e.salary_count_display();
            break;
        default:
            break;
        }
        cout << "----------------------------" << endl;
    }
}
