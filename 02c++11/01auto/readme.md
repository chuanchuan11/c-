> ## auto 类型推导

(1) auto 功能

   C++11 赋予 auto 关键字新的含义，使用它来做自动类型推导。也就是说，使用了 auto 关键字以后，编译器会在编译期间自动推导出变量的类型，这样我们就不用手动指明变量的数据类型了。

(2) auto 使用

```
//auto与其他类型混用
int  x = 0;
auto *p1 = &x;   //p1 为 int *，auto 推导为 int
auto  p2 = &x;   //p2 为 int*，auto 推导为 int*
auto &r1  = x;   //r1 为 int&，auto 推导为 int
auto r2 = r1;    //r2 为  int，auto 推导为 int

//auto与const结合
int  x = 0;
const  auto n = x;   //n 为 const int ，auto 被推导为 int
auto f = n;          //f 为 const int，auto 被推导为 int（const 属性被抛弃）
const auto &r1 = x;  //r1 为 const int& 类型，auto 被推导为 int
auto &r2 = r1;       //r1 为 const int& 类型，auto 被推导为 const int 类型

```

(3)auto 限制

  a) 使用 auto 类型推导的变量必须马上初始化
  
      因为 auto 在 C++11 中只是“占位符”，并非如 int 一样的真正的类型声明。

  b) auto 不能在函数的参数中使用

      定义函数的时候只是对参数进行了声明，指明了参数的类型，但并没有给它赋值，只有在实际调用函数的时候才会给参数赋值；而 auto 要求必须对变量进行初始化，所以这是矛盾的
      
  c) auto 不能作用于类的非静态成员变量（也就是没有 static 关键字修饰的成员变量）中     
      
  d) auto 关键字不能定义数组 

```
char url[] = "http://c.biancheng.net/";
auto  str[] = url;  //arr 为数组，所以不能使用 auto
``` 

  e) auto 不能作用于模板参数
      
```
template <typename T>
class A{
    //TODO:
};
int  main(){
    A<int> C1;
    A<auto> C2 = C1;  //错误
    return 0;
}
```
   
(4) auto 常用场景
   
  a) 定义 stl 的迭代器, 简化迭代器类型的定义
   
```
//正常定义
#include <vector>
using namespace std;
int main(){
    vector<int> v1;
    vector<int>::iterator i = v.begin(); //定义迭代器 i 的时候，类型书写比较冗长，容易出错
    return 0;
}

//使用auto简化迭代器定义
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);

    for(auto ele=v1.begin(); ele!=v1.end(); ele++)       //auto 定义的ele 相当于vector<int>::iterator
    {
        cout << *ele << endl; 
    }
}

//使用auto简化for循环
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);

    for(auto ele : v1)       //auto 定义的ele 相当于v1中的元素
    {
        cout << ele << endl; 
    }
}

```

参考：

(1) http://c.biancheng.net/view/6984.html

