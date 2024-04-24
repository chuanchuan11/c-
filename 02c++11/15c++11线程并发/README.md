> ## c++11 线程并发

    c++11关于并发引入了好多新东西，这里按照如下顺序介绍：

        1) std::thread相关

        2) std::mutex相关

        3) std::lock相关

        4) std::atomic相关

        5) std::call_once相关

        6) volatile相关

        7) std::condition_variable相关

        8) std::future相关

        9) async相关

##### (1) std::thread

    c++11之前可能使用pthread_xxx来创建线程，繁琐且不易读，c++11引入了std::thread来创建线程，支持对线程join或者detach

##### (2) std::mutex

  std::mutex是一种线程同步的手段，用于保存多线程同时操作的共享数据, 分为四种：

    1) std::mutex：独占的互斥量，不能递归使用，不带超时功能

    2) std::recursive_mutex：递归互斥量，可重入，不带超时功能

    3) std::timed_mutex：带超时的互斥量，不能递归

    4) std::recursive_timed_mutex：带超时的互斥量，可以递归使用

```
示例1：std::mutex
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;
std::mutex mutex_;

int main() 
{
    auto func1 = [](int k) {
        mutex_.lock();
        for (int i = 0; i < k; ++i) 
        {
            cout << i << " ";
        }
        cout << endl;
        mutex_.unlock();
    };
    
    std::thread threads[5];
    for (int i = 0; i < 5; ++i) 
    {
        threads[i] = std::thread(func1, 200);
    }
    for (auto& th : threads) 
    {
        th.join();
    }
    return 0;
}

//2. std::timed_mutex
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

using namespace std;
std::timed_mutex timed_mutex_;

int main() {
    auto func1 = [](int k) {
        timed_mutex_.try_lock_for(std::chrono::milliseconds(200));
        for (int i = 0; i < k; ++i) 
        {
            cout << i << " ";
        }
        cout << endl;
        timed_mutex_.unlock();
    };
    std::thread threads[5];
    for (int i = 0; i < 5; ++i) 
    {
        threads[i] = std::thread(func1, 200);
    }
    for (auto& th : threads) 
    {
        th.join();
    }
    return 0;
}

```

##### (3) std::lock

    可以动态的释放锁资源，防止线程由于编码失误导致一直持有锁, c++11主要有std::lock_guard和std::unique_lock两种方式

```
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

using namespace std;
std::mutex mutex_;

int main() {
    auto func1 = [](int k) {
        // std::lock_guard<std::mutex> lock(mutex_); //只能自动解锁,效率高
        std::unique_lock<std::mutex> lock(mutex_);  //自动解锁,也支持手动加解锁,常与条件变量一起使用
        for (int i = 0; i < k; ++i) {
            cout << i << " ";
        }
        cout << endl;
    };
    std::thread threads[5];
    for (int i = 0; i < 5; ++i) 
    {
        threads[i] = std::thread(func1, 200);
    }
    for (auto& th : threads) 
    {
        th.join();
    }
    return 0;
}

注意：
    (1) std::lock_gurad相比于std::unique_lock更加轻量级，少了一些成员函数，std::unique_lock类有unlock函数，可以手动释放锁，所以条件变量都配合std::unique_lock使用，而不是std::lock_guard，因为条件变量在wait时需要有手动释放锁的能力
```

##### (4) std::atomic

    c++11提供了原子类型std::atomic，理论上这个T可以是任意类型，不需要使用std::mutex来保护该变量

原子操作：更小的代码片段，并且该片段必定是连续执行的，不可分割。

1.1 原子操作std::atomic与互斥量的区别

    1）互斥量：类模板，保护一段共享代码段，可以是一段代码，也可以是一个变量。

    2）原子操作std::atomic：类模板，保护一个变量。

1.2 为何需要原子操作std::atomic

    为何已经有互斥量了，还要引入std::atomic呢，这是因为互斥量保护的数据范围比较大，我们期望更小范围的保护。并且当共享数据为一个变量时，原子操作std::atomic效率更高。

```
//示例1
struct OriginCounter { // 普通的计数器
    int count;
    std::mutex mutex_;
    void add() {
        std::lock_guard<std::mutex> lock(mutex_); //需要加锁进行保护
        ++count;
    }

    void sub() {
        std::lock_guard<std::mutex> lock(mutex_);
        --count;
    }

    int get() {
        std::lock_guard<std::mutex> lock(mutex_);
        return count;
    }
};

//示例2：
struct NewCounter { // 使用原子变量的计数器
    std::atomic<int> count;
    void add() {
        ++count;  //不需要加锁保护
        // count.store(++count);这种方式也可以
    }

    void sub() {
        --count;
        // count.store(--count);
    }

    int get() {
        return count.load();
    }
};
```

参考： https://blog.csdn.net/weixin_44479862/article/details/128059243



##### (5) std::condition_variable 与 std::condition_variable_any

    条件变量是c++11引入的一种同步机制，它可以阻塞一个线程或者多个线程，直到有线程通知或者超时才会唤醒正在阻塞的线程，条件变量需要和锁配合使用，这里的锁就是上面介绍的std::unique_lock

    等待相关函数:
       
       std::wait(cond, pred)                 等待，直到通知且pred在一次苏醒后结果为true
       
       std::wait_for(cond, duration, pred)   等待超时或直到通知且pred在一次苏醒后结果为true
       
       std::until(cond, timepoint, pred)     等待通知或时间点且pred在一次苏醒后结果为true
       
       注意：pred参数可以不使用
     
    通知相关函数：
    
       std::notify_one 通知一个
       
       std::notify_all 通知所有

    condition_variable与condition_variable_any的区别：
    
      std::condition_variable_any 的 wait 函数可以接受任何 lockable 参数,而 std::condition_variable 只能接受 std::unique_lock<std::mutex> 类型的参数，

除此以外，和 std::condition_variable 几乎完全一样。推荐首先使用：condition_variable

```
//示例：
class CountDownLatch {
    public:
    explicit CountDownLatch(uint32_t count) : count_(count);

    void CountDown() {
        std::unique_lock<std::mutex> lock(mutex_);
        --count_;
        if (count_ == 0) {
            cv_.notify_all();  //通知
        }
    }

    void Await(uint32_t time_ms = 0) {
        std::unique_lock<std::mutex> lock(mutex_);
        while (count_ > 0) {
            if (time_ms > 0) {
                cv_.wait_for(lock, std::chrono::milliseconds(time_ms));  //超时等待
            } else {
                cv_.wait(lock); //等待
            }
        }
    }

    uint32_t GetCount() const {
        std::unique_lock<std::mutex> lock(mutex_);
        return count_;
    }

    private:
    std::condition_variable cv_;
    mutable std::mutex mutex_;
    uint32_t count_ = 0;
};
```

参考：

(1) https://blog.csdn.net/baidu_41388533/article/details/106680428

(2) https://www.cnblogs.com/haippy/p/3252041.html


##### (6) std::future

    c++11关于异步操作提供了future相关的类，主要有std::future、std::promise和std::packaged_task，std::future比std::thread高级些，std::future作为异步结果的传输通道，通过get()可以很方便的获取线程函数的返回值，std::promise用来包装一个值，将数据和future绑定起来，而std::packaged_task则用来包装一个调用对象，将函数和future绑定起来，方便异步调用。而std::future是不可以复制的，如果需要复制放到容器中可以使用std::shared_future

```
示例1： std::promise与std::future配合使用
#include <iostream>       
#include <functional>     
#include <thread>        
#include <future>     // std::promise, std::future

void print_int(std::future<int>& fut) 
{
    int x = fut.get();                    // 获取共享状态的值.
    std::cout << "value: " << x << '\n';  // 打印 value: 10.
}

int main ()
{
    std::promise<int> prom;                    // 生成一个 std::promise<int> 对象.
    std::future<int> fut = prom.get_future();  // 和 future 关联.
    std::thread t(print_int, std::ref(fut));   // 将 future 交给另外一个线程t.
    prom.set_value(10);                        // 设置共享状态的值, 此处和线程t保持同步.
    t.join();
    return 0;
}

示例2：std::packaged_task与std::future
#include <functional>
#include <future>
#include <iostream>
#include <thread>

using namespace std;

int func(int in) 
{
    return in + 1;
}

int main() {
    std::packaged_task<int(int)> task(func);   //生成一个packaged_task对象
    std::future<int> fut = task.get_future();  //和future关联
    std::thread(std::move(task), 5).detach();  //异步调用
    cout << "result " << fut.get() << endl;    //获取可调用对象的结果
    return 0;
}
```
