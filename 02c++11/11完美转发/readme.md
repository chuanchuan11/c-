> ## 完美转发

### (1) 什么是完美转发？

  完美转发的概念只对模板编程且对函数性能非常讲究的时候才有用。它指的是函数模板可以将自己的**参数“完美”地转发给内部调用的其它函数**。所谓完美，即不仅能准确地**转发参数的值，还能保证被转发参数的左、右值属性不变**。
  
```
 //1. 例子
template<typename T>
void function(T t) {
    otherdef(t);
}

如上所示：
    function() 函数模板中调用了 otherdef() 函数。在此基础上，完美转发指的是：如果 function() 函数接收到的参数 t 为左值，那么该函数传递给 otherdef() 的参数 t 也是左值；
反之如果 function() 函数接收到的参数 t 为右值，那么传递给 otherdef() 函数的参数 t 也必须为右值。

    显然，function() 函数模板并没有实现完美转发。一方面，参数 t 为非引用类型，这意味着在调用 function() 函数时，实参将值传递给形参的过程就需要额外进行一次拷贝操作；
另一方面，无论调用 function() 函数模板时传递给参数 t 的是左值还是右值，对于函数内部的参数 t 来说，它有自己的名称，也可以获取它的存储地址，因此它永远都是左值，也就是说，
传递给 otherdef() 函数的参数 t 永远都是左值。总之，无论从那个角度看，function() 函数的定义都不“完美”。

```

  该功能很常用吗？因为很多场景中是否实现完美转发，直接决定了该参数的传递过程使用的是拷贝语义（调用拷贝构造函数）还是移动语义（调用移动构造函数）。

### (2) 完美转发使用

   C++11 标准中规定，通常情况下右值引用形式的参数只能接收右值，不能接收左值。但对于**函数模板中**使用右值引用语法定义的参数来说，它**不再遵守这一规定，既可以接收右值，也可以接收左值**（此时的右值引用又被称为“万能引用”）。

```
#include <iostream>
using namespace std;

//重载被调用函数，查看完美转发的效果
void otherdef(int & t) {
    cout << "lvalue\n";
}
void otherdef(const int & t) {
    cout << "rvalue\n";
}

//实现完美转发的函数模板
template <typename T>
void function(T&& t) {
    otherdef(forward<T>(t));   //forword() 函数模板用于修饰被调用函数中需要维持参数左、右值属性的参数
}

int main()
{
    function(5);
    int  x = 1;
    function(x);
    return 0;
}

输出结果：
    rvalue
    lvalue
```

### (3) 完美转发实现原理

#####  1) 引用折叠

    引用折叠是模板编程中的一个概念，是为了解决模板推导后出现双重引用（如下所示）的情况

```
//1. c++11规定&&在模板变成中为万能引用
template <typename T>
void function(T&& t) {
    otherdef(t);
}

问题：
    参数 t 既可以接收左值，也可以接收右值。但如果调用 function() 函数时为其传递一个左值引用或者右值引用的实参：
int n = 10;
int & num = n;
function(num); // T 为 int&
int && num2 = 11;
function(num2); // T 为 int &&

    function(num) 实例化的函数底层就变成了 function(int& && t) 和 function(int&& && t)。要知道，C++98/03 标准是不支持这种用法的，而 C++ 11标准为了更好地实现完美转发，特意为其指定了新的类型匹配规则，又称为引用折叠规则：
    a) 当实参为左值或者左值引用（A&）时， 函数模板中 T&& 将转变为 A& （A& && = A&）；
    b) 当实参为右值或者右值引用（A&&）时，函数模板中 T&& 将转变为 A&&（A&& && = A&&）
    
    **如果任一引用为左值引用，则结果为左值引用。两个都是右值引用，结果为右值引用**
```

##### 2) 完美转发 std::forward

    但除此之外，还需要解决一个问题，即无论传入的形参是左值还是右值，对于函数模板内部来说，形参既有名称又能寻址，因此它都是左值。那么如何才能将函数模板接收到的形参连同其左、右值属性，一起传递给被调用的函数呢？

    C++11 标准的开发者已经帮我们想好的解决方案，该新标准还引入了一个模板函数 forword<T>()，

```
//实现完美转发的函数模板
template <typename T>
void function(T&& t) {
    otherdef(forward<T>(t));   //forword() 函数模板用于修饰被调用函数中需要维持参数左、右值属性的参数
}
```

    那么std::forward是如何做到完美转发的呢？

```
// std::forward的大致定义如下：[精简了标准库的代码，在细节上可能不完全正确，但是足以让我们了解转发函数 forward ]
template<typename T>
T&& forward(T &param){
    return static_cast<T&&>(param);
}

解释：
    不管T是值类型，还是左值引用，还是右值引用，T&经过引用折叠，都将是左值引用类型。也就是forward 以左值引用的形式接收参数 param

示例1：
    传入 function 实参是右值类型： 根据以上的分析，可以知道T将被推导为右值类型，也就是 int &&。那么，将T = int && 带入forward。
template <typename T>
void function(int&& && t) {
    otherdef(forward<int&&>(t));
}

int&& forward(int &param){
    return static_cast<int&& &&>(param);
}
    param在forward内还是右值引用。最终保持了实参的右值属性，转发正确。


示例2：
  传入 function 实参是左值类型：根据以上的分析，可以知道T将被推导为左值引用类型为int&。那么，将T = int& 带入forward。

template <typename T>
void function(int& && t) {
    otherdef(forward<int &>(t));
}

int& && forward(int& &param){
    return static_cast<int& &&>(param);
}

  引用折叠一下就是 int &类型，转发正确
```

参考：

(1) https://zhuanlan.zhihu.com/p/398817111

(2) http://c.biancheng.net/view/7868.html

