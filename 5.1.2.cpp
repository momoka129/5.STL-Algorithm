#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

class myPrint{
public:
    void operator()(int a){
        cout<<a<<" ";
    }
};

class Transform{
public:
    int operator()(int a){
        return a + 22;
    }
};

void test01(){
    vector<int> v;
    for(int i = 0; i < 10; i++){
        v.push_back(i);
    }

    vector<int> target;

    //the target container need to allocate space in advance!!!
    target.resize(v.size());

    transform(v.begin(), v.end(), target.begin(), Transform());

    for_each(target.begin(), target.end(), myPrint());
}

int main(){

    test01();

    return 0;
}