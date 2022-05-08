> ## 移动构造函数

### (1) 为什么引入右值引用，引入移动构造函数？

  引入右值引用的主要目的是提高程序运行的效率。当类持有其它资源时，例如动态分配的内存、指向其他数据的指针等，拷贝构造函数中需要以深拷贝（而非浅拷贝）的方式复制对象的所有数据。深拷贝往往非常耗时，合理使用右值引用可以避免没有必要的深拷贝操作。

  这里引入了移动语义，所谓移动语义（Move语义），指的就是以移动而非深拷贝的方式初始化含有指针成员的类对象。对于程序执行过程中产生的临时对象，往往只用于传递数据（没有其它的用处），并且会很快会被销毁。因此在使用临时对象初始化新对象时，我们可以将其包含的指针成员指向的内存资源直接移给新对象所有，无需再新拷贝一份，这大大提高了初始化的执行效率。

  移动语义的具体实现就是C++移动构造函数。

```
例子：
#include <iostream>
#include <string>

using namespace std;

class Integer
{
public:
    //参数为常量左值引用的深拷贝构造函数，不改变source.ptr_的值
    Integer(const Integer& source) : ptr_(new int(*source.ptr_))
    {
        cout << "const左值引用拷贝构造函数" << endl;
    }

    //参数为左值引用的深拷贝构造函数，转移堆内存资源所有权后，改变source.ptr_的值
    Integer(Integer& source) : ptr_(source.ptr_)
    {
        source.ptr_ = nullptr;
        cout << "左值引用拷贝构造函数" << endl;
    }

    Integer(int value) : ptr_(new int(value))
    {
        cout << "有参构造函数" << endl;
    }

    ~Integer()
    {
        cout << "析构函数" << endl;
    }

    int GetValue(void)
    {
        return *ptr_;
    }
private:
    string name_;
    int* ptr_;

};

int main()
{
    Integer a(Integer(100)); //匿名对象为右值，调用常左值引用拷贝构造
    int a_value = a.GetValue();
    cout << a_value << endl;
    cout << "--------------------" << endl;

    Integer temp(200);
    Integer b(temp); //左值对象，优先调用左值引用拷贝构造
    int b_value = b.GetValue();
    cout << b_value << endl;
    cout << "--------------------" << endl;

    return 0;

}

输出结果：【编译时需加：-fno-elide-constructors】
   有参构造函数
   const左值引用拷贝构造函数
   析构函数
   100
   -----------------------
   有参构造函数
   左值引用拷贝构造函数
   200
   -----------------------
   析构函数
   析构函数
   析构函数

```

  可知：当同时存在参数类型为常量左值引用和左值引用的深拷贝构造函数时，匿名对象 Integer(100) 只能选择前者，非匿名对象 temp 可以选择后者，这是因为**常量左值引用**可以接受**左值、右值、常量左值、常量右值**，而**左值引用**只能接受**左值**。因此，对于匿名变量，参数为任何类型左值引用的深拷贝构造函数都无法实现完美转发。还有一种办法--右值引用。

![image](https://user-images.githubusercontent.com/42632290/167282250-4172b49c-252a-4bf6-a53a-a0971c1e324c.png)

### (2) 移动构造函数











