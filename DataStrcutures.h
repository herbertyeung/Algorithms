#pragma once

#include <queue>
using namespace std;

template< typename T>
struct bstNode
{

	T value;
	bstNode<T> * left;
	bstNode<T> * right;
	bstNode<T> * parent;
};

template< class T>
class CBSTree
{
public:
	CBSTree(void)
	{
		m_pRoot = NULL;
	}

	CBSTree(T tValue)
	{
		InsertNode(tValue);
	}

	~CBSTree(void)
	{
		_deleteAll();
	}

	inline void InsertNode(T tValue)
	{

		if(m_pRoot == NULL)
		{
			m_pRoot = new bstNode<T>;
			m_pRoot->value = tValue;
			m_pRoot->left = NULL;
			m_pRoot->right = NULL;
			m_pRoot->parent = NULL;
		}
		else
		{
			bstNode<T> * pNode = m_pRoot;
			while (pNode != NULL)
			{
				if(tValue <= pNode->value)
				{
					if(pNode->left == NULL)
					{
						pNode->left = new bstNode<T>;
						pNode->left->value = tValue;
						pNode->left->parent = pNode;
						pNode->left->left = NULL;
						pNode->left->right = NULL;
						break;
					}
					else
						pNode = pNode->left;

				}
				else
				{
					if(pNode->right == NULL)
					{
						pNode->right = new bstNode<T>;
						pNode->right->parent = pNode;
						pNode->right->value = tValue;
						pNode->right->left = NULL;
						pNode->right->right = NULL;
						break;
					}
					else
						pNode = pNode->right;

				}
			}

		}

	}

	void DeleteNode(bstNode<T> * pNode)
	{
		_deleteNode(pNode);
	}

	/*void DeleteNode(T Key)
	{
		bstNode<T> * pNode = FindNode(Key);
		DeleteNode(pNode);
	}*/

	bstNode<T> * FindNode(T key)
	{
		if(m_pRoot != NULL)
		{
			bstNode<T> * pNode = m_pRoot;
			while (pNode != NULL)
			{
				if(pNode->value == key)
					return pNode;
				if(key < pNode->value)
					pNode = pNode->left;
				else
					pNode = pNode->right;
			}
		}
		return NULL;
	}

	void Printf(bool bLevel = true,int order = 1)
	{
		if(m_pRoot == NULL)
		{
			printf("BST is empty\r\n");
			return;
		}
		bstNode<T> * pNode = m_pRoot;
		if(bLevel)
		{
			queue<bstNode<T> *> q;
			
			q.push(pNode);

			while (!q.empty())
			{
				pNode = q.front();
				q.pop();
				if(pNode)
				{
					printf("%d,",pNode->value);
					q.push(pNode->left);
					q.push(pNode->right);
				}

			}
		}
		else
		{
			_print(m_pRoot,order);
		}
		printf("\n");
	}
	
protected:
	void _print(bstNode<T> * pNode,int order)
	{
		if(pNode != NULL)
		{
			switch (order)
			{
			case 1:
				printf("%d,",pNode->value);
				_print(pNode->left,order);
				_print(pNode->right,order);
				break;
			case 2:
				_print(pNode->left,order);
				printf("%d,",pNode->value);
				_print(pNode->right,order);
				break;
			case 3:
				_print(pNode->left,order);	
				_print(pNode->right,order);
				printf("%d,",pNode->value);
				break;
			default:
				break;
			}		

		}

	}
	//返回指定结点以下的最小结点
	inline bstNode<T> * _findMinNode(bstNode<T> * pNode)
	{
		bstNode<T> * pReturn = NULL;
		while (pNode != NULL)
		{
			pReturn = pNode;
			pNode = pNode->left;
		}
		return pReturn;
	}
	//返回指定结点以下的最大值
	inline bstNode<T> * _findMaxNode(bstNode<T> * pNode)
	{
		bstNode<T> * pReturn = NULL;
		while (pNode != NULL)
		{
			pReturn = pNode;
			pNode = pNode->right;
		}
		return pReturn;
	}
	inline void _deleteAll()
	{
		_delete(m_pRoot);
		m_pRoot = NULL;
	}
	inline void _delete(bstNode<T> * pNode)
	{
		 if(pNode != NULL)
		 {
			 _delete(pNode->left);
			 _delete(pNode->right);
			 delete pNode;
		 }
	}

	//删除指定结点
	inline void _deleteNode(bstNode<T> * pNode)
	{
		if(pNode != NULL)
		{
			bstNode<T> * pNodeParent = pNode->parent;
			
			//找到其右边的最小点
			bstNode<T> * newNode = _findMinNode(pNode->right);
			if(newNode != NULL) //右子点有值
			{
				
				if(newNode == pNode->right)//olnly have right node			
				{
					newNode->parent = pNodeParent;
					newNode->left = pNode->left;

					if(pNodeParent != NULL)//如果parent不为空，其右为新换节点
						pNodeParent->right = newNode;
					else
						m_pRoot = newNode;
				}
				else //中间位置
				{
					newNode->parent->left = NULL;
					newNode->parent = pNodeParent;
					newNode->left = pNode->left;
					newNode->right = pNode->right;
					if(pNodeParent != NULL) //如果parent不为空，其左为新换节点
						pNodeParent->left = newNode;
					else
						m_pRoot = newNode;
				}
				
			}
			else if(pNode->left != NULL) //左子点有值，右边为null
			{
				newNode = pNode->left;
				if(pNodeParent != NULL)
				{
					pNodeParent->left = newNode;
					newNode->parent = pNodeParent;
				}
				else
				{
					newNode->parent = NULL;
					m_pRoot = newNode;
				}
			}
			else if(pNodeParent == NULL)//只有一个根节点
				m_pRoot = NULL;
			else //最小子节点
			{
				if(pNodeParent->left == pNode)
					pNodeParent->left = NULL;
				else
					pNodeParent->right = NULL;
			}
			//删除节点
			delete pNode;
			pNode = NULL;
			
		}
	}
private:
	bstNode<T> *m_pRoot;
};


class HtDListNode
{
public:
	HtDListNode(HtDListNode *pPrve,HtDListNode *pNext,int nValue)
	{
		m_pNode = (HtDListNode *)((int)pPrve ^ (int)pNext);
		m_nValue = nValue;
	}
	HtDListNode * GetPrev(HtDListNode * pNext)
	{
		return (HtDListNode * )((int)m_pNode ^(int)pNext);
	}

	HtDListNode * GetNext(HtDListNode * pPrev)
	{
		return (HtDListNode * )((int)m_pNode ^(int)pPrev);
	}
	void Update(HtDListNode *pPrve,HtDListNode *pNext)
	{
		m_pNode = (HtDListNode *)((int)pPrve ^ (int)pNext);
	}

	int GetValue()const {return  m_nValue;}
	int SetValue(int nValue){m_nValue = nValue;}

	
private:
	HtDListNode * m_pNode;
	int m_nValue;

};

class HtDList
{
public:
	HtDList()
	{
	}
	virtual ~HtDList()
	{
	}

	HtDListNode *GetBegin(){return m_pBegin;}
	HtDListNode *GetEnd()
	{
		if (!m_pBegin)
			return NULL;

		HtDListNode *prev = NULL;
		HtDListNode *it = m_pBegin;
		while (it)
		{
			HtDListNode *t = it;
			it = it->GetNext(prev);
			prev = t;
		}

		return prev;

	}
	void AddNode(int nValue)
	{
		HtDListNode * pNode = GetEnd();
		if(pNode == NULL)
		{
			m_pBegin = new HtDListNode(NULL,NULL,nValue);
		}
		else
		{
			HtDListNode *p = pNode->GetPrev(NULL);
			HtDListNode *pNext = new HtDListNode(pNode,NULL,nValue);
			pNode->Update(p,pNext);
		}
	}

	void Test();
private:
	HtDListNode *m_pBegin;

};