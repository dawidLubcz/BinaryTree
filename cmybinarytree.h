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

    ////////////////////////////////////////
    /// \brief m_uiItemsCounter
    ///
    uint64_t m_uiItemsCounter;

    ////////////////////////////////////////
    /// \brief m_pRootElement
    ///
    CNode* m_pRootElement;

    ////////////////////////////////////////
    /// \brief add new node using recursive
    /// \param a_pCurrentNode
    /// \param a_oItem
    /// \return 
    ///
    bool_t addNodeR(CMyBinaryTree::CNode *&a_pCurrentNode, CNode a_oItem);
    
    ////////////////////////////////////////
    /// \brief add new node using iteration
    /// \param a_pCurrentNode
    /// \param a_oItem
    /// \return 
    ///
    bool_t addNodeI(CNode **a_pCurrentNode, CNode a_oItem);
    
    ////////////////////////////////////////
    /// \brief remove node
    /// \param a_oItem
    /// \return 
    ///
    bool_t removeNode(CNode a_oItem);
    
    ////////////////////////////////////////
    /// \brief Method returns pointer to a parent node if value was found in any child nodes.
    /// If value was not found, method will return 0. Method using recursion.
    /// \param a_pRootNode
    /// \param a_oItem
    /// \return 
    ///
    sItemToRemWithParent findNodeWithParentR(CNode **a_pRootNode, CNode a_oItem); 
    
    ////////////////////////////////////////
    /// \brief Method returns pointer to a parent node if value was found in any child nodes.
    /// If value was not found, method will return 0. Method using iteration.
    /// \param a_pRootNode
    /// \param a_oItem
    /// \return 
    ///
    sItemToRemWithParent findNodeWithParentI(CNode **a_pRootNode, CNode a_oItem);

public:
    
    ////////////////////////////////////////
    /// \brief class constructor
    ///
    CMyBinaryTree();

    ////////////////////////////////////////
    /// \brief class destructor
    ///
    ~CMyBinaryTree();

    ////////////////////////////////////////
    /// \brief push item into the tree
    /// \param a_oItem
    /// \param a_eMethod
    /// \return 
    /// 
    /// Note: Recursion is slower and need more memory, it was wrote just for research
    ///
    bool_t push(T a_oItem, int a_eMethod = METHOD_ITERATION);

    ////////////////////////////////////////
    /// \brief remove item from the tree
    /// \param a_oItem
    /// \return 
    ///
    bool_t remove(T a_oItem);

    ////////////////////////////////////////
    /// \brief find item in the tree
    /// \param a_oItem
    /// \param a_eMethod
    /// \return 
    ///
    /// Note: Recursion is slower and need more memory, it was wrote just for research 
    /// 
    bool_t find(T a_oItem, int a_eMethod = METHOD_ITERATION);

    ////////////////////////////////////////
    /// \brief get number of items it the tree
    /// \return 
    ///
    uint64_t getItemsNumber();

#ifdef DEBUG
    void doActionTreeInOrder(void (*exteralFunction)(T));
    void doActionTreeInOrder(CNode *a_pCurrentNode, void (*exteralFunction)(T));
#endif
};

#include "cmybinarytree.cpp"

#endif // CMYBINARYTREE_H
