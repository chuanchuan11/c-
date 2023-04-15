>>  单例模式

#### 概念

    单例模式：保证一个类只生成唯一的实例对象. 也就是说在整个程序空间中，该类只存在一个实例对象

#### 为什么使用单例模式

    在整个程序空间使用全部变量，共享资源. 大规模系统中，为了性能考虑，需要节省对象的创建时间

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
