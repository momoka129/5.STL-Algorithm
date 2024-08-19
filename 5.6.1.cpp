#include<iostream>
#include<vector>
using namespace std;
#include<algorithm>

void myPrint(int a){
    cout<<a<<" ";
}

void test01(){

    vector<int> v1;
    vector<int> v2;

    for(int i = 0; i < 10; i++){
        v1.push_back(i);    //0~9
        v2.push_back(i + 5);    //5~14
    }

    vector<int> v;
    
    //use smaller container size
    v.resize(min(v1.size(), v2.size()));

    //return the iterator address of the last element
    vector<int>::iterator itEnd = set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), v.begin());

    for_each(v.begin(), itEnd, myPrint);
}

int main(){

    test01();

    return 0;
}