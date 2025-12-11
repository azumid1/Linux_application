#include <iostream>
#include <string>
using namespace std;

class Dog{
public:
    string name;
    void func();
};

int main(){
    Dog dog;
    dog.func();
    return 0;
}

void Dog::func(){
    this->name = "旺财";
    cout<<"小狗的名字是:"<<this->name<<endl;
}