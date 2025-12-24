#include <iostream>
using namespace std;

class Person {
private:
    string name;
    int age;

public:
    Person(string n = "", int a = 0) : name(n), age(a) {}

    // 声明为友元
    friend istream& operator>>(istream& in, Person& p);
    friend ostream& operator<<(ostream& out, const Person& p);
};
