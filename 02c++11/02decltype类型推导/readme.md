> ## decltype 自动类型推导

### (1) decltype 功能

  auto 并不适用于所有的自动类型推导场景，在某些特殊情况下 auto 用起来非常不方便，甚至压根无法使用，所以 decltype 关键字也被引入到 C++11 中

```
auto varname = value;
decltype(exp) varname = value;

auto 根据=右边的初始值 value 推导出变量的类型，而 decltype 根据 exp 表达式推导出变量的类型，跟=右边的 value 没有关系。所以 auto 要求变量必须初始化，** 而 decltype 不要求 **。
```

  exp 就是一个普通的表达式，它可以是任意复杂的形式，但是我们必须要保证 exp 的结果是有类型的，不能是 void；例如，当 exp 调用一个返回值类型为 void 的函数时，exp 的结果也是 void 类型，此时就会导致编译错误。

### (2) decltype 推导规则

  a) 如果 exp 是一个不被括号( )包围的表达式，或者是一个类成员访问表达式，或者是一个单独的变量，那么 decltype(exp) 的类型就和 exp 一致，这是最普遍最常见的情况
  
  b) 如果 exp 是函数调用，那么 decltype(exp) 的类型就和函数返回值的类型一致
  
  c) 如果 exp 是一个左值，或者被括号( )包围，那么 decltype(exp) 的类型就是 exp 的引用；假设 exp 的类型为 T，那么 decltype(exp) 的类型就是 T&。
  
```
//规则1：表达式为普通表达式
#include <string>
using namespace std;

class Student{
public:
    static int total;
    string name;
    int age;
    float scores;
};
int Student::total = 0;

int  main(){
    int n = 0;
    const int &r = n;
    Student stu;
    decltype(n) a = n;                                          //n 为 int 类型，a 被推导为 int 类型
    decltype(r) b = n;                                          //r 为 const int& 类型, b 被推导为 const int& 类型
    decltype(Student::total) c = 0;                             //total 为类 Student 的一个 int 类型的成员变量，c 被推导为 int 类型
    decltype(stu.name) url = "http://c.biancheng.net/cplus/";   //total 为类 Student 的一个 string 类型的成员变量， url 被推导为 string 类型
    return 0;
}


//规则2：表达式为函数调用
//函数声明
int& func_int_r(int, char);  //返回值为 int&
int&& func_int_rr(void);     //返回值为 int&&
int func_int(double);        //返回值为 int
const int& fun_cint_r(int, int, int);  //返回值为 const int&
const int&& func_cint_rr(void);        //返回值为 const int&&

//decltype类型推导
int n = 100;
decltype(func_int_r(100, 'A')) a = n;  //a 的类型为 int&
decltype(func_int_rr()) b = 0;         //b 的类型为 int&&
decltype(func_int(10.5)) c = 0;        //c 的类型为 int
decltype(fun_cint_r(1,2,3))  x = n;    //x 的类型为 const int &
decltype(func_cint_rr()) y = 0;        //y 的类型为 const int&&

注意：
  exp 中调用函数时需要带上括号和参数，但这仅仅是形式，并不会真的去执行函数代码
  
//规则3：表达式为左值或者被()包围

using namespace std;
class Base{
public:
    int x;
};

int main(){
    const Base obj;
    
    //带有括号的表达式
    decltype(obj.x) a = 0;    //obj.x 为类的成员访问表达式，符合推导规则一，a 的类型为 int
    decltype((obj.x)) b = a;  //obj.x 带有括号，符合推导规则三，b 的类型为 int&。
    
    //加法表达式
    int n = 0, m = 0;
    decltype(n + m) c = 0;      //n+m 得到一个右值，符合推导规则一，所以推导结果为 int
    decltype(n = n + m) d = c;  //n=n+m 得到一个左值，符号推导规则三，所以推导结果为 int&
    return 0;
}

左值与右值：左值是指那些在表达式执行结束后依然存在的数据，也就是持久性的数据；右值是指那些在表达式执行结束后不再存在的数据，也就是临时性的数据。有一种很简单的方法来区分左值和右值，对表达式取地址，如果编译器不报错就为左值，否则为右值。


```

### (3) decltype 的实际应用

  a) auto 只能用于类的静态成员，不能用于类的非静态成员（普通成员），如果我们想推导非静态成员的类型，这个时候就必须使用 decltype 了

```
#include <vector>
using namespace std;

template <typename T>
class Base {
public:
    void func(T& container) {
        m_it = container.begin();
    }
private:
    typename T::iterator m_it;  //注意这里, T::iterator并不能包括所有的迭代器类型，当 T 是一个 const 容器时，应当使用 const_iterator。
};

int main()
{
    const vector<int> v;
    Base<const vector<int>> obj;
    obj.func(v);
    return 0;
}

//简化
template <typename T>
class Base {
public:
    void func(T& container) {
        m_it = container.begin();
    }
private:
    decltype(T().begin()) m_it;  //注意这里， 自动推导出类型
};
```
