#include<iostream>
#include<algorithm>
using namespace std;
#include<vector>

void test01(){

    vector<int> v;

    v.push_back(10);
    v.push_back(10);
    v.push_back(10);
    v.push_back(10);
    v.push_back(10);
    v.push_back(20);

    int target = 10;
    int num = count(v.begin(), v.end(), target);
    cout<<"the number of 10 in the container: "<<num<<endl;
}

class Person{
public:
    Person(string name, int age){
        this->name = name;
        this->age = age;
    }

    //remember to add const
    bool operator==(const Person &p){
        if(p.age == this->age){
            return 1;
        }
        else{
            return 0;
        }
    }

    string name;
    int age;
};

void test02(){

    vector<Person> v;

    Person p1("sdoij", 9);
    Person p2("vawoi", 3);
    Person p3("vmvosia", 4);
    Person p4("voi", 9);

    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);

    Person keyP("i", 9);

    int num = count(v.begin(), v.end(), keyP);
    cout<<"the number of people whose age is the same with keyP: "<<num<<endl;
    
}

int main(){

    test01();
    cout<<"-----------------------------------"<<endl;
    test02();

    return 0;
}