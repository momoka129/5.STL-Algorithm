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

    vector<int> v2;

    v2.resize(v.size());

    copy(v.begin(), v.end(), v2.begin());

    cout<<"\n-------------------"<<endl;
    for_each(v2.begin(), v2.end(), myPrint);
}

int main(){

    test01();

    return 0;
}