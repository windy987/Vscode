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

// 输错职务、性别后重新输入 ~
// 用户输入内容前加上>符号用于区分，加一些换行是交互界面更整洁 ~
// 加一个退出程序的选项 ~
// 添加成功删除成员信息 ~

#include <iostream>
#include <fstream>
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
    int birthMonth;
    int birthDay;

public:
    Employee(string name, string sex, int grade, int bm = 0, int bd = 0)
    {
        idVal = ++id;
        this->name = name;
        this->sex = sex;
        this->grade = grade;
        birthMonth = bm;
        birthDay = bd;
    }
    virtual ~Employee() = default;
    string get_name() { return name; }
    int get_id() { return idVal; }
    string get_sex() { return sex; }
    int get_grade() { return grade; }
    int get_birthMonth() { return birthMonth; }
    int get_birthDay() { return birthDay; }
    virtual int get_salary() = 0;
    virtual string get_role() = 0;
    void grade_up() { grade++; }
    virtual void promote() = 0;
    virtual void printInfo()
    {
        cout << "姓名：" << name << "\n"
             << "id：" << idVal << "\n"
             << "性别：" << sex << "\n"
             << "级别：" << grade << "\n"
             << "生日：" << birthMonth << "月" << birthDay << "日" << endl; // 显示生日
    }

    // 新增：由对象负责将自身写入文件（多态）
    virtual void save(ofstream &out) = 0;
};

int Employee::id = 1000;

// 技术人员
class Technician : public Employee
{
private:
    int workHours;
    int hourRate;

public:
    Technician(string name, string sex, int grade, int workHours, int hourRate, int bm = 0, int bd = 0)
        : Employee(name, sex, grade, bm, bd)
    {
        this->workHours = workHours;
        this->hourRate = hourRate;
    }
    int get_workHours() { return workHours; }
    int get_hourRate() { return hourRate; }
    int get_salary() override { return workHours * hourRate; }
    void add_hourRate() { hourRate += 100; }
    string get_role() override { return "Technician"; }
    void promote() override
    {
        if (get_grade() < 5)
        {
            grade_up();
            add_hourRate();
            cout << "已提升级别为" << get_grade() << ",时薪增加100为" << get_hourRate() << endl;
        }
        else
            cout << "级别已最高" << endl;
    }
    void printInfo() override
    {
        cout << "职务：技术人员" << endl;
        Employee::printInfo();
        cout << "工作时间：" << get_workHours() << "\n"
             << "每小时薪水：" << get_hourRate() << "\n"
             << "总薪水：" << get_salary() << endl;
    }

    // 实现 save
    void save(ofstream &out) override
    {
        out << "Technician" << ' ' << get_name() << ' ' << get_sex() << ' ' << get_grade() << ' '
            << workHours << ' ' << hourRate << ' '
            << get_birthMonth() << ' ' << get_birthDay() << '\n';
    }
};

// 经理
class Manager : virtual public Employee
{
private:
    int fixedSalary;

public:
    Manager(string name, string sex, int grade, int fixedSalary, int bm = 0, int bd = 0)
        : Employee(name, sex, grade, bm, bd)
    {
        this->fixedSalary = fixedSalary;
    }
    int get_fixedSalary() { return fixedSalary; }
    int get_salary() override { return fixedSalary; }
    void add_fixedSalary() { fixedSalary += 10000; }
    string get_role() override { return "Manager"; }
    void promote() override
    {
        if (get_grade() < 5)
        {
            grade_up();
            add_fixedSalary();
            cout << "已提升级别为" << get_grade() << ",固定薪资增加10000为" << get_fixedSalary() << endl;
        }
        else
            cout << "级别已最高" << endl;
    }
    void printInfo() override
    {
        cout << "职务：经理" << endl;
        Employee::printInfo();
        cout << "薪水：" << get_salary() << endl;
    }

    // 实现 save
    void save(ofstream &out) override
    {
        out << "Manager" << ' ' << get_name() << ' ' << get_sex() << ' ' << get_grade() << ' '
            << fixedSalary << ' ' << get_birthMonth() << ' ' << get_birthDay() << '\n';
    }
};

// 销售
class Salesman : virtual public Employee
{
private:
    int salesAmount;
    float commissionRate;

public:
    Salesman(string name, string sex, int grade, int salesAmount, float commissionRate, int bm = 0, int bd = 0)
        : Employee(name, sex, grade, bm, bd)
    {
        this->salesAmount = salesAmount;
        this->commissionRate = commissionRate;
    }
    int get_salesAmount() { return salesAmount; }
    float get_commissionRate() { return commissionRate; }
    int get_salary() override { return (int)(salesAmount * commissionRate); }
    void add_commissionRate() { commissionRate += 0.1f; }
    string get_role() override { return "Salesman"; }
    void promote() override
    {
        if (get_grade() < 5)
        {
            grade_up();
            add_commissionRate();
            cout << "已提升级别为" << get_grade() << ",提成比例增加0.1为" << get_commissionRate() << endl;
        }
        else
            cout << "级别已最高" << endl;
    }
    void printInfo() override
    {
        cout << "职务：销售" << endl;
        Employee::printInfo();
        cout << "当月销售额：" << salesAmount << "\n"
             << "提成比例：" << commissionRate << "\n"
             << "总工资：" << get_salary() << endl;
    }

    // 实现 save
    void save(ofstream &out) override
    {
        out << "Salesman" << ' ' << get_name() << ' ' << get_sex() << ' ' << get_grade() << ' '
            << salesAmount << ' ' << commissionRate << ' '
            << get_birthMonth() << ' ' << get_birthDay() << '\n';
    }
};

// 销售经理
class Salesmanager : public Manager, public Salesman
{
public:
    Salesmanager(string name, string sex, int grade, int fixedSalary, int salesAmount, float commissionRate, int bm = 0, int bd = 0)
        : Employee(name, sex, grade, bm, bd),
          Manager(name, sex, grade, fixedSalary, bm, bd),
          Salesman(name, sex, grade, salesAmount, commissionRate, bm, bd) {}
    int get_salary() override { return get_fixedSalary() + (int)(get_salesAmount() * get_commissionRate()); }
    string get_role() override { return "Salesmanager"; }
    void promote() override
    {
        if (get_grade() < 5)
        {
            grade_up();
            add_commissionRate();
            add_fixedSalary();
            cout << "已提升级别为" << get_grade() << ",提成比例增加0.1为" << get_commissionRate() << ",固定薪资增加10000为" << get_fixedSalary() << endl;
        }
        else
            cout << "级别已最高" << endl;
    }
    void printInfo() override
    {
        cout << "职务：销售经理" << endl;
        Employee::printInfo();
        cout << "固定薪水：" << get_fixedSalary() << "\n"
             << "当月销售额：" << get_salesAmount() << "\n"
             << "提成比例：" << get_commissionRate() << "\n"
             << "总工资：" << get_salary() << endl;
    }

    // 实现 save
    void save(ofstream &out) override
    {
        out << "Salesmanager" << ' ' << get_name() << ' ' << get_sex() << ' ' << get_grade() << ' '
            << get_fixedSalary() << ' ' << get_salesAmount() << ' ' << get_commissionRate() << ' '
            << get_birthMonth() << ' ' << get_birthDay() << '\n';
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
        for (int i = 0; i < size; ++i)
            delete data[i];
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
        int bm, bd; // 生日月日
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
        while (1)
        {
            cout << "员工的职位是：" << endl;
            cout << '>';
            cin >> role;

            if (role == "技术人员" || role == "技术" || role == "jishu")
            {
                cout << "请输入姓名：" << endl;
                cout << '>';
                cin >> name;

                cout << "请输入性别：" << endl;
                cout << '>';
                cin >> sex;

                cout << "请输入级别(1-5)：" << endl;
                cout << '>';
                cin >> grade;

                cout << "请输入每日工作时长：" << endl;
                cout << '>';
                cin >> workHours;

                cout << "请输入每小时薪水：" << endl;
                cout << '>';
                cin >> hourRate;

                cout << "请输入出生月：" << endl;
                cout << '>';
                cin >> bm;

                cout << "请输入出生日：" << endl;
                cout << '>';
                cin >> bd;

                Employee *p = new Technician(name, sex, grade, workHours, hourRate, bm, bd);
                data[size++] = p;
                break;
            }
            // 录入经理信息
            else if (role == "经理" || role == "jingli")
            {
                cout << "请输入姓名：" << endl;
                cout << '>';
                cin >> name;

                cout << "请输入性别：" << endl;
                cout << '>';
                cin >> sex;

                cout << "请输入级别(1-5)：" << endl;
                cout << '>';
                cin >> grade;

                cout << "请输入固定月薪：" << endl;
                cout << '>';
                cin >> fixedSalary;

                cout << "请输入出生月：" << endl;
                cout << '>';
                cin >> bm;

                cout << "请输入出生日：" << endl;
                cout << '>';
                cin >> bd;

                Employee *p = new Manager(name, sex, grade, fixedSalary, bm, bd);
                data[size++] = p;
                break;
            }
            // 录入销售信息
            else if (role == "销售" || role == "销售员" || role == "销售人员" || role == "xiaoshou" || role == "推销")
            {
                cout << "请输入姓名：" << endl;
                cout << '>';
                cin >> name;

                cout << "请输入性别：" << endl;
                cout << '>';
                cin >> sex;

                cout << "请输入级别(1-5)：" << endl;
                cout << '>';
                cin >> grade;

                cout << "请输入当月销售额：" << endl;
                cout << '>';
                cin >> salesAmount;

                cout << "请输入提成比例：" << endl;
                cout << '>';
                cin >> commissionRate;

                cout << "请输入出生月：" << endl;
                cout << '>';
                cin >> bm;

                cout << "请输入出生日：" << endl;
                cout << '>';
                cin >> bd;

                Employee *p = new Salesman(name, sex, grade, salesAmount, commissionRate, bm, bd);
                data[size++] = p;
                break;
            }
            // 录入销售经理信息
            else if (role == "销售经理" || role == "xiaoshoujingli")
            {
                cout << "请输入姓名：" << endl;
                cout << '>';
                cin >> name;

                cout << "请输入性别：" << endl;
                cout << '>';
                cin >> sex;

                cout << "请输入级别(1-5)：" << endl;
                cout << '>';
                cin >> grade;

                cout << "请输入固定月薪：" << endl;
                cout << '>';
                cin >> fixedSalary;

                cout << "请输入当月销售额：" << endl;
                cout << '>';
                cin >> salesAmount;

                cout << "请输入提成比例：" << endl;
                cout << '>';
                cin >> commissionRate;

                cout << "请输入出生月：" << endl;
                cout << '>';
                cin >> bm;

                cout << "请输入出生日：" << endl;
                cout << '>';
                cin >> bd;

                Employee *p = new Salesmanager(name, sex, grade, fixedSalary, salesAmount, commissionRate, bm, bd);
                data[size++] = p;
                break;
            }
            else
                cout << "职位输入错误请重新输入" << endl;
        }
    }
    void lookup_name()
    {
        string name;
        cout << "请输入要查询的员工的姓名：" << endl;
        cout << '>';
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
        cout << "请输入要查询的员工的id：" << endl;
        cout << '>';
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
        cout << "请输入要删除的员工的名字：" << endl;
        cout << '>';
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
                break; // 删除后退出循环
            }
        }
        if (idx == -1)
        {
            cout << "未找到此员工" << endl;
            return;
        }
        cout << "已成功删除" << endl;
    }
    void remove_by_id()
    {
        int id;
        cout << "请输入要删除的员工的id：" << endl;
        cout << '>';
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
                break; // 删除后退出循环
            }
        }
        if (idx == -1)
        {
            cout << "未找到此员工" << endl;
            return;
        }
        cout << "已成功删除" << endl;
    }
    void list_all_employees()
    {
        cout << "所有员工罗列如下：" << endl;
        for (int i = 0; i < size; i++)
        {
            data[i]->printInfo();
            cout << endl;
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
        if (salary_amount == 0)
            salary_amount = 1; // 防止除0
        cout << "所有员工的总工资为：" << salary_amount << "\n"
             << "技术人员的总工资占比为：" << salary_Technician / salary_amount << "\n"
             << "所有经理的总工资占比为：" << salary_Manager / salary_amount << "\n"
             << "所有销售的总工资占比为：" << salary_Salesman / salary_amount << "\n"
             << "所有销售经理的总工资占比为：" << salary_Salesmanager / salary_amount << endl;
    }
    void promote()
    {
        string s;
        cout << "请输入员工姓名" << endl;
        cout << '>';
        cin >> s;
        for (int i = 0; i < size; i++)
        {
            if (data[i]->get_name() == s)
            {
                data[i]->promote();
                break;
            }
        }
    }

    // 生日提醒
    void birthday_remind()
    {
        int m, d;
        cout << "请输入今天的日期（月 日）：" << endl;
        cout << '>';
        cin >> m >> d;

        bool found = false;
        for (int i = 0; i < size; i++)
        {
            if (data[i]->get_birthMonth() == m && data[i]->get_birthDay() == d)
            {
                cout << "今天是员工 " << data[i]->get_name() << " 的生日！" << endl;
                found = true;
            }
        }
        if (!found)
            cout << "今天没有员工过生日。" << endl;
    }

    void save_to_file()
    {
        ofstream out("employees.txt");
        if (!out)
        {
            cout << "保存文件失败" << endl;
            return;
        }
        for (int i = 0; i < size; ++i)
        {
            data[i]->save(out);
        }
        out.close();
        cout << "已保存到 employees.txt" << endl;
    }

    void load_from_file()
    {
        ifstream in("employees.txt");
        if (!in)
            return; // 文件不存在则直接返回

        // 清掉当前数据（若有）
        for (int i = 0; i < size; ++i)
            delete data[i];
        size = 0;

        string role;
        while (in >> role)
        {
            string name, sex;
            int grade;
            int bm = 0, bd = 0;

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

            if (role == "Technician")
            {
                int workHours, hourRate;
                in >> name >> sex >> grade >> workHours >> hourRate >> bm >> bd;
                Employee *p = new Technician(name, sex, grade, workHours, hourRate, bm, bd);
                data[size++] = p;
            }
            else if (role == "Manager")
            {
                int fixedSalary;
                in >> name >> sex >> grade >> fixedSalary >> bm >> bd;
                Employee *p = new Manager(name, sex, grade, fixedSalary, bm, bd);
                data[size++] = p;
            }
            else if (role == "Salesman")
            {
                int salesAmount;
                float commissionRate;
                in >> name >> sex >> grade >> salesAmount >> commissionRate >> bm >> bd;
                Employee *p = new Salesman(name, sex, grade, salesAmount, commissionRate, bm, bd);
                data[size++] = p;
            }
            else if (role == "Salesmanager")
            {
                int fixedSalary, salesAmount;
                float commissionRate;
                in >> name >> sex >> grade >> fixedSalary >> salesAmount >> commissionRate >> bm >> bd;
                Employee *p = new Salesmanager(name, sex, grade, fixedSalary, salesAmount, commissionRate, bm, bd);
                data[size++] = p;
            }
            else
            {
                string rest;
                getline(in, rest);
            }
        }

        in.close();
        if (size > 0)
            cout << "已从 employees.txt 中加载 " << size << " 条员工记录。" << endl;
    }
};

int main()
{
    EmployeeArray e(1);
    e.load_from_file();

    while (1)
    {
        int i;
        cout << "------企业员工管理系统------" << endl;
        cout << "录入员工信息请按1" << endl;
        cout << "查询员工信息请按2" << endl;
        cout << "删除员工信息请按3" << endl;
        cout << "罗列所有员工信息请按4" << endl;
        cout << "计算并展示工资占比情况请按5" << endl;
        cout << "晋升员工请按6" << endl;
        cout << "员工生日提醒请按7" << endl;
        cout << "退出程序请按8（退出前会自动保存）" << endl;
        cout << '>';
        cin >> i;

        // 基本的输入错误处理，防止字母导致死循环（最小改动）
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "输入错误，请输入数字！" << endl;
            continue;
        }

        switch (i)
        {
        case 1:
        {
            int n;
            cout << "要录入几个员工？" << endl;
            cout << '>';
            cin >> n;
            while (n--)
                e.push();
            break;
        }
        case 2: // 查询
        {
            int op;
            cout << "按姓名查询请按1，按id查询请按2" << endl;
            cout << '>';
            cin >> op;
            if (op == 1)
                e.lookup_name();
            else if (op == 2)
                e.lookup_id();
            else
                cout << "输入错误" << endl;
            break;
        }
        case 3: // 删除
        {
            int op;
            cout << "按姓名删除请按1，按id删除请按2" << endl;
            cout << '>';
            cin >> op;
            if (op == 1)
                e.remove_by_name();
            else if (op == 2)
                e.remove_by_id();
            else
                cout << "输入错误" << endl;
            break;
        }
        case 4:
            e.list_all_employees();
            break;
        case 5:
            e.salary_count_display();
            break;
        case 6:
            e.promote();
            break;
        case 7:
            e.birthday_remind();
            break;
        case 8:
            e.save_to_file();
            return 0;
        default:
            cout << "输入错误，请重新选择" << endl;
            break;
        }
        cout << '\n'
             << "按回车以继续......";
        cin.ignore();
        cin.get();
    }
}
