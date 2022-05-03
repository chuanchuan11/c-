> ## using 定义别名

### (1) 功能描述

    using 的别名语法覆盖了 typedef 的全部功能，重定义类型更加简洁[重定义的类型并不是一个新的类型，仅仅只是原有的类型取了一个新的名字]

### (2) 使用实例

```
//1. 重定义变量类型
typedef std::map<std::string, int> map_int_t;
using map_int_t = std::map<std::string, int>;

//2. 重定义函数指针类型
typedef void (*func_t)(int, int);
using func_t = void (*)(int, int);

//3. 重定义模板类型
/* C++98/03 */
template <typename T>
struct func_t
{
    typedef void (*type)(T, T);
};
// 使用 func_t 模板
func_t<int>::type xx_1;

/* C++11 */
template <typename T>
using func_t = void (*)(T, T);
// 使用 func_t 模板
func_t<int> xx_2;
```

参考：http://c.biancheng.net/view/3730.html
