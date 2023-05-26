> ## 无序关联式容器

##### 0. 概述

  无序容器又称为：“哈希容器”或者“无序关联容器”. 无序容器也使用键值对（pair 类型）的方式存储数据。不过它们有本质上的不同:
 
```
    a) 关联式容器的底层实现采用的树存储结构，更确切的说是红黑树结构
    b) 无序容器的底层实现采用的是哈希表的存储结构
```

  C++ STL 底层采用哈希表实现无序容器时，会将所有数据存储到一整块连续的内存空间中，并且当数据存储位置发生冲突时，解决方法选用的是“链地址法”（又称“开链法”）

```
    无序容器具有以下 2 个特点：
        a) 无序容器内部存储的键值对是无序的，各键值对的存储位置取决于该键值对中的键
        b) 无序容器擅长通过指定键查找对应的值（平均时间复杂度为 O(1)）；但对于使用迭代器遍历容器中存储的元素，无序容器的执行效率则不如关联式容器
```

  无序容器种类:

<img width="575" alt="image" src="https://github.com/chuanchuan11/cplus/assets/42632290/8ce59f96-93dc-45c5-86e5-cfdad2140820">

````
    实际使用中选哪种容器呢？
        总的来说，如果涉及大量遍历容器的操作，建议首选关联式容器；反之，如果更多的操作是通过键获取对应的值，则应首选无序容器
````

##### 1. unordered_map 容器

(0) 概述

  unordered_map 容器和 map 容器一样，以键值对（pair类型）的形式存储数据，存储的各个键值对的键互不相同且不允许被修改。但由于 unordered_map 容器底层采用的是哈希表存储结构，该结构本身不具有对数据的排序功能，所以此容器内部不会自行对存储的键值对进行排序

  即 map 容器中存储的数据是有序的，而 unordered_map 容器中是无序的.

```
1) 头文件
    #include <unordered_map>
    using namespace std;
    
2) unordered_map 容器模板的定义为:
    template < class Key,                                    //键值对中键的类型
               class T,                                      //键值对中值的类型
               class Hash = hash<Key>,                       //容器内部存储键值对所用的哈希函数
               class Pred = equal_to<Key>,                   //判断各个键值对键相同的规则
               class Alloc = allocator< pair<const Key,T> >  // 指定分配器对象的类型
             > class unordered_map;

注意:
    以上 5 个参数中，必须显式给前 2 个参数传值，并且除特殊情况外，最多只需要使用前 4 个参数，各自的含义和功能如表所示
```

<img width="575" alt="image" src="https://github.com/chuanchuan11/cplus/assets/42632290/997113a5-9e6f-469e-87dc-7666c9f397bf">

```
注意: 当无序容器中存储键值对的键为自定义类型时，默认哈希函数 hash 以及比较函数 equal_to 将不再适用，只能自己设计适用该类型的哈希函数和比较函数，并显式传递给 Hash 参数和 Pred 参数
```

(1) 创建

```
a) 创建空的 unordered_map 容器
    
    std::unordered_map<std::string, std::string> umap;

b) 创建 unordered_map 容器同时，完成初始化操作
    //包含有 3 个键值对元素
    std::unordered_map<std::string, std::string> umap {
                          {"Python教程","http://www.cdsy.xyz/computer/programme/Python/"},
                          {"Java教程","http://www.cdsy.xyz/computer/programme/java/"},
                          {"Linux教程","http://www.cdsy.xyz/computer/system/linux/"} 
                      };

c) 调用拷贝构造函数, 将现有 unordered_map 容器中的值，复制给新unordered_map 容器

    std::unordered_map<std::string, std::string> umap2(umap);  //umap是上步创建的容器
    
d) 调用移动构造函数, 即以右值引用的方式将临时 unordered_map 容器中存储的所有值，复制给新容器

    //返回临时 unordered_map 容器的函数
    std::unordered_map <std::string, std::string > retUmap()
    {
        std::unordered_map<std::string, std::string> tempUmap {
                  {"Python教程","http://www.cdsy.xyz/computer/programme/Python/"},
                  {"Java教程","http://www.cdsy.xyz/computer/programme/java/"},
                  {"Linux教程","http://www.cdsy.xyz/computer/system/linux/"} };
        return tempUmap;
    }
    //调用移动构造函数，创建 umap2 容器
    std::unordered_map<std::string, std::string> umap2(retUmap());

d) 选择部分区域内的键值对，为新建 unordered_map 容器初始化

    std::unordered_map<std::string, std::string> umap2(++umap.begin(),umap.end());      //传入 2 个迭代器
```

(2) 常见成员函数

<img width="575" alt="image" src="https://github.com/chuanchuan11/cplus/assets/42632290/760050ca-cb13-46f5-bf85-1a89b51d98d1">

<img width="578" alt="image" src="https://github.com/chuanchuan11/cplus/assets/42632290/023cc23d-c8bd-4f5c-bae3-d6a8f391499e">

(3) 迭代器使用详解

1. 遍历

```
示例:

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
int main()
{
    //创建空 umap 容器
    unordered_map<string, string> umap;
    
    //向 umap 容器添加新键值对
    umap.emplace("Python教程", "http://www.cdsy.xyz/computer/programme/Python/");
    umap.emplace("Java教程", "http://www.cdsy.xyz/computer/programme/java/");
    umap.emplace("Linux教程", "http://www.cdsy.xyz/computer/system/linux/");

    //输出 umap 存储键值对的数量
    cout << "umap size = " << umap.size() << endl;
    
    //使用迭代器输出 umap 容器存储的所有键值对
    for (auto iter = umap.begin(); iter != umap.end(); ++iter) 
    {
        cout << iter->first << " " << iter->second << endl;
    }
    return 0;
}
```       

2. 增

```
a) insert() 直接插入: 成功返回pair, 迭代器指向新添加键值对, bool值为true; 失败返回已经存在键值对的迭起器,bool为false
    
    1) 以普通方式传递参数:     pair<iterator,bool> insert ( const value_type& val );
    2) 以右值引用方式传递参数: 
                             template <class P>
                             pair<iterator,bool> insert ( P&& val );
    #include <iostream>
    #include <string>
    #include <unordered_map>
    using namespace std;
    int main()
    {
        unordered_map<string, string> umap;
        std::pair<string, string>mypair("STL教程", "http://www.cdsy.xyz/computer/programme/stl/");   //构建要添加的键值对
        std::pair<unordered_map<string, string>::iterator, bool> ret;   //创建接收 insert() 方法返回值的pair类型变量

        ret = umap.insert(mypair);   //以普通方式传递参数
        ret = umap.insert(std::make_pair("Python教程","http://www.cdsy.xyz/computer/programme/Python/"));  //右值引用方式传递参数

        return 0;
    }

b) insert 添加到指定位置: 成功返回新元素的迭代器, 失败返回已有元素的迭代器,bool为false

    1) 以普通方式传递参数: iterator insert ( const_iterator hint, const value_type& val );
    2) 以右值引用方法传递参数: 
                              template <class P>
                              iterator insert ( const_iterator hint, P&& val );
    #include <iostream>
    #include <string>
    #include <unordered_map>
    using namespace std;
    int main()
    {
        unordered_map<string, string> umap;

        std::pair<string, string>mypair("STL教程", "http://www.cdsy.xyz/computer/programme/stl/");  //构建要添加的键值对
        unordered_map<string, string>::iterator iter;  //创建接收 insert() 方法返回值的迭代器类型变量

        iter = umap.insert(umap.begin(), mypair);  //调用第一种语法格式
        iter = umap.insert(umap.begin(), std::make_pair("Python教程", "http://www.cdsy.xyz/computer/programme/Python/"));  //调用第二种语法格式
        return 0;
    }
注意：
    以上 2 种语法格式中，虽然通过 hint 参数指定了新键值对添加到容器中的开始位置，但该键值对真正存储的位置并不是 hint 参数说了算，
    最终的存储位置仍取决于该键值对的键的值

c) insert 将某一个unordered_map 容器中指定区域内的所有键值对，复制到另一个 unordered_map 容器中

    #include <iostream>
    #include <string>
    #include <unordered_map>
    using namespace std;
    int main()
    {
        unordered_map<string, string> umap
        { 
          {"STL教程","http://www.cdsy.xyz/computer/programme/stl/"},
          {"Python教程","http://www.cdsy.xyz/computer/programme/Python/"},
          {"Java教程","http://www.cdsy.xyz/computer/programme/java/"} 
        };
        unordered_map<string, string> otherumap;     //创建一个空的 unordered_map 容器

        unordered_map<string, string>::iterator first = ++umap.begin(); //指定要拷贝 umap 容器中键值对的范围
        unordered_map<string, string>::iterator last = umap.end();

        //复制给 otherumap 容器
        otherumap.insert(first, last);
        return 0;
    }

d) insert 一次向 unordered_map 容器添加多个键值对

    #include <iostream>
    #include <string>
    #include <unordered_map>
    using namespace std;
    int main()
    {
        unordered_map<string, string> umap;

        //向 umap 容器同时添加多个键值对
        umap.insert({ {"STL教程","http://www.cdsy.xyz/computer/programme/stl/"},
                      {"Python教程","http://www.cdsy.xyz/computer/programme/Python/"},
                      {"Java教程","http://www.cdsy.xyz/computer/programme/java/"} 
                    });
        return 0;
    }
    
 /*********************************************/
 /*emplace 方法和emplace_hint方法效率比insert高 */
 /*********************************************/
e) emplace方法: 成功返回新添加得键值对pair, bool为true；失败返回已经存在元素得键值对pair, bool为false

    #include <iostream>
    #include <string>
    #include <unordered_map>
    using namespace std;
    int main()
    {
        unordered_map<string, string> umap;
        pair<unordered_map<string, string>::iterator, bool> ret; //定义一个接受 emplace() 方法的 pair 类型变量

        ret = umap.emplace("STL教程", "http://www.cdsy.xyz/computer/programme/stl/"); //调用 emplace() 方法
        //输出 ret 中包含的 2 个元素的值
        cout << "bool =" << ret.second << endl;
        cout << "iter ->" << ret.first->first << " " << ret.first->second << endl;
        return 0;
    }

f) emplace_hint方法: 成功返回指向新键值对得迭代器; 失败返回已经存在键值对得迭代器

    #include <iostream>
    #include <string>
    #include <unordered_map>
    using namespace std;
    int main()
    {
        unordered_map<string, string> umap;
        unordered_map<string,string>::iterator iter;          //定义一个接受 emplace_hint() 方法的迭代器
        
        iter = umap.emplace_hint(umap.begin(),"STL教程", "http://www.cdsy.xyz/computer/programme/stl/");  //调用 empalce_hint() 方法
        //输出 emplace_hint() 返回迭代器 iter 指向的键值对的内容
        cout << "iter ->" << iter->first << " " << iter->second << endl;
        return 0;
    }



注意: 
    (1) 需要注意的是，在操作 unordered_map 容器过程（尤其是向容器中添加新键值对）中，一旦当前容器的负载因子超过最大负载因子（默认值为 1.0）
        ,该容器就会适当增加桶的数量（通常是翻一倍），并自动执行 rehash() 成员方法，重新调整各个键值对的存储位置（此过程又称“重哈希”）, 
        此过程很可能导致之前创建的迭代器失效
        
    (2) 所谓迭代器失效，针对的是那些用于表示容器内某个范围的迭代器，由于重哈希会重新调整每个键值对的存储位置，所以容器重哈希之后,
        之前表示特定范围的迭代器很可能无法再正确表示该范围。但是，重哈希并不会影响那些指向单个键值对元素的迭代器
```       

3. 删

```
a) erase: 接受正向迭代器, 并删除迭代器指向得键值对

    用法: 
        iterator erase ( const_iterator position );   //position 为指向容器中某个键值对的迭代器, 返回被删除键值对之后位置得迭代器
    实例: 
    #include <iostream>
    #include <string>
    #include <unordered_map>
    using namespace std;
    int main()
    {
        unordered_map<string, string> umap
        {
            {"STL教程", "http://www.cdsy.xyz/computer/programme/stl/"},
            {"Python教程", "http://www.cdsy.xyz/computer/programme/Python/"},
            {"Java教程", "http://www.cdsy.xyz/computer/programme/java/"} 
        };

        unordered_map<string,string>::iterator ret;  //定义一个接收 erase() 方法的迭代器
        ret = umap.erase(umap.begin());  //删除容器中第一个键值对
        cout << "ret = " << ret->first << " " << ret->second << endl;
        return 0;
    }
    注意: 如果删除的是最后一个键值对，则返回容器中最后一个键值对之后的位置, 等同于end()方法

b) erase：接受key值, 返回成功删除键值对的数量

    用法：
        size_type erase ( const key_type& k );
    实例: 
    #include <iostream>
    #include <string>
    #include <unordered_map>
    using namespace std;
    int main()
    {
        unordered_map<string, string> umap
        {
            {"STL教程", "http://www.cdsy.xyz/computer/programme/stl/"},
            {"Python教程", "http://www.cdsy.xyz/computer/programme/Python/"},
            {"Java教程", "http://www.cdsy.xyz/computer/programme/java/"} 
        }; 

        int delNum = umap.erase("Python教程");
        cout << "delNum = " << delNum << endl;
        return 0;
    }

c) erase: 一次删除指定范围内的所有键值对, 返回被删除的最后一个键值对之后一个位置的迭代器

    用法: 
        iterator erase ( const_iterator first, const_iterator last );
    实例:
    #include <iostream>
    #include <string>
    #include <unordered_map>
    using namespace std;
    int main()
    {
        unordered_map<string, string> umap
        {
            {"STL教程", "http://www.cdsy.xyz/computer/programme/stl/"},
            {"Python教程", "http://www.cdsy.xyz/computer/programme/Python/"},
            {"Java教程", "http://www.cdsy.xyz/computer/programme/java/"} 
        };
        //first 指向第一个键值对
        unordered_map<string, string>::iterator first = umap.begin();
        //last 指向最后一个键值对
        unordered_map<string, string>::iterator last = --umap.end();
        //删除[fist,last)范围内的键值对
        auto ret = umap.erase(first, last);
        cout << "ret -> " << ret->first << " " << ret->second << endl;
        return 0;
    } 

d) clear: 一次性删除 容器中所有键值对

    实例：
    #include <iostream>
    #include <string>
    #include <unordered_map>
    using namespace std;
    int main()
    {
        unordered_map<string, string> umap
        {
            {"STL教程", "http://www.cdsy.xyz/computer/programme/stl/"},
            {"Python教程", "http://www.cdsy.xyz/computer/programme/Python/"},
            {"Java教程", "http://www.cdsy.xyz/computer/programme/java/"} 
        };
        //删除容器内所有键值对
        umap.clear();
        cout << "umap size = " << umap.size() << endl;
        return 0;
    } 
```         
             
 4. 查与改

  建议首选at使用,[]容易出错

```
1) []运算符访问元素
    #include <iostream>
    #include <string>
    #include <unordered_map>
    using namespace std;
    int main()
    {
      //创建 umap 容器
      unordered_map<string, string> umap
      {
          {"Python教程","http://www.cdsy.xyz/computer/programme/Python/"},
          {"Java教程","http://www.cdsy.xyz/computer/programme/java/"},
          {"Linux教程","http://www.cdsy.xyz/computer/system/linux/"} 
      };
      //获取 "Java教程" 对应的值
      string str = umap["Java教程"];
      cout << str << endl;            //输出结果: http://www.cdsy.xyz/computer/programme/java/
      return 0;
    }

2) []访问时, 无存在元素则新添加键值对
    #include <iostream>
    #include <string>
    #include <unordered_map>
    using namespace std;
    int main()
    {
        unordered_map<string, string> umap;  //创建空 umap 容器
        
        string str = umap["STL教程"];  //[]运算符在=右侧, 没有存在的元素, 则新添加, value值为空字符串
        
        umap["C教程"] = "http://www.cdsy.xyz/computer/programme/C_language/";   //[]运算符在=左侧, 没有存在元素则新添加键值对

        return 0;
    }

3) at 成员方法查看, 查找失败抛出out_of_range异常
    #include <iostream>
    #include <string>
    #include <unordered_map>
    using namespace std;
    int main()
    {
        //创建 umap 容器
        unordered_map<string, string> umap
        {
            {"Python教程","http://www.cdsy.xyz/computer/programme/Python/"},
            {"Java教程","http://www.cdsy.xyz/computer/programme/java/"},
            {"Linux教程","http://www.cdsy.xyz/computer/system/linux/"} 
        };

        string str = umap.at("Python教程");  //获取指定键对应的值
        cout << str << endl;

        //cout << umap.at("GO教程");  //执行此语句会抛出 out_of_range 异常
        return 0;
    }

4) find成员方法查找: 成功返回指定元素迭代器, 失败返回最后一个键值对之后的位置
    #include <iostream>
    #include <string>
    #include <unordered_map>
    using namespace std;
    int main()
    {
        //创建 umap 容器
        unordered_map<string, string> umap
        {
            {"Python教程","http://www.cdsy.xyz/computer/programme/Python/"},
            {"Java教程","http://www.cdsy.xyz/computer/programme/java/"},
            {"Linux教程","http://www.cdsy.xyz/computer/system/linux/"} 
        };

        unordered_map<string, string>::iterator iter = umap.find("Python教程");  //查找成功, 返回指定元素的迭代器
        cout << iter->first << " " << iter->second << endl;

        unordered_map<string, string>::iterator iter2 = umap.find("GO教程");  //查找失败, 返回最后一个键值对之后的位置
        if (iter2 == umap.end()) {
            cout << "当前容器中没有以\"GO教程\"为键的键值对";
        }
        return 0;
    }


```  

 6. 无序容器实现机制 

    参考: https://www.cdsy.xyz/computer/programme/stl/20210307/cd161510783312009.html


##### 2. unordered_multimap

(0) 概述

    unordered_multimap 容器也以键值对形式存储数据，且底层也采用哈希表结构存储各个键值对。两者唯一的不同之处在于，unordered_multimap 容器可以存储多个键相等的键值对

```
1. unordered_multimap 容器模板的定义如下所示：
    template < class Key,               //键（key）的类型
               class T,                 //值（value）的类型
               class Hash = hash<Key>,  //底层存储键值对时采用的哈希函数
               class Pred = equal_to<Key>,                  //判断各个键值对的键相等的规则
               class Alloc = allocator< pair<const Key,T> > // 指定分配器对象的类型
               > class unordered_multimap;
               
    以上 5 个参数中，必须显式给前 2 个参数传值，且除极个别的情况外，最多只使用前 4 个参数，它们各自的含义和功能如表 1 所示
```

<img width="425" alt="image" src="https://github.com/chuanchuan11/cplus/assets/42632290/c5d22dee-beb4-4663-b9f5-933eecaaa20c">

注意：当 unordered_multimap 容器中存储键值对的键为自定义类型时，默认的哈希函数 hash<key> 以及比较函数 equal_to<key> 将不再适用，这种情况下，需要我们自定义适用的哈希函数和比较函数，并分别显式传递给 Hash 参数和 Pred 参数

```
2. 头文件
    #include <unordered_map>
    using namespace std;
```

(1) 创建
```
1) 使用默认构造函数, 创建空的容器
  
   std::unordered_multimap<std::string, std::string> myummap; 
  
2) 创建同时进行初始化
  
  unordered_multimap<string, string>myummap
  {
    {"Python教程","http://www.cdsy.xyz/computer/programme/Python/"},
    {"Java教程","http://www.cdsy.xyz/computer/programme/java/"},
    {"Linux教程","http://www.cdsy.xyz/computer/system/linux/"} 
  };
 
3) 使用已有容器初始化新的容器, 调用拷贝构造函数
  
  unordered_multimap<string, string> myummap2(myummap);
  
4) 范围选择性初始化新容器
  
  std::unordered_multimap<std::string, std::string> myummap2(++myummap.begin(), myummap.end());    //传入 2 个迭代器
  
```
(2) 常见成员函数

<img width="425" alt="image" src="https://github.com/chuanchuan11/cplus/assets/42632290/bd040546-6f70-4e5f-88b2-4378d2ac5b76">
  
<img width="427" alt="image" src="https://github.com/chuanchuan11/cplus/assets/42632290/fa73fb97-9285-461c-90b1-98aa0db07cb4">

  
(3) 迭代器使用详解

  增删改查基本与unordered_map一致, 只是unordered_multimap没有提供[]和at方法, 意味着该容器无法通过指定键获取值, 因为该容器允许相等的键存在

##### 3. unordered_set容器

(0) 概述

  unordered_set容器和 set 容器很像，唯一的区别就在于 set 容器会自行对存储的数据进行排序，而 unordered_set 容器不会
  
```
1. unordered_set 容器具有以下几个特性:
  
    a) 不再以键值对的形式存储数据, 而是直接存储数据的值

    b) 容器内部存储的各个元素的值都互不相等, 且不能被修改

    c) 不会对内部存储的数据进行排序
  
注意: 不以键值对的形式存储数据, 理解为，为了节省存储空间，该类容器在实际存储时选择只存储每个键值对的值
  
2.头文件
  #include <unordered_set>
  using namespace std; 
```

  unordered_set 容器的类模板定义如下: 

```
  template < class Key,                    //容器中存储元素的类型
             class Hash = hash<Key>,       //确定元素存储位置所用的哈希函数
             class Pred = equal_to<Key>,   //判断各个元素是否相等所用的函数
             class Alloc = allocator<Key>  //指定分配器对象的类型
             > class unordered_set;
  
  以上 4 个参数中，只有第一个参数没有默认值，这意味着至少需要手动传递 1 个参数。事实上在 99% 的实际场景中最多只需要使用前 3 个参数，最后一个参数保持默认值即可
```

  <img width="427" alt="image" src="https://github.com/chuanchuan11/cplus/assets/42632290/b169d1ed-3c6c-4dc0-be47-202263fefda4">

  注意：如果 unordered_set 容器中存储的元素为自定义的数据类型，则默认的哈希函数 hash<key> 以及比较函数 equal_to<key> 将不再适用，只能自己设计适用该类型的哈希函数和比较函数，并显式传递给 Hash 参数和 Pred 参数

(1) 创建

```
a) 空的unordered_set容器
  
   std::unordered_set<std::string> uset; 
 
b) 创建同时完成初始化

   std::unordered_set<std::string> uset{ "http://www.cdsy.xyz/computer/programme/C_language/",
                                         "http://www.cdsy.xyz/computer/programme/java/",
                                         "http://www.cdsy.xyz/computer/system/linux/" 
                                       };

c) 已有容器初始化新容器
  
   std::unordered_set<std::string> uset2(uset);  //调用拷贝构造，如何是临时对象则调用移动构造函数

d) 选择性元素初始化新容器
  
   std::unordered_set<std::string> uset2(++uset.begin(),uset.end());  //传入迭代器，选择元素范围
```

(2) 常见成员函数

<img width="426" alt="image" src="https://github.com/chuanchuan11/cplus/assets/42632290/37b58c35-002c-4327-858d-5fb842cf9306">

<img width="428" alt="image" src="https://github.com/chuanchuan11/cplus/assets/42632290/414f5bb8-dbd3-43ae-a2fd-742c97333e57">

注意: 此容器模板类中没有重载 [ ] 运算符，也没有提供 at() 成员方法。不仅如此，由于 unordered_set 容器内部存储的元素值不能被修改，因此无论使用那个迭代器方法获得的迭代器，都不能用于修改容器中元素的值

(3) 迭代器使用详解

    增删改查参考常见成员函数

##### 4. unordered_multiset容器

(0) 概述

```
1. unordered_multiset 容器大部分的特性都和 unordered_set 容器相同: 
   
   a) unordered_multiset 不以键值对的形式存储数据, 而是直接存储数据的值

   b) 该类型容器底层采用的也是哈希表存储结构, 它不会对内部存储的数据进行排序

   c) unordered_multiset 容器内部存储的元素, 其值不能被修改
  
2. 不同点
  
   unordered_multiset 容器可以同时存储多个值相同的元素
  
3. 头文件
   #include <unordered_set>
   using namespace std;

4. unordered_multiset 容器类模板的定义如下
   template < class Key,                    //容器中存储元素的类型
              class Hash = hash<Key>,       //确定元素存储位置所用的哈希函数
              class Pred = equal_to<Key>,   //判断各个元素是否相等所用的函数
              class Alloc = allocator<Key>  //指定分配器对象的类型
           > class unordered_multiset;

   注意: 在 99% 的实际场景中，最多只需要使用前 3 个参数（各自含义如表 1 所示），最后一个参数保持默认值即可
```

<img width="424" alt="image" src="https://github.com/chuanchuan11/cplus/assets/42632290/c4f80223-11e0-4462-a907-ecef5d3e3a0c">

注意: 如果 unordered_multiset 容器中存储的元素为自定义的数据类型，则默认的哈希函数 hash<key> 以及比较函数 equal_to<key> 将不再适用，只能自己设计适用该类型的哈希函数和比较函数，并显式传递给 Hash 参数和 Pred 参数
  
(1) 创建

```
a) 创建空的 unordered_multiset 容器
  
   std::unordered_multiset<std::string> umset;
  
b) 创建同时完成初始化  
  
    std::unordered_multiset<std::string> umset{ "http://www.cdsy.xyz/computer/programme/C_language/",
                                                "http://www.cdsy.xyz/computer/programme/java/",
                                                "http://www.cdsy.xyz/computer/system/linux/" 
                                               };
c) 已有容器初始化新容器

    std::unordered_multiset<std::string> umset2(umset);  //拷贝构造函数, 如果是临时对象则调用移动构造函数
  
d) 选择性元素初始化

    std::unordered_multiset<std::string> umset2(++umset.begin(), umset.end());  //传入两个迭代器，选择元素范围
  
```

(2) 常见成员函数

<img width="427" alt="image" src="https://github.com/chuanchuan11/cplus/assets/42632290/ee19da63-d8a5-4016-8326-509ebc249044">

<img width="427" alt="image" src="https://github.com/chuanchuan11/cplus/assets/42632290/490a01a6-7e21-40ff-870c-cbe0c8cbe9c1">

注意，和 unordered_set 容器一样，unordered_multiset 模板类也没有重载 [ ] 运算符，没有提供 at() 成员方法。不仅如此，无论是由哪个成员方法返回的迭代器，都不能用于修改容器中元素的值

(3) 迭代器使用详解

    增删改查参考常用成员函数


##### 5. 无序容器的哈希函数和比较规则

1. 无序关联式容器中遗留得一个共性问题, 如何给无序容器自定义一个哈希函数和比较规则？

```
  默认的 hash<key> 哈希函数和 equal_to<key> 比较规则，它们仅适用于存储基本类型（比如 int、double、float、string 等）数据的无序容器, 
如果无序容器存储的数据类型为自定义的结构体或类，则 STL 标准库提供的 hash<key> 和 equal_to<key> 将不再适用

```

2. C++无序容器自定义哈希函数
  
    无序容器以键值对的方式存储数据（unordered_set 和 unordered_multiset 容器可以看做存储的是键和值相等的键值对），且底层采用哈希表结构存储各个键值对。在此存储结构中，哈希函数的功能是根据各个键值对中键的值，计算出一个哈希值（本质就是一个整数），哈希表可以根据该值判断出该键值对具体的存储位

    简单地理解哈希函数，它可以接收一个元素，并通过内部对该元素做再加工，最终会得出一个整形值并反馈回来。需要注意的是，哈希函数只是一个称谓，其本体并不是普通的函数形式，而是一个函数对象类。因此，如果我们想自定义个哈希函数，就需要自定义一个函数对象类

```
1) 例子, 假如有个person类: 
    class Person {
    public:
        Person(string name, int age) :name(name), age(age) {};
        string getName() const;
        int getAge() const;
    private:
        string name;
        int age;
    };
    string Person::getName() const {
        return this->name;
    }
    int Person::getAge() const {
        return this->age;
    }
  
2) 创建存储 Person 类对象的 unordered_set 容器，考虑到为自定义的类型，因此默认的哈希函数不再适用，这时就需要以函数对象类的方式自定义一个哈希函数。比如：
 
    class hash_fun {
    public:
        int operator()(const Person &A) const   //重载 ( ) 运算符时，其参数必须为 const 类型，且该方法也必须用 const 修饰
        {    
            return A.getAge();    //该哈希函数每接收一个 Person 类对象，都会返回该对象的 age 成员变量的值
        }
    };

3) 创建unordered_set 容器时，将 hash_fun 作为参数传递给该容器模板类中的 Pred 参数
  
  std::unordered_set<Person, hash_fun> myset；

  注意：此时创建的 myset 容器还无法使用，因为该容器使用的是默认的 std::equal_to<key> 比较规则，但此规则并不适用于该容器
```
 
3. C++无序容器自定义比较规则
   
```
    和哈希函数一样，无论创建哪种无序容器，都需要为其指定一种可比较容器中各个元素是否相等的规则。

    值得一提的是，默认情况下无序容器使用的 std::equal_to<key> 比较规则，其本质也是一个函数对象类，底层实现如下：
  
    template<class T>
    class equal_to
    {
    public:   
        bool operator()(const T& _Left, const T& _Right) const{
            return (_Left == _Right);
        }   
    };
  
    该规则在底层实现过程中，直接用 == 运算符比较容器中任意 2 个元素是否相等，这意味着，如果容器中存储的元素类型，支持直接用 == 运算符比较是否相等，则该容器可以使用默认的 std::equal_to<key> 比较规则；反之，就不可以使用
  
1) 自定义比较规则, 有以下 2 种方式:
  
   a) 在类中重载==运算符, 使得 std::equal_to<key> 比较规则中使用的 == 运算符变得合法
      
      //在person类中重载==运算符
      bool operator==(const Person &A, const Person &B)   //重载 == 运算符时，2 个参数必须用 const 修饰
      {
        return (A.getAge() == B.getAge());
      }
      
      示例:
           std::unordered_set<Person, hash_fun> myset{ {"zhangsan", 40},{"zhangsan", 40},{"lisi", 40},{"lisi", 30} };  
      
      结果: 只会存储 {"zhangsan", 40} 和 {"lisi", 30}, 因为前边3个对象根据比较规则是相等的

   b) 以函数对象类的方式自定义比较规则, 完全丢弃默认比较规则
  
      //自定义函数对象类的比较规则
      class mycmp 
      {
          public:
              bool operator()(const Person &A, const Person &B) const {
                  return (A.getName() == B.getName()) && (A.getAge() == B.getAge());
              }
      };
  
      示例:
          std::unordered_set<Person, hash_fun, mycmp> myset{ {"zhangsan", 40},{"zhangsan", 40},{"lisi", 40},{"lisi", 30} };
      结果: 
          内部存有  {"zhangsan", 40}、{"lisi", 40} 和 {"lisi", 30}，因为基于比较规则，前两个对象是相等的
```
  
##### 6. 实际使用中，如何选择合适的STL容器

