#include "stdafx.h"
#include "DataStrcutures.h"

void HtDList::Test()
{
	HtDList dl;
	for(int i = 0; i < 5; i++)
		dl.AddNode(i+100);
	int i = 0;
	HtDListNode *prev = NULL;
	HtDListNode *it = dl.GetBegin();
	while (it)
	{
		HtDListNode *t = it;
		printf("%d:%d",++i,it->GetValue());
		it = it->GetNext(prev);
		prev = t;
	}

}