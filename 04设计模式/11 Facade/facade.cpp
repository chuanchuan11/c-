#include <iostream>

//subsystem1
class CSyntaxParser
{
public:
    static void SyntaxParser()
    {
        std::cout << "syntax parser" << std::endl;
    }
};

//subsystem2
class CGenMidCode
{
public:
    static void GenMidCode()
    {
        std::cout << "genMidCode" << std::endl;
    }
};

//subsystem3
class CGenAssemblyCode
{
public:
    static void GenAssemblyCode()
    {
        std::cout << "GenAssemblyCode" << std::endl;
    }
};

//subsystem4
class CLink
{
public:
    static void Link()
    {
        std::cout << "Link" << std::endl;
    }
};

//Facade mode
class CFacade
{
public:
    static void Facade()
    {
        CSyntaxParser::SyntaxParser();
        CGenMidCode::GenMidCode();
        CGenAssemblyCode::GenAssemblyCode();
        CLink::Link();
    }
};

int main()
{
    CFacade::Facade();
    return 0;
}