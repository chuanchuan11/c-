#include <iostream>
#include <memory>

// 命令接口, C++中为抽象基类
class Command {
 public:
    virtual void execute() = 0;
};

// 接受者: 电视
class Television{
 public:
    void open() {
        std::cout << "打开电视机!" << std::endl;
    }

    void close() {
        std::cout << "关闭电视机!" << std::endl;
    }

    void changeChannel(){
        std::cout << "切换电视频道!" << std::endl;
    }
};

// 具体命令类: 打开电视
class TVOpenCommand : public Command{
 public:
    TVOpenCommand(std::shared_ptr<Television> tv) : tv_(tv) {}

    void execute() override
    {
        tv_->open();
    }

 private:
    std::shared_ptr<Television> tv_;
};

// 具体命令类: 关闭电视
class TVCloseCommand : public Command{
 public:
    TVCloseCommand(std::shared_ptr<Television> tv) : tv_(tv) {}

    void execute() override
    {
        tv_->close();
    }

 private:
    std::shared_ptr<Television> tv_;
};

// 具体命令类: 切换频道
class TVChangeCommand : public Command{
 public:
    TVChangeCommand(std::shared_ptr<Television> tv) : tv_(tv) {}
    void execute() override
    {
        tv_->changeChannel();
    }

 private:
    std::shared_ptr<Television> tv_;
};

// 触发者: 遥控器
class Controller{
 public:
    Controller() {}
    // 设置命令
    void setCommand(std::shared_ptr<Command> cmd) {
        cmd_ = cmd;
    }
    // 执行命令
    void executeCommand() 
    {
        cmd_->execute();
    }

 private:
    std::shared_ptr<Command> cmd_;
};

int main()
{
    // 接收者: 电视机
    std::shared_ptr<Television> tv = std::make_shared<Television>();

    // 命令
    std::shared_ptr<Command> openCommand = std::make_shared<TVOpenCommand>(tv);
    std::shared_ptr<Command> closeCommand = std::make_shared<TVCloseCommand>(tv);
    std::shared_ptr<Command> changeCommand = std::make_shared<TVChangeCommand>(tv);

    // 调用者: 遥控器
    std::shared_ptr<Controller> controller = std::make_shared<Controller>();

    // 测试, 请求命令
    controller->setCommand(openCommand);
    controller->executeCommand();
    controller->setCommand(closeCommand);
    controller->executeCommand();
    controller->setCommand(changeCommand);
    controller->executeCommand();

    // 也可以将命令使用vector统一储存到controller中, 最后统一执行

    return 0;
}