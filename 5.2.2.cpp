#include<iostream>
#include<algorithm>
using namespace std;
#include<vector>

class Greaterfive{
public:
    bool operator()(int a){
        return a > 5;
    }
};

void test01(){

    vector<int> v;
    for(int i = 0; i < 10; i++){
        v.push_back(i);
    }

    cout<<"check if there is a number greater than 5 in the container"<<endl;
    if(find_if(v.begin(), v.end(), Greaterfive()) != v.end()){
        cout<<"found"<<endl;
    }
    else{
        cout<<"not found."<<endl;
    }
}

class Person{
public:
    Person(string name, int age){
        this->name = name;
        this->age = age;
    }

    string name;
    int age;
};

class Greater5{
public:
    bool operator()(Person &p){
        return p.age > 5;
    }
};

void test02(){

    vector<Person> v;

    Person p1("sdoij", 7);
    Person p2("vawoi", 3);
    Person p3("vmvosia", 4);
    Person p4("voi", 9);

    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);

    int count = 0;

    for(vector<Person>::iterator it = v.begin(); it != v.end(); it++){
        if(find_if(v.begin(), v.end(), Greater5()) != v.end()){
            count++;
        }
    }
    if(count != 0){
        cout<<"found."<<endl;
        cout<<count<<" person age greater than 5."<<endl;
    }
    else{
        cout<<"not found"<<endl;
    }
    
}

int main(){

    test01();
    cout<<"-----------------------------------"<<endl;
    test02();

    return 0;
}