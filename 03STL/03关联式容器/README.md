> ## 关联式容器

##### 1. 概述

    关联式容器存储的元素，都是一个一个的“键值对”（ <key,value> ），这是和序列式容器最大的不同。除此之外，序列式容器中存储的元素默认都是未经过排序的，而使用关联式容器存储的元素，默认会根据各元素的键值的大小做升序排序
    
```
map: 各个元素的键必须是唯一的（即不能重复），该容器会根据各元素键的大小，默认进行升序排序（调用 std::less<T>）

set: 各个元素键和值完全相同，且各个元素的值不能重复（保证了各元素键的唯一性）, 该容器会自动根据各个元素的键（其实也就是元素值）的大小进行升序排序（调用 std::less<T>）

multimap: 和 map 容器唯一的不同在于，multimap 容器中存储元素的键可以重复

multiset: 和 set 容器唯一的不同在于，multiset 容器中存储元素的值可以重复（一旦值重复，则意味着键也是重复的）

注意：C++ 11 还新增了 4 种哈希容器，即 unordered_map、unordered_multimap 以及 unordered_set、unordered_multiset。严格来说，它们也属于关联式容器，但由于哈希容器底层采用的是哈希表，而不是红黑树。后续讲解
```

##### 2. pair用法

    考虑到“键值对”并不是普通类型数据，C++ STL 标准库提供了 pair 类模板，其专门用来将 2 个普通元素 first 和 second（可以是 C++ 基本数据类型、结构体、类自定的类型）创建成一个新元素<first, second>。通过其构成的元素格式不难看出，使用 pair 类模板来创建“键值对”形式的元素，再合适不过。

```
1. 头文件：pair 类模板定义在<utility>头文件中

2. pair对象创建
#include <iostream>
#include <utility>      // pair
#include <string>       // string
using namespace std;

int main() {
    // 1. 调用默认构造函数
    pair <string, double> pair1;
    // 2. 调用有参构造函数
    pair <string, string> pair2("STL教程","http://www.cdsy.xyz/computer/programme/stl/");  
    // 3. 调用拷贝构造函数
    pair <string, string> pair3(pair2);
    // 4. 调用移动构造函数
    pair <string, string> pair4(make_pair("C++教程", "http://www.cdsy.xyz/computer/programme/vc/"));  //make_pair() 函数的返回值（是一个临时对象）
    // 5. 调用右值引用构造函数
    pair <string, string> pair5(string("Python教程"), string("http://www.cdsy.xyz/computer/programme/Python/"));  
   
    cout << "pair1: " << pair1.first << " " << pair1.second << endl; 
    cout << "pair2: "<<  pair2.first << " " << pair2.second << endl;
    cout << "pair3: " << pair3.first << " " << pair3.second << endl;
    cout << "pair4: " << pair4.first << " " << pair4.second << endl;
    cout << "pair5: " << pair5.first << " " << pair5.second << endl;
    return 0;
}

3. C++ 11 还允许手动为 pair1 对象赋值
pair1.first = "Java教程";
pair1.second = "http://www.cdsy.xyz/computer/programme/java/";
cout << "new pair1: " << pair1.first << " " << pair1.second << endl;

4. make_pair还可以直接使用
pair <string, string> pair4 = make_pair("C++教程", "http://www.cdsy.xyz/computer/programme/vc/");
cout << "pair4: " << pair4.first << " " << pair4.second << endl;

5. <utility>头文件中除了提供创建 pair 对象的方法之外，还为 pair 对象重载了 <、<=、>、>=、==、!= 这 6 的运算符，其运算规则是：对于进行比较的 2 个 pair 对象，先比较 pair.first 元素的大小，如果相等则继续比较 pair.second 元素的大小

#include <iostream>
#include <utility>      // pair
#include <string>       // string
using namespace std;
int main() {
    pair <string, int> pair1("STL教程", 20);
    pair <string, int> pair2("C++教程", 20);
    pair <string, int> pair3("C++教程", 30);
    //pair1和pair2的key不同，value相同
    if (pair1 != pair2) {
        cout << "pair != pair2" << endl;   //pair != pair2
    }
    //pair2和pair3的key相同，value不同
    if (pair2 != pair3) {
        cout << "pair2 != pair3" << endl;  //pair2 != pair3
    }
    return 0;
}

注意：对于进行比较的 2 个 pair 对象，其对应的键和值的类型要相同，否则将没有可比性，同时编译器提示没有相匹配的运算符，即找不到合适的重载运算符。

//6. pair类模板还提供有一个 swap() 成员函数，能够互换 2 个 pair 对象的键值对，其操作成功的前提是这 2 个 pair 对象的键和值的类型要相同
#include <iostream>
#include <utility>      // pair
#include <string>       // string
using namespace std;
int main() {
    pair <string, int> pair1("pair", 10);                   
    pair <string, int> pair2("pair2", 20);
    //交换 pair1 和 pair2 的键值对
    pair1.swap(pair2);
    cout << "pair1: " << pair1.first << " " << pair1.second << endl;  //pair1: pair2 20
    cout << "pair2: " << pair2.first << " " << pair2.second << endl;  //pair2: pair 10
    return 0;
}

```

##### 2. map容器

(0) 概述

  map 容器存储的都是 pair 对象，也就是用 pair 类模板创建的键值对. 
    
  与此同时, 在使用 map 容器存储多个键值对时, 该容器会自动根据各键值对的**键的大小, 按照既定的规则进行排序**. 默认情况下, map容器选用std::less<T>排序规则(其中 T 表示键的数据类型), 其会根据键的大小对所有键值对做升序排序. 当然, 根据实际情况的需要, 我们可以手动指定 map 容器的排序规则, 既可以选用 STL 标准库中提供的其它排序规则（比如std::greater<T>），也可以自定义排序规则

  使用 map 容器存储的各个键值对，键的值既不能重复也不能被修改

```
1. 头文件： <map> ，并位于 std 命名空间中
   #include <map>
   using namespace std;

2. map 容器的模板定义
   template < class Key,                                     // 指定键（key）的类型
              class T,                                       // 指定值（value）的类型
              class Compare = less<Key>,                     // 指定排序规则
              class Alloc = allocator<pair<const Key,T> >    // 指定分配器对象的类型
            > class map;
    
   map 容器模板有 4 个参数，其中后 2 个参数都设有默认值。大多数场景中，我们只需要设定前 2 个参数的值，有些场景可能会用到第 3 个参数，但最后一个参数几乎不会用到。  
```
    
(1) map 创建

```
1. 使用默认构造函数
   std::map<std::string, int> myMap;  //创建空的map
    
2. 创建map时直接初始化
   std::map<std::string, int> myMap1{ {"C语言教程",10},{"STL教程",20} };                             //创建map时候直接初始化
   std::map<std::string, int> myMap2{std::make_pair("C语言教程",10), std::make_pair("STL教程",20)};  //使用make_pair直接初始化
    
3. 使用拷贝构造函数初始化map
   std::map<std::string, int> newMap3(myMap);
    
4. 调用移动构造函数初始化map
   #创建一个会返回临时 map 对象的函数
   std::map<std::string,int> disMap() 
   {
      std::map<std::string, int>tempMap{ {"C语言教程",10},{"STL教程",20} };  //临时对象
      return tempMap;
   }
   std::map<std::string, int> newMap(disMap());  //调用 map 类模板的移动构造函数创建 newMap 容器

5. 取已建 map 容器中指定区域内的键值对，创建并初始化新的 map 容器
   std::map<std::string, int>myMap{ {"C语言教程",10},{"STL教程",20} };
   std::map<std::string, int>newMap(++myMap.begin(), myMap.end());

6. 手动修改 map 容器的排序规则 
   std::map<std::string, int, std::less<std::string> >    myMap1{ {"C语言教程",10},{"STL教程",20} };  //按键值大小，升序，默认不写
    输出：
         <"C语言教程", 10>
         <"STL教程", 20>
    
   std::map<std::string, int, std::greater<std::string> > myMap2{ {"C语言教程",10},{"STL教程",20} };  //按键值大小，降序
    输出：
         <"STL教程", 20>
         <"C语言教程", 10>
             

注意：我们还需要为 map 容器自定义排序规则，此部分知识后续讲解。
    
```

(2) map 容器常用成员方法       
       
![image](https://user-images.githubusercontent.com/42632290/172041959-88288e60-10a2-454c-bc52-002652dafb10.png)
![image](https://user-images.githubusercontent.com/42632290/172041976-ae7aedff-7eae-4345-9494-d75ac3a61b93.png)

           
(3) map 容器迭代器用法详解

  C++ STL 标准库为 map 容器配备的是双向迭代器（bidirectional iterator）。这意味着，map 容器迭代器只能进行 ++p、p++、--p、p--、*p 操作，并且迭代器之间只能使用 == 或者 != 运算符进行比较。
             
1. 遍历

```
#include <iostream>
#include <map>          // pair
#include <string>       // string
using namespace std;

int main() 
{
    //创建并初始化 map 容器
    std::map<std::string, std::string>myMap{ {"STL教程","http://www.cdsy.xyz/computer/programme/stl/"},
                                             {"C语言教程","http://www.cdsy.xyz/computer/programme/C_language/"} 
                                           };

    //调用 begin()/end() 组合，遍历 map 容器
    for (auto iter = myMap.begin(); iter != myMap.end(); ++iter) 
    {
        cout << iter->first << " " << iter->second << endl;
    }
    return 0;
}         
```    

2. 增     

``` 
a) []运算符：前提是要保证新添加键值对的键和当前 map 容器中已存储的键值对的键都不一样
             
#include <iostream>
#include <map>      // map
#include <string>   // string
using namespace std;

int main() 
{
    //创建空 map 容器
    std::map<string, string>myMap; 
    myMap["STL教程"]="http://www.cdsy.xyz/computer/programme/java/";         //新增
    myMap["Python教程"] = "http://www.cdsy.xyz/computer/programme/Python/";  //新增
    myMap["STL教程"] = "http://www.cdsy.xyz/computer/programme/stl/";        //已经存在，则修改

    for (auto i = myMap.begin(); i != myMap.end(); ++i) {
        cout << i->first << " " << i->second << endl;
    }
    return 0;
}  
             
b) insert 函数: 当使用 insert() 方法向 map 容器的指定位置插入新键值对时，其底层会先将新键值对插入到容器的指定位置，如果其破坏了 map 容器的有序性，该容器会对新键值对的位置进行调整。
             
    方法1： 无需指定插入位置，同时该方法会返回一个 pair 对象，其中 pair.first 表示一个迭代器，pair.second 为一个 bool 类型变量
            pair<iterator,bool> insert (const value_type& val); //1、引用传递一个键值对
            template <class P>
                pair<iterator,bool> insert (P&& val);           //2、以右值引用的方式传递键值对 
             
            如果成功插入 val，则该迭代器指向新插入的 val，bool 值为 true；
            如果插入 val 失败，则表明当前 map 容器中存有和 val 的键相同的键值对（用 p 表示），此时返回的迭代器指向 p，bool 值为 false
示例：
#include <iostream>
#include <map>  //map
#include <string> //string
using namespace std;

int main()
{
    //创建一个空 map 容器
    std::map<string, string> mymap;
   
    //创建一个真实存在的键值对变量
    std::pair<string, string> STL = { "STL教程","http://www.cdsy.xyz/computer/programme/stl/" };
   
    //创建一个接收 insert() 方法返回值的 pair 对象
    std::pair<std::map<string, string>::iterator, bool> ret;
   
    //插入 STL，由于 STL 并不是临时变量，因此会以第一种方式传参
    ret = mymap.insert(STL);
    cout << "ret.iter = <{" << ret.first->first << ", " << ret.first->second << "}, " << ret.second << ">" << endl;  //ret.iter = <{STL教程, http://www.cdsy.xyz/computer/programme/stl/}, 1>

    //以右值引用的方式传递临时的键值对变量
    ret = mymap.insert({ "C语言教程","http://www.cdsy.xyz/computer/programme/C_language/" });
    cout << "ret.iter = <{" << ret.first->first << ", " << ret.first->second << "}, " << ret.second << ">" << endl;  //ret.iter = <{C语言教程, http://www.cdsy.xyz/computer/programme/C_language/}, 1>

    //插入失败样例
    ret = mymap.insert({ "STL教程","http://www.cdsy.xyz/computer/programme/java/" });
    cout << "ret.iter = <{" << ret.first->first << ", " << ret.first->second << "}, " << ret.second << ">" << endl;  //ret.iter = <{STL教程, http://www.cdsy.xyz/computer/programme/stl/}, 0>
    return 0;
}

             
    方法2：向 map 容器的指定位置插入新键值对,返回的是迭代器
    ```
      iterator insert (const_iterator position, const value_type& val);     //以普通引用的方式传递 val 参数
      template <class P>
          iterator insert (const_iterator position, P&& val);               //以右值引用的方式传递 val 键值对参数
             
      成功：返回一个指向 map 容器中已插入键值对的迭代器
      失败：返回一个迭代器，该迭代器指向 map 容器中和 val 具有相同键的那个键值对
    ```
示例：
#include <iostream>
#include <map>    //map
#include <string> //string
using namespace std;
int main()
{
    //创建一个空 map 容器
    std::map<string, string> mymap;
   
    //创建一个真实存在的键值对变量
    std::pair<string, string> STL = { "STL教程","http://www.cdsy.xyz/computer/programme/stl/" };
             
    //指定要插入的位置
    std::map<string, string>::iterator it = mymap.begin();
             
    //向 it 位置以普通引用的方式插入 STL
    auto iter1 = mymap.insert(it, STL);
    cout << iter1->first << " " << iter1->second << endl;  //STL教程 http://www.cdsy.xyz/computer/programme/stl/

    //向 it 位置以右值引用的方式插入临时键值对
    auto iter2 = mymap.insert(it, std::pair<string, string>("C语言教程", "http://www.cdsy.xyz/computer/programme/C_language/"));
    cout << iter2->first << " " << iter2->second << endl;  //C语言教程 http://www.cdsy.xyz/computer/programme/C_language/

    //插入失败样例
    auto iter3 = mymap.insert(it, std::pair<string, string>("STL教程", "http://www.cdsy.xyz/computer/programme/java/"));
    cout << iter3->first << " " << iter3->second << endl;  //STL教程 http://www.cdsy.xyz/computer/programme/stl/
    return 0;
}
             
    注意：即便指定了新键值对的插入位置，map 容器仍会对存储的键值对进行排序。也可以说，决定新插入键值对位于 map 容器中位置的，不是 insert() 方法中传入的迭代器，而是新键值对中键的值。


    方法3：插入其它 map 容器指定区域内的所有键值对，传入制定位置的迭代器
           template <class InputIterator>
           void insert (InputIterator first, InputIterator last);
示例：
#include <iostream>
#include <map>  //map
#include <string> //string
using namespace std;
int main()
{
    //创建并初始化 map 容器
    std::map<std::string, std::string>mymap{ {"STL教程","http://www.cdsy.xyz/computer/programme/stl/"},
                                                {"C语言教程","http://www.cdsy.xyz/computer/programme/C_language/"},
                                                {"Java教程","http://www.cdsy.xyz/computer/programme/java/"} };
    //创建一个空 map 容器
    std::map<std::string, std::string>copymap;
             
    //指定插入区域
    std::map<string, string>::iterator first = ++mymap.begin();
    std::map<string, string>::iterator last = mymap.end();
             
    //将<first,last>区域内的键值对插入到 copymap 中
    copymap.insert(first, last);
             
    //遍历输出 copymap 容器中的键值对
    for (auto iter = copymap.begin(); iter != copymap.end(); ++iter) {
        cout << iter->first << " " << iter->second << endl;
    }
    return 0;
}
             
    
    方法4：一次向 map 容器中插入多个键值对
          void insert ({val1, val2, ...});  //vali 都表示的是键值对变量。
             
示例：
#include <iostream>
#include <map>    //map
#include <string> //string
using namespace std;
int main()
{
    //创建空的 map 容器
    std::map<std::string, std::string>mymap;
             
    //向 mymap 容器中添加 3 个键值对
    mymap.insert({ {"STL教程", "http://www.cdsy.xyz/computer/programme/stl/"},
                   { "C语言教程","http://www.cdsy.xyz/computer/programme/C_language/" },
                   { "Java教程","http://www.cdsy.xyz/computer/programme/java/" } });

    for (auto iter = mymap.begin(); iter != mymap.end(); ++iter) {
        cout << iter->first << " " << iter->second << endl;
    }
    return 0;
}
    
c) emplace函数: 返回值也是一个 pair 对象，其中 pair.first 为一个迭代器，pair.second 为一个 bool 类型变量
             
     template <class... Args>
     pair<iterator,bool> emplace (Args&&... args); 
             
    只需要将创建新键值对所需的数据作为参数直接传入即可，此方法可以自行利用这些数据构建出指定的键值对. 该方法的返回值也是一个 pair 对象:        
    成功时：返回的迭代器指向该新插入的键值对，同时 bool 变量的值为 true；
    失败时：则表明 map 容器中存在具有相同键的键值对，此时返回的迭代器指向此具有相同键的键值对，同时 bool 变量的值为 false。
             
示例：
#include <iostream>
#include <map>        //map
#include <string>     //string
using namespace std;

int main()
{
    //创建并初始化 map 容器
    std::map<string, string>mymap;
             
    //插入键值对
    pair<map<string, string>::iterator, bool> ret = mymap.emplace("STL教程", "http://www.cdsy.xyz/computer/programme/stl/");
    cout << "1、ret.iter = <{" << ret.first->first << ", " << ret.first->second << "}, " << ret.second << ">" << endl;
             
    //插入新键值对
    ret = mymap.emplace("C语言教程", "http://www.cdsy.xyz/computer/programme/C_language/");
    cout << "2、ret.iter = <{" << ret.first->first << ", " << ret.first->second << "}, " << ret.second << ">" << endl;

    //失败插入的样例
    ret = mymap.emplace("STL教程", "http://www.cdsy.xyz/computer/programme/java/");
    cout << "3、ret.iter = <{" << ret.first->first << ", " << ret.first->second << "}, " << ret.second << ">" << endl;
    return 0;
}
             
d)  emplace_hint函数：和 emplace() 类似，还需要指明要插入的位置（新键值对键会插入到该迭代器指向的键值对的前面）
             
     template <class... Args>
     iterator emplace_hint (const_iterator position, Args&&... args);        

     成功时：插入新键值对时，返回的迭代器指向新插入的键值对
     失败时：则表明 map 容器中存有相同键的键值对，返回的迭代器就指向这个键值对  
 
示例：
#include <iostream>
#include <map>      //map
#include <string>   //string
using namespace std;

int main()
{
    //创建并初始化 map 容器
    std::map<string, string>mymap;
             
    //指定在 map 容器插入键值对
    map<string, string>::iterator iter = mymap.emplace_hint(mymap.begin(),"STL教程", "http://www.cdsy.xyz/computer/programme/stl/");
    cout << iter->first << " " << iter->second << endl;

    iter = mymap.emplace_hint(mymap.begin(), "C语言教程", "http://www.cdsy.xyz/computer/programme/C_language/");
    cout << iter->first << " " << iter->second << endl;

    //插入失败样例
    iter = mymap.emplace_hint(mymap.begin(), "STL教程", "http://www.cdsy.xyz/computer/programme/java/");
    cout << iter->first << " " << iter->second << endl;
    return 0;
}
             
```
             
3. 删

4. 改

```
a) []运算符修改值
             
    std::map<string, string> mymap;
    //借用 operator[] 添加新键值对
    mymap["STL教程"] = "http://www.cdsy.xyz/computer/programme/java/";
    cout << "old mymap：" << mymap["STL教程"] << endl;

    //借用 operator[] 更新某个键对应的值
    mymap["STL教程"] = "http://www.cdsy.xyz/computer/programme/stl/";
    cout << "new mymap：" << mymap["STL教程"] << endl;
             
b) insert函数修改值
             
    //借用insert()添加新键值对
    std::pair<string, string> STL = { "Java教程","http://www.cdsy.xyz/computer/programme/Python/" };
    std::pair<std::map<string, string>::iterator, bool> ret;
    ret = mymap.insert(STL);
    cout << "old ret.iter = <{" << ret.first->first << ", " << ret.first->second << "}, " << ret.second << ">" << endl;

    //借用 insert() 更新键值对
    mymap.insert(STL).first->second = "http://www.cdsy.xyz/computer/programme/java/";
    cout << "new ret.iter = <" << ret.first->first << ", " << ret.first->second << ">" << endl;
    return 0;
             
注意：
     向 map 容器中添加新键值对元素的操作时，insert() 成员方法的执行效率更高；而在实现更新 map 容器指定键值对的值的操作时，operator[ ] 的效率更高       
```
             
5. 查
         
```
a) find 函数查找
#include <iostream>
#include <map>          // pair
#include <string>       // string
using namespace std;

int main() 
{
    //创建并初始化 map 容器
    std::map<std::string, std::string> myMap{ {"STL教程","http://www.cdsy.xyz/computer/programme/stl/"},
                                             {"C语言教程","http://www.cdsy.xyz/computer/programme/C_language/"},
                                             {"Java教程","http://www.cdsy.xyz/computer/programme/java/"} };
    //查找键为 "Java教程" 的键值对
    auto iter = myMap.find("Java教程");
    //从 iter 开始，遍历 map 容器
    for (; iter != myMap.end(); ++iter) 
    {
        cout << iter->first << " " << iter->second << endl;
    }
    return 0;
}             
             
b) lower_bound(key)/upper_bound(key)函数查找
#include <iostream>
#include <map>          // pair
#include <string>       // string
using namespace std;

int main() 
{
    //创建并初始化 map 容器
    std::map<std::string, std::string>myMap{ {"STL教程","http://www.cdsy.xyz/computer/programme/stl/"},
                                             {"C语言教程","http://www.cdsy.xyz/computer/programme/C_language/"},
                                             {"Java教程","http://www.cdsy.xyz/computer/programme/java/"} };
    //找到第一个键的值大于等于 "Java教程" 的键值对
    auto iter = myMap.lower_bound("Java教程");    
    cout << "lower：" << iter->first << " " << iter->second << endl; //lower：Java教程 http://www.cdsy.xyz/computer/programme/java/
   
    //找到第一个键的值大于 "Java教程" 的键值对
    iter = myMap.upper_bound("Java教程");
    cout <<"upper：" << iter->first << " " << iter->second << endl;  //upper：STL教程 http://www.cdsy.xyz/computer/programme/stl/
    return 0;
}

c) equal_range(key) 查找：返回一个 pair 对象，其中的 2 个元素都是迭代器类型，其中 pair.first 实际上就是 lower_bound(key) 的返回值，而 pair.second 则等同于 upper_bound(key) 的返回值
#include <iostream>
#include <utility>      //pair
#include <map>          // map
#include <string>       // string
using namespace std;

int main() 
{
    //创建并初始化 map 容器
    std::map<string, string>myMap{ {"STL教程","http://www.cdsy.xyz/computer/programme/stl/"},
                                   {"C语言教程","http://www.cdsy.xyz/computer/programme/C_language/"},
                                   {"Java教程","http://www.cdsy.xyz/computer/programme/java/"} };       
    //创建一个 pair 对象，来接收 equal_range() 的返回值
    pair <std::map<string, string>::iterator, std::map<string, string>::iterator> myPair = myMap.equal_range("C语言教程");
             
    //通过遍历，输出 myPair 指定范围内的键值对
    for (auto iter = myPair.first; iter != myPair.second; ++iter) {
        cout << iter->first << " " << iter->second << endl;  //C语言教程 http://www.cdsy.xyz/computer/programme/C_language/
    }
    return 0;
}
             
d) []运算符查键取值
            
#include <iostream>
#include <map>      // map
#include <string>   // string
using namespace std;

int main() 
{
    //创建并初始化 map 容器
    std::map<std::string, std::string>myMap{ {"STL教程","http://www.cdsy.xyz/computer/programme/stl/"},
                                             {"C语言教程","http://www.cdsy.xyz/computer/programme/C_language/"},
                                             {"Java教程","http://www.cdsy.xyz/computer/programme/java/"} };
    string cValue = myMap["C语言教程"];
    cout << cValue << endl;
    return 0;
}

    注意：只有当 map 容器中确实存有包含该指定键的键值对，借助重载的 [ ] 运算符才能成功获取该键对应的值；反之，若当前 map 容器中没有包含该指定键的键值对，则此时使用 [ ] 运算符将不再是访问容器中的元素，而变成了向该 map 容器中增添一个键值对。其中，该键值对的键用 [ ] 运算符中指定的键，其对应的值取决于 map 容器规定键值对中值的数据类型，如果是基本数据类型，则值为 0；如果是 string 类型，其值为 ""，即空字符串（即使用该类型的默认值作为键值对的值），示例如下：
    
#include <iostream>
#include <map>      // map
#include <string>   // string
using namespace std;

int main() {
    //创建空 map 容器
    std::map<std::string, int>myMap;
    int cValue = myMap["C语言教程"];
    for (auto i = myMap.begin(); i != myMap.end(); ++i) {
        cout << i->first << " "<< i->second << endl;         //C语言教程 0
    }
    return 0;
}    
             
e) at函数查键取值: 不存在则抛出 out_of_range 异常

#include <iostream>
#include <map>      // map
#include <string>   // string
using namespace std;

int main() 
{
    //创建并初始化 map 容器
    std::map<std::string, std::string>myMap{ {"STL教程","http://www.cdsy.xyz/computer/programme/stl/"},
                                             {"C语言教程","http://www.cdsy.xyz/computer/programme/C_language/"},
                                             {"Java教程","http://www.cdsy.xyz/computer/programme/java/"} };

    cout << myMap.at("C语言教程") << endl;
             
    //不存在则抛出 out_of_range 异常
    //cout << myMap.at("Python教程") << endl;
    return 0;
}

f) 遍历查找
             
    略

总结：
      获取指定键对应的值”的角度出发，更推荐使用 at() 成员方法，因为该方法既简单又安全
```

(4) 插入方法效率对比

    使用 insert() 向 map 容器中插入键值对的过程是，先创建该键值对，然后再将该键值对复制或者移动到 map 容器中的指定位置；
             
    使用 emplace() 或 emplace_hint() 插入键值对的过程是，直接在 map 容器中的指定位置构造该键值对。
             
    也就是说，向 map 容器中插入键值对时，emplace() 和 emplace_hint() 方法都省略了移动键值对的过程，因此执行效率更高。
             
详细参考：
             
(1) http://www.cdsy.xyz/computer/programme/stl/20210307/cd161510781911997.html


##### 3. multimap容器             
 
(1) 概述

  multimap 容器具有和 map 相同的特性，和 map 容器的区别在于，multimap 容器中可以同时存储多（≥2）个键相同的键值对。
 
(2) 常用成员函数

    multimap的常用成员函数和map基本一致，除了下列:

```
1. 头文件：#include <map>
             
2. multimap 未提供 at() 成员方法，也没有重载 [] 运算符。因为 multimap 容器中指定的键可能对应多个键值对，而不再是 1 个。    
             
3. find 函数查找首个键为 key 的键值对，如果成功找到，则返回指向该键值对的双向迭代器；反之，则返回和 end() 方法一样的迭代器         
```
     
具体函数参考：
             
(1) http://www.cdsy.xyz/computer/programme/stl/20210307/cd161510782011998.html
             
##### 4. set容器

(0) 概述

  map/multimap 容器不同,使用**set容器存储的各个键值对, 要求键 key 和值 value 必须相等**
             
```
例如：
  {<'a', 1>, <'b', 2>, <'c', 3>}
  {<'a', 'a'>, <'b', 'b'>, <'c', 'c'>}  

  第一组数据中各键值对的键和值不相等，而第二组中各键值对的键和值对应相等。对于 set 容器来说，只能存储第 2 组键值对，而无法存储第一组键值对.
```

  基于 set 容器的这种特性，当使用 set 容器存储键值对时，只需要为其提供各键值对中的 value 值（也就是 key 的值）即可。以存储上面第 2 组键值对为例，只需要为 set 容器提供 {'a','b','c'} ，该容器即可成功将它们存储起来

  set 容器也会根据 key 排序，也就等价为根据 value 排序，默认为升序排序

  set 容器并没有强制对存储元素的类型做 const 修饰。但是，C++ 标准为了防止用户修改容器中元素的值，对所有可能会实现此操作的行为做了限制，使得在正常情况下，用户是无法做到修改 set 容器中元素的值的。切勿尝试直接修改 set 容器中已存储元素的值，这很有可能破坏 set 容器中元素的有序性，最正确的修改 set 容器中元素值的做法是：**先删除该元素，然后再添加一个修改后的元素**
             
```
1. 头文件 #include <set>
          using namespace std;
             
2. 类模板定义
template < class T,                        // 键 key 和值 value 的类型
           class Compare = less<T>,        // 指定 set 容器内部的排序规则
           class Alloc = allocator<T>      // 指定分配器对象的类型
           > class set;
             
  注意：由于 set 容器存储的各个键值对，其键和值完全相同，因此 set 容器类模板的定义中，仅有第 1 个参数用于设定存储数据的类型。
对于 set 类模板中的 3 个参数，后 2 个参数自带默认值，且几乎所有场景中只需使用前 2 个参数，第 3 个参数不会用到
```

(1) 创建

```
1. 使用默认构造函数
   std::set<std::string> myset;  //空set容器
             
2. 创建 set 容器的同时，对其进行初始化        
   std::set<std::string> myset{"http://www.cdsy.xyz/computer/programme/java/",
                               "http://www.cdsy.xyz/computer/programme/stl/",
                               "http://www.cdsy.xyz/computer/programme/Python/"};

3. 拷贝（复制）构造函数       
   std::set<std::string> copyset(myset);  //等同于std::set<std::string> copyset = myset
                                          //将已有 set 容器中存储的所有元素全部复制到新 set 容器中
             
4. 移动构造函数
   set<string> retSet() {
   std::set<std::string> myset{ "http://www.cdsy.xyz/computer/programme/java/",
                                "http://www.cdsy.xyz/computer/programme/stl/",
                                "http://www.cdsy.xyz/computer/programme/Python/" };
    return myset;
   }
   std::set<std::string> copyset(retSet());     // 等同于 std::set<std::string> copyset = retSet();   
                                                // 利用临时的 set 容器初始化新建对象

5. 取已有 set 容器中的部分元素，来初始化新 set 容器
   std::set<std::string> myset{ "http://www.cdsy.xyz/computer/programme/java/",
                                "http://www.cdsy.xyz/computer/programme/stl/",
                                "http://www.cdsy.xyz/computer/programme/Python/" };
    std::set<std::string> copyset(++myset.begin(), myset.end());
             
6. 手动修改 set 容器中的排序规则
   std::set<std::string,std::greater<string> > myset{"http://www.cdsy.xyz/computer/programme/java/",
                                                     "http://www.cdsy.xyz/computer/programme/stl/",
                                                     "http://www.cdsy.xyz/computer/programme/Python/"};
   std::greater<string>降序规则，输出：
                                      "http://www.cdsy.xyz/computer/programme/stl/"
                                      "http://www.cdsy.xyz/computer/programme/Python/"
                                      "http://www.cdsy.xyz/computer/programme/java/"
             
             
```

(2) 常见成员函数

![image](https://user-images.githubusercontent.com/42632290/175796439-2909223b-89b7-4605-82d0-11c20b98b61c.png)
![image](https://user-images.githubusercontent.com/42632290/175796451-d3f09570-d943-48ab-a7f2-6327fbd20836.png)

  注意：以上成员函数返回的迭代器，指向的只是 set 容器中存储的元素，而不再是键值对。另外，以上成员方法返回的迭代器，无论是 const 类型还是非 const 类型，都不能用于修改 set 容器中的值

(3) 迭代器使用详解

   set 容器类模板中未提供 at() 成员函数，也未对 [] 运算符进行重载。因此，要想访问 set 容器中存储的元素，只能借助 set 容器的迭代器
   
   C++ STL 标准库为 set 容器配置的迭代器类型为双向迭代器。这意味着其只能进行 ++p、p++、--p、p--、*p 操作，并且 2 个双向迭代器之间做比较，也只能使用 == 或者 != 运算符

1. 遍历

```
#include <iostream>
#include <set>
#include <string>
using namespace std;

int main()
{
    //创建并初始化set容器
    std::set<std::string> myset{ "http://www.cdsy.xyz/computer/programme/java/",
                                 "http://www.cdsy.xyz/computer/programme/stl/",
                                 "http://www.cdsy.xyz/computer/programme/Python/"
    };
    //利用双向迭代器，遍历myset
    for (auto iter = myset.begin(); iter != myset.end(); ++iter) {
        cout << *iter << endl;  // iter 指向的是 set 容器存储的某个元素，而不是键值对，因此通过 *iter 可以直接获取该迭代器指向的元素的值
    }
    return 0;
}
```       

2. 增

```
a) insert 函数：该方式会破坏容器内部的有序状态，set 容器还会自行对新元素的位置做进一步调整
             
   方法1：给定目标元素的值，添加到 set 容器中     
          pair<iterator,bool> insert (const value_type& val); //普通引用方式传参
          pair<iterator,bool> insert (value_type&& val);      //右值引用方式传参
             
        成功：该迭代器指向 set 容器新添加的元素，bool 类型的值为 true；
        失败：即证明原 set 容器中已存有相同的元素，此时返回的迭代器就指向容器中相同的此元素，同时 bool 类型的值为 false。

示例：
#include <iostream>
#include <set>
#include <string>
using namespace std;

int main()
{
    //创建并初始化set容器
    std::set<std::string> myset;
    //准备接受 insert() 的返回值
    pair<set<string>::iterator, bool> retpair;
    //采用普通引用传值方式
    string str = "http://www.cdsy.xyz/computer/programme/stl/";
    retpair = myset.insert(str);
    cout << "iter->" << *(retpair.first) << " " << "bool = " << retpair.second << endl;
    //采用右值引用传值方式
    retpair = myset.insert("http://www.cdsy.xyz/computer/programme/Python/");
    cout << "iter->" << *(retpair.first) << " " << "bool = " << retpair.second << endl;
    return 0;
}
             
输出：
      ter->http://www.cdsy.xyz/computer/programme/stl/ bool = 1
      iter->http://www.cdsy.xyz/computer/programme/Python/ bool = 1       

             
  方法2： 指定将新元素插入到 set 容器中的具体位置            
          iterator insert (const_iterator position, const value_type& val);  //以普通引用的方式传递 val 值
          iterator insert (const_iterator position, value_type&& val);       //以右值引用的方式传递 val 值

      成功：当向 set 容器添加元素成功时，该迭代器指向容器中新添加的元素；
      失败：当添加失败时，证明原 set 容器中已有相同的元素，该迭代器就指向 set 容器中相同的这个元素

示例：
#include <iostream>
#include <set>
#include <string>
using namespace std;

int main()
{
    //创建并初始化set容器
    std::set<std::string> myset;
    //准备接受 insert() 的返回值
    set<string>::iterator iter;

    //采用普通引用传值方式
    string str = "http://www.cdsy.xyz/computer/programme/stl/";
    iter = myset.insert(myset.begin(),str);
    cout << "myset size =" << myset.size() << endl;

    //采用右值引用传值方式
    iter = myset.insert(myset.end(),"http://www.cdsy.xyz/computer/programme/Python/");
    cout << "myset size =" << myset.size() << endl;
    return 0;
}  

输出：
     myset size =1
     myset size =2


    方法3：向当前 set 容器中插入其它 set 容器指定区域内的所有元素
           template <class InputIterator>
           void insert (InputIterator first, InputIterator last);
             
        注意：first 和 last 都是迭代器，它们的组合 [first,last) 可以表示另一 set 容器中的一块区域，该区域包括 first 迭代器指向的元素，但不包含 last 迭代器指向的元素

示例：
#include <iostream>
#include <set>
#include <string>
using namespace std;

int main()
{
    //创建并初始化set容器
    std::set<std::string> myset{ "http://www.cdsy.xyz/computer/programme/stl/",
                                "http://www.cdsy.xyz/computer/programme/Python/",
                                "http://www.cdsy.xyz/computer/programme/java/" };
    //创建一个同类型的空 set 容器
    std::set<std::string> otherset;
    //利用 myset 初始化 otherset
    otherset.insert(++myset.begin(), myset.end());
    //输出 otherset 容器中的元素
    for (auto iter = otherset.begin(); iter != otherset.end(); ++iter) {
        cout << *iter << endl;
    }
    return 0;
}
             
输出：
     http://www.cdsy.xyz/computer/programme/Python/
     http://www.cdsy.xyz/computer/programme/stl/
             
     
    方法4：实现一次向 set 容器中添加多个元素
           void insert ( {E1, E2,...,En} );  //其中，Ei 表示新添加的元素
             
示例：
#include <iostream>
#include <set>
#include <string>
using namespace std;

int main()
{
    //创建并初始化set容器
    std::set<std::string> myset;
    //向 myset 中添加多个元素
    myset.insert({ "http://www.cdsy.xyz/computer/programme/stl/",
        "http://www.cdsy.xyz/computer/programme/Python/",
        "http://www.cdsy.xyz/computer/programme/java/" });

    for (auto iter = myset.begin(); iter != myset.end(); ++iter) {
        cout << *iter << endl;
    }
    return 0;
}
             
输出：
      http://www.cdsy.xyz/computer/programme/java/
      http://www.cdsy.xyz/computer/programme/Python/
      http://www.cdsy.xyz/computer/programme/stl/ 
             

b) emplace(): 返回值类型为 pair 类型，其包含 2 个元素，一个迭代器和一个 bool 值：
             
        template <class... Args>
        pair<iterator,bool> emplace (Args&&... args);   //构造新结构体变量（或者类对象）需要多少个数据，就需要为该方法传入相应个数的数据

    成功：返回的迭代器指向新插入的元素，同时 bool 值为 true；
    失败：表明原 set 容器中已存在相同值的元素，此时返回的迭代器指向容器中具有相同键的这个元素，同时 bool 值为 false。
             
示例：
#include <iostream>
#include <set>
#include <string>
using namespace std;
int main()
{
    //创建并初始化 set 容器
    std::set<string>myset;
    //向 myset 容器中添加元素
    pair<set<string, string>::iterator, bool> ret = myset.emplace("http://www.cdsy.xyz/computer/programme/stl/");
    cout << "myset size = " << myset.size() << endl;
    cout << "ret.iter = <" << *(ret.first) << ", " << ret.second << ">" << endl;
    return 0;
}

输出：
    myset size = 1
    ret.iter = <http://www.cdsy.xyz/computer/programme/stl/, 1>
             
             
c) emplace_hint(): 需要额外传入一个迭代器，用来指明新元素添加到 set 容器的具体位置（新元素会添加到该迭代器指向元素的前面）
             
     template <class... Args>
     iterator emplace_hint (const_iterator position, Args&&... args);
             
     成功: 返回的迭代器指向新添加的元素
     失败: 则迭代器就指向 set 容器和要添加元素的值相同的元素        

示例：
#include <iostream>
#include <set>
#include <string>
using namespace std;
int main()
{
    //创建并初始化 set 容器
    std::set<string>myset;
    //在 set 容器的指定位置添加键值对
    set<string>::iterator iter = myset.emplace_hint(myset.begin(), "http://www.cdsy.xyz/computer/programme/stl/");
    cout << "myset size = " << myset.size() << endl;
    cout << *iter << endl;
    return 0;
}
             
输出：
     myset size = 1
     http://www.cdsy.xyz/computer/programme/stl/

             
注意：虽然能在指定位置插入新元素，但set 容器为了保持数据的有序状态，可能会移动其位置
```       

3. 删

```
a) erase(): 删除指定的元素
             
   方法1：  
         size_type erase (const value_type& val);    //删除 set 容器中值为 val 的元素
   方法2：
         iterator  erase (const_iterator position);  //删除 position 迭代器指向的元素
   方法3：                     
         iterator  erase (const_iterator first, const_iterator last);  //删除 [first,last) 区间内的所有元素

   注意：
         1) 第 1 种 erase方法，其返回值为一个整数，表示成功删除的元素个数；后 2 种格式的 erase方法，返回值都是迭代器，其指向的是 set 容器中删除元素之后的第一个元素。
         2) 如果要删除的元素就是 set 容器最后一个元素，则 erase方法返回的迭代器就指向新 set 容器中最后一个元素之后的位置（等价于 end() 方法返回的迭代器）
             
示例：
#include <iostream>
#include <set>
#include <string>
using namespace std;
int main()
{
    //创建并初始化 set 容器
    std::set<int>myset{1,2,3,4,5};
    cout << "myset size = " << myset.size() << endl;
   
    //1) 调用第一种格式的 erase() 方法
    int num = myset.erase(2); //删除元素 2，myset={1,3,4,5}
    cout << "1、myset size = " << myset.size() << endl;
    cout << "num = " << num << endl;

    //2) 调用第二种格式的 erase() 方法
    set<int>::iterator iter = myset.erase(myset.begin()); //删除元素 1，myset={3,4,5}
    cout << "2、myset size = " << myset.size() << endl;
    cout << "iter->" << *iter << endl;

    //3) 调用第三种格式的 erase() 方法
    set<int>::iterator iter2 = myset.erase(myset.begin(), --myset.end());//删除元素 3,4，myset={5}
    cout << "3、myset size = " << myset.size() << endl;
    cout << "iter2->" << *iter2 << endl;
    return 0;
}
             
输出：
     myset size = 5
     1、myset size = 4
        num = 1
     2、myset size = 3
        iter->3
     3、myset size = 1
        iter2->5
             
             
b) clear: 删除 set 容器中存储的所有元素, 不需要传入任何参数，也没有任何返回值

示例：
#include <iostream>
#include <set>
#include <string>
using namespace std;
int main()
{
    //创建并初始化 set 容器
    std::set<int>myset{1,2,3,4,5};
    cout << "1、myset size = " << myset.size() << endl;
    //清空 myset 容器
    myset.clear();
    cout << "2、myset size = " << myset.size() << endl;
    return 0;
}
             
输出：
    1、myset size = 5
    2、myset size = 0   
```         
             
 4. 改

```
             
```              
  
 5. 查

```
             
```      


##### 5. multiset容器

(0) 概述
             
    multiset 容器和 set 容器唯一的差别在于，multiset 容器允许存储多个值相同的元素，而 set 容器中只能存储互不相同的元素

(1) 常见成员函数
             
```
1. 头文件
        #include <set>
        using namespace std;
             
2.multiset 容器和 set 容器拥有的成员方法完全相同，但由于 multiset 容器允许存储多个值相同的元素，因此诸如 count()、find()、lower_bound()、upper_bound()、equal_range()等方法，更常用于 multiset 容器
             
示例：
#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {
    std::multiset<int> mymultiset{1,2,2,2,3,4,5};
    cout << "multiset size = " << mymultiset.size() << endl;
    cout << "multiset count(2) =" << mymultiset.count(2) << endl;
    //向容器中添加元素 8
    mymultiset.insert(8);
    //删除容器中所有值为 2 的元素
    int num = mymultiset.erase(2);
    cout << "删除了 " << num << " 个元素 2" << endl;
    //输出容器中存储的所有元素
    for (auto iter = mymultiset.begin(); iter != mymultiset.end(); ++iter) {
        cout << *iter << " ";
    }
    return 0;
}
             
输出：
     multiset size = 7
     multiset count(2) =3
     删除了 3 个元素 2
     1 3 4 5 8         
```
             
具体函数参考：
             
       (1) http://www.cdsy.xyz/computer/programme/stl/20210307/cd161510782712004.html
             
##### 6. 自定义关联式容器的排序规则   
  
  为关联式容器自定义排序规则，有以下 2 种方法：
             
```  
 1) 使用函数对象自定义排序规则
             
    无论关联式容器中存储的是基础类型（如 int、double、float 等）数据，还是自定义的结构体变量或类对象（包括 string 类），都可以使用函数对象的方式为该容器自定义排序规则.
             
示例：
#include <iostream>
#include <set>          // set
#include <string>       // string
using namespace std;
             
//定义函数对象类
class cmp {
public:
    bool operator ()(const string &a,const string &b)    //重载 () 运算符
    {
        return  (a.length() < b.length());               //按照字符串的长度，做升序排序(即存储的字符串从短到长)
    }                                                    //由于是以字符串的长度为准进行排序，因此其无法存储相同长度的多个字符串。
};
                                          
int main() {
    //创建 set 容器，并使用自定义的 cmp 排序规则
    std::set<string, cmp>myset{"http://www.cdsy.xyz/computer/programme/stl/",
                               "http://www.cdsy.xyz/computer/programme/Python/",
                               "http://www.cdsy.xyz/computer/programme/java/"};
    //输出容器中存储的元素
    for (auto iter = myset.begin(); iter != myset.end(); ++iter) {
            cout << *iter << endl;
    }
    return 0;
}
             
输出：
     http://www.cdsy.xyz/computer/programme/stl/
     http://www.cdsy.xyz/computer/programme/java/
     http://www.cdsy.xyz/computer/programme/Python/
             
//也可以定义函数对象模板类
template <typename T>
class cmp {
public:
    bool operator ()(const T &a, const T &b)       //重载 () 运算符
    {
        return  a < b;                             //按照值的大小，做升序排序
    }
};

```

2) 重载关系运算符实现自定义排序

   其实在 STL 标准库中，本就包含几个可供关联式容器使用的排序规则，如表 1 表示:

![image](https://user-images.githubusercontent.com/42632290/175803401-71fc2311-9011-483f-9471-866b2478dcbf.png)
               
   在此基础上，当关联式容器中存储的数据类型为自定义的结构体变量或者类对象时，通过对现有排序规则中所用的关系运算符进行重载，也能实现自定义排序规则的目的             
                   
**注意，当关联式容器中存储的元素类型为结构体指针变量或者类的指针对象时，只能使用函数对象的方式自定义排序规则，此方法不再适用**

```
#include <iostream>
#include <set>          // set
#include <string>       // string
using namespace std;
//自定义类
class myString {
public:
    myString(string tempStr) :str(tempStr) {};  //定义构造函数，向 myset 容器中添加元素时会用到
    
    string getStr() const;  //获取 str 私有对象，由于会被私有对象调用，因此该成员方法也必须为 const 类型
private:
    string str;
};
string myString::getStr() const{
    return this->str;
}
             
bool operator <(const myString &stra, const myString & strb) //重载 < 运算符，参数必须都为 const 类型
{
    return stra.getStr().length() < strb.getStr().length();  //以字符串的长度为标准比较大小
}

int main() {
    //创建空 set 容器，仍使用默认的 less<T> 排序规则
    std::set<myString>myset;

    //向 set 容器添加元素，这里会调用 myString 类的构造函数
    myset.emplace("http://www.cdsy.xyz/computer/programme/stl/");
    myset.emplace("http://www.cdsy.xyz/computer/programme/C_language/");
    myset.emplace("http://www.cdsy.xyz/computer/programme/Python/");

    for (auto iter = myset.begin(); iter != myset.end(); ++iter) 
    {
        myString mystr = *iter;
        cout << mystr.getStr() << endl;
    }
    return 0;
}
             
输出结果：
        http://www.cdsy.xyz/computer/programme/C_language/
        http://www.cdsy.xyz/computer/programme/Python/
        http://www.cdsy.xyz/computer/programme/stl/

        虽然 myset 容器表面仍采用默认的 std::less<T> 排序规则，但由于我们对其所用的 < 运算符进行了重载，使得 myset 容器内部实则是以字符串的长度为基准，对各个 mystring 类对象进行排序


```

##### 7. 修改关联式容器中键值对的键
             
  对于如何修改容器中某个键值对的键，所有关联式容器可以采用同一种解决思路，即**先删除该键值对，然后再向容器中添加修改之后的新键值对**
             
  是否可以不删除目标键值对，而直接修改它的键呢？           
  
       C++ STL 标准中明确规定, **map 和 multimap 容器**用于存储类型为 pair<const K, V> 的键值对。显然，只要目标键值对存储在当前容器中，键的值就无法被修改
             
       使用 const_cast 能直接修改 set 或者 multiset 容器中的元素，但一定不要修改元素的键！如果要修改，只能采用“先删除，再添加”的方式

参考：
             
(1) http://www.cdsy.xyz/computer/programme/stl/20210307/cd161510782912006.html

