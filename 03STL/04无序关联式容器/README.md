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

 6. 无序容器实现机制 


##### 2. TBD

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

##### 3. TBD

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

##### 4. TBD

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







