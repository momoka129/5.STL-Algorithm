#include<iostream>
#include<algorithm>
using namespace std;
#include<vector>

void test01(){

    vector<int> v;
    for(int i = 0; i < 10; i++){
        v.push_back(i);
    }

    cout<<"check if there is 5 in the container"<<endl;
    if(find(v.begin(), v.end(), 5) != v.end()){
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

    //重载== 让底层find知道如何对比Person数据类型
    //Overload == to let the underlying find know how to compare the Person data type
    bool operator==(const Person &p){
        if(this->age == p.age && this->name == p.name){
            return true;
        }
        else{
            return false;
        }
    }

    string name;
    int age;
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

    if(find(v.begin(), v.end(), p4) != v.end()){
        cout<<"found."<<endl;
    }
    else{
        cout<<"not found."<<endl;
    }


}

int main(){

    test01();
    test02();

    return 0;
}