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

### (3) shared_ptr [共享智能指针]

  0) shared_ptr的定义
	
```
  和 unique_ptr、weak_ptr 不同之处在于，多个 shared_ptr 智能指针可以共同使用同一块堆内存。并且，由于该类型智能指针在实现上采用的是引用计数机制，即便有一个
shared_ptr 指针放弃了堆内存的“使用权”（引用计数减 1），也不会影响其他指向同一堆内存的 shared_ptr 指针（只有引用计数为 0 时，堆内存才会被自动释放）
```

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
  
  注意：shared_ptr管理动态数组时，需要指定删除器，默认删除器[delete]不支持数组对象
  
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
  
### (4) unique_ptr 智能指针[独占智能指针]

  0) unique_ptr 的定义

```
    某个时刻只能有一个unique_ptr指向一个动态分配的资源对象，也就是这个资源不会被多个unique_ptr对象同时占有. 它所管理的资源只能在unique_ptr对象之间进行移动，不能拷贝，所以它只提供了移动语义。
	
    资源对象的生命周期被唯一的一个unique_ptr对象托管着，一旦这个unique_ptr对象被销毁或者变成空对象，或者拥有了另一个资源对象，它所管理的资源对象同时一并销毁。资源对象要么随同unique_ptr对象一起销毁，要么在离开unique_ptr对象的管理范围时被销毁，从而保证了内存不会泄露	
```

  1) 基本使用

```
//1. 独占所指向的对象,通过函数返回给其他的unique_ptr，或者用std::move转移到其他的unique_ptr
     unique_ptr<int> p(new int);        // OK，正常初始化
     unique_ptr<int> p1 = p;            // 错误，unique_ptr不允许复制
     unique_ptr<int> p2 = std::move(p); // OK，移动语义初始化
     unique_ptr<int> p3 = unique_ptr<int>(new int(1));  //OK，使用匿名对象初始化
    
     注意：C++11中没有，C++14中才有make_unique
	
//2. unique_ptr可以指向一个数组
     unique_ptr<int []> ptr(new int[10])    //ok, 可以直接指定数组
     ptr[9]=9                               //ok, 重载[]
	
     shared_ptr<int []> ptr(new int[10])    //错误：shared_ptr 不支持,需通过删除器
     shared_ptr<int> p(new int[10], [](int* p) { delete [] p; }); //OK

//3. 指定删除器时，不能直接传入lambda表达式，需要指定删除器类型
     shared_ptr<int> p(new int(1), [](int* p) { delete p; });   // OK
	
     unique_ptr<int> p2(new int(1), [](int* p) { delete p; });  // 错误：为unique_ptr指定删除器时，需要确定删除器的类型
	
     unique_ptr<int, void(*)(int *)> p2(new int(1), [](int* p) { delete p; });  // OK, 无捕获列表可以转换为函数指针
	
     unique_ptr<int, void(*)(int *)> p2(new int(1), [&](int* p) { delete p; }); // 错误：有捕获列表时lambda无法转换为函数指针,需修改为std::function类型
	
     unique_ptr<int, function<void(int *)>> p2(new int(1), [&](int* p) { delete p; }); //OK
	
     注意：如果没有指定删除器，unique_ptr会使用缺省删除器，即缺省使用delete和delete[]来销毁对象，分别用于普通版本和数组版本。如果动态分配的资源有专门的释放函数，必须在构造时同时提供一个删除器
	
//3. 不能直接把裸指针赋值给unique_ptr对象，它没有提供这样的隐式转换，但是可以把nullptr赋值给unique_ptr对象。
     std::unique_ptr<int> up_0 = new int(4); // 错误：不支持隐式转换
     std::unique_ptr<int> up_1(nullptr);     // OK, 可以使用nullptr直接构造
     std::unique_ptr<int> up_2 = nullptr;    // OK, 可以使用nullptr直接赋值
     up_2.reset(nullptr);                    // OK

//4. 移动语义，一个unique_ptr对象在move时，源和目的unique_ptr对象的删除器类型也必须一样
     unique_ptr<int, function<void(int*)>> up1(new int(4), [](int *ptr){ddelete ptr;})
     unique_ptr<int> up2(move(up1));  错误：删除器类型不一样
	
```

参考：

(1) https://blog.csdn.net/moter/article/details/121075200

	
  2) 模板类提供的成员方法

```
示例：
1. get()获取原始裸指针
    int *q = up.get();
	
2. 重载[]，同时返回引用可以做为左值使用
    ar_up[1] = 150;

3. unique_ptr没有重载+, -, ++, -, +=, -=算数操作符，如果访问其他位置元素只能通过指针
    int *q = up.get();
    cout << *q << endl;
    cout << *(q+1) << endl;

4. 可以直接判断是否为nullptr
    if(!up)
	cout << "up is nullptr" << endl;
	
5. unique_ptr 可以像普通指针一样，实现多态

6. release 返回指针，放弃控制权，并将up置空
    int *p = up.release();  //返回裸指针，并不会释放内存，要由程序员负责释放这个指针
    up.release();           //内存泄漏
    int *p = up.get();      //返回裸指针，不需要程序员自己释放内存
	
```	
	
  3) 空间和时间开销成本

```
1. 一般而言，如果删除器不是缺省的或者空函数对象，unique_ptr对象与裸指针相比要占用额外的内存空间，即unique_ptr要分配空间来存放删除器对象，可见，为了管理动态分配的对象资源，在内存消耗上是要花费代价的。此外，在定义unique_ptr对象时，不要轻易使用std::function来声明删除器的类型，它会使unique_ptr的空间开销变得更大

2. unique_ptr使用了缺省删除器，无论是空间开销还是时间开销，几乎等同于使用裸指针的开销。使用其它形式的删除器，尤其是使用std::fucntion包装后的可调用对象作为删除器时，unique_ptr对象占用的内存空间要多一些，而且在调用删除器时，使用了动态绑定的函数调用形式，也会增加一定的运行时开销，我们在程序开发时要注意这点。
	
```	
	
  4) 使用场景

```
    如果希望只有一个智能指针管理资源或者管理数组就用unique_ptr
    如果希望多个智能指针管理同一个资源就用shared_ptr
```

参考：
	
(1) https://blog.csdn.net/Dorothy_yy/article/details/121446118
	
### (5) wake_ptr 智能指针[弱引用智能指针]

  0) wake_ptr 的定义

```	
    weak_ptr 定位为智能指针的一种，但该类型指针通常不单独使用（没有实际用处），只能和 shared_ptr 类型指针搭配使用。用来解决shared_ptr相互引用时的死锁问题

    需要注意的是，当 weak_ptr 类型指针的指向和某一 shared_ptr 指针相同时，weak_ptr 指针并不会使所指堆内存的引用计数加 1；同样，当 weak_ptr 指针被释放时，之前所指堆内存的引用计数也不会因此而减 1。也就是说，weak_ptr 类型指针并不会影响所指堆内存空间的引用计数。

    除此之外，weak_ptr<T> 模板类中没有重载 * 和 -> 运算符，这也就意味着，weak_ptr 类型指针只能访问所指的堆内存，而无法修改它
```	
		
  1) 基本使用

```
1. weak_ptr 指针的创建 
    std::shared_ptr<int> sp = make_shared<int>(1);  //创建一个shared_ptr指针
    std::weak_ptr<int> wp1 (sp);    //OK, 用shared_ptr来初始化
    std::weak_ptr<int> wp2(sp1);    //OK, 用已有的weak_ptr指针，来初始化
	
```

  2) 模板类提供的成员方法

![image](https://user-images.githubusercontent.com/42632290/169649754-5874fdd4-ab5e-42fb-a0b6-b1bb604e69fd.png)

```
示例：
#include <iostream>
#include <memory>
using namespace std;
int main()
{
    //1. 创建weak_ptr
    std::shared_ptr<int> sp1(new int(10));
    std::shared_ptr<int> sp2(sp1);
    std::weak_ptr<int> wp(sp2);

    cout << wp.use_count() << endl; // result: 2 输出和wp同指向的 shared_ptr 类型指针的数量

    //2. 释放 sp2
    sp2.reset();
    cout << wp.use_count() << endl; //result: 1 

    
    //3. 借助 lock() 函数，返回一个和 wp 同指向的 shared_ptr 类型指针，获取其存储的数据
    cout << *(wp.lock()) << endl;  //result: 10
    return 0;
	
    //4. expired 判断所观测到资源是否已经被释放，即：强引用所指向的对象还存在表示未过期
    if(wp.expired())
	cout << "该weak_ptr所指向的资源已经被释放了" << endl;

}

```

  3) 解决循环引用问题

```
// 用weak_ptr解决循环引用问题，具体方法是将A或B类中，shared_ptr类型修改为weak_ptr

struct A;
struct B;

struct A {
	shared_ptr<B> bptr;
	~A() { cout << "A is deleted" << endl; }
};

struct B {
	weak_ptr<A> aptr; // 将B中指向A对象的智能指针，由shared_ptr修改为weak_ptr
	~B() { cout << "B is deleted" << endl; }
};

void test() {
	shared_ptr<A> pa(new A);
	shared_ptr<B> pb(new B);
	pa->bptr = pb;
	pb->aptr = pa;
} // OK
```

参考：

(1) https://blog.csdn.net/weixin_44980842/article/details/121828485
	
(2) http://c.biancheng.net/view/7918.html
	
(3) https://blog.csdn.net/Dorothy_yy/article/details/121446118
