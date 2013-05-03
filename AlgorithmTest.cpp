// AlgorithmTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <queue>
using namespace std;

#define DEFAULT_SIZE 50

template <class T>
class CHtQueue
{
public:
	CHtQueue(int nSize = DEFAULT_SIZE)
	{

		m_pArray = NULL;
		if(nSize > 0)
			m_pArray = new T[nSize + 1];
		m_nSize = nSize;
		nHead = 0;
		nTail = 0;
	}
	virtual ~CHtQueue()
	{
		if(m_pArray != NULL)
			delete [] m_pArray;
	}
	void Push(T key)
	{
		//队是否满了
		if(nHead == nTail + 1)
			return;
		if(nTail >= m_nSize)
		{
			nTail = nHead - 1;
			if(nTail < 0)
				return;
		
		}
		
		m_pArray[nTail++] = key;
	}

	T Pop()
	{
		if(nHead >= m_nSize)
		{
			nHead = nTail - 1;
			if(nHead < 0)
				return NULL;
		}
		
		return m_pArray[nHead++];
	}

	bool Empty()
	{
		return (nHead == nTail);
	}

private:
	T *m_pArray;
	int nHead;
	int nTail;
	int m_nSize;
};

//Linked List
class HtList
{
public:
	HtList( int nVal):Value(nVal)
	{
		
	}

	HtList * Next;
	int Value;

	inline void Add(int newVal)
	{
		HtList *pNode = new HtList(newVal);
		HtList * pTemp = this;
		while(NULL != pTemp->Next )
			pTemp = pTemp->Next;
		pTemp->Next = pNode;
	}

	inline HtList * Del(HtList * pHead,int nKey)
	{
		
		return _del(pHead,nKey);
	}

	inline HtList * Sort(HtList *pHead,bool bReverse)
	{
		HtList * pNode = pHead,*pNext;
		int nTemp = 0;
		while (pNode != NULL)
		{
			pNext = pNode->Next;
			if(pNext)
			{
				if(pNode->Value > pNext->Value)
				{
					nTemp = pNode->Value;
					pNode->Value = pNext->Value;
					pNext->Value = nTemp;
				}
				
			}
			pNode = pNode->Next;

		}
		return pHead;
	}
	
	inline HtList * FinNthToLast(HtList * pHead, int n)
	{
		if(pHead == NULL || n < 1)
			return NULL;
		HtList * pNode = pHead;
		for(int i = 0; i < n-1; i++)
		{
			if(pNode == NULL)
				return NULL;
			pNode = pNode->Next;
		}

		return pNode;
	}
	inline HtList * CheckDuplicate(HtList * pHead)
	{
		HtList * pCurrent = pHead, *pNext,*pTemp,*pTempHead = NULL;
		while (pCurrent != NULL)
		{
			pNext = pCurrent->Next;
			pTempHead = pCurrent;
			while (NULL != pNext)
			{
				
				if(pCurrent->Value == pNext->Value)
				{
					pTemp = pNext->Next;
					delete pNext;
					
					pTempHead->Next =pTemp;
					pNext = pTemp;
				}
				else
				{
					pTempHead= pNext;
					pNext = pNext->Next;

				}
			}
			pCurrent = pCurrent->Next;
		}

		return pHead;
	}
	inline void Print(HtList *pHead)
	{
		HtList * pNode = pHead;
		while (pNode)
		{
			printf(" %d|",pNode->Value);
			pNode = pNode->Next;
		}
		printf("\r\n");

	}
private:
	HtList * _del(HtList * pHead,int nKey)
	{
		if(NULL == pHead )
			return NULL;
		
		HtList * pNext, *pNode = pHead;
		//HtList *pReturn = pHead;
		
		if(pNode->Value == nKey)
		{
			pNext = pNode->Next;
			delete pNode;
			return _del(pNext,nKey);
		}
		pNext = pNode->Next;
		while(pNext != NULL)
		{
			if(pNext->Value == nKey)
			{
				pNode->Next = pNext->Next;
				delete pNext;
				pNext = pNode;
			}
			else
				pNode = pNext;
			pNext = pNext->Next;

		}
	
		return pHead;
	}

};

///BST
struct node
{
	node()
	{
		key_value = 0;
		left = NULL;
		right = NULL;
		 bRoot = false;
	}
	node(int nvalue)
	{
		left = NULL;
		right = NULL;
		 bRoot = false;;
		key_value = nvalue;
	}
	//node(int nvalue,int nleft,int nright)
	//{
	//	node(nvalue);
	//	left = new node(nleft);
	//	right = new node(nright);
	//}
  int key_value;
  node *left;
  node *right;
  bool bRoot;
};

class BTree
{
public:
	BTree()
	{
		m_pRoot = NULL;
	}

	inline void Insert(int Key)
	{
		if(m_pRoot != NULL)
		{
			_Inert(Key,m_pRoot);
		}
		else
		{
			m_pRoot = new node();
			m_pRoot->key_value = Key;
			m_pRoot->left = m_pRoot->left = NULL;
			m_pRoot->bRoot = true;
		}
	}
	
	inline void Print(bool ByLevel = false)
	{
		if(ByLevel)
		{
			//queue<node *> q;
			CHtQueue<node *> q;

			node * pnode = NULL;
			q.Push(m_pRoot);
			while (!q.Empty())
			{
				pnode = q.Pop();
				if(pnode)
				{
					printf("%d ",pnode->key_value);
					//q.pop();
					if(pnode->left != NULL)
						q.Push(pnode->left);
					if(pnode->right != NULL)
						q.Push(pnode->right);
				}
			}
		}
		else
			_Print(m_pRoot);
	
	
	}

	//lowest (nearest) common ancestor
	//node * LowestAncestor(int p1, int p2)
	//{
	//	if(m_pRoot == NULL)
	//		return NULL;
	//	if(p1 == m_pRoot->key_value || p2 == m_pRoot->key_value)
	//		return m_pRoot;
	//	node * pNode1 = m_pRoot->left,*pNode2 = m_pRoot->right;
	//	node *pNode;
	//	while (pNode1)
	//	{
	//		pNode = pNode1->left;
	//		if(pNode)
	//		{
	//			pNode->key_value == p1
	//		}
	//	}
	//}
private:
	inline void _Print(node *pNode)
	{
		if(pNode != NULL)
		{
			printf("%d ",pNode->key_value);

			_Print(pNode->left);
			_Print(pNode->right);
		}

	}

	inline void _Inert(int Key,node *pNode)
	{
		if(pNode != NULL)
		{
			if(Key < pNode->key_value)
			{
				if(pNode->left != NULL)
					_Inert(Key,pNode->left);
				else
				{
					pNode->left = new node();
					pNode->left->key_value = Key;
					pNode->left->left = NULL;
					pNode->left->right = NULL;
						
				}
			}
			else
			{
				if(pNode->right != NULL)
					_Inert(Key,pNode->right);
				else
				{
					pNode->right = new node();
					pNode->right->key_value = Key;
					pNode->right->left = NULL;
					pNode->right->right = NULL;
				}
			}
		}
	}
	node *m_pRoot;
};

void swapNode(node * p1,node *p2)
{
	if(p1 && p2 == NULL)
		return;
	int tmp = p1->key_value;
	p1->key_value = p2->key_value;
	p2->key_value = tmp;
}



void SortTNode(node *pNode)
{
	if(pNode == NULL)
		return;
	if(pNode->left != NULL && pNode->key_value < pNode->left->key_value)
		swapNode(pNode,pNode->left);
	if(pNode->right != NULL && pNode->key_value > pNode->right->key_value)
		swapNode(pNode,pNode->right);
	SortTNode(pNode->left);
	SortTNode(pNode->right);
}
void AdjustTree(node * pHead,node * pNode,bool bLeft  = true)
{
	if(pNode == NULL)
		return;
	if(bLeft)
	{		
		if(pNode && pNode->key_value > pHead->key_value)
		{
			swapNode(pNode,pHead);	
			SortTNode(pHead);
		}
	}
	else
	{
		if(pNode && pNode->key_value < pHead->key_value)
		{
			swapNode(pNode,pHead);
			SortTNode(pHead);
		}
	}
	AdjustTree(pHead,pNode->left,bLeft);
	AdjustTree(pHead,pNode->right,bLeft);
}
void SortBT(node *pHead)
{
	node * pNode = pHead;
	SortTNode(pNode);
	AdjustTree(pHead,pHead->left);
	AdjustTree(pHead,pHead->right,false);
}

void TestSortBT()
{
	node * pHead = new node(6);

	pHead->left = new node(8);
	pHead->right = new node(7);
	pHead->left->left = new node(3);
	pHead->left->right = new node(2);

	pHead->right->left = new node(1);
	pHead->right->right = new node(4);

	SortBT(pHead);

}

/*
       6
	 4    8
   3   5 2  9
 1
*/
void buildTree(BTree * root)
{
	int nA[] = {6,4,8,3,5,2,9,1};


	for(int i = 0 ; i < sizeof(nA)/sizeof(int); i++)
	{	
		root->Insert(nA[i]);
	}


}
//print a BST level order
void LevelPrintBST()
{
	BTree * pBTree = new BTree();
	buildTree(pBTree);

	pBTree->Print(true);
}

//Given an array, which is sorted but rotated. Find an element efficiently in this array
//O(lgN)

int Search(int * pArray,int Key,int low, int high)
{

	if(low > high) // 
		return -1;
	//divided
	int mid = (high + low) /2;

	if(pArray[mid] == Key)
		return mid;//return key index;

	if(pArray[low] <= pArray[mid]) // left half is sorted;
	{
		if(pArray[low] <= Key && pArray[mid] >= Key)//the key is present in left half.
			return Search(pArray,Key,low,mid - 1);
		else
			return Search(pArray,Key,mid + 1, high);

	}
	else
	{
		//right half is sorted;
		if(pArray[mid] <= Key && pArray[high] >= Key)
			return Search(pArray,Key,mid + 1, high);
		else// if key is not present in right half..search in left half.
			return Search(pArray,Key,low,mid - 1);

	}

}
void RotaedArrayFindKey()
{
	//rotated array
	int nArray[] = {7,8,9,1,2,3,4,5,6};//roteated 3 times.
	int Key = 9;
	int nPos = Search(nArray,Key,0,sizeof(nArray)/sizeof(int));
	printf("found %d at %d ",Key,nPos);
}


//Binary tree to Binary Search Tree conversion
#include <algorithm>


int add(int x, int y) 
{ 
	int a, b; 
	do 
	{ 
		a = x & y;
		b = x ^ y; 
		x = a << 1; 
		y = b; 
	}
	while (a > 0); 
	return b; 
} 
int divideby3(int num) 
{ 
	int sum = 0; 

	while (num > 3)
	{ 
		sum = add(num >> 2, sum); 
		num = add(num >> 2, num & 3); 
	} 
	if (num == 3)
        sum = add(sum, 1);

	return sum;
}
char * ht_strstr(char *str, char *serach)
{
	return NULL;
}
char * ht_strcat(char *dst, char * src)
{
	char *cp = dst;
	while (*cp) // find dst end;
		cp++;
	while (*cp++ = *src++)
	{
		;
	}
	return (dst);
}
char * ht_strcpy(char * dst,char * src)
{
	
	while (*dst++ = *src++)
		;
	return (dst);
}
bool IsPower2(int n)
{
	int ae =(0 == (n&(n-1) ));
	return ae;

	bool bResult = false;
	int x = 0;
	x = n/2;
	char * a = "this is a test";
	char * c = " about algorithm";
	char b[100];
	ht_strcpy(b,a);
	ht_strcat(b,c);
	char *t = strstr(a,"it");
	//int nr = ht_strstr(b,"it");
	while (x%2 == 0)
	{
		x >>= 1;
		if(x == 1)
		{
			bResult = true;
			break;
		}

	}
	return bResult;
}
#include <iostream>

int func(int a,int b)
{
	a^=b^=a^=b;
	return 1;
}

void LinkedListTest()
{
	HtList * pList = new HtList(2);
	int nArray[] ={2,2,5,6,3,2,3,2,2,1,7,10,3,2,4,5,6,2,3,7,8,9};
	for(int i = 0 ;i < sizeof(nArray) /sizeof(int); i++)
	{
		pList->Add(nArray[i]);
	}
	pList->Print(pList);

	HtList * pNewHead = pList->FinNthToLast(pList,7);
	if(pNewHead)
	{
		pNewHead->Print(pNewHead);
	}
}
void ht_swap(char * a, char * b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}
void Mernupation(char * str,int index,int size)
{
	if(str== NULL || size < 0 )
		return;
	if( index == size)
		printf("%s",str);
	else
	{
		for(int j = index; j < size; j++)
		{
			ht_swap((str+index),(str +j));
			
			printf("%s ,", str);
			Mernupation(str,index+1,size);
			ht_swap((str+index),(str +j));
			printf("%s ,", str);
			
			
		}
	}
	
	//printf("共 %d \r\n",ncount);

}
int Fibonacci(int n)
{
	if( n < 2 )
		return n;
	return (Fibonacci(n-1) + Fibonacci(n-2));

}

void testF(int n)
{
	for(int i = 0;i < n; i++)
		printf("%d,",Fibonacci(i));
}
int F(int n)
{
	_Longlong temp = 0;
	_Longlong t1 = 0,t2 = 1;
	//printf("0,1,1,2,3,5,8");
	printf("0,1");
	for(int i = 2; i < n;i++)
	{
		temp = t1 + t2;
		printf(",%d",temp);
		t1 = t2;
		t2 = temp;
		

	}
	printf("\r\n");
	return 0;
}
int factorial(int n)
{
	if(n > 1)
		return (factorial(n -1) * n);
	else
		return 1;
}
void setPixel( int xCoord, int yCoord )
{
	printf("%d,%d|",xCoord,yCoord);
}
void drawEighthOfCircle( int radius )
{

	//float t;
	//int x,y;
	//for(int i =0; i< 45; i++)
	//{
	//	t = cos(i/360);
	//	x = radius*t;
	//	t = sin(i/360);
	//	y = radius*t;
	//	setPixel(x,y);

	//}
	int x = radius,y =0;
	while (y <=x)
	{
		x = sqrt(radius * radius - y*y);
		setPixel(x,y);
		y++;
	}
	
}

char * ReverseStr(char *str)
{

	char * end = str;
	char tmp;
	if (str) {
		while (*end) {
			++end;
		}
		--end;
		while (str < end) {
			tmp = *str;
			*str++ = *end;
			*end-- = tmp;
		}
	}
	return str;
}


void RemoveDuplicate(char *str)
{
	int len = strlen(str);
	if(len < 2)
		return;
	int tail = 1,j=0;
	
	for(int i = 1; i < len; i++)
	{
		for(j = 0; j < tail; j++) //check unique list 0 - tail
		{
			if(str[i] == str[j])
				break;
		}
		if(j == tail) //if unique list is not duplicate, copy it;
			str[tail++] = str[i];
			
	}
	str[tail] = '\0';

	return;
	//int len = strlen(str);
	//if (len < 2) return;
	//int tail = 1;
	//for (int i = 1; i < len; ++i) {
	//	int j;
	//	for (j = 0; j < tail; ++j) {
	//		if (str[i] == str[j]) break;
	//	}
	//	if (j == tail) {
	//		str[tail] = str[i];
	//		++tail;
	//	}
	//}
	//str[tail] = 0;
	//return;
	////sort
	//if(str == NULL)
	//	return;
	//char *end = str + 1;
	//char *beg = str ;
	//char temp,t2;
	//while (*beg)
	//{
	//	temp = *beg;
	//	while (*end)
	//	{
	//		if(temp != '*' && temp == *end)
	//		{
	//			*end = '*';

	//		}
	//		end++;
	//	}	
	//	beg++;
	//	end = beg + 1;
	//}
}

char * MergStr(char *begin1,char * end1,char *begin2,char * end2)
{
	int len = (end1-begin1)+(end2 - begin2);
	char * newStr = new char[len + 1];
	char tmp;
	while (begin1 != end1 )
	{
		if(*begin2 && *begin2 < *begin1)
		{
			*newStr++ = *begin2;
			begin2++;
		}
		else
		{
			*newStr++ = *begin1;
			begin1++;
		}
		
	}
	while (begin2 != end2)
	{
		*newStr++ = *begin2++;
	}
	return newStr;
}
void SortStrt(char * str);
void SortStr(char  *begin, char *end)
{
	int len = (end - begin);

	//if(len < 32)
	//{
	//	while (begin != end)
	//	{
	//		char tmp = *begin;
	//		char * p = begin + 1;
	//		while (p != end)
	//		{
	//			if(*p < *begin)
	//			{
	//				tmp =  *p;
	//				*p = *begin;
	//				*begin = tmp;
	//			}
	//			p++;
	//		}
	//		begin++;
	//	}

	//}
	//else
	if(len > 2)
	{
		int mid = len >> 1;
		SortStr(begin,begin+mid);
		SortStr(begin+mid + 1, end);
		MergStr(begin,begin+mid,begin+mid + 1, end);
	}

}

void SortStrt(char * str)
{
	
	if(str == NULL)
		return;
	char * p = NULL;
	char temp = 'a';
	while (*str)
	{
		p = str+1;
		while (*p)
		{
			if(*p < *str)
			{
				temp =  *p;
				*p = *str;
				*str = temp;
			}
			p++;
		}
		str++;
	}
	return;
	int len = strlen(str);
	char tmp;
	for(int i =0 ; i< len;i++)
	{
		for(int j =i+1; j < len ; j++)
		{
			if(str[i] > str[j])
			{
				tmp = str[j];
				str[j] = str[i];
				str[i] = tmp;
			}
		}
	}
}

bool CompareStr(char *str1,char *str2)
{
	char t1,t2;
	if(strlen(str1) != strlen(str2))
		return false;
	while((t1=*str1++) && (t2 = *str2++))
	{
		if(t1 != t2)
			return false;
	}
	return true;
}

void RoateMatrix90(int matrix[4][4],int n,bool print = false)
{
	if(n<1 || matrix == NULL)
		return;
	if(print)
	{
		for(int i = 0 ; i < n; i++)
		{
			for(int j = 0; j < n; j++)
				printf("%02d ",matrix[i][j]);
			printf("\r\n");
		}
		return;
	}
	
	int tmp = 0,t0,t1,t2,t3;
	int first= 0,last = 0,offset = 0;
	for(int nLayer = 0 ; nLayer < n/2;nLayer ++)
	{
		
		last = n - nLayer -1; //每层的个数
		first = nLayer;
		for(int i = first; i < last;i++)
		{
			offset = i - first;
			tmp = matrix[first][i];//(0,0)
			t0 = matrix[first][i] = matrix[first][last-offset];//(0,n)
			t1 = matrix[first][last-offset] = matrix[last-offset][last];
			t2 = matrix[last-offset][last] = matrix[i][last];
			//t3 = matrix[nlc][i] = tmp;
		}
	}
}
#include <hash_map>
#include <algorithm>
#include <list>
//A array
//B,begin of A
//E,end of A
int nReversionCount = 0;

int * MergeSort(int * A, int B,int E)
{
	return NULL;
}
void Partation(int * A, int B,int E)
{
	if(A == NULL || E <= B)
		return;
	
	if(E-B == 1)
	{
		if(A[B] > A[E])
		{
			nReversionCount++;
		}
		return;
	}
	int mid = (E - B )/ 2;

	Partation(A,B,mid);
	Partation(A,mid,E);
	

}
//void LowestAncestor(BTree
void Inversion(int * A, int n)
{
	Partation(A,0,n-1);
	
}

char * ReplaceSpace(char *str)
{
	if(str == NULL)
		return NULL;

	int len = 0;
	int spaceCount = 0;
	char *p = str;
	while (*p)
	{
		len++;
		if(*p == ' ')
			spaceCount++;
		p++;
	}
	int newLen =  len + spaceCount * 2;
	str[newLen] = '\0';
	for(int i = len-1; i >= 0; i--)
	{
		if(str[i] == ' ')
		{
			str[--newLen] = '0';
			str[--newLen] = '2';
			str[--newLen] = '%';
			//newLen = newLen -3;
		}else
		{
			str[--newLen] = str[i];
			
		}

	}
	return str;
	//char * newBuff = (char *)malloc(newLen + 1);
	//int i = 0;
	////
	//while (*str)
	//{
	//	if(*str == ' ')
	//	{
	//		newBuff[i++] = '%';
	//		newBuff[i++] = '2';
	//		newBuff[i++] = '0';
	//	}
	//	else
	//	{
	//		newBuff[i++] = *str;
	//		//newBuff++;
	//	}
	//	str++;

	//}
	//newBuff[newLen] = '\0';
	//return newBuff;
}

#include "DataStrcutures.h"
#include <algorithm>

void Shuffle(int *Cards, int nLen)
{
	if(Cards == NULL || nLen <= 0)
		return;
	for(int i=0;i<nLen;i+=2)
	{
		int nTIndex = rand() % nLen;
		int nTValue = Cards[i];
		Cards[i] = Cards[nTIndex];
		Cards[nTIndex] = nTValue;

	}
}
void ShuffleCard()
{
	int theCards[52];
	int nLen = sizeof(theCards)/sizeof(int);
	for(int I = 0 ; I < nLen; I++)
	{
		theCards[I] = I+1;
		printf("%d ",theCards[I]);
	}
	printf("\n");
	Shuffle (theCards,nLen);
	for(int I = 0 ; I < nLen; I++)
	{
		
		printf("%d ",theCards[I]);
	}
	printf("\n");

}

 void ReverseStr(char *begin,char * end)
{

	if(begin && end == NULL || end < begin)
		return;
	char tmp;
	

	while (begin < end)
	{
		tmp = *end;
		*end = *begin;
		*begin = tmp;
		++begin;
		--end;
	}
}

 void ReverseString(char *str)
 {
	 char *end = str;
	 while (*end)
		 end++;
	 ReverseStr(str,end-1);
	 char * p = str;
	 char * nb = p;
	 while (p != end+1)
	 {
		 if(*p == ' ' || *p == '\0')
		 {
			 ReverseStr(nb,p-1);
			 nb = p+1;
		 }
		 ++p;
	 }
 }

void sstrrev(char *p)
{
  char *q = p;
  while(q && *q) ++q;
  for(--q; p < q; ++p, --q)
    *p = *p ^ *q,
    *q = *p ^ *q,
    *p = *p ^ *q;
}

void myMemcpy(char* dst, const char* src, int nBytes)
{

	// Try to be fast and copy a word at a time instead of byte by byte
	//Should be sure the perimeters are valuable.  
	int* wordDst = (int*)dst;
	int* wordSrc = (int*)src;
	int numWords = nBytes / sizeof(int);
	for (int i=0; i<numWords; i++)
	{
		*wordDst++ = *wordSrc++;
	}

	int numRemaining = nBytes - (numWords*sizeof(int));
	dst = (char*)wordDst;
	src = (char*)wordSrc; 
	for (int i=0 ; i<= numRemaining; i++);
	{
		*dst++ = *src++;
	}
	*dst = '\0';
} 

size_t myHashFunb(const char *x,int len)
{
	const size_t _offset = 3121532313U;
	const size_t _prime = 13357733U;
	size_t _value = _offset;
	for(int i = 0 ;i < len; i++)
	{
		_value ^= (size_t)x[i];
		_value *= _prime;
	}
	return _value;
}
size_t myHash(int nvalue)
{
	return myHashFunb((const char*)&nvalue,sizeof(int));
}
size_t myHash(char *str)
{
  unsigned long __h = 0;
  for ( ; *str; ++str)
    __h = 5*__h + *str;

  return size_t(__h);
}
void printValue()
{
	for(int i = 1; i <= 9; i++)
	{
		for(int j = 1; j <= 9; j++)
		{
			if(i%3 != j%3)
				printf("A %d:B %d | ",i,j);

		}
		printf("\n");
	}
}

#include "HtSingleton.h"

int* FindMax(int *B,int *E)
{
	int *pMax = B;
	while( B++ != E)
		if(*pMax < *B)
			pMax = B;
	return pMax;
}

void ReverseInt(int *B,int *E)
{
	while(B < E)
	{
		int nTmp = *E;
		*E = *B;
		*B = nTmp;
		B++;E--;
	}
}
unsigned int fastcaclone(unsigned int val)
{
	unsigned int aNumbers[] = {9,99,999,9999,99999,999999,9999999,99999999,999999999};
	unsigned int aCounts[] = {1,20,300,4000,50000,600000,7000000,80000000,900000000};
	int pos = 0;
	bool bm = true;
	for(pos = 0 ; pos < sizeof(aNumbers)/sizeof(int);)
	{
		if(val <= aNumbers[pos])
		{
			bm = false;
			break;
		}
		else
			 pos++;
	}
	if(bm)
		pos--;
	unsigned int tval,ncount;
	unsigned int nNV = val - ( val < aNumbers[pos]? aNumbers[pos-1]:aNumbers[pos]);
	ncount = aCounts[val < aNumbers[pos]?pos-1:pos];
	if(nNV == 0)
		return aCounts[pos];
	//else if(nNV > 9)
	//{
	//	ncount += fastcaclone(nNV);
	//	return ncount;
	//}
	else
	{

		for(unsigned int i = val - nNV; i <= val;i++)
		{
			tval = i;
			while (tval > 0)
			{
				if(tval % 10 == 1)
					ncount++;
				tval/=10;
			}
		}
	}
	return ncount;

}

unsigned int caclone(unsigned int val)
{
	unsigned int tval,ncount = 1;
	if(val < 9)
		return ncount;

	for(unsigned int i = 10; i <= val;i++)
	{
		tval = i;
		while (tval > 0)
		{
			if(tval % 10 == 1)
				ncount++;
			tval/=10;
		}
	}
	return ncount;
}
#include <stdlib.h>

int _tmain(int argc, _TCHAR* argv[])
{
	//for (int i = 0;i<100; i++){  
 //       //这里用Sleep()来代替一些费时的操作，如读写文件，大量的运算。  
 //       Sleep(100); //some work to do  
 //       //输出百分比  
 //       printf("已经完成%d%%\r", i );  
 //   }
	int ale = 0x12345678;
	char * ble = (char*)&ale;
	int bltt = ale & 0xFFFF;
	TestSortBT();
	int A[] = {0,15,10,17,8,12,16,19,6,9,11,14,18,21,13};
	//{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37};
	int N = sizeof(A) / sizeof(int);
	bool bResult = false;
	for(int i = 0 ; i< N; i++)
	{
		bResult = IsPower2(A[i]);
		if(bResult)
			printf("%d是2的次方\n",A[i]);
	}
	//vector<int> heaptest(A,A+N);
	make_heap(A,A+N);
	push_heap(A,A+N);

	list<int> lt;
	lt.push_back(15);
	lt.push_back(5);
	lt.push_back(3);
	lt.push_back(11);
	lt.push_back(7);
	lt.push_back(4);
	lt.sort();
	int nP[] = {9,99,999,9999,99999,999999,9999999,99999999,999999999};
	unsigned int oc;
	oc = fastcaclone(9999999999);
	//hashtable<string,int,hash<string>,identity<string>,equal_to<string>> hasht(100,hash<string>(),equal_to<string>());
	for(int i = 0; i < sizeof(nP)/sizeof(int);i++)
	{
		oc = caclone(nP[i]);
		printf("%d : %d\n",nP[i],oc);
	}
	//HtSingleton<MyNewClass>::Instance()->Print ("Hello World");
	printValue();
	char buff[10];
	_itoa_s(-4130,buff,10);
	hash<char *> hashint;
	size_t st = hashint("hello");

	size_t st1 = myHash("hello");
	size_t st2 = myHash(102);
	size_t st3 = myHash(103);

	char astr[] = "hello the C++ world The name is your  fat";
	char *newc = new char[strlen(astr)];
	myMemcpy(newc,astr,strlen(astr));

	ReverseString(astr);
	//reverse(astr,astr+strlen(astr));
	//sstrrev(astr);
	ShuffleCard();

	for(int i = 0 ; i < N;i++)
	{
		int *pMax = FindMax(A,A+N-i-1);
		ReverseInt(A,pMax);
		ReverseInt(A,A+N-1-i);
		//pMax = FindMax(A,A+N-i-2);
	}
	vector<int> myIntV;
	for(int i = 0 ; i < N;i++)
		myIntV.push_back(A[i]);
	
	reverse(myIntV.begin(),myIntV.end());
	vector<int>::iterator iti = myIntV.begin();
		
	for(iti = myIntV.begin();iti != myIntV.end(); )
	{
		if(*iti %2 == 0)
		{
			iti = myIntV.erase(iti);
			if(iti == myIntV.end())
				break;
		}
		else
			iti++;
	}
	
		const int ncount = 4;
	int matrix[ncount][ncount] = {{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
	RoateMatrix90(matrix,ncount,true);
	RoateMatrix90(matrix,ncount);
	RoateMatrix90(matrix,ncount,true);

		char str[] ="cccfaadcecaadagsdfwe3rwrfasdfasdgbasdfgasgaskdjfkljweriwu4293458902riasdfklbnjasdfhsklfhwioyhowiytoweuaejfrlasjhnalkbhasjdfkljaseriwo4t990345u234oj3ija;jkdfkjslf";
	char str2[] ="ae cfa dcc aad";	
	char * newBuff = ReplaceSpace(str2);
	//free(newBuff);
	SortStr(str,str+strlen(str));
	//SortStr(str);

	RemoveDuplicate(str);

	CBSTree<int> *pBST = new CBSTree<int>();

	list<int> l;
	
	

	random_shuffle(A,A+N);

	for(int i= 0 ;i < N ; i++)
		pBST->InsertNode(A[i]);

	pBST->Printf(false,1);
	pBST->Printf(false,2);
	pBST->Printf(false,3);
	delete pBST;
	Inversion(A,N);
	printf("Reversion count is %d",nReversionCount);
	

	vector<int> v;
	int t = 0,nt=0;
	for(int i = 0; i< N; i++)
		v.push_back(A[i]);
	for(int i = 0; i< N; i++)
	{
		
		nt = rand()%N;
		l.push_back(nt);
		t = A[i];
		A[i] = A[nt];
		A[nt] = t;
	}
	for(int i = 0;i < N; i++)
		printf("%d,",A[i]);
	printf("\n");
	
	make_heap(A,A+N);

	sort_heap(A,A+N);
	//qsort(A,);
	
	for(int i = 0;i < N; i++)
		printf("%d,",A[i]);
	//l.reverse();
	l.sort();
	std::hash_map<int,int> stlhash;
	for(int i = 0; i< 10; i++)
	{
		stlhash[i] = i*rand();
		printf("key=%d,value=%d\r\n",i,stlhash[i]);
		
	}
	
	
	func(5,8);

	SortStrt(str);
	bool be = CompareStr(str,str2);
	SortStrt(str2);
	be = CompareStr(str,str2);
	
	char * newstr = ReverseStr(str);
	drawEighthOfCircle(10);
	 F(30);
	 testF(30);
	int nTest = 10;
	//char str[] = "abcd";
	Mernupation(str,0,3);
	LinkedListTest();
	

	
	bool bR = IsPower2(10);
	bR = IsPower2(102400000);
	int np = add(15,-5);
	int nR = divideby3(nTest);
	int nV = nR << 1;
	nV = nV >> 1;
	//LevelPrintBST();
	RotaedArrayFindKey();
	

	
	return 0;
}

