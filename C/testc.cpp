#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

// 日期工具类
class DateUtils
{
public:
    static bool isLeapYear(int year)
    {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    static bool isValidDate(const string &date)
    {
        if (date.length() != 10 || date[4] != '-' || date[7] != '-')
            return false;

        int year, month, day;
        try
        {
            year = stoi(date.substr(0, 4));
            month = stoi(date.substr(5, 2));
            day = stoi(date.substr(8, 2));
        }
        catch (...)
        {
            return false;
        }

        if (year < 1900 || year > 2100 || month < 1 || month > 12)
            return false;

        int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (month == 2 && isLeapYear(year))
            daysInMonth[1] = 29;

        return day >= 1 && day <= daysInMonth[month - 1];
    }

    static string getCurrentDate()
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        stringstream ss;
        ss << 1900 + ltm->tm_year << "-"
           << setfill('0') << setw(2) << 1 + ltm->tm_mon << "-"
           << setfill('0') << setw(2) << ltm->tm_mday;
        return ss.str();
    }

    static bool isBirthdayToday(const string &birthday)
    {
        string today = getCurrentDate();
        return birthday.substr(5, 5) == today.substr(5, 5);
    }

    static int getDaysDifference(const string &start, const string &end)
    {
        tm startTm = {};
        tm endTm = {};
        istringstream(start) >> get_time(&startTm, "%Y-%m-%d");
        istringstream(end) >> get_time(&endTm, "%Y-%m-%d");

        time_t startTime = mktime(&startTm);
        time_t endTime = mktime(&endTm);

        return difftime(endTime, startTime) / (60 * 60 * 24);
    }
};

// 用户类
class User
{
private:
    string username;
    string password;
    string role; // admin/user
public:
    User(string uname, string pwd, string r) : username(uname), password(pwd), role(r) {}

    string getUsername() const { return username; }
    string getRole() const { return role; }

    bool verifyPassword(const string &pwd) const
    {
        return password == pwd;
    }
};

// 用户管理类
class UserManager
{
private:
    vector<User> users;
    const string USER_FILE = "users.dat";

    void loadUsers()
    {
        ifstream file(USER_FILE, ios::binary);
        if (!file)
            return;

        int count;
        file.read((char *)&count, sizeof(int));

        for (int i = 0; i < count; ++i)
        {
            int unameLen, pwdLen, roleLen;
            file.read((char *)&unameLen, sizeof(int));
            char *uname = new char[unameLen + 1];
            file.read(uname, unameLen);
            uname[unameLen] = '\0';

            file.read((char *)&pwdLen, sizeof(int));
            char *pwd = new char[pwdLen + 1];
            file.read(pwd, pwdLen);
            pwd[pwdLen] = '\0';

            file.read((char *)&roleLen, sizeof(int));
            char *role = new char[roleLen + 1];
            file.read(role, roleLen);
            role[roleLen] = '\0';

            users.emplace_back(uname, pwd, role);

            delete[] uname;
            delete[] pwd;
            delete[] role;
        }
        file.close();
    }

    void saveUsers()
    {
        ofstream file(USER_FILE, ios::binary);
        int count = users.size();
        file.write((char *)&count, sizeof(int));

        for (const auto &user : users)
        {
            string uname = user.getUsername();
            int unameLen = uname.length();
            file.write((char *)&unameLen, sizeof(int));
            file.write(uname.c_str(), unameLen);

            // 实际应用中应加密存储密码
            string pwd = "123456"; // 简化处理
            int pwdLen = pwd.length();
            file.write((char *)&pwdLen, sizeof(int));
            file.write(pwd.c_str(), pwdLen);

            string role = user.getRole();
            int roleLen = role.length();
            file.write((char *)&roleLen, sizeof(int));
            file.write(role.c_str(), roleLen);
        }
        file.close();
    }

public:
    UserManager()
    {
        loadUsers();
        if (users.empty())
        {
            // 默认管理员
            users.emplace_back("admin", "admin123", "admin");
            saveUsers();
        }
    }

    User *login(const string &uname, const string &pwd)
    {
        for (auto &user : users)
        {
            if (user.getUsername() == uname && user.verifyPassword(pwd))
            {
                return &user;
            }
        }
        return nullptr;
    }
};

// 抽象员工类
class Employee
{
protected:
    int id;
    string name;
    string gender;
    int level;
    string birthday;
    string hireDate;

public:
    Employee(int id_, string name_, string gender_, int level_, string bday, string hdate)
        : id(id_), name(name_), gender(gender_), level(level_), birthday(bday), hireDate(hdate) {}

    virtual ~Employee() = default;

    // 纯虚函数，计算月薪
    virtual double calculateSalary() const = 0;

    // 提升级别
    void promote() { level++; }

    // 获取属性
    int getId() const { return id; }
    string getName() const { return name; }
    string getGender() const { return gender; }
    int getLevel() const { return level; }
    string getBirthday() const { return birthday; }
    string getHireDate() const { return hireDate; }
    virtual string getType() const = 0;

    // 设置属性
    void setName(string n) { name = n; }
    void setGender(string g) { gender = g; }
    void setLevel(int l) { level = l; }

    // 序列化
    virtual void serialize(ofstream &file) const
    {
        file.write((char *)&id, sizeof(int));

        int nameLen = name.length();
        file.write((char *)&nameLen, sizeof(int));
        file.write(name.c_str(), nameLen);

        int genderLen = gender.length();
        file.write((char *)&genderLen, sizeof(int));
        file.write(gender.c_str(), genderLen);

        file.write((char *)&level, sizeof(int));

        int bdayLen = birthday.length();
        file.write((char *)&bdayLen, sizeof(int));
        file.write(birthday.c_str(), bdayLen);

        int hdateLen = hireDate.length();
        file.write((char *)&hdateLen, sizeof(int));
        file.write(hireDate.c_str(), hdateLen);
    }

    // 反序列化
    static Employee *deserialize(ifstream &file)
    {
        int typeLen;
        file.read((char *)&typeLen, sizeof(int));
        char *typeStr = new char[typeLen + 1];
        file.read(typeStr, typeLen);
        typeStr[typeLen] = '\0';
        string type(typeStr);
        delete[] typeStr;

        int id;
        file.read((char *)&id, sizeof(int));

        int nameLen;
        file.read((char *)&nameLen, sizeof(int));
        char *name = new char[nameLen + 1];
        file.read(name, nameLen);
        name[nameLen] = '\0';

        int genderLen;
        file.read((char *)&genderLen, sizeof(int));
        char *gender = new char[genderLen + 1];
        file.read(gender, genderLen);
        gender[genderLen] = '\0';

        int level;
        file.read((char *)&level, sizeof(int));

        int bdayLen;
        file.read((char *)&bdayLen, sizeof(int));
        char *bday = new char[bdayLen + 1];
        file.read(bday, bdayLen);
        bday[bdayLen] = '\0';

        int hdateLen;
        file.read((char *)&hdateLen, sizeof(int));
        char *hdate = new char[hdateLen + 1];
        file.read(hdate, hdateLen);
        hdate[hdateLen] = '\0';

        if (type == "Manager")
        {
            double fixedSalary;
            file.read((char *)&fixedSalary, sizeof(double));
            return new Manager(id, name, gender, level, bday, hdate, fixedSalary);
        }
        else if (type == "PartTimeTechnician")
        {
            double hourlyWage;
            int workHours;
            file.read((char *)&hourlyWage, sizeof(double));
            file.read((char *)&workHours, sizeof(int));
            return new PartTimeTechnician(id, name, gender, level, bday, hdate, hourlyWage, workHours);
        }
        else if (type == "SalesManager")
        {
            double fixedSalary;
            double salesVolume;
            file.read((char *)&fixedSalary, sizeof(double));
            file.read((char *)&salesVolume, sizeof(double));
            return new SalesManager(id, name, gender, level, bday, hdate, fixedSalary, salesVolume);
        }
        else if (type == "PartTimeSalesman")
        {
            double salesVolume;
            file.read((char *)&salesVolume, sizeof(double));
            return new PartTimeSalesman(id, name, gender, level, bday, hdate, salesVolume);
        }

        return nullptr;
    }
};

// 经理类
class Manager : public Employee
{
private:
    double fixedSalary; // 固定月薪
public:
    Manager(int id_, string name_, string gender_, int level_, string bday, string hdate, double salary)
        : Employee(id_, name_, gender_, level_, bday, hdate), fixedSalary(salary) {}

    double calculateSalary() const override
    {
        // 级别越高，工资越高（10%涨幅）
        return fixedSalary * (1 + (level - 1) * 0.1);
    }

    string getType() const override { return "Manager"; }

    double getFixedSalary() const { return fixedSalary; }
    void setFixedSalary(double s) { fixedSalary = s; }

    void serialize(ofstream &file) const override
    {
        string type = getType();
        int typeLen = type.length();
        file.write((char *)&typeLen, sizeof(int));
        file.write(type.c_str(), typeLen);

        Employee::serialize(file);
        file.write((char *)&fixedSalary, sizeof(double));
    }
};

// 兼职技术人员类
class PartTimeTechnician : public Employee
{
private:
    double hourlyWage; // 时薪
    int workHours;     // 工作小时数
public:
    PartTimeTechnician(int id_, string name_, string gender_, int level_, string bday, string hdate, double wage, int hours)
        : Employee(id_, name_, gender_, level_, bday, hdate), hourlyWage(wage), workHours(hours) {}

    double calculateSalary() const override
    {
        // 级别越高，时薪越高（5%涨幅）
        return hourlyWage * workHours * (1 + (level - 1) * 0.05);
    }

    string getType() const override { return "PartTimeTechnician"; }

    double getHourlyWage() const { return hourlyWage; }
    int getWorkHours() const { return workHours; }
    void setHourlyWage(double w) { hourlyWage = w; }
    void setWorkHours(int h) { workHours = h; }

    void serialize(ofstream &file) const override
    {
        string type = getType();
        int typeLen = type.length();
        file.write((char *)&typeLen, sizeof(int));
        file.write(type.c_str(), typeLen);

        Employee::serialize(file);
        file.write((char *)&hourlyWage, sizeof(double));
        file.write((char *)&workHours, sizeof(int));
    }
};

// 销售经理类
class SalesManager : public Employee
{
private:
    double fixedSalary; // 固定月薪
    double salesVolume; // 销售额
public:
    SalesManager(int id_, string name_, string gender_, int level_, string bday, string hdate, double salary, double sales)
        : Employee(id_, name_, gender_, level_, bday, hdate), fixedSalary(salary), salesVolume(sales) {}

    double calculateSalary() const override
    {
        // 固定工资 + 销售额提成（3%）
        double base = fixedSalary * (1 + (level - 1) * 0.1);
        double commission = salesVolume * 0.03;
        return base + commission;
    }

    string getType() const override { return "SalesManager"; }

    double getFixedSalary() const { return fixedSalary; }
    double getSalesVolume() const { return salesVolume; }
    void setFixedSalary(double s) { fixedSalary = s; }
    void setSalesVolume(double sv) { salesVolume = sv; }

    void serialize(ofstream &file) const override
    {
        string type = getType();
        int typeLen = type.length();
        file.write((char *)&typeLen, sizeof(int));
        file.write(type.c_str(), typeLen);

        Employee::serialize(file);
        file.write((char *)&fixedSalary, sizeof(double));
        file.write((char *)&salesVolume, sizeof(double));
    }
};

// 兼职推销员类
class PartTimeSalesman : public Employee
{
private:
    double salesVolume; // 销售额
public:
    PartTimeSalesman(int id_, string name_, string gender_, int level_, string bday, string hdate, double sales)
        : Employee(id_, name_, gender_, level_, bday, hdate), salesVolume(sales) {}

    double calculateSalary() const override
    {
        // 销售额提成（5%）+ 级别加成
        return salesVolume * 0.05 * (1 + (level - 1) * 0.05);
    }

    string getType() const override { return "PartTimeSalesman"; }

    double getSalesVolume() const { return salesVolume; }
    void setSalesVolume(double sv) { salesVolume = sv; }

    void serialize(ofstream &file) const override
    {
        string type = getType();
        int typeLen = type.length();
        file.write((char *)&typeLen, sizeof(int));
        file.write(type.c_str(), typeLen);

        Employee::serialize(file);
        file.write((char *)&salesVolume, sizeof(double));
    }
};

// 人力资源管理系统类
class HRSystem
{
private:
    vector<Employee *> employees;
    const string FILE_NAME = "employees.dat";
    int nextId;
    User *currentUser;
    UserManager userManager;

    void loadEmployees()
    {
        ifstream file(FILE_NAME, ios::binary);
        if (!file)
        {
            nextId = 1;
            return;
        }

        int count;
        file.read((char *)&count, sizeof(int));

        for (int i = 0; i < count; ++i)
        {
            Employee *emp = Employee::deserialize(file);
            if (emp)
            {
                employees.push_back(emp);
                if (emp->getId() >= nextId)
                {
                    nextId = emp->getId() + 1;
                }
            }
        }

        file.close();
    }

    void saveEmployees()
    {
        ofstream file(FILE_NAME, ios::binary);
        int count = employees.size();
        file.write((char *)&count, sizeof(int));

        for (const auto &emp : employees)
        {
            emp->serialize(file);
        }

        file.close();
    }

public:
    HRSystem() : nextId(1), currentUser(nullptr)
    {
        loadEmployees();
    }

    ~HRSystem()
    {
        for (auto emp : employees)
        {
            delete emp;
        }
        employees.clear();
    }

    bool login(const string &username, const string &password)
    {
        currentUser = userManager.login(username, password);
        return currentUser != nullptr;
    }

    void logout()
    {
        currentUser = nullptr;
    }

    bool isAdmin() const
    {
        return currentUser && currentUser->getRole() == "admin";
    }

    // 添加员工
    int addEmployee(Employee *emp)
    {
        if (!emp)
            return -1;

        emp->promote();   // 级别从1开始
        emp->~Employee(); // 调用析构函数（实际不需要，此处为演示）
        emp->Employee::Employee(nextId, emp->getName(), emp->getGender(), 1, emp->getBirthday(), emp->getHireDate());

        employees.push_back(emp);
        int newId = nextId++;
        saveEmployees();
        return newId;
    }

    // 删除员工
    bool deleteEmployee(int id)
    {
        if (!isAdmin())
            return false;

        for (auto it = employees.begin(); it != employees.end(); ++it)
        {
            if ((*it)->getId() == id)
            {
                delete *it;
                employees.erase(it);
                saveEmployees();
                return true;
            }
        }
        return false;
    }

    // 查找员工
    vector<Employee *> findEmployee(const string &key, const string &value)
    {
        vector<Employee *> results;

        if (key == "id")
        {
            int id;
            try
            {
                id = stoi(value);
            }
            catch (...)
            {
                return results;
            }

            for (auto emp : employees)
            {
                if (emp->getId() == id)
                {
                    results.push_back(emp);
                    break;
                }
            }
        }
        else if (key == "name")
        {
            for (auto emp : employees)
            {
                if (emp->getName() == value)
                {
                    results.push_back(emp);
                }
            }
        }

        return results;
    }

    // 更新员工信息
    bool updateEmployee(int id, const string &field, const string &value)
    {
        if (!isAdmin())
            return false;

        auto emp = findEmployee("id", to_string(id));
        if (emp.empty())
            return false;

        Employee *e = emp[0];
        if (field == "name")
        {
            e->setName(value);
        }
        else if (field == "gender")
        {
            if (value != "男" && value != "女")
                return false;
            e->setGender(value);
        }
        else if (field == "level")
        {
            try
            {
                int level = stoi(value);
                if (level < 1)
                    return false;
                e->setLevel(level);
            }
            catch (...)
            {
                return false;
            }
        }
        else
        {
            return false;
        }

        saveEmployees();
        return true;
    }

    // 提升员工级别
    bool promoteEmployee(int id)
    {
        auto emp = findEmployee("id", to_string(id));
        if (emp.empty())
            return false;

        emp[0]->promote();
        saveEmployees();
        return true;
    }

    // 统计总工资
    double calculateTotalSalary() const
    {
        double total = 0;
        for (const auto &emp : employees)
        {
            total += emp->calculateSalary();
        }
        return total;
    }

    // 统计各类员工工资占比
    void calculateSalaryRatio() const
    {
        double total = calculateTotalSalary();
        if (total == 0)
        {
            cout << "暂无工资数据" << endl;
            return;
        }

        double managerSal = 0, technicianSal = 0, salesManagerSal = 0, salesmanSal = 0;
        int managerCount = 0, technicianCount = 0, salesManagerCount = 0, salesmanCount = 0;

        for (const auto &emp : employees)
        {
            double sal = emp->calculateSalary();
            if (dynamic_cast<Manager *>(emp))
            {
                managerSal += sal;
                managerCount++;
            }
            else if (dynamic_cast<PartTimeTechnician *>(emp))
            {
                technicianSal += sal;
                technicianCount++;
            }
            else if (dynamic_cast<SalesManager *>(emp))
            {
                salesManagerSal += sal;
                salesManagerCount++;
            }
            else if (dynamic_cast<PartTimeSalesman *>(emp))
            {
                salesmanSal += sal;
                salesmanCount++;
            }
        }

        cout << "\n=== 工资统计 ===" << endl;
        cout << "总工资: " << fixed << setprecision(2) << total << " 元" << endl;
        cout << "\n经理（" << managerCount << "人）: " << managerSal << " 元 (" << (managerSal / total) * 100 << "%)" << endl;
        cout << "兼职技术人员（" << technicianCount << "人）: " << technicianSal << " 元 (" << (technicianSal / total) * 100 << "%)" << endl;
        cout << "销售经理（" << salesManagerCount << "人）: " << salesManagerSal << " 元 (" << (salesManagerSal / total) * 100 << "%)" << endl;
        cout << "兼职推销员（" << salesmanCount << "人）: " << salesmanSal << " 元 (" << (salesmanSal / total) * 100 << "%)" << endl;
    }

    // 生日提醒
    void birthdayReminder() const
    {
        vector<Employee *> birthdays;
        for (const auto &emp : employees)
        {
            if (DateUtils::isBirthdayToday(emp->getBirthday()))
            {
                birthdays.push_back(emp);
            }
        }

        if (!birthdays.empty())
        {
            cout << "\n=== 今日生日提醒 ===" << endl;
            for (const auto &emp : birthdays)
            {
                cout << "ID: " << emp->getId() << ", 姓名: " << emp->getName() << endl;
            }
        }
        else
        {
            cout << "\n今日无员工生日" << endl;
        }
    }

    // 转正提醒（假设试用期3个月）
    void probationReminder() const
    {
        vector<Employee *> probations;
        string today = DateUtils::getCurrentDate();

        for (const auto &emp : employees)
        {
            int days = DateUtils::getDaysDifference(emp->getHireDate(), today);
            if (days >= 90 && days <= 97)
            { // 转正前7天提醒
                probations.push_back(emp);
            }
        }

        if (!probations.empty())
        {
            cout << "\n=== 转正提醒 ===" << endl;
            for (const auto &emp : probations)
            {
                cout << "ID: " << emp->getId() << ", 姓名: " << emp->getName()
                     << ", 入职日期: " << emp->getHireDate() << endl;
            }
        }
        else
        {
            cout << "\n近期无员工转正" << endl;
        }
    }

    // 显示所有员工
    void showAllEmployees() const
    {
        cout << "\n=== 员工列表 ===" << endl;
        cout << left << setw(5) << "ID"
             << setw(10) << "姓名"
             << setw(6) << "性别"
             << setw(6) << "级别"
             << setw(15) << "类型"
             << setw(15) << "月薪" << endl;
        cout << "----------------------------------------" << endl;

        for (const auto &emp : employees)
        {
            cout << left << setw(5) << emp->getId()
                 << setw(10) << emp->getName()
                 << setw(6) << emp->getGender()
                 << setw(6) << emp->getLevel()
                 << setw(15) << emp->getType()
                 << setw(15) << fixed << setprecision(2) << emp->calculateSalary() << endl;
        }
    }

    // 获取下一个ID
    int getNextId() const { return nextId; }
};

// 交互界面
class Interface
{
private:
    HRSystem hrSystem;

    void showMenu()
    {
        cout << "\n=== 企业人力管理系统 ===" << endl;
        cout << "1. 登录" << endl;
        cout << "2. 退出" << endl;
        cout << "请选择操作: ";
    }

    void showMainMenu()
    {
        cout << "\n=== 主菜单 ===" << endl;
        cout << "1. 员工管理" << endl;
        cout << "2. 工资统计" << endl;
        cout << "3. 提醒功能" << endl;
        cout << "4. 退出登录" << endl;
        cout << "请选择操作: ";
    }

    void showEmployeeMenu()
    {
        cout << "\n=== 员工管理 ===" << endl;
        cout << "1. 添加员工" << endl;
        cout << "2. 删除员工" << endl;
        cout << "3. 修改员工" << endl;
        cout << "4. 查找员工" << endl;
        cout << "5. 显示所有员工" << endl;
        cout << "6. 提升员工级别" << endl;
        cout << "7. 返回上一级" << endl;
        cout << "请选择操作: ";
    }

    void addEmployee()
    {
        if (!hrSystem.isAdmin())
        {
            cout << "权限不足！" << endl;
            return;
        }

        cout << "\n=== 添加员工 ===" << endl;
        cout << "员工类型：" << endl;
        cout << "1. 经理" << endl;
        cout << "2. 兼职技术人员" << endl;
        cout << "3. 销售经理" << endl;
        cout << "4. 兼职推销员" << endl;
        cout << "请选择类型: ";

        int type;
        cin >> type;
        cin.ignore();

        string name, gender, birthday, hireDate;
        cout << "姓名: ";
        getline(cin, name);

        while (true)
        {
            cout << "性别(男/女): ";
            getline(cin, gender);
            if (gender == "男" || gender == "女")
                break;
            cout << "性别只能是男或女，请重新输入！" << endl;
        }

        while (true)
        {
            cout << "生日(YYYY-MM-DD): ";
            getline(cin, birthday);
            if (DateUtils::isValidDate(birthday))
                break;
            cout << "日期格式不正确，请重新输入！" << endl;
        }

        while (true)
        {
            cout << "入职日期(YYYY-MM-DD): ";
            getline(cin, hireDate);
            if (DateUtils::isValidDate(hireDate))
                break;
            cout << "日期格式不正确，请重新输入！" << endl;
        }

        Employee *emp = nullptr;
        int id = hrSystem.getNextId();

        switch (type)
        {
        case 1:
        {
            double fixedSalary;
            cout << "固定月薪: ";
            cin >> fixedSalary;
            emp = new Manager(id, name, gender, 1, birthday, hireDate, fixedSalary);
            break;
        }
        case 2:
        {
            double hourlyWage;
            int workHours;
            cout << "时薪: ";
            cin >> hourlyWage;
            cout << "工作小时数: ";
            cin >> workHours;
            emp = new PartTimeTechnician(id, name, gender, 1, birthday, hireDate, hourlyWage, workHours);
            break;
        }
        case 3:
        {
            double fixedSalary, salesVolume;
            cout << "固定月薪: ";
            cin >> fixedSalary;
            cout << "销售额: ";
            cin >> salesVolume;
            emp = new SalesManager(id, name, gender, 1, birthday, hireDate, fixedSalary, salesVolume);
            break;
        }
        case 4:
        {
            double salesVolume;
            cout << "销售额: ";
            cin >> salesVolume;
            emp = new PartTimeSalesman(id, name, gender, 1, birthday, hireDate, salesVolume);
            break;
        }
        default:
            cout << "无效类型！" << endl;
            return;
        }

        int newId = hrSystem.addEmployee(emp);
        if (newId > 0)
        {
            cout << "员工添加成功，ID: " << newId << endl;
        }
        else
        {
            cout << "员工添加失败！" << endl;
            delete emp;
        }
    }

    void deleteEmployee()
    {
        if (!hrSystem.isAdmin())
        {
            cout << "权限不足！" << endl;
            return;
        }

        cout << "\n=== 删除员工 ===" << endl;
        cout << "请输入员工ID: ";
        int id;
        cin >> id;

        if (hrSystem.deleteEmployee(id))
        {
            cout << "员工删除成功！" << endl;
        }
        else
        {
            cout << "员工不存在或删除失败！" << endl;
        }
    }

    void findEmployee()
    {
        cout << "\n=== 查找员工 ===" << endl;
        cout << "1. 按ID查找" << endl;
        cout << "2. 按姓名查找" << endl;
        cout << "请选择方式: ";

        int choice;
        cin >> choice;
        cin.ignore();

        vector<Employee *> results;

        if (choice == 1)
        {
            cout << "请输入ID: ";
            int id;
            cin >> id;
            results = hrSystem.findEmployee("id", to_string(id));
        }
        else if (choice == 2)
        {
            cout << "请输入姓名: ";
            string name;
            getline(cin, name);
            results = hrSystem.findEmployee("name", name);
        }
        else
        {
            cout << "无效选择！" << endl;
            return;
        }

        if (results.empty())
        {
            cout << "未找到员工！" << endl;
            return;
        }

        cout << "\n查找结果:" << endl;
        cout << left << setw(5) << "ID"
             << setw(10) << "姓名"
             << setw(6) << "性别"
             << setw(6) << "级别"
             << setw(15) << "类型"
             << setw(15) << "月薪" << endl;
        cout << "----------------------------------------" << endl;

        for (const auto &emp : results)
        {
            cout << left << setw(5) << emp->getId()
                 << setw(10) << emp->getName()
                 << setw(6) << emp->getGender()
                 << setw(6) << emp->getLevel()
                 << setw(15) << emp->getType()
                 << setw(15) << fixed << setprecision(2) << emp->calculateSalary() << endl;
        }
    }

public:
    void run()
    {
        while (true)
        {
            showMenu();
            int choice;
            cin >> choice;

            switch (choice)
            {
            case 1:
            {
                cout << "\n=== 登录 ===" << endl;
                cout << "用户名: ";
                string username;
                cin >> username;
                cout << "密码: ";
                string password;
                cin >> password;

                if (hrSystem.login(username, password))
                {
                    cout << "登录成功！欢迎 " << username << endl;
                    mainLoop();
                }
                else
                {
                    cout << "用户名或密码错误！" << endl;
                }
                break;
            }
            case 2:
                cout << "感谢使用，再见！" << endl;
                return;
            default:
                cout << "无效选择，请重新输入！" << endl;
            }
        }
    }

    void mainLoop()
    {
        while (true)
        {
            showMainMenu();
            int choice;
            cin >> choice;

            switch (choice)
            {
            case 1:
                employeeManagement();
                break;
            case 2:
                hrSystem.calculateSalaryRatio();
                break;
            case 3:
                hrSystem.birthdayReminder();
                hrSystem.probationReminder();
                break;
            case 4:
                hrSystem.logout();
                cout << "已退出登录！" << endl;
                return;
            default:
                cout << "无效选择，请重新输入！" << endl;
            }
        }
    }

    void employeeManagement()
    {
        while (true)
        {
            showEmployeeMenu();
            int choice;
            cin >> choice;

            switch (choice)
            {
            case 1:
                addEmployee();
                break;
            case 2:
                deleteEmployee();
                break;
            case 3:
                // 修改员工信息（实现略）
                cout << "功能开发中..." << endl;
                break;
            case 4:
                findEmployee();
                break;
            case 5:
                hrSystem.showAllEmployees();
                break;
            case 6:
            {
                if (!hrSystem.isAdmin())
                {
                    cout << "权限不足！" << endl;
                    break;
                }
                cout << "请输入员工ID: ";
                int id;
                cin >> id;
                if (hrSystem.promoteEmployee(id))
                {
                    cout << "级别提升成功！" << endl;
                }
                else
                {
                    cout << "员工不存在或提升失败！" << endl;
                }
                break;
            }
            case 7:
                return;
            default:
                cout << "无效选择，请重新输入！" << endl;
            }
        }
    }
};

int main()
{
    Interface interface;
    interface.run();
    return 0;
}
