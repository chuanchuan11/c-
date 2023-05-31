#include <iostream>
#include <string>

//抽象处理者
class AbstractLogger
{
protected:
    int level;
    AbstractLogger* nextLogger = nullptr;
public:
    static const int INFO  = 1;
    static const int DEBUG = 2;
    static const int ERROR = 3;

    /*设置下一个处理者*/
    void setNextLogger(AbstractLogger* nextLogger)
    {
        this->nextLogger = nextLogger;
    }

    /*日志信息打印*/
    void logMessage(int level, std::string message)
    {
        if(this->level <= level)
        {
            write(message);
        }
        else
        {
            if(nullptr != nextLogger)
            {
                nextLogger->logMessage(level, message);
            }
        }
    }

    /*具体处理节点*/
    virtual void write(std::string message) = 0;
};

class ConsoleLogger : public AbstractLogger
{
public:
    ConsoleLogger(int level)
    {
        this->level = level;
    }
    void write(std::string message)
    {
        std::cout << "standard console::Logger: " << message << std::endl;
    }
};

class ErrorLogger : public AbstractLogger
{
public:
    ErrorLogger(int level)
    {
        this->level = level;
    }
    void write(std::string message)
    {
        std::cout << "Error console::Logger: " << message << std::endl;
    }
};

class FileLogger : public AbstractLogger
{
public:
    FileLogger(int level)
    {
        this->level = level;
    }
    void write(std::string message)
    {
        std::cout << "File console::Logger: " << message << std::endl;
    }
};

AbstractLogger* getChainOfLoggers()
{
    AbstractLogger* errorLogger = new ErrorLogger(AbstractLogger::ERROR);
    AbstractLogger* fileLogger  = new FileLogger(AbstractLogger::DEBUG);
    AbstractLogger* consoleLogger = new ConsoleLogger(AbstractLogger::INFO);

    errorLogger->setNextLogger(fileLogger);
    fileLogger->setNextLogger(consoleLogger);

    return errorLogger;
}

int main()
{
    AbstractLogger* loggerChain = getChainOfLoggers();
    loggerChain->logMessage(AbstractLogger::INFO, "this is an information");
    loggerChain->logMessage(AbstractLogger::DEBUG, "this is debug log");
    loggerChain->logMessage(AbstractLogger::ERROR, "this error log");
    return 0;
}