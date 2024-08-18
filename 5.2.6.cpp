#include<iostream>
#include<algorithm>
using namespace std;
#include<vector>

class Greater10{
public:
    bool operator()(int a){
        return a > 10;
    }
};

void test01(){

    vector<int> v;

    v.push_back(10);
    v.push_back(10);
    v.push_back(30);
    v.push_back(10);
    v.push_back(11);
    v.push_back(20);

    int num = count_if(v.begin(), v.end(), Greater10());
    cout<<"the number of numbers greater than 10 in the container: "<<num<<endl;
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

class Greater5{
public:
    bool operator()(const Person &p){
        return p.age > 5;
    }
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

    int num = count_if(v.begin(), v.end(), Greater5());
    cout<<"the number of people whose age is greater than 5: "<<num<<endl;
    
}

int main(){

    test01();
    cout<<"-----------------------------------"<<endl;
    test02();

    return 0;
}