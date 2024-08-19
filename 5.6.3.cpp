#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void myPrint(int a){
    cout<<a<<" ";
}

void test01(){

    vector<int> v1;
    vector<int> v2;

    for(int i = 0; i < 10; i++){
        v1.push_back(i);
        v2.push_back(i+5);
    }

    vector<int> v;
    
    //take the larger size
    v.resize(max(v1.size(), v2.size()));

    cout<<"v1 and v2 difference: "<<endl;

    vector<int>::iterator itEnd1 = set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), v.begin());

    for_each(v.begin(), itEnd1, myPrint);

    cout<<"\nv2 and v1 difference: "<<endl;

    vector<int>::iterator itEnd2 = set_difference(v2.begin(), v2.end(), v1.begin(), v1.end(), v.begin());

    for_each(v.begin(), itEnd2, myPrint);

}

int main(){

    test01();

    return 0;
}