> ## 序列式容器

##### 0. 概述

  所谓序列容器，即以线性排列（类似普通数组的存储方式）来存储某一指定类型的数据，该类容器并不会自动对存储的元素按照值的大小进行排序

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
    
  array 容器是 C++ 11 标准中新增的序列容器，简单地理解，它就是在 C++ 普通数组的基础上，添加了一些成员函数和全局函数。在使用上，它比普通数组更安全（原因后续会讲），且效率并没有因此变差。

  array 容器的大小是固定的，无法动态的扩展或收缩，这也就意味着，在使用过程中无法通过增加或移除元素而改变其大小，**只允许访问或者替换存储的元素**。

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

  array 容器代替普通数组，最直接的好处就是 array 模板类中已经为我们写好了很多实用的方法，可以大大提高我们编码效率。例如:
  
         1) array 容器提供的 at() 成员函数，可以有效防止越界操纵数组的情况
  
         2) fill() 函数可以实现数组的快速初始化
  
         3) swap() 函数可以轻松实现两个相同数组内容交换（类型相同，大小相同）

         4) 两个 array 容器满足大小相同并且保存元素的类型相同时，两个 array 容器可以直接直接做赋值操作

         5) 可以用任何比较运算符直接比较两个 array 容器

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

  vector 容器是 STL 中最常用的容器之一，它和 array 容器非常类似，都可以看做是对 C++ 普通数组的“升级版”。不同之处在于，array 实现的是静态数组（容量固定的数组），而 vector 实现的是一个**动态数组，即可以进行元素的插入和删除，在此过程中，vector 会动态调整所占用的内存空间，整个过程无需人工干预**。

  vector 常被称为向量容器，因为该容器擅长在尾部插入或删除元素，效率高；而对于在容器头部或者中部插入或删除元素，效率较低（移动元素需要耗费时间）。

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

(3) 迭代器使用详解

1. 遍历

```
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
