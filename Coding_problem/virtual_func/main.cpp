#include <iostream>
#include <string>
using namespace std;

class robot{
public:
    robot(){
        pos = 0;
        vel = 0;
    }
    virtual void forward(int step) = 0;
    virtual void backward(int step) = 0;
    virtual void accelerate(int step) = 0;
    virtual void show(){
        cout<<"robot show "<<to_string(pos)<<endl;
    }
    int pos;
    int vel;
};

class machineDog: public robot{
public:
    machineDog(){
        haveMaster = true;
    }
    void forward(int step) override {
        pos += step;
    }
    void backward(int step) override {
        pos -= step;
    }
    void accelerate(int step) override {
        vel += step;
    }
    void show() override {
        cout<<"Machine Dog show "<<to_string(pos)<<endl;
    }


private:
    bool haveMaster;
};


int main()
{
    machineDog dog = machineDog();
    dog.forward(5);
    dog.show();
    return 0;
}
