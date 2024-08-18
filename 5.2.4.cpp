#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void test01(){

    vector<int> v;

    //the sequence must in order
    for(int i = 0; i < 10; i++){
        v.push_back(i+1);
    }

    cout<<"9?"<<endl;

    bool res = binary_search(v.begin(), v.end(), 9);
    if(res){
        cout<<"found."<<endl;
    }
    else{
        cout<<"not found."<<endl;
    }
}

int main(){

    test01();

    return 0;
}