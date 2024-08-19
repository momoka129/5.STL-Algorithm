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

void test01(){

    vector<int> v;

    v.push_back(10);
    v.push_back(2);
    v.push_back(1);
    v.push_back(4);
    v.push_back(7);
    v.push_back(13);

    vector<int> v2;
    for(int i = 0; i < 10; i++){
        v2.push_back(i);
    }

    for_each(v.begin(), v.end(), Print());
    cout<<endl;
    for_each(v2.begin(), v2.end(), Print());
    cout<<endl;

    swap(v, v2);
    
    cout<<"======================="<<endl;

    for_each(v.begin(), v.end(), Print());
    cout<<endl;
    for_each(v2.begin(), v2.end(), Print());
    cout<<endl;
}

int main(){

    test01();
    
    return 0;
}