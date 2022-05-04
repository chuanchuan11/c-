> ## 基于范围的for循环

### (1) 功能描述

    简化通过for循环对数据的遍历写法，尤其是对容器的元素访问
    
### (2) 使用方法

```
语法格式：
    for (declaration : expression)
    {
        //循环体
    }

declaration：
      表示此处要定义一个变量，该变量的类型为要遍历序列中存储元素的类型。可以用 auto 关键字表示，自行推导该变量的数据类型。
expression：
      表示要遍历的序列，常见的可以为事先定义好的普通数组或者容器，还可以是用 {} 大括号初始化的序列。


//1. 未简化的遍历
#include <iostream>
#include <vector>
#include <string.h>
using namespace std;
int main() {

    char arc[] = "http://c.biancheng.net/cplus/11/";
    int i;
    //for循环遍历普通数组
    for (i = 0; i < strlen(arc); i++) {
        cout << arc[i];
    }
    cout << endl;
    
    vector<char>myvector(arc,arc+23);
    vector<char>::iterator iter;
    //for循环遍历 vector 容器
    for (iter = myvector.begin(); iter != myvector.end(); ++iter) {
        cout << *iter;
    }
    return 0;
}

执行结果：
    http://c.biancheng.net/cplus/11/
    http://c.biancheng.net/

//2. 简化后的for循环
#include <iostream>
#include <vector>
using namespace std;
int main() {
    char arc[] = "http://c.biancheng.net/cplus/11/";
    
    //for循环遍历普通数组
    for (char ch : arc) {
        cout << ch;
    }
    cout << '!' << endl;
    
    vector<char>myvector(arc, arc + 23);
    //for循环遍历 vector 容器
    for (auto ch : myvector) {   //ch表示的是元素，不是迭代器
        cout << ch;
    }
    cout << '!';
    return 0;
}

执行结果：
    http://c.biancheng.net/cplus/11/ !
    http://c.biancheng.net/!
    
注意：
    新格式的 for 循环在遍历字符串序列时，不只是遍历到最后一个字符，还会遍历位于该字符串末尾的 '\0'（字符串的结束标志）。之所以第二行输出的字符串和 "!" 之间没有空格，是因为 myvector 容器中没有存储 '\0'。
    
//3. 遍历过程中修改变量，则用引用
#include <iostream>
#include <vector>
using namespace std;

int main() {
    char arc[] = "abcde";
    vector<char>myvector(arc, arc + 5);
    //for循环遍历并修改容器中各个字符的值
    for (auto &ch : myvector) {   
        ch++;
    }
    //for循环遍历输出容器中各个字符
    for (auto ch : myvector) {
        cout << ch;
    }
    return 0;
}
```
