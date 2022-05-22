> ## std::function

##### (1) 什么是std::function

  C++中可调用对象的虽然都有一个比较统一的操作形式，但是定义方法五花八门，这样就导致**使用统一的方式保存可调用对象或者传递可调用对象**时，会十分繁琐。C++11中提供了std::function统一了可调用对象的各种操作。
    
  类模版std::function是一种通用、多态的函数封装。std::function的实例可以对任何可以调用的目标实体进行存储、复制、和调用操作，这些目标实体包括:
  
      1) 普通函数
      
      2) Lambda表达式
      
      3) 函数指针
      
      4) 仿函数[重载()运算符实现]
      
      5) 类成员函数
      
      6) 静态成员函数
      
  若std::function不含目标，则称它为空，调用空的std::function的目标会抛出std::bad_function_all异常
  
##### (2) 使用实例

```
#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;

//声明一个模板
typedef std::function<int(int)> Functional;

//普通函数
int TestFunc(int a)
{
  return a;
}

//lambda表达式
auto lambda = [](int a)->int{return a;};

//仿函数
class Functor
{
public:
  int operator() (int a)
  {
      return a;
  }
};

//类的成员函数和类的静态成员函数
class CTest
{
public:
  int Func(int a)
  {
      return a;
  }
  static int SFunc(int a)
  {
      return a;
  }
};

int main(int argc, char* argv[])
{
  //1. 封装普通函数
  Functional obj = TestFunc;
  int res = obj(0);
  cout << "normal function : " << res << endl;
  
  //2. 封装lambda表达式
  obj = lambda;
  res = obj(1);
  cout << "lambda expression : " << res << endl;
  
  //3. 封装仿函数
  Functor functorObj;
  obj = functorObj;
  res = obj(2);
  cout << "functor : " << res << endl;
  
  //4. 封装类的成员函数和static成员函数
  CTest t;
  obj = std::bind(&CTest::Func, &t, std::placeholders::_1);
  res = obj(3);
  cout << "member function : " << res << endl;
  
  obj = CTest::SFunc;
  res = obj(4);
  cout << "static member function : " << res << endl;
  return 0;
}

```

 **注意：std::function对象最大的用处就是在实现函数回调，它不能被用来检查相等或者不相等，但是可以与NULL或者nullptr进行比较
 
> ## std::bind

##### (1) std::bind的作用

  可将std::bind函数看作一个通用的**函数适配器**，它接受一个可调用对象，生成一个新的可调用对象来“适应”原对象的参数列表。

  std::bind将可调用对象与其参数一起进行绑定，绑定后的结果可以**使用std::function保存**,并延迟调用到任何需要的时候。std::bind主要有以下两个作用：

      1) 将可调用对象和其参数绑定成一个防函数；
      
      2) 只绑定部分参数，减少可调用对象传入的参数或改变参数传入顺序

##### (2) 实例

```
//1. bind静态函数
#include <functional>		// std::bind() 函数在头文件<functional>中
#include <iostream>

// 定义静态函数
void print_fruit(std::string fruit_1, std::string fruit_2)		
{
    std::cout << "fruit_1: " << fruit_1 <<std::endl;
    std::cout << "fruit_2: " << fruit_2 <<std::endl;
}

int main()
{
    // 将静态函数print_fruit绑定到fo，并传入参数
    // std::placeholders::_1为占位符，表示第一个参数的位置  
    auto fo = bind(&print_fruit, std::placeholders::_1 ,"banana"); //占位符的位置也可以打乱
    fo("apple");   
}
结果：
    fruit_1: apple
    fruit_2: banana

//2. bind类成员函数
#include <functional>
#include <iostream>

// 定义类
class Fruit{
public:
    void print_fruit(std::string fruit_1,std::string fruit_2,std::string fruit_3);
    void bind_test();
};

void Fruit::print_fruit(std::string fruit_1,std::string fruit_2,std::string fruit_3)
{
    std::cout << "fruit_1: " << fruit_1 << std::endl;
    std::cout << "fruit_2: " << fruit_2 << std::endl;
    std::cout << "fruit_3: " << fruit_2 << std::endl;
}

void Fruit::bind_test()
{
    // 第一个参数为成员函数地址，需要加取地址符，第二个参数为对象地址，类内可以用this，类外可以用&obj
    auto foo = std::bind(&Fruit::print_fruit, this, "apple_0",std::placeholders::_2,std::placeholders::_1);
    foo("apple_2","apple_3");
}

int main()
{
    Fruit test;
    test.bind_test();
}

结果为:
    fruit_1: apple_0
    fruit_2: apple_3
    fruit_3: apple_2

```

注意：bind常用场景为：类内成员函数做回掉函数，需要bind到this指针
