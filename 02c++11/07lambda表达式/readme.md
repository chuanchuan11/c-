> ## lambda 表达式

### (1) 功能描述

  它被用来表示一种**匿名函数**。所谓匿名函数，简单地理解就是没有名称的函数，又常被称为 lambda 函数或者 lambda 表达式。

### (2) lambda语法定义

```
语法格式：
          [外部变量访问方式说明符] (参数) mutable noexcept/throw() -> 返回值类型
          {
              函数体;
          };

1) [外部变量访问方式说明符]
   [] 方括号用于向编译器表明当前是一个 lambda 表达式，其不能被省略。在方括号内部，可以注明当前 lambda 函数的函数体中可以使用哪些“外部变量”。
所谓外部变量，指的是和当前 lambda 表达式位于同一作用域内的所有局部变量。

2) (参数)
   和普通函数的定义一样，lambda 匿名函数也可以接收外部传递的多个参数。和普通函数不同的是，如果不需要传递参数，可以连同 () 小括号一起省略

3) mutable
   此关键字可以省略，如果使用则之前的 () 小括号将不能省略（参数个数可以为 0）。默认情况下，对于以值传递方式引入的外部变量，不允许在 lambda 表达式内部修改它们的
值（可以理解为这部分变量都是 const 常量）。而如果想修改它们，就必须使用 mutable 关键字

   注意，对于以值传递方式引入的外部变量，lambda 表达式修改的是拷贝的那一份，并不会修改真正的外部变量；

4) noexcept/throw()
   可以省略，如果使用，在之前的 () 小括号将不能省略（参数个数可以为 0）。默认情况下，lambda 函数的函数体中可以抛出任何类型的异常。而标注 noexcept 关键字，则表示函数
体内不会抛出任何异常；使用 throw() 可以指定 lambda 函数内部可以抛出的异常类型。

   值得一提的是，如果 lambda 函数标有 noexcept 而函数体内抛出了异常，又或者使用 throw() 限定了异常类型而函数体内抛出了非指定类型的异常，这些异常无法使用 try-catch 捕获，会导致程序执行失败。 

5)  -> 返回值类型
   指明 lambda 匿名函数的返回值类型。如果 lambda 函数体内只有一个 return 语句，或者该函数返回 void，则编译器可以自行推断出返回值类型，此情况下可以
直接省略-> 返回值类型。

6) 函数体
   和普通函数一样，lambda 匿名函数包含的内部代码都放置在函数体中。该函数体内除了可以使用指定传递进来的参数之外，还可以使用指定的外部变量以及全局范围内的所有全局变量。

lambda匿名函数中的[外部变量]:
```

![image](https://user-images.githubusercontent.com/42632290/166631196-94cd4e20-ff69-4005-9ea6-d270a7a42749.png)

### (3) lambda表达式使用

```
//1. 从小到大排序
#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    int num[4] = {4, 2, 3, 1};
    //对 a 数组中的元素进行排序
    sort(num, num+4, [=](int x, int y) -> bool{ return x < y; } );
    for(int n : num){
        cout << n << " ";
    }
    return 0;
}

执行结果：
   1 2 3 4

//2. 使用auto设置匿名函数名
#include <iostream>
using namespace std;
int main()
{
    //display 即为 lambda 匿名函数的函数名
    auto display = [](int a,int b) -> void{cout << a << " " << b;};
    //调用 lambda 函数
    display(10,20);
    return 0;
}

执行结果：
   10 20
   
//3. 值传递方式只能修改全局变量，无法修改外部变量，值引用方式修改外部变量
#include <iostream>
using namespace std;
//全局变量
int all_num = 0;

int main()
{
    //局部变量
    int num_1 = 1;
    int num_2 = 2;
    int num_3 = 3;
    cout << "lambda1:\n";
    auto lambda1 = [=]{
        //全局变量可以访问甚至修改
        all_num = 10;
        //函数体内只能使用外部变量，而无法对它们进行修改
        cout << num_1 << " "
             << num_2 << " "
             << num_3 << endl;
    };
    lambda1();
    cout << all_num <<endl;
    
    cout << "lambda2:\n";
    auto lambda2 = [&]{
        //全局变量和外部变量都可以访问甚至修改
        all_num = 100;
        num_1 = 10;
        num_2 = 20;
        num_3 = 30;
        cout << num_1 << " "
             << num_2 << " "
             << num_3 << endl;
    };
    lambda2();
    cout << all_num << endl;
    return 0;
}

//4. 执行抛出异常类型
#include <iostream>
using namespace std;
int main()
{
    auto except = []()throw(int) {
        throw 10;
    };
    try {
        except();
    }
    catch (int) {
        cout << "捕获到了整形异常";
    }
    return 0;
}

执行结果：
   捕获到了整形异常
   
5. 程序运行会直接崩溃, 由于指定异常类型和真正发生的异常类型不匹配，导致 try-catch 无法捕获
#include <iostream>
using namespace std;
int main()
{
    auto except1 = []()noexcept{
        throw 100;
    };
    auto except2 = []()throw(char){
        throw 10;
    };
    try{
        except1();
        except2();
    }catch(int){
        cout << "捕获到了整形异常"<< endl;
    }
    return 0;
}

```
