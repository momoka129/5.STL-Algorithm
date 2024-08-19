#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Print{
public:
    void operator()(int a){
        cout<<a<<" ";
    }
};

void test01(){

    vector<int> v;

    v.push_back(1);
    v.push_back(1);
    v.push_back(1);
    v.push_back(2);
    v.push_back(1);
    v.push_back(4);
    v.push_back(1);
    v.push_back(13);

    for_each(v.begin(), v.end(), Print());

    replace(v.begin(), v.end(), 1, 3);

    cout<<"\n--------------------------"<<endl;
    for_each(v.begin(), v.end(), Print());

}

int main(){

    test01();

    return 0;
}