>> 类图与类之间的关系

```
(1) 类图属性可见性
    包括共有（Public），私有（Private），受保护（Protected）和朋友（Friendly）4种，在类图中分别用 +，-，#，~表示
```

![image](https://github.com/chuanchuan11/cplus/assets/42632290/5fb463cb-d1e3-4cba-ae25-3a5ef5f9fc87)

```
(2) 类图关系:
    a) 依赖关系: 临时关联
        代码层面: 某个类的方法通过局部变量、方法的参数或者对静态方法的调用来访问另一个类（被依赖类）中的某些方法来完成一些职责
        表示: 带箭头虚线, 箭头指向被依赖的类
```

![image](https://github.com/chuanchuan11/cplus/assets/42632290/6a77025d-0c5e-469e-8297-70c328a60ad8)

```
    b) 关联关系: 属于引用关系
        代码层面: 将一个类的对象作为另一个类的成员变量来实现关联关系
        表示：用带两个箭头或者没有箭头的实线来表示，单向的关联用带一个箭头的实线来表示，箭头从使用类指向被关联的类
```

![image](https://github.com/chuanchuan11/cplus/assets/42632290/79f21778-f201-4962-8547-d7f86f55c416)

```
    c) 聚合关系: 是关联关系的一种，是强关联关系，是整体和部分之间的关系
        代码层面: 成员对象来实现的，其中成员对象是整体对象的一部分，但是成员对象可以脱离整体对象而独立存在
        表示: 聚合关系可以用带空心菱形的实线来表示，菱形指向整体
```

![image](https://github.com/chuanchuan11/cplus/assets/42632290/f9c5ff6f-c04f-47c1-bd8f-4c3bc5ba38d7)

```
    d) 组合关系: 也是关联关系的一种，也表示类之间的整体与部分的关系，但它是一种更强烈的聚合关系
        代码层面：整体对象可以控制部分对象的生命周期，一旦整体对象不存在，部分对象也将不存在，部分对象不能脱离整体对象而存在
        表示：用带实心菱形的实线来表示，菱形指向整体
```

![image](https://github.com/chuanchuan11/cplus/assets/42632290/f1562aaf-7d42-474f-afdd-e3ca8a570f4c)

```
    e) 泛化关系: 父类与子类之间的继承关系
        代码层面：面向对象的继承机制来实现泛化关系
        表示：用带空心三角箭头的实线来表示，箭头从子类指向父类
```

![image](https://github.com/chuanchuan11/cplus/assets/42632290/d8fe4f89-d670-4986-8b13-c701e4c2192f)

```
    d) 实现关系: 接口与实现类之间的关系
        代码层面：类实现了接口，类中的操作实现了接口中所声明的所有的抽象操作
        表示：使用带空心三角箭头的虚线来表示，箭头从实现类指向接口
```

![image](https://github.com/chuanchuan11/cplus/assets/42632290/e6ec3202-3867-4060-afac-3fd5cbdbf809)



(1) 参考： https://www.cnblogs.com/bardzx/p/12096958.html

(2) 详细UML学习参考：https://github.com/chuanchuan11/UML
