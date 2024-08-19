#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#include<ctime>

void myPrint(int a){
    cout<<a<<" ";
}

void test01(){

    vector<int> v;

    for(int i = 0; i < 10; i++){
        v.push_back(i);
    }

    for_each(v.begin(), v.end(), myPrint);

    reverse(v.begin(), v.end());

    cout<<"\n-------------------"<<endl;
    for_each(v.begin(), v.end(), myPrint);
}

int main(){

    test01();

    return 0;
}