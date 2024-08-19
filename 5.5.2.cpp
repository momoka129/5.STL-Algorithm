#include<iostream>
#include<vector>
#include<numeric>
#include<algorithm>
using namespace std;

void myPrint(int a){
    cout<<a<<" ";
}

void test01(){

    vector<int> v;
    v.resize(10);

    //后期重新填充
    //refill later
    fill(v.begin(), v.end(), 100);

    for_each(v.begin(), v.end(), myPrint);
}

int main(){

    test01();

    return 0;
}