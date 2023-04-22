>>  单例模式

#### 应用场景

    1) 日志系统. 一个项目中应该只有一个日志系统, 则应当确保日志对象只能被创建一份
    
    2) 全局数据存储. C++中应尽量避免全局变量的使用. 可以通过一个数据类专门负责存储数据, 该类只存在一个实例化对象, 其他各类可以在其中存储需要传递的数据

#### 优缺点

    (1) 通过单例模式，可以实现类之间的数据传输，而不必写各类两两之间的通信接口，降低了代码的复杂度

    (2) 在多线程下不做保护可能会生成多份实例

#### 实现单例常用步骤

    (1) 构造函数私有化[默认/拷贝/移动/构造]
    
    (2) 提供一个全局的静态方法
    
    (3) 在类中定义一个静态指针，指向本类静态实例
    
#### 示例1:非线程安全

```
class singleTon
{
public:
    static std::shared_ptr<singleTon> instance_ptr();
private:

    singleTon();
    singleTon(const singleTon &); //copy
    singleTon(singleTon &&);      //move
};

std::shared_ptr<singleTon> singleTon::instance_ptr()
{
    static std::shared_ptr<singleTon> instance = nullptr;
    if(nullptr == instance)
    {
        instance =  std::shared_ptr<singleTon>(new singleTon);
    }
    return instance;
}

singleTon::singleTon()
{
    std::cout << " singleTon creat" << std::endl;
}
```

#### 示例2：线程安全

    当多个线程同时运行，当第一个线程调用构造函数时候，进入休眠状态，第二个线程进入时候，发现指针还是空，又调用一次构造函数，此时单例模式失效. 优化：

```
std::shared_ptr<singleTon> singleTon::instance_ptr()
{
    static std::shared_ptr<singleTon> instance = nullptr;
 
    std::lock_guard<std::mutex> lock(creatMtx);
    if(nullptr == instance)
    {
        instance =  std::shared_ptr<singleTon>(new singleTon);
    }
    return instance;
}
```
