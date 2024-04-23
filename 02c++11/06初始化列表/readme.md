> ## C++11 初始化列表

### (1) 功能

  针对不同数据类型初始化方式不同，统一了各种对象的初始化方式，而且还使代码的书写更加简单清晰。

### (2) 初始化列表的使用

```
//多种数据类型，初始化方式不同
//1. 初始化列表初始化
int i_arr[3] = { 1, 2, 3 };  //普通数组
struct A
{
    int x;
    struct B
    {
        int i;
        int j;
    } b;
} a = { 1, { 2, 3 } };  //POD类型

//2. 拷贝初始化（copy-initialization）
int i = 0;
class Foo
{
    public:
    Foo(int) {}
} foo = 123;  //需要拷贝构造函数

//3. 直接初始化（direct-initialization）
int j(0);
Foo bar(123);

总结：只有数组和结构体可以使用初始化列表，C++11扩大初始化列表的使用范围

//1. 类对象使用初始化列表
class Foo
{
public:
    Foo(int) {}
private:
    Foo(const Foo &);
};

int main(void)
{
    Foo a1(123);      //直接初始化
    Foo a2 = 123;     //error: 'Foo::Foo(const Foo &)' is private 无法使用拷贝构造
    Foo a3 = { 123 }; //初始化列表初始化
    Foo a4 { 123 };   //初始化列表初始化
    int a5 = { 3 };   //初始化列表初始化
    int a6 { 3 };     //初始化列表初始化
    return 0;
}

//2. 初始化时，{}前面的等于号是否书写对初始化行为没有影响
int i_arr[3] { 1, 2, 3 };  //普通数组
struct A
{
    int x;
    struct B
    {
        int i;
        int j;
    } b;
} a { 1, { 2, 3 } };       //结构体

//3. new 操作符返回的内存，通过初始化列表方式初始化
int* a = new int { 123 };
int* arr = new int[3] { 1, 2, 3 };
```

```
总结：
    必须使用初始化列表的场景:
       (1) const 和 引用类型 的成员变量,必须使用初始化列表
       (2) 需要调用有参构造的成员类变量
       (3) 继承中需要调用基类有参构造的场景
```
