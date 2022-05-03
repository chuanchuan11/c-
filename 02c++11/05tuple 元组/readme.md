> ## tuple元组

### (1) 功能描述

  C++11 标准新引入了一种类模板，命名为 tuple（中文可直译为元组）。tuple 最大的特点是：实例化的对象可以存储 **任意数量、任意类型的数据**

### (2) tuple 创建和使用

    tuple 本质是一个以可变模板参数定义的类模板，它定义在 <tuple> 头文件并位于 std 命名空间中.

```
// 1. tuple对象的创建常用的方法有两种，一种是借助该类的构造函数，另一种是借助 make_tuple() 函数
#include <tuple>
using std::tuple;

int main()
{
    std::tuple<int, char> first;                             // 1)   first{}   默认构造
    std::tuple<int, char> second(first);                     // 2)   second{}  拷贝构造
    std::tuple<int, char> third(std::make_tuple(20, 'b'));   // 3)   third{20,'b'} 使用make_tuple函数创建临时对象
    std::tuple<long, char> fourth(third);                    // 4)的左值方式, fourth{20,'b'}
    std::tuple<int, char> fifth(10, 'a');                    // 5)的右值方式, fifth{10.'a'}
    std::tuple<int, char> sixth(std::make_pair(30, 'c'));    // 6)的右值方式, sixth{30,''c}  将pair对象转换为tuple对象
    return 0;
}

// 2. tuple常用函数
```


### (3) 常用场景与示例

   tuple 的应用场景很广泛，例如当需要存储多个不同类型的元素时，可以使用 tuple；当函数需要返回多个数据时，可以将这些数据存储在 tuple 中，函数只需返回一个 tuple 对象即可。

```
#include <iostream>
#include <tuple>
int main()
{
    int size;
    //创建一个 tuple 对象存储 10 和 'x'
    std::tuple<int, char> mytuple(10, 'x');
    
    //计算 mytuple 存储元素的个数
    size = std::tuple_size<decltype(mytuple)>::value;
    
    //输出 mytuple 中存储的元素
    std::cout << std::get<0>(mytuple) << " " << std::get<1>(mytuple) << std::endl;
    
    //修改指定的元素
    std::get<0>(mytuple) = 100;
    std::cout << std::get<0>(mytuple) << std::endl;
    
    //使用 makde_tuple() 创建一个 tuple 对象
    auto bar = std::make_tuple("test", 3.1, 14);
    
    //拆解 bar 对象，分别赋值给 mystr、mydou、myint
    const char* mystr = nullptr;
    double mydou;
    int myint;
    //使用 tie() 时，如果不想接受某个元素的值，实参可以用 std::ignore 代替
    std::tie(mystr, mydou, myint) = bar;
    //std::tie(std::ignore, std::ignore, myint) = bar;  //只接收第 3 个整形值
    
    //将 mytuple 和 bar 中的元素整合到 1 个 tuple 对象中
    auto mycat = std::tuple_cat(mytuple, bar);
    size = std::tuple_size<decltype(mycat)>::value;
    std::cout << size << std::endl;
    return 0;
}
```

参考：

  (1) http://c.biancheng.net/view/8600.html
  
