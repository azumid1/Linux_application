#include <iostream>
#include <string>
using namespace std;

class Animal{
public:
    string color;
    int weight;

};

class Dog:public Animal{
public:
    string name;
    int age;
    void run();
};

int main(){
    Dog dog;
    dog.name = "旺财";
    dog.age = 2;
    dog.color = "黑色";
    dog.weight = 120;
    cout<<"狗的名字是:"<<dog.name<<endl;
    cout<<"狗的年龄是:"<<dog.age<<endl;
    cout<<"狗的毛发颜色是:"<<dog.color<<endl;
    cout<<"狗的体重是:"<<dog.weight<<endl;
    return 0;
}