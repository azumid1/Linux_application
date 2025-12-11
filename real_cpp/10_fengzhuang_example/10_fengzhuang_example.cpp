#include <iostream>
#include <string>
using namespace std;

class Dog{
private:
    int total;
public:
    string name;
    Dog(int i=0){
        total = i;
    }
    void addFood(int number){
        total = total + number;
    }
    int getFood(){
        return total;
    }

};

int main(){
    Dog dog = Dog(4);
    cout<<"初始的食物数量是:"<<dog.getFood()<<endl;
    dog.addFood(1);
    dog.addFood(2);
    dog.name = "旺财";
    cout<<dog.name<<"最后一共有"<<dog.getFood()<<"份食物"<<endl;
    return 0;
}