# 	C++提高编程

- 本阶段主要针对c++==泛型编程==和==STL==技术做详细讲解，探讨c++更深层的使用



### 1 模板

#### 1.1 模板的概念

模板就是建立**通用的摸具**，大大提高**复用性**

模板的特点：

- 模板不可以直接使用，它只是一个框架
- 模板的通用并不是万能的



#### 1.2 函数模板

- c++另一种编程思想称为 ==泛型编程==，主要利用的技术就是模板
- c++提供两种模板机制：==函数模板==和==类模板==

##### 1.2.1 函数模板语法

作用：

建立一个通用函数，其函数返回值类型和形参类型可以不具体制定，用一个==虚拟的类型==来代表

语法：

`````c++
template<typename/class T>
函数声明或定义
`````

解释：

template — 声明创建模板

typename — 表面其后面的符号是一种数据类型，可以用class代替

T — 通用的数据类型，名称可以替换，通常为大写字母

`````c++
#include<iostream>
using namespace std;

template<typename T>
void CommonSwap(T &a, T &b){    //同一个T 所以a,b类型要一样
    T temp = a;
    a = b;
    b = temp;
}

int main(){
    //两种使用函数模板方式
    int a = 1;
    int b = 2;
    //1 自动类型推导
    CommonSwap(a,b);
    cout<<"a: "<<a<<endl;
    cout<<"b: "<<b<<endl;
    //2 显示指定类型
    CommonSwap<int>(a,b);
    cout<<"a: "<<a<<endl;
    cout<<"b: "<<b<<endl;
}
`````

> 类型参数化



##### 1.2.2 函数模板注意事项

- 自动类型推导，必须推导出一致的数据类型T
- 模板必须要确定出T 的数据类型

`````c++
template<class T>
void func(){
    cout<<"call.."<<endl;
}
int main(){
    //func(); //错误 必须给出T的类型
    func<int>();    //利用显示指定类型的方式 给T一个类型 才可以使用模板
}
`````



##### 1.2.3 函数模板案例

案例描述：利用函数模板封装一个排序的函数，可以对不同数据类型的数组进行排序

`````c++
#include<iostream>
using namespace std;

template<class T>
int partition(T arr[], int first, int last){
    T pivot = arr[first];
    int lastS1 = first;
    for(int i = first +1; i <= last; i++){
        if(arr[i] > pivot){     //desceding order
            lastS1++;
            swap(arr[lastS1],arr[i]);
        }
    }
    swap(arr[first],arr[lastS1]);
    return lastS1;
}

template<class T>
void quickSort(T arr, int first, int last){
    if(first < last){
        int pivotIndex = partition(arr,first,last);
        quickSort(arr, first,pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, last);
    }
}

template<class T>
void print(T arr[], int n){
    //n = sizeof(arr) / sizeof(T);//错误 因为数组在函数中退化为指针
    for(int i = 0; i < n; i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

int main(){
    int a[] = {3,2,5,6,23,66};
    double b[] = {24.5,52.5,32.1};
    char charA[] = "svhaweriovhb";

    int len_a = sizeof(a) / sizeof(a[0]);
    int len_b = sizeof(b) / sizeof(b[0]);
    int len_c = sizeof(charA) / sizeof(charA[0]);
    
    quickSort(a,0,5);
    quickSort(b,0,2);
    quickSort(charA,0,len_c-1);
    
    print(a,len_a);
    print(b,len_b);
    print(charA,len_c);
}
`````



##### 1.2.4 普通函数与函数模板的区别

- 普通函数调用时可以发生自动类型转换（==隐式类型转换==）
- 函数模板调用时，如果利用自动类型推导，不会发生隐式类型转换
- 如果利用显示指定类型的方式，可以发生隐式类型转换

`````c++
#include<iostream>
using namespace std;

int myAdd(int a, int b){
    return a + b;
}

template<class T>
T myAdd02(T a, T b){
    return a + b;
}

int main(){
    int a = 10;
    double b = 10.999;
    char c = 'c';   //a-97 c-99
    int d = 1;
    cout<<myAdd(a,c)<<endl;
    cout<<myAdd(a,b)<<endl;
    
    cout<<myAdd02(a,d)<<endl;
    //cout<<myAdd02(a,c)<<endl;       //不给自动转换（或者说不知道转换为什么类型 
    cout<<myAdd02<int>(a,b)<<endl;
}
`````

> 总结：建议使用显示指定类型的方式，调用函数模板，因为可以自己确定通用类型T



##### 1.2.5 普通函数与函数模板的调用规则

1. 如果函数模板和普通函数都可以实现，**优先调用普通函数**
2. 可以通过**空模板参数列表**来强制调用函数模板
3. 函数**模板也可以发生重载**
4. 如果函数模板可以产生==更好的匹配==优先调用函数模板

```c++
#include<iostream>
using namespace std;

void myPrint(int a, int b){
    cout<<"This is a normal function."<<endl;
}

template<class T>
void myPrint(T a, T b){
    cout<<"This is template function."<<endl;
}

template<class T>
void myPrint(T a, T b, T c){
    cout<<"override template function."<<endl;
}

int main(){
    int a = 10;
    int b = 20;

    myPrint(a, b);
    myPrint<>(a, b);
    myPrint(a, b, 1);

    char a1 = 'a';
    char b1 = 'b';
    myPrint(a1, b1);
}
```

> 总结： 既然提供了函数模板，最好不要提供普通函数，否则容易出现二义性



##### 1.2.6 模板的局限性

`````c++
template<class T>
void func(T a, T b){
	a = b;
}
`````

如果a,b 传入的是数组，就无法实现

或如果T 的数据类型传入的是自定义的数据类型，也无法实现

因此为了解决这种问题，提供模板的重载，可以为这些**特定的类型**提供**具体化的模板**

`````c++
#include<iostream>
using namespace std;

class Person{
public:
    Person(int n){
        this->name = n;
    }
    string name;
};

template<class T>
bool myCompare(T &a, T &b){
    if(a == b)
        return true;
    return false;
}

//利用具体化Person的版本实现代码 具体化优先调用
//template<>告诉编译器这是一个特化的模板版本 不可以省略
template<> bool myCompare(Person &p1, Person &p2){		
    if(p1.name == p2.name)
        return true;
    return false;
}

int main(){
    int a = 10;
    int b = 20;
    bool rel = myCompare(a, b);
    if(rel)
        cout<<"a = b"<<endl;
    else    cout<<"a != b"<<endl;
    Person p1(1);
    Person p2(1);
    bool rel2 = myCompare(p1, p2);
    if(rel2)
        cout<<"a = b"<<endl;
    else    cout<<"a != b"<<endl;
}
`````

> 学习模板并不是为了写模板，而是在STL能够运用系统提供的模板



#### 1.3 类模板

##### 1.3.1 类模板语法

作用：

- 建立一个通用类，类中的成员 数据类型可以不具体制定，用一个虚拟的类型来代表

语法

```c++
template<typename T>
类
```

解释：

template — 声明创建模板

typename — 表面其后面的符号是一种数据类型，可以用class代替

T — 通用的数据类型，名称可以替换，通常为大写字母

`````c++
#include<iostream>
using namespace std;

template<class NameType, class AgeType>
class Person{
public:
    Person(NameType name, AgeType age){
        this->m_Name = name;
        this->m_Age = age;
    }
    void showPersonInfo(){
        cout<<"Name: "<<this->m_Name<<endl;
    }

    NameType m_Name;
    AgeType m_Age;
};

void test01(){
    Person<string,int> p1("kong", 1000);
    p1.showPersonInfo();
}

int main(){
    test01();
}
`````



##### 1.3.2 类模板与函数模板区别

1. 类模板**没有自动类型推导**的使用方式
2. 类模板在模板参数列表中可以有**默认参数**

`````c++
#include<iostream>
using namespace std;

template<class NameType, class AgeType = int>
class Person{
public:
    Person(NameType name, AgeType age){
        this->m_Age = age;
        this->m_Name = name;
    }

    void showInfo(){
        cout<<"Name: "<<this->m_Name<<" Age: "<<this->m_Age<<endl;
    }

    NameType m_Name;
    AgeType m_Age;
};

void test01(){
    //Person p("Xiao", 17);   //missing template arguments before'p'
    Person<string,int> p("Xiao", 17);
    p.showInfo();
}

void test02(){
    Person<string>p("Zhu",11);
    p.showInfo();
}

int main(){
    test01();
    test02();
}
`````



##### 1.3.3 类模板中成员函数创建时机

类模板中成员函数和普通类中成员函数创建时机是有区别的：

- 普通类中的成员函数一开始就可以创建
- 类模板中的成员函数在调用时才创建

`````c++
#include<iostream>
using namespace std;

class Person1{
public:
    void showPerson1(){
        cout<<"Person1 show"<<endl;
    }
};

class Person2{
public:
    void showPerson2(){
        cout<<"Person2 show"<<endl;
    }
};

template<class T>
class Myclass{
public:
    T obj;
    void func1(){
        obj.showPerson1();
    }
    void func2(){
        obj.showPerson2();
    }
};
//前面的代码build成功是因为类模板中的成员函数根本没有创建

int main(){
    Myclass<Person1> p1;
    p1.func1();
    //p1.func2();
}
`````

> [!NOTE]
>
> obj无法确认数据类型——成员函数未创建——直到调用（实例化）创建



##### 1.3.4 类模板对象做函数参数

- 类模板实例化出的对象，向函数传参的方式

1. 指定传入的类型       - - - 直接显示对象的数据类型
2. 参数模板化              - - - 将对象中的参数变为模板进行传递
3. 整个类模板化         - - - 将这个对象类型 模板化进行传递

`````c++
#include<iostream>
using namespace std;

template<class T1, class T2>
class Person{
public:
    Person(T1 name, T2 age){
        this->m_Age = age;
        this->m_Name = name;
    }
    void showInfo(){
            cout<<"Name: "<<m_Name<<" Age: "<<m_Age<<endl;
    }

    T1 m_Name;
    T2 m_Age;
};

//1 指定传入类型
void printPerson1(Person<string,int> &p){
    p.showInfo();
}

void test01(){
    Person<string,int> p("FEN", 20);
    printPerson1(p);
}

//2 参数模板化
template<class T1, class T2>
void printPerson2(Person<T1, T2> &p){
    p.showInfo();
    cout<<"T1 type: "<<typeid(T1).name()<<endl;
    cout<<"T2 type: "<<typeid(T2).name()<<endl;
}

void test02(){
    Person<string,int> p("NU", 20);
    printPerson2(p);
}

//3 整个类模板化
template<class T>
void printPerson3(T &p){
    p.showInfo();
}

void test03(){
    Person<string,int> p("Shang", 20);
    printPerson3(p);
}

int main(){
    test01();
    test02();
    test03();
}
`````

> 使用比较广泛的是第一种：指定传入类型



##### 1.3.5 类模板与继承

- 当子类继承的父类是一个类模板时，子类在声明的时候，要指定出父类中T的类型
- 如果不指定，编译器无法给子类分配内存
- 如果向灵活指定出父类中T的类型，子类也需要变为类模板

`````c++
#include<iostream>
using namespace std;

template<class T>
class Base{
public:
    T base_m;
};

class Son: public Base<int>{};

template<class T1, class T2>
class Son2: public Base<T2>{
    T1 obj;
};

int main(){
    Son2<int,char> s2;
}
`````



##### 1.3.6 类模板成员函数类外实现

`````c++
#include<iostream>
using namespace std;

template<class T1, class T2>
class  Person{
public:
    Person(T1 n, T2 a);
    void ShowInfo();
    T1 name;
    T2 age;
};

//构造函数类外实现
template<class T1, class T2>
Person<T1,T2>::Person(T1 n, T2 a){
    this->name = n;
    this->age = a;
} 

//成员函数类外实现
template<class T1, class T2>
void Person<T1,T2>::ShowInfo(){
    cout<<"....."<<endl;
}

int main(){
    Person<string,int> p("Tom", 11);
    p.ShowInfo();
}
`````



##### 1.3.7 类模板分文件编写

目标：

- 掌握类模板成员函数分文件编写产生的问题以及解决方式

问题：

- **类模板中成员函数创建时机是在调用阶段，导致分文件编写时链接不到**

解决：

- 1： 直接包含.cpp源文件
- 2：==将声明和实现写到同一个文件中==，并更改后缀名为.hpp



##### 1.3.8 类模板与友元

全局函数类内实现 —— 直接在类内声明友元

全局函数类外实现 —— 需要提前让编译器知道全局函数的存在

`````c++
#include<iostream>
using namespace std;

template<class T1, class T2>
class Person;
//编译器需要提前知道函数的存在
template<class t1, class t2>
void printPerson2(Person<t1,t2> p){
    cout<<"Name: "<<p.m_Name<<" Age: "<<p.m_Age<<endl;
}

template<class T1, class T2>
class Person{
    //全局 友元函数类内实现？
    friend void printPerson(Person<T1,T2> p){
        cout<<"Name: "<<p.m_Name<<" Age: "<<p.m_Age<<endl;
    }
    //添加空模板参数列表
    friend void printPerson2<>(Person<T1,T2> p);
public:
    Person(T1 name, T2 age){
        this->m_Age = age;
        this->m_Name = name;
    }
    void showInfo(){
            cout<<"Name: "<<m_Name<<" Age: "<<m_Age<<endl;
    }
private:
    T1 m_Name;
    T2 m_Age;
};

int main(){
    Person<string,int> p("RIu",20);
    printPerson(p);
    printPerson2(p);
}
`````

> 建议全局友元函数做类内实现。。



##### 1.3.9 类模板案例

案例描述：实现一个通用的数组类，需求如下：

-  可以对内置以及自定义的数据类型进行存储
-  将数组中的数据存储到堆区
-  构造函数中可以传入数组的容量
-  提供对应的构造拷贝函数以及operator=防止浅拷贝问题
-  提供尾插法和尾删法对数组中的数据进行增加和删除
-  可以通过下标的方式访问数组中的元素
-  可以获取数组中当前元素个数和数组的容量



### 2 STL初识

#### 2.1 STL的诞生

- 长久以来，软件界一直希望建立一种可重复利用的东西
- C++的**面向对象和泛型编程**思想，目的就是提升复用性
- 大多情况下，数据结构和算法都未能有一套标准，导致了大量重复工作
- 为了建立数据结构和算法的一套标准诞生了**STL**



#### 2.2 STL基本概念

- standard template library，**标准模板库**
- STL从广义上分为：**容器（container）算法（algorithm）迭代器（iterator）**
- **容器**和**算法**之间通过迭代器进行无缝衔接。
- STL几乎所有的代码都采用了模板类或者模板函数



#### 2.3 STL六大组件

STL大体分为六大组件，分别是**容器、算法、迭代器、仿函数、适配器（配接器）、空间配置器**

1. 容器：各种数据结构，如vector、list、deque、set、map等，用来存放数据。
2. 算法：各种常见的算法，如sort、find、copy、for_each等
3. 迭代器：扮演了容器与算法之间的胶合剂。
4. 仿函数：行为类似函数，可作为算法的某种策略。
5. 适配器：一种用来修饰容器或者仿函数或迭代器接口的东西。
6. 空间配置器：负责空间的配置与管理。



#### 2.4 STL中容器、算法、迭代器

**容器**：置物之所也

STL容器就是将运用**最广泛的一些数据结构**实现出来

常用的数据结构：数组、链表、树、栈、队列，集合，映射表等

这些容器分为**序列式容器**和**关联式容器**：

​	**序列式容器**：强调值的排序，序列式容器中的每个元素均有固定的位置

​	**关联式容器**：二叉树结构，各元素之间没有严格的物理上的顺序关系



**算法**：问题之解法也

有限的步骤，解决逻辑或数学上的问题，这一门学科我们叫做算法（algorithm）

算法分为：**质变算法**和**非质变算法**

**质变算法**：运算过程中会更改区间内的元素的内容。例如拷贝，替换，删除等

**非质变算法**：运算过程中不会更改区间内的元素内容，例如查找，计数，遍历，寻找极值等



**迭代器**：容器和算法之粘合剂

提供一种方法，使之能够依序寻访某个容器所含的各个元素，而又无需暴露该容器的内部的表达方式。

每个容器都有自己专属的迭代器

迭代器使用非常类似于指针，初学阶段我们可以先理解迭代器为指针。



迭代器种类：

| 种类           | 功能                                                     | 支持运算                   |
| -------------- | -------------------------------------------------------- | -------------------------- |
| 输入迭代器     | 对数据的只读访问                                         | 只读，支持++、==、!=       |
| 输出迭代器     | 对数据的只写访问                                         | ++                         |
| 前向迭代器     | 读写操作，并能向前推进迭代器                             | ++、==、!=                 |
| 双向迭代器     | 读写操作，并能向前和向后操作                             | ++、- -                    |
| 随机访问迭代器 | 读写操作，可以以跳跃的方式访问任意数据，功能最强的迭代器 | ++、- -、[n]、-n、<、>、>= |

常见的容器中迭代器种类为双向迭代器和随机访问迭代器



#### 2.5 容器算法迭代器初始

STL中最常用的容器为Vector，可以理解为数组。



##### 2.5.1 vector存放内置数据类型

容器：`vector`

算法：`for_each`

迭代器：`vector<int>::interator`



##### 2.5.2 vector存放自定义数据类型

学习目标：vector中存放自定义数据类型，并打印输出

> [!NOTE]
>
> (*it).getName()    it->getName()



##### 2.5.3 Vector容器嵌套容器

学习目标：容器中嵌套容器，我们将所有数据进行遍历输出



### 3 STL-常用容器

#### 3.1 string容器

##### 3.1.1 string基本概念

本质：

- string是c++风格的字符串，而string本质上是一个类

string和char*的区别：

- char*是一个指针
- string是一个类，类内部封装了char*，管理这个字符串，是一个char *类型的容器。

特点：

string类内部封装了很多成员方法

例如：find，copy，delete，insert，replace

string管理char*所分配的内存，不用担心复制越界和取值越界等，由类内部进行负责



##### 3.1.2 string构造函数

构造函数原型：

- string（）；	//创建一个空的字符串 例如：string str；
- string（const char* s）；      //使用字符串s初始化
- string（const string& str）；    //使用一个string对象初始化另一个string对象
- string（int n，char c）；    //使用n个字符c初始化

> 总结：string的多种构造方式没有可比性，灵活使用即可



##### 3.1.3 string赋值操作

功能描述：

- 给string字符串进行赋值



赋值的函数原型：

- string& operator=（const char* s）；    //char*类型字符串 赋值给当前的字符串
- string& operator=（const string &s）；    //把字符串赋给当前的字符串
- string& operator=（char c）；    //字符赋值给当前的字符串
- string& assign（const char *s）；    //把字符串s赋给当前的字符串
- string& assign（const char *s，int n）；    //把字符串s的前n个字符赋给当前字符串
- string& assign（const string &s）；    //把字符串s赋给当前字符串
- string& assign（int n，char c）；    //用n个字符c赋给当前字符串



##### 3.1.4 string字符串拼接

功能描述：

- 实现在字符串末尾拼接字符串



函数原型：

- 



##### 3.1.5 string查找和替换

功能描述：

- 查找：查找指定字符是否存在
- 替换：在指定的位置替换字符串

> [!NOTE]
>
> find从左往右找 rfind从右往左
>
> find找到字符串后返回查找的第一个字符位置，找不到返回-1
>
> replace在替换时，要指定从哪个位置起，多少个字符，替换成什么样的字符串



##### 3.1.6 string字符串比较

功能描述：

- 字符串之间的比较

比较方式：

- 字符串比较是按字符的ASCII码进行对比

= 返回 0

返回 1  >

< 返回 -1

> 主要意义是比较两个字符串是否相等



##### 3.1.7 string字符存取

string中单个字符存取方式有两种

[ ]   /    at



##### 3.1.8 string插入和删除

- 插入和删除字符串

> 插入和删除的起始下标都是0



##### 3.1.9 string子串

- 从字符串中获取想要的字串



#### 3.2 vector容器

##### 3.2.1 vector基本概念

功能：

- vector数据结构和**数组非常相似，也称为==单端==数组**



vector与普通数组区别：

- 数组是静态空间，vector可以动态扩展



动态扩展：

- 并不是在原空间之后续接新空间，而是找更大的内存空间，然后将原数据拷贝到新空间，释放原空间



- vector容器的迭代器是支持随机访问的迭代器



##### 3.2.2 vector构造函数



##### 3.2.3 vector赋值操作

- assign
- operator=



##### 3.2.4 vector容量和大小

- 判断是否为空——empty

- 返回元素个数——size
- 返回容器容量——capacity
- 重新指定大小——resize



##### 3.2.5 vector插入和删除

- 尾插 ——push_back
- 尾删——pop_back
- 插入——insert（位置迭代器）
- 删除——erase（位置迭代器）
- 清空——clear



##### 3.2.6 vector数据存取

- 出了用迭代器可以访问vector容器中的元素，[ ]和at也可以
- front返回容器的第一个元素
- back返回容器的最后一个元素



##### 3.2.7 vector互换容器



##### 3.2.8 vector预留空间

：减少vector在动态扩展容量时的扩展次数

容器预留len个元素长度，预留位置不初始化，元素不可访问	

如果数据量较大，可以一开始就利用reserve预留空间



#### 3.3 deque容器

##### 3.3.1deque容器的基本概念

功能：

- 双端数组，可以对双头进行插入删除操作

deque和vector区别：

- vector对于头部的插入删除效率低，数据量越大，效率越低
- deque相对而言，对头部的插入删除速度更快
- vector访问元素时的速度比deque快，和内部实现有关



##### 3.3.2 deque构造函数



##### 3.3.3 deque赋值操作



##### 3.3.4 deque大小



##### 3.3.5 deque插入和删除

两端插入操作：

指定位置操作：



##### 3.3.6 deque数据存取



##### 3.3.7 deque排序



#### 3.4 案例-评委打分

##### 3.4.1 案例描述

有5名选手：10个评委分别对每一名选手打分，去除最高分和最低分，取平均值



##### 3.4.2 实现步骤

1. 创建五名选手，放到vector中
2. 遍历vector容器，取出来每一个选手，执行for循环，可以把10个评分存到deque容器中
3. sort算法对deque容器中的分数排序，去除最高分和最低分
4. deque容器遍历一遍，累加总分
5. 获取平均分



#### 3.5 stack容器

##### 3.5.1 stack基本概念

：stack是一种先进后出（first in last out）的数据结构，它只有一个出口

栈中只有顶端的元素才可以被外界使用，因此栈不允许有遍历行为

栈中进入数据称为——入栈`push`

栈中弹出数据称为——出栈`pop`



##### 3.5.2 stack常用接口

：栈容器常用的对外接口

构造函数：



赋值操作：



数据存取：

- push(element)     //向栈顶添加元素
- pop（）    //从栈顶移除第一个元素
- top（）   //返回栈顶元素

大小操作：

- empty（）      //判断堆栈是否为空
- size（）       //返回栈的大小



#### 3.6 queue容器

##### 3.6.1 queue基本概念

：queue是一种**先进先出**（first in first out）的数据结构，它有两个出口

队列容器允许从一端新增元素，从另一端移除元素

队列中**只有队头和队尾才可以被外界使用**，因此队列不允许有遍历行为

队列中进数据称为——入队`push`

队列中出数称为——出队`pop`



##### 3.6.2 queue常用接口

构造函数：

赋值操作：

数据存取：

- push         //往队尾添加元素
- pop          //从队头移除第一个元素
- back           //返回最后一个元素
- front           //返回第一个元素

大小操作：

- empty            //判断队列是否为空
- size                 //返回队列的大小



#### 3.7 list容器

##### 3.7.1 list基本概念

:将数据进行链式存储

**链表**是一种物理储存单元上非连续的存储结构，数据元素的逻辑顺序是通过链表中的指针链接实现的



链表的组成：链表由一系列**节点**组成



节点的组成：一个是存储数据元素的**数据域**，另一个是存储下一个结点地址的**指针域**



STL中的链表是一个双向循环链表



由于链表的存储方式并不是连续的内存空间，因此链表list中的迭代器只支持前移和后移，属于**双向迭代器**



list的优点：

- 采用动态存储分配，不会造成内存浪费和溢出
- 链表执行插入和删除操作十分方便，修改指针即可，不需要移动大量元素

list的缺点：

- 链表灵活，但是空间（指针域）和时间（遍历）额外耗费较大

List有一个重要的性质，插入操作和删除操作都不会造成原有list迭代器的失效，这在vector是不成立的。



> STL中**list和vector是两个最常被使用的容器**，各有优缺点



##### 3.7.2 list构造函数



##### 3.7.3 list赋值和交换



##### 3.7.4 list大小操作



##### 3.7.5 list插入和删除



##### 3.7.6 list数据存取

因为不是连续存储空间，所以不能使用[ ] 和 .at( )方式访问数据



##### 3.7.7 list反转和排序



##### 3.7.8 排序案例

案例描述：将Person自定义数据类型进行排序，属性有姓名、年龄、身高

排序规则：按照年龄进行升序，如果年龄相同按照身高进行降序

> [!NOTE]
>
> 对于自定义数据类型，必须要指定排序规则，否则编译器不知道如何进行排序
>
> 高级排序只是在排序规则上再进行一次逻辑规则制定，并不复杂



#### 3.8 set / multiset 容器

##### 3.8.1 set基本概念

- 所有元素都会在插入时自动被排序

本质：

- set / multiset属于**关联式容器**，底层结构是用**二叉树**实现

set和multiset区别：

- set不允许容器有重复的元素
- multiset允许容器有重复的元素



##### 3.8.2 set构造和赋值



##### 3.8.3 set大小和交换



##### 3.8.4 set插入和删除



##### 3.8.5 set查找和统计



##### 3.8.6 set和multiset的区别



##### 3.8.7 pair对组创建

- 成对出现的数据，利用对组可以返回两个数据

​	

##### 3.8.8 set容器排序

- set容器默认排序规则为从小到大，掌握如何改变排序规则

- 利用仿函数，可以改变set容器的排序规则

1. set存放内置数据类型
2. 自定义数据类型
   - 对于自定义类型，不知道该按照什么排序，所以报错，需要自己指定规则



#### 3.9 map / multimap容器

##### 3.9.1 基本概念

简介：

- map中所有元素都是pair
- pair中第一个元素为**key（键值）**，起到索引作用，第二个元素为**value（实值）**
- 所有元素都会根据元素的键值自动排序

本质：

- map / multimap属于**关联式容器**，底层结构是用二叉树实现。

优点：

- 可以根据key值快速找到value值

map / multimap区别：

- map不允许容器中有重复key值元素
- multimap允许容器中有重复key值元素



##### 3.9.2 map构造和赋值



##### 3.9.3 map大小和交换



##### 3.9.4 map插入和删除



##### 3.9.5 map查找和统计



##### 3.9.6 map容器排序



##### 3.10 案例-员工分组

###### 3.10.1 案例描述

- 公司招聘了10个员工
- 员工信息：姓名，工资组成   部门：策划、美术、研发
- 随机给10名员工分配部门和工资
- 通过multimap进行信息的插入      
- 分部门显示员工信息



###### 3.10.2 实现步骤

1. 创建十名员工
2. 遍历vector容器，取出每个员工，进行随机分组
3. 分组后，将员工部门作为key，具体员工作为value，放入到multimap容器中
4. 分部门显示信息



### 4 STL-函数对象

#### 4.1 函数对象

##### 4.1.1 函数对象的概念

概念：

- 重载**函数调用操作符**的类，其对象常称为**函数对象**
- 函数对象使用重载的（）时，行为类似函数调用，也叫**仿函数**

本质：

函数对象（仿函数）是一个**类**，不是一个函数



##### 4.1.2 函数对象使用

特点：

- 函数对象在使用时，可以像普通函数那样调用，可以有参数，可以有返回值
- 函数对象超出普通函数的概念，函数对象可以有自己的状态
- 函数对象可以作为参数传递



#### 4.2 谓词

##### 4.2.1 谓词概念

概念：

- 返回bool类型的仿函数称为谓词
- 如果operator（）接受一个参数，那么叫做一元谓词
- 如果operator（）接受两个参收，那么叫做二元谓词



##### 4.2.2 一元谓词



##### 4.2.3 二元谓词



#### 4.3 内建函数对象

##### 4.3.1 内建函数对象意义

概念：

- STL 内建了一些函数对象

分类：

- 算术仿函数
- 关系仿函数
- 逻辑仿函数

用法：

- 这些仿函数所产生的对象，用法和一般函数完全相同
- 使用内建函数对象，需要引入头文件`#include<functional>`



##### 4.3.2 算术仿函数

plus minus multiplies divides modulus negate



##### 4.3.3 关系仿函数



##### 4.3.4 逻辑仿函数



### 5 STL-常用算法

概述：

- 算法主要由头文件`<algorithm>` `<functional>``<numberic>`组成
- algorithm是所有STL头文件中最大的一个，范围涉及到比较、交换、查找、遍历操作、复制、修改等等
- numeric体积很小，只包括几个在序列上面进行简单数学运算的模板函数
- functional定义了一些模板类，用以声明函数对象



#### 5.1 常用遍历算法

算法简介：

- `for_each`      //遍历容器
- `transform`       //搬运容器到另一个容器中



##### 5.1.1 for_each

功能描述：

- 实现遍历容器

函数原型：

`for_each(iterator beg, iterator end, _func)`



> for_each是开发中最常用的遍历算法



##### 5.1.2 transform

功能描述：

- 搬运容器到另一个容器中

函数原型：

`transform(iterator beg1, iterator end1, iterator beg2, _func);`

//beg1 源容器开始迭代器

//end1源容器结束迭代器

//beg2 目标容器开始迭代器

//_fun 函数或者函数对象



> 搬运的目标容器必须要提前开辟空间



#### 5.2 常用查找算法

算法简介：

- `find` 	//查找元素
- `find_if`              //按条件查找
- `adjacent_find`             //查找相邻重复元素
- `binary_search`          //二分法查找法
- `count`               //统计元素个数
- `count_if`              //按条件统计



##### 5.2.1 find

：找到返回指定元素的迭代器，找不到返回结束迭代器end()

`find(iterator beg, iterator end, value);`



> find 可以在容器中找指定的元素，==返回值是迭代器==



##### 5.2.2 find_if

`find_if(iterator beg, iterator end, _Pred);`

_pred函数或者谓词（返回bool'类型的仿函数）



##### 5.2.3 adjacent_find

返回相邻元素的第一个位置的迭代器



##### 5.2.4 binary_search

`bool binary_search(iterator beg, iterator end, value);`

- 返回true or false
- 注意：**在无序序列中不可用！**



##### 5.2.5 count

`count(iterator beg, iterator end, value);`



##### 5.2.6 count_if

`count_if(iterator beg, iterator end, _Pred);`



#### 5.3 常用排序算法

`sort`       //对容器内元素进行排序

`random_shuffle`       //洗牌   指定范围内的元素随机调整次序

`merge`      //容器元素合并，并存储到另一容器中

`reverse`       //反转指定范围的元素



##### 5.3.1 sort

`sort(iterator beg, iterator end, _Pred);`



##### 5.3.2 random_
