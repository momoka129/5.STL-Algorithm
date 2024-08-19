#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#include<ctime>

void myPrint(int a){
    cout<<a<<" ";
}

void test01(){

    vector<int> v1;
    vector<int> v2;

    for(int i = 0; i < 10; i++){
        v1.push_back(i);
        v2.push_back(i+1);
    }

    //target container
    vector<int> v;

    v.resize(v1.size() + v2.size());

    merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v.begin());

    for_each(v.begin(), v.end(), myPrint);
}

int main(){

    test01();

    return 0;
}