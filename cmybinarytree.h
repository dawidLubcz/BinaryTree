#ifndef CMYBINARYTREE_H
#define CMYBINARYTREE_H

typedef bool bool_t;
typedef long unsigned int uint64_t;

enum eFindItemMethod
{
    METHOD_RECURSION = 0,
    METHOD_ITERATION
};

template<class T>
class CMyBinaryTree
{
private:
    class CNode
    {
    public:
        CNode* m_pLeft;
        CNode* m_pRight;
        T m_oValue;

        explicit CNode(T a_oValue);

        friend bool_t operator ==(const CNode &a_rLValue, const CNode &a_rRValue)
        {
            bool_t fResult = (a_rLValue.m_oValue == a_rRValue.m_oValue);
            return fResult;
        }

        friend bool_t operator <(const CNode &a_rLValue, const CNode &a_rRValue)
        {
            bool_t fResult = (a_rLValue.m_oValue < a_rRValue.m_oValue);
            return fResult;
        }

        friend bool_t operator >(const CNode &a_rLValue, const CNode &a_rRValue)
        {
            bool_t fResult = (a_rLValue.m_oValue > a_rRValue.m_oValue);
            return fResult;
        }

        friend bool_t operator <=(const CNode &a_rLValue, const CNode &a_rRValue)
        {
            bool_t fResult = (a_rLValue.m_oValue <= a_rRValue.m_oValue);
            return fResult;
        }
    };
    
    struct sItemToRemWithParent
    {
        CNode** m_ppItemToRem;
        CNode** m_ppParent;
    };

    uint64_t m_uiItemsCounter;
    CNode* m_pRootElement;

    bool_t addNodeR(CMyBinaryTree::CNode *&a_pCurrentNode, CNode a_oItem);
    bool_t addNodeI(CNode **a_pCurrentNode, CNode a_oItem);
    bool_t removeNode(CNode a_oItem);
    
    // Method returns pointer to parent node. 0 if not found
    // Method use recursion.
    sItemToRemWithParent findNodeWithParentR(CNode **a_pRootNode, CNode a_oItem); 
    
    // Method returns pointer to a parent node. 0 if not found.
    // Method use iterations.
    sItemToRemWithParent findNodeWithParentI(CNode **a_pRootNode, CNode a_oItem);

public:
    CMyBinaryTree();
    ~CMyBinaryTree();

    bool_t push(T a_oItem, int a_eMethod = METHOD_ITERATION);
    bool_t remove(T a_oItem);
    bool_t find(T a_oItem, int a_eMethod = METHOD_ITERATION);
    uint64_t getItemsNumber();

#ifdef DEBUG
    void doActionTreeInOrder(void (*exteralFunction)(T));
    void doActionTreeInOrder(CNode *a_pCurrentNode, void (*exteralFunction)(T));
#endif
};

#include "cmybinarytree.cpp"

#endif // CMYBINARYTREE_H
