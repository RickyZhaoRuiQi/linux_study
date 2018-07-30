#ifndef MYUNIQUE_H
#define MYUNIQUE_H

#include<vector>
typedef vector<int>::iterator iterator

iterator my_unique(iterator start,iterator end)
{
	if(start==end)
	  return end;

	iterator result;
	while(++start != end)
	{
		if(*result != *start)
		  *(++result) = *start;
	}
	return ++result;
}
