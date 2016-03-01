#include "cmybinarytree.h"



#ifdef DEBUG
#include <new>
#include<iostream>
using namespace std;
#endif

template<typename T>
CMyBinaryTree<T>::CNode::CNode(T a_oValue): m_pLeft(0), m_pRight(0), m_oValue(a_oValue)
{
}

template<typename T>
bool_t CMyBinaryTree<T>::addNodeR(CMyBinaryTree::CNode *&a_pCurrentNode, CMyBinaryTree::CNode a_oItem)
{
    bool_t fResult = false;
    CNode* newItem = 0;
    
    try
    {
        newItem = new CNode(a_oItem);
    }
#ifdef DEBUG
    catch(std::bad_alloc& ba)
    {
        std::cerr << "bad_alloc caught: " << ba.what() << '\n';
    }
#else
    catch(...){}
#endif

    if(0 == a_pCurrentNode && 0 != newItem)
    {
        a_pCurrentNode = newItem;
        m_uiItemsCounter++;
        fResult = true;
    }
    else if(0 != newItem)
    {
        if((*a_pCurrentNode) <= a_oItem )
        {
            if(0 != a_pCurrentNode->m_pRight)
            {
                fResult = addNodeR(a_pCurrentNode->m_pRight, a_oItem);
            }
            else
            {
                a_pCurrentNode->m_pRight = newItem;
                m_uiItemsCounter++;
                fResult = true;
            }
        }
        else
        {
            if(0 != a_pCurrentNode->m_pLeft)
            {
                fResult = addNodeR(a_pCurrentNode->m_pLeft, a_oItem);
            }
            else
            {
                a_pCurrentNode->m_pLeft = newItem;
                m_uiItemsCounter++;
                fResult = true;
            }
        }
    }

    return fResult;
}

template<typename T>
bool_t CMyBinaryTree<T>::addNodeI(CMyBinaryTree::CNode **a_pCurrentNode, CMyBinaryTree::CNode a_oItem)
{
    bool_t  _fResult = false;
    CNode*  _pNewItem = 0;
    CNode** _pCurrentItem = a_pCurrentNode;
    
    try
    {
        _pNewItem = new CNode(a_oItem);
    }
#ifdef DEBUG
    catch(std::bad_alloc& ba)
    {
        std::cerr << "bad_alloc caught: " << ba.what() << '\n';
    }
#else
    catch(...){}
#endif

    while(0 != (*_pCurrentItem))
    {
        if(**(_pCurrentItem) <= a_oItem)
        {
            _pCurrentItem = &((*_pCurrentItem)->m_pRight);
        }
        else
        {
            _pCurrentItem = &((*_pCurrentItem)->m_pLeft);
        }
    }
    
    if(0 == (*_pCurrentItem) && 0 != _pNewItem)
    {
        if(m_pRootElement == 0)
            m_pRootElement = _pNewItem;
        else
            (*_pCurrentItem) = _pNewItem;
        m_uiItemsCounter++;
        _fResult = true;
    }
    return _fResult;
}

template<typename T>
bool_t CMyBinaryTree<T>::removeNode(CMyBinaryTree::CNode a_oItem)
{
    bool_t _fResult = false;

    if(0 != m_pRootElement)
    {
        sItemToRemWithParent _oItem = findNodeWithParentI(&m_pRootElement, a_oItem);        
        
        if(0 != _oItem.m_ppItemToRem)
        {
            CNode* _pNodeToRemove = *_oItem.m_ppItemToRem;
            
            /// first case, element to remove has only a left child 
            ///-----------------------------------------------------
            if(0 != (*_oItem.m_ppItemToRem)->m_pLeft && 0 == (*_oItem.m_ppItemToRem)->m_pRight)
            {
                if (0 == _oItem.m_ppParent)
                {
                    m_pRootElement = (*_oItem.m_ppItemToRem)->m_pLeft;
                }
                else
                {
                    if((**_oItem.m_ppParent) > (**_oItem.m_ppItemToRem))
                    {
                        (*_oItem.m_ppParent)->m_pLeft = (*_oItem.m_ppItemToRem)->m_pLeft;
                    }
                    else
                    {
                        (*_oItem.m_ppParent)->m_pRight = (*_oItem.m_ppItemToRem)->m_pLeft;
                    }
                }                
                _fResult = true;
            }
            /// second case, element to remove has only a right child 
            ///----------------------------------------------------
            else if (0 == (*_oItem.m_ppItemToRem)->m_pLeft && 0 != (*_oItem.m_ppItemToRem)->m_pRight)
            {
                // copy left child of the child of removing element
                (*_oItem.m_ppParent)->m_pLeft = (*_oItem.m_ppItemToRem)->m_pLeft;
                
                if (0 == _oItem.m_ppParent)
                {
                    m_pRootElement = (*_oItem.m_ppItemToRem)->m_pRight;
                }
                else
                {
                    if((**_oItem.m_ppParent) > (**_oItem.m_ppItemToRem))
                    {
                        (*_oItem.m_ppParent)->m_pLeft = (*_oItem.m_ppItemToRem)->m_pRight;
                    }
                    else
                    {
                        (*_oItem.m_ppParent)->m_pRight = (*_oItem.m_ppItemToRem)->m_pRight;
                    }
                }                
                _fResult = true;
            }
            /// third case, element to remove has a right child and a left child
            ///----------------------------------------------------
            else if (0 != (*_oItem.m_ppItemToRem)->m_pLeft && 0 != (*_oItem.m_ppItemToRem)->m_pRight)
            {
                CNode* _pRightSideMin = (*_oItem.m_ppItemToRem)->m_pRight;
                CNode* _pRightSideMinParent = *_oItem.m_ppItemToRem;
                
                while(0 != _pRightSideMin->m_pLeft)
                {
                    _pRightSideMinParent = _pRightSideMin;
                    _pRightSideMin = _pRightSideMin->m_pLeft;
                }
                
                _pRightSideMinParent->m_pLeft = _pRightSideMin->m_pRight;
                _pRightSideMin->m_pLeft = (*_oItem.m_ppItemToRem)->m_pLeft;
                _pRightSideMin->m_pRight = (*_oItem.m_ppItemToRem)->m_pRight;
                
                if (0 == _oItem.m_ppParent)
                {
                    m_pRootElement = _pRightSideMin;
                }
                else
                {
                    if((**_oItem.m_ppParent) > (**_oItem.m_ppItemToRem))
                    {
                        (*_oItem.m_ppParent)->m_pLeft = _pRightSideMin;
                    }
                    else
                    {
                        (*_oItem.m_ppParent)->m_pRight = _pRightSideMin;
                    }
                }
                _fResult = true; 
            }
            /// last case, element to remove has no a right child and a left child
            ///----------------------------------------------------
            else
            {
                if (0 == _oItem.m_ppParent)
                {
                    m_pRootElement = 0;
                }
                else
                {
                    if((**_oItem.m_ppParent) > (**_oItem.m_ppItemToRem))
                    {
                        (*_oItem.m_ppParent)->m_pLeft = 0;
                    }
                    else
                    {
                        (*_oItem.m_ppParent)->m_pRight = 0;
                    }
                }
                
                _fResult = true;
            }
            
            if (true == _fResult)
            {
                delete _pNodeToRemove;
                _pNodeToRemove = 0;
            }
            
            m_uiItemsCounter--;
        }
        else
        {
            //Node not found
        }
    }

    return _fResult;
}

template<typename T>
typename CMyBinaryTree<T>::sItemToRemWithParent CMyBinaryTree<T>::findNodeWithParentR(CMyBinaryTree::CNode **a_pCurrentNode, CMyBinaryTree::CNode a_oItem)
{
    sItemToRemWithParent _sRetVaule = {0,0};
    static CNode** _pParent = 0;

    if(0 != (*a_pCurrentNode))
    {
        if( (**a_pCurrentNode) == a_oItem )
        {
            _sRetVaule.m_ppItemToRem = a_pCurrentNode;
            _sRetVaule.m_ppParent = _pParent;
            _pParent = 0;
        }
        else if ( (**a_pCurrentNode) > a_oItem )
        {
            _pParent = a_pCurrentNode;
            _sRetVaule = findNodeWithParentR(&(*a_pCurrentNode)->m_pLeft, a_oItem);
        }
        else
        {
            _pParent = a_pCurrentNode;
            _sRetVaule = findNodeWithParentR(&(*a_pCurrentNode)->m_pRight, a_oItem);
        }
    }

    return _sRetVaule;
}

template<typename T>
typename CMyBinaryTree<T>::sItemToRemWithParent CMyBinaryTree<T>::findNodeWithParentI(CMyBinaryTree::CNode **a_pCurrentNode, CMyBinaryTree::CNode a_oItem)
{
    CNode** _pCurrent = a_pCurrentNode;
    sItemToRemWithParent _sRetVaule = {0,0};
    
    while(0 != (*_pCurrent))
    {
        if((**_pCurrent) == a_oItem )
        {
            _sRetVaule.m_ppItemToRem = _pCurrent;
            break;
        }
        if( (**_pCurrent) > a_oItem )
        {
            _sRetVaule.m_ppParent = _pCurrent;
            _pCurrent = &((*_pCurrent)->m_pLeft);
        }
        else if ( (**_pCurrent) < a_oItem )
        {
            _sRetVaule.m_ppParent = _pCurrent;
            _pCurrent = &((*_pCurrent)->m_pRight);
        }
    }
    return _sRetVaule;
}

template<typename T>
CMyBinaryTree<T>::CMyBinaryTree():m_uiItemsCounter(0), m_pRootElement(0)
{

}

template<typename T>
CMyBinaryTree<T>::~CMyBinaryTree()
{
    
}

template<typename T>
bool_t CMyBinaryTree<T>::push(T a_oItem, int a_eMethod)
{
    bool_t _fResult = false;

    CNode _oItem(a_oItem);
    if(METHOD_ITERATION == a_eMethod)
        _fResult = addNodeI(&m_pRootElement, _oItem);
    else
        _fResult = addNodeR(m_pRootElement, _oItem);

    return _fResult;
}

template<typename T>
bool_t CMyBinaryTree<T>::remove(T a_oItem)
{
    bool_t _fResult = false;

    CNode _oItem(a_oItem);
    _fResult = removeNode(_oItem);

    return _fResult;
}

template<typename T>
bool_t CMyBinaryTree<T>::find(T a_oItem, int a_eMethod)
{
    bool_t _fResult = false;

    CNode  _oItem(a_oItem);
    sItemToRemWithParent _sItem = {0,0};
    
    if(METHOD_ITERATION == a_eMethod)
    {
        _sItem = findNodeWithParentI(&m_pRootElement, _oItem);
        _fResult = (0 != *(_sItem.m_ppItemToRem));
    }
    else
    {
        _sItem = findNodeWithParentR(&m_pRootElement, _oItem);
        _fResult = (0 != *(_sItem.m_ppItemToRem));
    }
    
    return _fResult;
}

template<typename T>
uint64_t CMyBinaryTree<T>::getItemsNumber()
{
    return m_uiItemsCounter;
}

#ifdef DEBUG

template<typename T>
void CMyBinaryTree<T>::doActionTreeInOrder(void (*exteralFunction)(T))
{
    doActionTreeInOrder(m_pRootElement, exteralFunction);
}

template<typename T>
void CMyBinaryTree<T>::doActionTreeInOrder(CNode *a_pCurrentNode, void (*exteralFunction)(T))
{
    if (0 != a_pCurrentNode)
    {
        doActionTreeInOrder(a_pCurrentNode->m_pLeft, exteralFunction);
        exteralFunction(a_pCurrentNode->m_oValue);
        doActionTreeInOrder(a_pCurrentNode->m_pRight, exteralFunction);
    }
}


#endif



