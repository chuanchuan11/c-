> ## 序列式容器

##### 0. 概述

&emsp;&emsp;所谓序列容器，即以线性排列（类似普通数组的存储方式）来存储某一指定类型的数据，该类容器并不会自动对存储的元素按照值的大小进行排序

```
array<T,N>（数组容器）：容器一旦建立，其长度就是固定不变的，这意味着不能增加或删除元素，只能改变某个元素的值；

vector<T>（向量容器）：长度可变的序列容器，即在存储空间不足时，会自动申请更多的内存。此容器，在尾部增加或删除元素的效率最高（时间复杂度为 O(1) 常数阶），在其它位置插入或删除元素效率较差（时间复杂度为 O(n) 线性阶，其中 n 为容器中元素的个数）；

deque<T>（双端队列容器）：和 vector 非常相似，区别在于使用该容器不仅尾部插入和删除元素高效，在头部插入或删除元素也同样高效，时间复杂度都是 O(1) 常数阶，但是在容器中某一位置处插入或删除元素，时间复杂度为 O(n) 线性阶；

list<T>（链表容器）：是一个长度可变的序列，它以双向链表的形式组织元素，在这个序列的任何地方都可以高效地增加或删除元素（时间复杂度都为常数阶 O(1)），但访问容器中任意元素的速度要比前三种容器慢，这是因为 list<T> 必须从第一个元素或最后一个元素开始访问，需要沿着链表移动，直到到达想要的元素。

forward_list<T>（正向链表容器）：和 list 容器类似，只不过它以单链表的形式组织元素，它内部的元素只能从第一个元素开始访问，是一类比链表容器快、更节省内存的容器。

注意：stack<T> 和 queue<T> 本质上也属于序列容器，只不过它们都是在 deque 容器的基础上改头换面而成，通常更习惯称它们为容器适配器，后续介绍

```

![image](https://user-images.githubusercontent.com/42632290/171986585-439f233f-0f3b-47c3-88a6-9a1933954db8.png)

##### 1. array容器

(0) 概述
    
&emsp;&emsp; array 容器是 C++ 11 标准中新增的序列容器，简单地理解，它就是在 C++ 普通数组的基础上，添加了一些成员函数和全局函数。在使用上，它比普通数组更安全（原因后续会讲），且效率并没有因此变差。

&emsp;&emsp; array 容器的大小是固定的，无法动态的扩展或收缩，这也就意味着，在使用过程中无法通过增加或移除元素而改变其大小，**只允许访问或者替换存储的元素**。

```
1. 头文件  <array> 

    #include <array>
    using namespace std;

2. array 容器以类模板的形式定义

   namespace std{
        template <typename T, size_t N>
        class array;
   }

   注意：array<T,N> 类模板中，T 用于指明容器中的存储的具体数据类型，N 用于指明容器的大小. 这里的 N 必须是常量，不能用变量表示

```

(1) 创建

```
a) 直接创建
    std::array<double, 10> values;    //各个元素的值是不确定的，array 容器不会做默认初始化操作
    
b) 创建并使用默认初始化为0    
    std::array<double, 10> values {}; //所有的元素被初始化为 0.0
    
c) 创建并自定义初始化值  
    std::array<double, 10> values {0.5,1.0,1.5,,2.0};  //只初始化前 4 个元素，剩余的元素都会被初始化为 0.0
    
```

(2) 常见成员函数

![image](https://user-images.githubusercontent.com/42632290/177032011-4e8646ef-b25f-46c5-9cf7-ee4277a0b6c9.png)

    另外，在 <array> 头文件中还重载了 get() 全局函数，该重载函数的功能是访问容器中指定的元素，并返回该元素的引用。

    **正是由于 array 容器中包含了 at() 这样的成员函数，使得操作元素时比普通数组更安全**



(3) 迭代器使用详解

1. 遍历

```
#include <iostream>
#include <array>
using namespace std;

int main()
{
    std::array<int, 4> values{};  //初始化 values 容器为 {0,1,2,3}
    
    for (int i = 0; i < values.size(); i++) {
        values.at(i) = i;  //使用at赋值
    }
    
    cout << get<3>(values) << endl;  //使用 get() 重载函数输出指定位置元素
    
    if (!values.empty()) {   //如果容器不为空，则输出容器中所有的元素
        for (auto val = values.begin(); val < values.end(); val++) 
        {
            cout << *val << " ";
        }
    }
}

输出：
    3
    0 1 2 3

```       

2. 增

```
  不支持      
```       

3. 删

```
  不支持          
```         
             
 4. 改

```
a) at 函数
b) []
c) data 函数
```              
  
 5. 查

```
a) []方法：该方式没有边界检查，即使越界访问，也不会被检测到

    values[4] = values[3] + 2.O*values[1];
    
b) at() 成员函数访问元素：索引越界时，程序会抛出 std::out_of_range 异常，更安全，推荐使用

    values.at (4) = values.at(3) + 2.O*values.at(1);

c) get<n> 模板函数: 参数实参必须是在编译时可以确定的常量表达式，所以它不能是一个循环变量

    #include <iostream>
    #include <array>
    #include <string>
    using namespace std;
    int main()
    {
        array<string, 5> words{ "one","two","three","four","five" };
        cout << get<3>(words) << endl;        // 输出：four
        //cout << get<6>(words) << std::endl; // 越界，会发生编译错误
        return 0;
    }
    
d)  data() 成员函数: 得到指向容器首个元素的指针

    #include <iostream>
    #include <array>
    using namespace std;
    int main()
    {
        array<int, 5> words{1,2,3,4,5};
        cout << *( words.data()+1);    //通过该指针，可以获得容器中的各个元素
        return 0;
    }

```  

(4) array相对于数组的提升

&emsp;&emsp; array 容器代替普通数组，最直接的好处就是 array 模板类中已经为我们写好了很多实用的方法，可以大大提高我们编码效率。例如:
  
&emsp;&emsp;&emsp;&emsp; 1) array 容器提供的 at() 成员函数，可以有效防止越界操纵数组的情况
  
&emsp;&emsp;&emsp;&emsp; 2) fill() 函数可以实现数组的快速初始化
  
&emsp;&emsp;&emsp;&emsp; 3) swap() 函数可以轻松实现两个相同数组内容交换（类型相同，大小相同）

&emsp;&emsp;&emsp;&emsp; 4) 两个 array 容器满足大小相同并且保存元素的类型相同时，两个 array 容器可以直接直接做赋值操作

&emsp;&emsp;&emsp;&emsp; 5) 可以用任何比较运算符直接比较两个 array 容器

例子：

```
1) 实现两个数组内容交换

    array<char, 50>addr1{"http://www.cdsy.xyz"};
    array<char, 50>addr2{ "http://www.cdsy.xyz/computer/programme/stl/" };
    addr1.swap(addr2);
    printf("addr1 is：%s\n", addr1.data());
    printf("addr2 is：%s\n", addr2.data());

    输出：
         addr1 is：http://www.cdsy.xyz/computer/programme/stl/
         addr2 is：http://www.cdsy.xyz

2) 两个数组之间赋值

    array<char, 50>addr1{ "http://www.cdsy.xyz" };
    array<char, 50>addr2{ "http://www.cdsy.xyz/computer/programme/stl/" };
    addr1 = addr2;
    
3) 两个数组之间比较

    array<char, 50>addr1{ "http://www.cdsy.xyz" };
    array<char, 50>addr2{ "http://www.cdsy.xyz/computer/programme/stl/" };
    if (addr1 == addr2) {
        std::cout << "addr1 == addr2" << std::endl;
    }
    if (addr1 < addr2) {
        std::cout << "addr1 < addr2" << std::endl;
    }
    if (addr1 > addr2) {
        std::cout << "addr1 > addr2" << std::endl;
    }

```

##### 2. vector容器

(0) 概述

&emsp;&emsp; vector 容器是 STL 中最常用的容器之一，它和 array 容器非常类似，都可以看做是对 C++ 普通数组的“升级版”。不同之处在于，array 实现的是静态数组（容量固定的数组），而 vector 实现的是一个**动态数组，即可以进行元素的插入和删除，在此过程中，vector 会动态调整所占用的内存空间，整个过程无需人工干预**。

&emsp;&emsp; vector 常被称为向量容器，因为该容器擅长在尾部插入或删除元素，效率高；而对于在容器头部或者中部插入或删除元素，效率较低（移动元素需要耗费时间）。

```
1. 头文件
   #include <vector>
   using namespace std;
```

(1) 创建

```
a) 创建空容器
    std::vector<double> values;  //空的 vector 容器，没有元素，所以没有为其分配空间。当添加第一个元素时，会自动分配内存。

b) 指定初始值及元素个数
    std::vector<int> primes {2, 3, 5, 7, 11, 13, 17, 19};  //含有 8 个素数的 vector 容器
    
    std::vector<double> values(20);      //含有 20 个元素，默认初始值都为 0

    std::vector<double> values(20, 1.0); //含有 20 个元素，值都是 1.0

c) 使用已有容器初始化新容器
    std::vector<char>value1(5, 'c');
    std::vector<char>value2(value1);  //value2 容器中也具有 5 个字符 'c'

d) 指定初始值的范围
    int array[]={1,2,3};
    std::vector<int>values(array, array+2);//values 将保存{1,2}
    
    std::vector<int>value1{1,2,3,4,5};
    std::vector<int>value2(std::begin(value1),std::begin(value1)+3);//value2保存{1,2,3}

```

(2) 常见成员函数

![image](https://user-images.githubusercontent.com/42632290/178138057-7e64b928-1154-4a9a-a2a7-561ffa7f19c1.png)
![image](https://user-images.githubusercontent.com/42632290/178138157-1578d909-5c90-44be-9e23-29ad6937e4fd.png)

(3) 迭代器使用详解

1. 遍历

```
a) 遍历容器所有元素

#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<char>value;    //初始化一个空vector容量
    
    value.push_back('S'); //向value容器中的尾部依次添加 S、T、L 字符
    value.push_back('T');
    value.push_back('L');
    
    printf("元素个数为：%d\n", value.size());             //调用 size() 成员函数容器中的元素个数
    
    for (auto i = value.begin(); i < value.end(); i++)   //使用迭代器遍历容器
    {  
        cout << *i << " ";
    }
    cout << endl;
    
    value.insert(value.begin(), 'C');   //向容器开头插入字符
    cout << "首个元素为：" << value.at(0) << endl;
    return 0;
}  

b) 当容器容量增加时，地址可能会发生改变，这会导致之前创建的迭代器失效

#include <iostream>
#include <vector>
using namespace std;
int main()
{
    vector<int>values{1,2,3};
    cout << "values 容器首个元素的地址：" << values.data() << endl;
    auto first = values.begin();
    auto end = values.end();
    
    //增加 values 的容量
    values.reserve(20);
    cout << "values 容器首个元素的地址：" << values.data() << endl;
    while (first != end) 
    {
        cout << *first;    //增加容量之后，首个元素的存储地址发生了改变，此时再使用先前创建的迭代器，显然是错误的
        ++first;
    }
    return 0;
}

  输出：
       values 容器首个元素的地址：0096DFE8
       values 容器首个元素的地址：00965560

```       

2. 增

```
a) push_back()函数: 先创建这个元素，然后再将这个元素拷贝或者移动到容器中（如果是拷贝的话，事后会自行销毁先前创建的这个元素）
b) emplace_back()函数:直接在容器尾部创建这个元素，省去了拷贝或移动元素的过程

#include <vector> 
#include <iostream> 
using namespace std;
class testDemo
{
public:
    testDemo(int num):num(num)
    {
        std::cout << "调用构造函数" << endl;
    }
    testDemo(const testDemo& other) :num(other.num) 
    {
        std::cout << "调用拷贝构造函数" << endl;
    }
    testDemo(testDemo&& other) :num(other.num) 
    {
        std::cout << "调用移动构造函数" << endl;
    }
private:
    int num;
};

int main()
{
    cout << "emplace_back:" << endl;
    std::vector<testDemo> demo1;
    demo1.emplace_back(2);  

    cout << "push_back:" << endl;
    std::vector<testDemo> demo2;
    demo2.push_back(2);
}

   输出：emplace_back:
            调用构造函数
         push_back:
            调用构造函数
            调用移动构造函数
   注意：在实际使用时，优先选用 emplace_back(), 由于emplace_back() 是 C++ 11 标准新增加的，如果程序要兼顾之前的版本，还是应该使用 push_back()

c) insert()函数：指定位置插入一个或多个元素
   iterator insert(pos,elem);             //在迭代器 pos 指定的位置之前插入一个新元素elem，并返回表示新插入元素位置的迭代器
   iterator insert(pos,n,elem);           //在迭代器 pos 指定的位置之前插入 n 个元素 elem，并返回表示第一个新插入元素位置的迭代器
   iterator insert(pos,first,last);       //在迭代器 pos 指定的位置之前，插入其他容器位于 [first,last) 区域的所有元素，并返回表示第一个新插入元素位置的迭代器
   iterator insert(pos,initlist);         //在迭代器 pos 指定的位置之前，插入初始化列表（用大括号{}括起来的多个元素，中间有逗号隔开）中所有的元素，并返回表示第一个新插入元素位置的迭代器
   
#include <iostream> 
#include <vector> 
#include <array> 
using namespace std;
int main()
{
    std::vector<int> demo{1,2};
    //第一种格式用法
    demo.insert(demo.begin() + 1, 3);//{1,3,2}

    //第二种格式用法
    demo.insert(demo.end(), 2, 5);//{1,3,2,5,5}

    //第三种格式用法
    std::array<int,3>test{ 7,8,9 };
    demo.insert(demo.end(), test.begin(), test.end());//{1,3,2,5,5,7,8,9}

    //第四种格式用法
    demo.insert(demo.end(), { 10,11 });//{1,3,2,5,5,7,8,9,10,11}

    for (int i = 0; i < demo.size(); i++) {
        cout << demo[i] << " ";
    }
    return 0;
}

d) emplace()函数：emplace() 每次只能插入一个元素，而不是多个
   iterator emplace (const_iterator pos, args...);  //args...，即被插入元素的构造函数需要多少个参数，那么在 emplace() 的第一个参数的后面，就需要传入相应数量的参数

#include <vector>
#include <iostream>
using namespace std;

int main()
{
    std::vector<int> demo1{1,2};
    //emplace() 每次只能插入一个 int 类型元素
    demo1.emplace(demo1.begin(), 3);
    for (int i = 0; i < demo1.size(); i++) {
        cout << demo1[i] << " ";
    }
    return 0;
}

    注意： emplace() 在插入元素时，是在容器的指定位置直接构造元素，而不是先单独生成，再将其复制（或移动）到容器中。因此，推荐优先使用 emplace()。

```       

3. 删

```
a) pop_back(): 删除 vector 容器中最后一个元素，该容器的大小（size）会减 1，但容量（capacity）不会发生改变
b) erase(pos): 删除 vector 容器中 pos 迭代器指定位置处的元素，并返回指向被删除元素下一个位置元素的迭代器。该容器的大小（size）会减 1，但容量（capacity）不会发生改变
c) swap(end)、pop_back(): 先调用 swap() 函数交换要删除的目标元素和容器最后一个元素的位置，然后使用 pop_back() 删除该目标元素
d) erase(beg,end): 删除 vector 容器中位于迭代器 [beg,end)指定区域内的所有元素，并返回指向被删除区域下一个位置元素的迭代器。该容器的大小（size）会减小，但容量（capacity）不会发生改变。
e) remove(): 删除容器中所有和指定元素值相等的元素，并返回指向最后一个元素下一个位置的迭代器。值得一提的是，调用该函数不会改变容器的大小和容量
f) clear(): 删除 vector 容器中所有的元素，使其变成空的 vector 容器。该函数会改变 vector 的大小（变为 0），但不是改变其容量

示例c:

#include <vector>
#include <iostream>
#include <algorithm>  //swap在头文件 <algorithm> 和 <utility> 中都有定义，使用时引入其中一个即可
using namespace std;

int main()
{
    vector<int>demo{ 1,2,3,4,5 };
    
    swap(*(std::begin(demo)+1),*(std::end(demo)-1));//等同于 swap(demo[1],demo[4]) //交换要删除元素和最后一个元素的位置
   
    //交换位置后的demo容器
    for (int i = 0; i < demo.size(); i++) {
        cout << demo[i] << " ";
    }
    demo.pop_back();
    cout << endl << "size is :" << demo.size() << endl;
    cout << "capacity is :" << demo.capacity() << endl;
    
    //输出demo 容器中剩余的元素
    for (int i = 0; i < demo.size(); i++) {
        cout << demo[i] << " ";
    }
    return 0;
}
  运行结果：
           1 5 3 4 2
           size is :4
           capacity is :5
           1 5 3 4

示例e:
#include <vector>
#include <iostream>
#include <algorithm>  //remove函数，定义在 <algorithm> 头文件中
using namespace std;

int main()
{
    vector<int>demo{ 1,3,3,4,3,5 };
    
    auto iter = std::remove(demo.begin(), demo.end(), 3);  //交换要删除元素和最后一个元素的位置

    cout << "size is :" << demo.size() << endl;
    cout << "capacity is :" << demo.capacity() << endl;
    //输出剩余的元素
    for (auto first = demo.begin(); first < iter;++first) {
        cout << *first << " ";
    }
    return 0;
}

输出：
    size is :6
    capacity is :6
    1 4 5

注意：
    在对容器执行完 remove 函数之后，由于并没有改变容器原来的大小和容量，因此无法使用之前的方法遍历容器，而是需要向程序中那样，借助 remove返回的迭代器完成正确的遍历

原理：
    remove() 的实现原理是，在遍历容器中的元素时，一旦遇到目标元素，就做上标记，然后继续遍历，直到找到一个非目标元素，即用此元素将最先做标记的位置覆盖掉，同时将此非目标元素所在的位置也做上标记，等待找到新的非目标元素将其覆盖。因此，如果将上面程序中 demo 容器的元素全部输出，得到的结果为 1 4 5 4 3 5

    另外还可以看到，既然通过 remove() 函数删除掉 demo 容器中的多个指定元素，该容器的大小和容量都没有改变，其剩余位置还保留了之前存储的元素。我们可以使用 erase() 成员函数删掉这些 "无用" 的元素

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
    vector<int>demo{ 1,3,3,4,3,5 };
    //交换要删除元素和最后一个元素的位置
    auto iter = std::remove(demo.begin(), demo.end(), 3);
    
    demo.erase(iter, demo.end());  // remove()用于删除容器中指定元素时，常和 erase() 成员函数搭配使用
    
    cout << "size is :" << demo.size() << endl;
    cout << "capacity is :" << demo.capacity() << endl;
    //输出剩余的元素
    for (int i = 0; i < demo.size();i++) {
        cout << demo[i] << " ";
    }
    return 0;
}

输出：size is :3
      capacity is :6
      1 4 5

```         
             
 4. 改

```
a) []：进行访问与修改元素，不会检查越界访问
 
   vector<int> values{1,2,3,4,5};
   cout << values[0] << endl;            //获取容器中首个元素：1
   
   values[0] = values[1] + values[2] + values[3] + values[4];   //修改容器中下标为 0 的元素的值
   cout << values[0] << endl;            // 输出：14
 
 b) at() 成员函数: 越界时，会抛出std::out_of_range异常，提高安全性
 
   vector<int> values{1,2,3,4,5};
    
   cout << values.at(0) << endl;    //获取容器中首个元素：1
    
   values.at(0) = values.at(1) + values.at(2) + values.at(3) + values.at(4);   //修改容器中下标为 0 的元素的值
   cout << values.at(0) << endl;    //输出：14

   //cout << values.at(5) << endl;  //这条语句会发生 out_of_range 异常
 
c)  front() 和 back(): 修改首尾元素

   vector<int> values{1,2,3,4,5};
   cout << "values 首元素为：" << values.front() << endl;   //输出：1
   cout << "values 尾元素为：" << values.back() << endl;    //输出：5

   values.front() = 10;      //修改首元素
   cout <<"values 新的首元素为：" << values.front() << endl;  //输出：10
   
   values.back() = 20;       //修改尾元素
   cout << "values 新的尾元素为：" << values.back() << endl;  //输出：20

d) data() 成员函数: 通过指针修改
   vector<int> values{1,2,3,4,5};
   cout << *(values.data() + 2) << endl;  //输出容器中第 3 个元素的值：3
   
   //修改容器中第 2 个元素的值
   *(values.data() + 1) = 10;    
   cout << *(values.data() + 1) << endl;  //输出：10

```              
  
 5. 查

```

```  

(4) 高级使用及特别注意事项

1. 如何避免vector容器进行不必要的扩容

&emsp;&emsp; vector 容器看做是一个动态数组, 只要**有新元素要添加到 vector 容器中而恰好此时 vector 容器的容量不足时，该容器就会自动扩容**, vector 容器扩容大致分为以下 4 个步骤：
    
&emsp;&emsp;&emsp;&emsp; a) 分配一块大小是当前 vector 容量几倍的新存储空间。注意，多数 STL 版本中的 vector 容器，其容器都会以 2 的倍数增长
    
&emsp;&emsp;&emsp;&emsp; b) 将 vector 容器存储的所有元素，依照原有次序从旧的存储空间复制到新的存储空间中；
    
&emsp;&emsp;&emsp;&emsp; c) 析构掉旧存储空间中存储的所有元素；
    
&emsp;&emsp;&emsp;&emsp; d) 释放旧的存储空间。

&emsp;&emsp; vector 容器的扩容过程是非常耗时的，并且当容器进行扩容后，之前和该容器相关的所有指针、迭代器以及引用都会失效。因此在使用 vector 容器过程中，我们应尽量避免执行不必要的扩容操作, reserve()函数可以实现该目标 

```
几种方法区分:
  a) size(): 当前 vector 容器中已经存有多少个元素
  
  b) capacity(): 当前 vector 容器总共可以容纳多少个元素。如果想知道当前 vector 容器有多少未被使用的存储空间，可以通过 capacity()-size() 得知
  
  c) resize(n): 强制 vector 容器必须存储 n 个元素, 如果 n 比 size() 小，则容器尾部多出的元素将会被删除；如果 n 比 size() 大，则 vector 会借助默认构造函数创建出更多的默认值元素，并将它们存储到容器末尾；如果 n 比 capacity() 的返回值还要大，则 vector 会先扩增，在添加一些默认值元素
  
  d) reserve(n): 强制 vector 容器的容量至少为 n。注意，如果 n 比当前 vector 容器的容量小，则该方法什么也不会做；反之如果 n 比当前 vector 容器的容量大，则 vector 容器就会扩容


避免 vector 容器执行不必要的扩容操作的关键在于，在使用 vector 容器初期，就要将其容量设为足够大的值:

示例1：
     代码的整个循环过程中，vector 容器会进行 2~10 次自动扩容（多数的 STL 标准库版本中，vector 容器通常会扩容至当前容量的 2 倍，而这里 1000≈2 10），程序的执行效率可想而知
vector<int>myvector;
for (int i = 1; i <= 1000; i++) {
    myvector.push_back(i);
}

优化：
vector<int>myvector;
myvector.reserve(1000);  //仅扩充了 1 次，执行效率大大提高
cout << myvector.capacity();
for (int i = 1; i <= 1000; i++) {
    myvector.push_back(i); 
}

注意：
   我们可能并不知道 vector 容器到底要存储多少个元素。这种情况下，可以先预留出足够大的空间，当所有元素都存储到 vector 容器中之后，再去除多余的容量

```

2. swap()成员方法使用

```

```

3. 切忌，vector<bool>不是存储bool类型元素的vector容器

```

```



##### 3. deque容器

(0) 概述


(1) 创建



(2) 常见成员函数




(3) 迭代器使用详解

1. 遍历

```



```       

2. 增

```



```       

3. 删

```





```         
             
 4. 改

```



```              
  
 5. 查

```




```  

##### 4. list容器

(0) 概述
             
(1) 创建

(2) 常见成员函数
             
(3) 迭代器使用详解

1. 遍历

```
             
```       

2. 增

```
             
```       

3. 删

```
             
```         
             
 4. 改

```
             
```              
  
 5. 查

```
             
```  

##### 5. forward_list容器

(0) 概述
             
(1) 创建

(2) 常见成员函数
             
(3) 迭代器使用详解

1. 遍历

```
             
```       

2. 增

```
             
```       

3. 删

```
             
```         
             
 4. 改

```
             
```              
  
 5. 查

```
             
```  
