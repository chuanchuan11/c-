> ## 跟踪返回值类型(返回值类型后置)

### (1) 功能描述

  返回值类型后置语法，是为了解决函数返回值类型依赖于参数而导致难以确定返回值类型的问题。有了这种语法以后，对返回值类型的推导就可以用清晰的方式（直接通过参数做运算）描述出来

### (2) 用法实例

```
//因为 t、u 在参数列表中，而 C++ 的返回值是前置语法，在返回值定义的时候参数变量还不存在
template <typename T, typename U>
decltype(t + u) add(T t, U u)  // error: t、u尚未定义
{
    return t + u;
}

//新语法，将 decltype 和 auto 结合起来完成返回值类型的推导
template <typename T, typename U>
auto add(T t, U u) -> decltype(t + u)
{
    return t + u;
}


```

参考：

(1) http://c.biancheng.net/view/3727.html

