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

    random_shuffle(v.begin(), v.end());

    for_each(v.begin(), v.end(), myPrint);
}

int main(){

    srand((unsigned int)time(NULL));
    test01();

    return 0;
}