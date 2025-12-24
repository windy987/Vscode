#include <iostream>
using namespace std;

// 基类
class vehicle
{
protected:
    int wheels;
    int weight;

public:
    vehicle(int w, int we) : wheels(w), weight(we) {}
    void show()
    {
        cout << "wheels:" << wheels << " weight:" << weight << endl;
    }
};

class car : private vehicle
{
private:
    int passenger_load;

public:
    car(int w, int we, int p) : vehicle(w, we), passenger_load(p) {}
    void show()
    {
        vehicle::show();
        cout << "passenger_load:" << passenger_load << endl;
    }
};

class truck : private vehicle
{
private:
    int passenger_load;
    int payload;

public:
    truck(int w, int we, int p, int pl)
        : vehicle(w, we), passenger_load(p), payload(pl) {}
    void show()
    {
        vehicle::show();
        cout << "passenger_load:" << passenger_load
             << " payload:" << payload << endl;
    }
};

int main()
{
    vehicle v(4, 60);
    cout << "vehicle:" << endl;
    v.show();

    car c(4, 60, 5);
    cout << "car:" << endl;
    c.show();

    truck t(4, 200, 10, 1000);
    cout << "truck:" << endl;
    t.show();

    return 0;
}
