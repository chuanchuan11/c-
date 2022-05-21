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

  0) shared_ptr的定义
	
	和 unique_ptr、weak_ptr 不同之处在于，多个 shared_ptr 智能指针可以共同使用同一块堆内存。并且，由于该类型智能指针在实现上采用的是引用计数机制，即便有一个
	
shared_ptr 指针放弃了堆内存的“使用权”（引用计数减 1），也不会影响其他指向同一堆内存的 shared_ptr 指针（只有引用计数为 0 时，堆内存才会被自动释放）

  1) 基本使用
  
```  
//1. 创建空智能指针
  std::shared_ptr<int> p1;             //不传入任何实参
  std::shared_ptr<int> p2(nullptr);    //传入空指针 nullptr
 
  注意：空的 shared_ptr 指针，其初始引用计数为 0，而不是 1 

//2. 创建并初始化智能指针
  std::shared_ptr<int> p3(new int(10));                //指向一块存有 10 这个 int 类型数据的堆内存空间
  std::shared_ptr<int> p3 = std::make_shared<int>(10); //使用 std::make_shared<T> 模板函数初始化，两种方式完全相同
  
//3. 使用拷贝构造或移动构造初始化
  std::shared_ptr<int> p4(p3);//或者 std::shared_ptr<int> p4 = p3;                        //调用拷贝构造函数
  std::shared_ptr<int> p5(std::move(p4)); //或者 std::shared_ptr<int> p5 = std::move(p4); //调用移动构造函数
  
  注意：若 p3 为空智能指针，则 p4 也为空智能指针，其引用计数初始值为 0；反之，则表明 p4 和 p3 指向同一块堆内存，同时该堆空间的引用计数会加 1。
        移动构造函数和调用拷贝构造函数不同，用 std::move(p4) 初始化 p5，会使得 p5 拥有了 p4 的堆内存，而 p4 则变成了空智能指针
  
//4. 获取原始指针
shared_ptr<int> p(new int(1));
int* rawp = p.get();         //get获取原始指针并不会引起引用计数变化，需要小心若智能指针释放了对象，该指针所指向的对象也就消失了
cout << *rawp << endl;
  
//5. 指定删除器：自定义释放规则
   void DeleteIntPtr(int* p)   //自定义删除器DeleteIntPtr
   {
	    delete p;
   }
  shared_ptr<int> p(new int, DeleteIntPtr);                      // 为指向int的shared_ptr指定删除器，删除器是自定义函数
  shared_ptr<int> p1(new int, [](int* p) { delete p; });         // 删除器也可以是lambda表达式
  
  注意：shared_ptr管理动态数组时，需要指定删除器，默认删除器不支持数组对象
  
//6. 数组指定delete[]删除器
  void deleteInt(int*p)     //自定义释放规则
  {
    delete []p;
  }

  std::shared_ptr<int> p7(new int[10], deleteInt);                //初始化智能指针，并自定义释放规则
  std::shared_ptr<int> p7(new int[10], [](int* p) {delete[]p; }); //通过lambda表达式删除

``` 

  2) 模板类提供的成员方法

  ![image](https://user-images.githubusercontent.com/42632290/167294273-c3fa4597-c03f-483c-b81b-6d489d3cfd30.png)
 
```
示例：
#include <iostream>
#include <memory>
using namespace std;
int main()
{
    //构建 2 个智能指针
    std::shared_ptr<int> p1(new int(10));
    std::shared_ptr<int> p2(p1);
  
    //输出 p2 指向的数据
    cout << *p2 << endl;
  
    p1.reset();//引用计数减 1,p1为空指针
  
    if (p1) {
        cout << "p1 不为空" << endl;
    }
    else {
        cout << "p1 为空" << endl;
    }
  
    //以上操作，并不会影响 p2
    cout << *p2 << endl;
  
    //判断当前和 p2 同指向的智能指针有多少个
    cout << p2.use_count() << endl;
    return 0;
}
```
  
  3) 使用陷阱

```
//1. 不要用同一原始指针分别初始化多个shared_ptr,这些shared_ptr指向同一块内存，并不知道互相的存在，当在引用计数为0时，造成多次析构原始指针
  int* ptr = new int;
  std::shared_ptr<int> p1(ptr);
  std::shared_ptr<int> p2(ptr);//错误
  
//2. 不要在函数实参中创建shared_ptr
  void func(shared_ptr<int> p, int a);
  int g();
  func(shared_ptr<int>(new int), g()); // 有缺陷
  
  C++的函数参数计算顺序在不同的编译器（不同的默认调用惯例）下，可能不一样，一般从右到左，也可能从左到右，因而可能的过程是先new int，然后调用g()。如果恰好g()发送异常，而shared_ptr 尚未创建，那么int内存就泄漏了
  
  正确做法：先创建智能指针，然后调用函数
  shared_ptr<int> p(new int());
  f(p, g());

//3. 不要将this指针作为shared_ptr返回出来，因为this指针本质上是一个裸指针，可能会导致重复析构
class A {
	shared_ptr<A> GetSelf() 
  {
		return shared_ptr<A>(this); //不要这样做，可能导致重复析构
	}
	~A() 
  {
		cout << "~A()" << endl;
	}
};

shared_ptr<A> p1(new A);
shared_ptr<A> p2 = p1->GetSelf(); // 同一个this指针构造了两个智能指针，他们之间没有任何联系，当离开作用域，this指针会被两个智能指针分别析构，造成重复析构的错误
  
//4. 避免循环引用 （循环引用会导致内存泄漏）
  struct A;
  struct B;

  struct A {
    std::shared_ptr<B> bptr;
    ~A() { cout << "A is delete!" << endl; }
  };
  struct B {
    std::shared_ptr<A> aptr;
    ~B() { cout << "B is delete!" << endl; }
  };

  void test() {
    shared_ptr<A> ap(new A);
    shared_ptr<B> bp(new B);
    ap->bptr = bp;
    bp->aptr = ap;
    // A和B对象应该都被删除，然而实际情况是都不会被删除：没有调用析构函数
  }
  
  循环引用导致对象ap和bp的引用计数为2，在离开作用域后，ap、bp指针被释放，对象的引用计数变为1，不会减为0。A中通过bptr持有了B，A要释放要B先释放。

```
  
  4) 多线程使用
 
```
shared_ptr的线程安全级别：
  a) 一个shared_ptr对象实体可被多个线程同时读取
  b) 两个shared_ptr对象实体可以被两个线程同时写入
  c) 如果多个线程同时读写同一个shared_ptr对象，需要加锁
```

参考：
  
(1) https://blog.csdn.net/Dorothy_yy/article/details/121446118
  
(2) http://m.biancheng.net/view/7898.html
  
(3) https://www.cnblogs.com/fortunely/p/15815741.html
  
### (4) unique_ptr 智能指针


### (5) wake_ptr 智能指针




