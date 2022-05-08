> ## 智能指针

### (1) 初始化空指针

  我们更习惯将指针初始化为 NULL。值得一提的是，NULL 并不是 C++ 的关键字.它是 C++ 为我们事先定义好的一个宏，并且它的值往往就是字面量 0（#define NULL 0）。
  
  nullptr 是 nullptr_t 类型的右值常量，专用于初始化空类型指针。nullptr_t 是 C++11 新增加的数据类型，可称为“指针空值类型”

```
//在 C++11 标准下，相比 NULL 和 0，使用 nullptr 初始化空指针可以令我们编写的程序更加健壮
int * a1 = nullptr;
char * a2 = nullptr;
double * a3 = nullptr;
```

### (2) 什么是智能指针

  智能指针是存储指向动态分配（位于堆）对象指针的类，用于生存期控制，能确保在离开指针所在作用域时，自动正确地销毁动态分配的对象，以防止内存泄漏。
智能指针通常通过引用计数技术实现：每使用一次，内部引用计数+1；每析构一次，内部引用计数-1，**当减为0时，删除所指堆内存**

  C++11提供3种智能指针：std::shared_ptr, std::unique_ptr, std::weak_ptr, 每种智能指针都是以类模板的方式实现的，shared_ptr 也不例外。shared_ptr<T>（其中 T 表示指针指向的具体数据类型）的定义位于<memory>头文件，并位于 std 命名空间中

```
#include <memory>
using namespace std;
```

### (3) shared_ptr 智能指针

  1) 基本使用
  
```  
  
``` 

  2) 模板类提供的成员方法

```
  
```
  
  3) 使用陷阱

```
  
```
  
  4) 多线程使用
 
```
  
```

参考：
  
(1) https://blog.csdn.net/Dorothy_yy/article/details/121446118
  
(2) http://m.biancheng.net/view/7898.html
  
  
### (4) unique_ptr 智能指针


### (5) wake_ptr 智能指针




