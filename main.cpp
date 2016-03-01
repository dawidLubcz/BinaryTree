#include <iostream>
#include <cstdarg>
#include <sstream>

#define DEBUG
#include "cmybinarytree.h"
#include "ilogger.h"
#include "celapsedtime.h"

using namespace std;

///////////////////////////////////////////////
/// \brief The CLogger class
//////////////////////////////////////////////
class CLogger: public ILogger
{
public:
    CLogger()
    {}
    void print(const char a_acArg[] ...)
    {
        std::string _strOutput; const char* _pcOpt;
        va_list _pArgument;
        va_start(_pArgument,a_acArg);
        
        for(_pcOpt = a_acArg;*_pcOpt != '\0';_pcOpt++)
        {
            while( *_pcOpt != '%' ) 
            { 
                 _strOutput += *_pcOpt;
                 _pcOpt++; 
            }
            _pcOpt++;  
            
            switch(*_pcOpt)
            {
                case 'i':
                case 'I':
                {
                    std::ostringstream s;
                    s<<va_arg(_pArgument,int);
                    _strOutput.append(s.str());
                }
                break;
                
                case 'd':
                case 'D':
                {
                    std::ostringstream s;
                    s<<va_arg(_pArgument,double);
                    _strOutput.append(s.str());
                }
                break;
                
                case 's':
                case 'S':
                {
                    _strOutput.append(va_arg(_pArgument,char*));
                }
                break;
                }
        }        
        cout<<_strOutput<<endl;        
        va_end(_pArgument);
    }    
};
CLogger g_oCLogger = CLogger();

/////////////////////////////////////////////////
/// \brief printRes
/// \param a_fRes
/// \param a_cName
////////////////////////////////////////////////
void printRes(bool a_fRes, const char* a_cName)
{
    using namespace std;
    cout<<"Test case: "<<a_cName<<" : "<<(a_fRes==true?"PASSED":"FAILED")<<endl;
}

#define PRINT_RES(a) printRes(a,__func__)

//////////////////////////////////////////////
/// \brief The CTest class
//////////////////////////////////////////////
class CTest
{
public:
    CTest(int a):member(a){}
    int member;

    friend bool operator >(const CTest &lvalue, const CTest &rvalue)
    {
        return (lvalue.member > rvalue.member);
    }
    friend bool operator <(const CTest &lvalue, const CTest &rvalue)
    {
        return (lvalue.member < rvalue.member);
    }
    friend bool operator <=(const CTest &lvalue, const CTest &rvalue)
    {
        return (lvalue.member <= rvalue.member);
    }
    friend bool operator ==(const CTest &lvalue, const CTest &rvalue)
    {
        return (lvalue.member == rvalue.member);
    }

    static void printTest(CTest var)
    {
        std::cout<<"Wartosc: "<<var.member<<std::endl;
    }
};

//////////////////////////////////////
const int g_iCount = 10000;
bool Test_1_adding_finding_items_I();
bool Test_2_adding_finding_items_R();
bool Test_3_removing_items();
/////////////////////////////////////

int main()
{    
    bool fResult = true;
    
    fResult &= Test_1_adding_finding_items_I();
    fResult &= Test_2_adding_finding_items_R();
    fResult &= Test_3_removing_items();
    
    cout<<"Test result: "<<(fResult==true?"PASSED":"FAILED")<<endl;
    
    return 0;
}

/////////////////////////////////////
/// \brief Test_1_adding_finding_items_I
/// \return 
/////////////////////////////////////
bool Test_1_adding_finding_items_I()
{
    CElapsedTime oETime = CElapsedTime(&g_oCLogger);
    /////////////////////////////////////
    /// Preconditions
    //////////////////////////////////// 
   
    CMyBinaryTree<CTest> tree; // tree
    const int liczbaElementow = g_iCount;  
    bool fResult = true;
    
    /////////////////////////////////////
    /// Test case
    //////////////////////////////////// 
    
    for(int i=0; i<liczbaElementow;i++)
    {
        CTest ob(i);
        fResult &= tree.push(ob, METHOD_ITERATION);
    }    

    for(int i=0;i<liczbaElementow;i++)
    {
        CTest ob(i);
        fResult &= tree.find(ob, METHOD_ITERATION);
    }    
    
    fResult &= (tree.getItemsNumber() == liczbaElementow);
    
    PRINT_RES(fResult);
    return fResult;
}

////////////////////////////////////
/// \brief Test_2_adding_finding_items_R
/// \return 
////////////////////////////////////
bool Test_2_adding_finding_items_R()
{
    CElapsedTime oETime = CElapsedTime(&g_oCLogger);
    /////////////////////////////////////
    /// Preconditions
    //////////////////////////////////// 
    
    CMyBinaryTree<CTest> tree;
    const int liczbaElementow = g_iCount;    
    bool fResult = true;

    /////////////////////////////////////
    /// Test case
    //////////////////////////////////// 
    
    for(int i=0; i<liczbaElementow;i++)
    {
        CTest ob(i);
        fResult &= tree.push(ob, METHOD_RECURSION);
    }    

    for(int i=0;i<liczbaElementow;i++)
    {
        CTest ob(i);
        fResult &= tree.find(ob, METHOD_RECURSION);
    }    
    
    fResult &= (tree.getItemsNumber() == liczbaElementow);
    
    PRINT_RES(fResult);
    return fResult;
}


bool Test_removing_items_no_right_child();
bool Test_removing_items_no_left_child();
bool Test_removing_items_right_and_left();
bool Test_removing_items_foreign_item();
bool Test_removing_last_item();

/////////////////////////////////////////
/// \brief Test_3_removing_items
/// \return 
/////////////////////////////////////////
bool Test_3_removing_items()
{
    CElapsedTime oETime = CElapsedTime(&g_oCLogger);
#define DEBUG
    bool fResult = true;
    
    fResult &= Test_removing_items_no_right_child();
    fResult &= Test_removing_items_no_left_child();
    fResult &= Test_removing_items_right_and_left();    
    fResult &= Test_removing_items_foreign_item();
    fResult &= Test_removing_last_item();
    
    PRINT_RES(fResult);
    return fResult;
}

/////////////////////////////////////////
/// \brief Test_removing_items_no_right_child
/// \return 
/////////////////////////////////////////
bool Test_removing_items_no_right_child()
{
    /////////////////////////////////////
    /// Preconditions
    //////////////////////////////////// 
    CMyBinaryTree<CTest> tree;
    const int liczbaElementow = 5;
    bool fResult = true;
    
    for(int i=0; i<liczbaElementow;i++)
    {
        CTest ob(i);
        fResult &= tree.push(ob, METHOD_RECURSION);
    }    
    
    // remove last item
    fResult &= tree.remove(CTest(liczbaElementow - 2));
    
    PRINT_RES(fResult);
    return fResult;
}

////////////////////////////////////////
/// \brief Test_removing_items_no_left_child
/// \return 
////////////////////////////////////////
bool Test_removing_items_no_left_child()
{
    /////////////////////////////////////
    /// Preconditions
    //////////////////////////////////// 
    bool fResult = true;
    // build the tree
    CMyBinaryTree<CTest> tree;
    CTest ob5(5); CTest ob4(4); CTest ob3(3); CTest ob6(6);
    tree.push(ob5);
    tree.push(ob4);
    tree.push(ob3);
    tree.push(ob6);
   
    fResult &= tree.remove(ob4);
    
    PRINT_RES(fResult);
    return fResult;
}

/////////////////////////////////////////
/// \brief Test_removing_items_right_and_left
/// \return 
/////////////////////////////////////////
bool Test_removing_items_right_and_left()
{
    /////////////////////////////////////
    /// Preconditions
    //////////////////////////////////// 
    bool fResult = true;

    CMyBinaryTree<CTest> tree3;
    CTest ob1(1); CTest ob2(2); CTest ob10(10); CTest ob12(12);
    CTest ob8(8); CTest ob6(6); CTest ob9(9); CTest ob5(5);
    tree3.push(ob1);
    tree3.push(ob2);
    tree3.push(ob10);
    tree3.push(ob8);
    tree3.push(ob12);
    tree3.push(ob6);
    tree3.push(ob9);
    tree3.push(ob5);
    
    /////////////////////////////////////////////////
    
    PRINT_RES(fResult);
    return fResult;
}

///////////////////////////////////////
/// \brief Test_removing_items_foreign_item
/// \return 
///////////////////////////////////////
bool Test_removing_items_foreign_item()
{
    /////////////////////////////////////
    /// Preconditions
    //////////////////////////////////// 
    CMyBinaryTree<CTest> tree;
    const int liczbaElementow = 5;
    bool fResult = true;
    
    for(int i=0; i<liczbaElementow;i++)
    {
        CTest ob(i);
        fResult &= tree.push(ob);
    }    
    
    for(int i=0; i<liczbaElementow-2;i++)
        fResult &= tree.remove(CTest(liczbaElementow + 10));
    
    PRINT_RES((fResult == false));
    return (fResult == false);
}

////////////////////////////////////////
/// \brief Test_removing_last_item
/// \return 
////////////////////////////////////////
bool Test_removing_last_item()
{
    /////////////////////////////////////
    /// Preconditions
    //////////////////////////////////// 
    CMyBinaryTree<CTest> tree;
    const int liczbaElementow = g_iCount;
    bool fResult = true;
    
    /////////////////////////////////////
    /// Test case
    //////////////////////////////////// 
    
    for(int i=0; i<liczbaElementow;i++)
    {
        CTest ob(i);
        fResult &= tree.push(ob);
    }    

    // remove last item
    for(int i=0; i<liczbaElementow;i++)
        fResult &= tree.remove(CTest(liczbaElementow -i-1));

    PRINT_RES(fResult);
    return fResult;
}
