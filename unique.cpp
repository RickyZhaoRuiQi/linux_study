#include <vector>
#include <iostream>
using namespace std;

typedef vector<int>::iterator itera;
itera my_unique(itera start,itera end)
{
	if(start == end)
	  return end;

	itera result = start;
	while(++start != end)
	{
		if(*result != *start)
		  *(++result) = *start;
	}
	return ++result;
}

int main()
{
	int arr[] = {1,2,2,2,3};
	vector<int> vec(arr,arr+5);
	itera it = my_unique(vec.begin(),vec.end());
	vec.erase(it,vec.end());
	it = vec.begin();
	while(it != vec.end())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
	return 0;
}
