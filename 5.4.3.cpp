#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Print{
public:
    void operator()(int a){
        cout<<a<<" ";
    }
};

class Greater3{
public:
    bool operator()(int a){
        return a > 3;
    }
};

void test01(){

    vector<int> v;

    v.push_back(10);
    v.push_back(2);
    v.push_back(1);
    v.push_back(4);
    v.push_back(7);
    v.push_back(13);

    for_each(v.begin(), v.end(), Print());
    cout<<endl;

    replace_if(v.begin(), v.end(), Greater3(), 9);
    
    for_each(v.begin(), v.end(), Print());
    cout<<endl;
}

int main(){

    test01();
    
    return 0;
}