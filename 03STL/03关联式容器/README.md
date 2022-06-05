> ## 关联式容器

##### 1. 概述

    关联式容器存储的元素，都是一个一个的“键值对”（ <key,value> ），这是和序列式容器最大的不同。除此之外，序列式容器中存储的元素默认都是未经过排序的，而使用关联式容器存储的元素，默认会根据各元素的键值的大小做升序排序
    
```
map: 各个元素的键必须是唯一的（即不能重复），该容器会根据各元素键的大小，默认进行升序排序（调用 std::less<T>）

set: 各个元素键和值完全相同，且各个元素的值不能重复（保证了各元素键的唯一性）, 该容器会自动根据各个元素的键（其实也就是元素值）的大小进行升序排序（调用 std::less<T>）

multimap: 和 map 容器唯一的不同在于，multimap 容器中存储元素的键可以重复

multiset: 和 set 容器唯一的不同在于，multiset 容器中存储元素的值可以重复（一旦值重复，则意味着键也是重复的）

注意：C++ 11 还新增了 4 种哈希容器，即 unordered_map、unordered_multimap 以及 unordered_set、unordered_multiset。严格来说，它们也属于关联式容器，但由于哈希容器底层采用的是哈希表，而不是红黑树。后续讲解
```

##### 2. pair用法

    考虑到“键值对”并不是普通类型数据，C++ STL 标准库提供了 pair 类模板，其专门用来将 2 个普通元素 first 和 second（可以是 C++ 基本数据类型、结构体、类自定的类型）创建成一个新元素<first, second>。通过其构成的元素格式不难看出，使用 pair 类模板来创建“键值对”形式的元素，再合适不过。

```
1. 头文件：pair 类模板定义在<utility>头文件中

2. pair对象创建
#include <iostream>
#include <utility>      // pair
#include <string>       // string
using namespace std;

int main() {
    // 1. 调用默认构造函数
    pair <string, double> pair1;
    // 2. 调用有参构造函数
    pair <string, string> pair2("STL教程","http://www.cdsy.xyz/computer/programme/stl/");  
    // 3. 调用拷贝构造函数
    pair <string, string> pair3(pair2);
    // 4. 调用移动构造函数
    pair <string, string> pair4(make_pair("C++教程", "http://www.cdsy.xyz/computer/programme/vc/"));  //make_pair() 函数的返回值（是一个临时对象）
    // 5. 调用右值引用构造函数
    pair <string, string> pair5(string("Python教程"), string("http://www.cdsy.xyz/computer/programme/Python/"));  
   
    cout << "pair1: " << pair1.first << " " << pair1.second << endl; 
    cout << "pair2: "<<  pair2.first << " " << pair2.second << endl;
    cout << "pair3: " << pair3.first << " " << pair3.second << endl;
    cout << "pair4: " << pair4.first << " " << pair4.second << endl;
    cout << "pair5: " << pair5.first << " " << pair5.second << endl;
    return 0;
}

3. C++ 11 还允许手动为 pair1 对象赋值
pair1.first = "Java教程";
pair1.second = "http://www.cdsy.xyz/computer/programme/java/";
cout << "new pair1: " << pair1.first << " " << pair1.second << endl;

4. make_pair还可以直接使用
pair <string, string> pair4 = make_pair("C++教程", "http://www.cdsy.xyz/computer/programme/vc/");
cout << "pair4: " << pair4.first << " " << pair4.second << endl;

5. <utility>头文件中除了提供创建 pair 对象的方法之外，还为 pair 对象重载了 <、<=、>、>=、==、!= 这 6 的运算符，其运算规则是：对于进行比较的 2 个 pair 对象，先比较 pair.first 元素的大小，如果相等则继续比较 pair.second 元素的大小

#include <iostream>
#include <utility>      // pair
#include <string>       // string
using namespace std;
int main() {
    pair <string, int> pair1("STL教程", 20);
    pair <string, int> pair2("C++教程", 20);
    pair <string, int> pair3("C++教程", 30);
    //pair1和pair2的key不同，value相同
    if (pair1 != pair2) {
        cout << "pair != pair2" << endl;   //pair != pair2
    }
    //pair2和pair3的key相同，value不同
    if (pair2 != pair3) {
        cout << "pair2 != pair3" << endl;  //pair2 != pair3
    }
    return 0;
}

注意：对于进行比较的 2 个 pair 对象，其对应的键和值的类型要相同，否则将没有可比性，同时编译器提示没有相匹配的运算符，即找不到合适的重载运算符。

//6. pair类模板还提供有一个 swap() 成员函数，能够互换 2 个 pair 对象的键值对，其操作成功的前提是这 2 个 pair 对象的键和值的类型要相同
#include <iostream>
#include <utility>      // pair
#include <string>       // string
using namespace std;
int main() {
    pair <string, int> pair1("pair", 10);                   
    pair <string, int> pair2("pair2", 20);
    //交换 pair1 和 pair2 的键值对
    pair1.swap(pair2);
    cout << "pair1: " << pair1.first << " " << pair1.second << endl;  //pair1: pair2 20
    cout << "pair2: " << pair2.first << " " << pair2.second << endl;  //pair2: pair 10
    return 0;
}

```

##### 2. map容器




##### 3. set容器




##### 4. multimap容器




##### 5. multiset容器



