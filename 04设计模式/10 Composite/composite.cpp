#include <iostream>
#include <memory>
#include <list>

//common interface
class I_Component
{
public:
    virtual ~I_Component() {};
    virtual void Add(std::shared_ptr<I_Component> cmpt){};
    virtual void Remove(std::shared_ptr<I_Component> cmpt){};
    virtual void Display() = 0;
};

//tree branch 
class CompositeEntity : public I_Component
{
public:
    CompositeEntity(const std::string &s) : m_sName(s)
    {}

    virtual void Add(std::shared_ptr<I_Component> element) override
    {
        lElements.push_back(element);
    }

    virtual void Remove(std::shared_ptr<I_Component> element) override
    {
        lElements.remove(element);
    }

    virtual void Display()
    {
        std::cout << "current:" << m_sName << std::endl;
        std::cout << "this is composite has children size= " << lElements.size() << std::endl;
        for(auto & leaf : lElements)
        {
            leaf->Display();
        }
    }

private:
    std::string m_sName;
    std::list<std::shared_ptr<I_Component>> lElements;
};

//leaf 
class LeafEntity : public I_Component
{
public:
    LeafEntity(std::string s) : m_Sname(s)
    {}

    virtual void Display() override
    {
        std::cout << "this is leaf:" << m_Sname << std::endl;
    }

private:
    std::string m_Sname;
};

static void ShowComponent(std::shared_ptr<I_Component> c)
{
	c->Display();
	std::cout << "\r" << std::endl;
}

int main()
{
    //root
    std::shared_ptr<I_Component> pRoot = std::make_shared<CompositeEntity>("root/");

    //home/demo1.cpp
    std::shared_ptr<I_Component> pLevel1_1 = std::make_shared<CompositeEntity>("/home");
    pLevel1_1->Add(std::make_shared<LeafEntity>("demo1.cpp"));

    std::shared_ptr<I_Component> pLevel1_2 = std::make_shared<CompositeEntity>("/dev");

    ///proc/demo2.cpp, demo3.cpp
    std::shared_ptr<I_Component> pLevel1_2_1 = std::make_shared<CompositeEntity>("/proc");
    pLevel1_2_1->Add(std::make_shared<LeafEntity>("demo2.cpp"));
    pLevel1_2_1->Add(std::make_shared<LeafEntity>("demo3.cpp"));

    //dev/proc/
    pLevel1_2->Add(pLevel1_2_1);
    //root/home, /root/dev/
    pRoot->Add(pLevel1_1);
    pRoot->Add(pLevel1_2);


    //show root 
    std::cout << "=======root====== " << std::endl;
    ShowComponent(pRoot);

    //show dev
    std::cout << "=======dev====== " << std::endl;
    ShowComponent(pLevel1_2);

    //show home
    std::cout << "=======home====== " << std::endl;
    ShowComponent(pLevel1_1);

    return 0;
}

