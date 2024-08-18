#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>

void print01(int a){
    cout<<a<<" ";
}

//functor
class Print02{
public:
    void operator()(int a){
        cout<<a<<" ";
    }
};

void test01(){

    vector<int> v;
    for(int i = 0; i < 10; i++){
        v.push_back(i);
    }

    for_each(v.begin(), v.end(), print01);
    cout<<endl;

    for_each(v.begin(), v.end(), Print02());
    cout<<endl;
}

int main(){

    test01();

    return 0;
}