#include <iostream>
#include <string>
using namespace std;

class Animal{
public:
    virtual void run(){
        cout<<"Animal::run func!"<<endl;
    }
};

class Dog:public Animal{
public:
    void run(){
        cout<<"Dog::run func!"<<endl;
    }
};

class Cat:public Animal{
public:
    void run(){
        cout<<"Cat::run func!"<<endl;
    }
};

int main(){
    Animal *animal = nullptr;
    Cat cat;
    Dog dog;

    animal = &dog;
    animal->run();
    animal = &cat;
    animal->run();
    return 0;
}