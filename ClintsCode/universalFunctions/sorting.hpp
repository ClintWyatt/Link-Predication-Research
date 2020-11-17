#ifndef SORTING_HPP
#define SORTING_HPP
using namespace std;


const int_string & median3(vector<int_string> & a, int left, int right)
{
	 int center = (left + right) / 2;
	
		 if (a[center].first < a[left].first)
		    swap(a[left], a[center]);
	 if (a[right].first < a[left].first)
		    swap(a[left], a[right]);
	 if (a[right].first < a[center].first)
		    swap(a[center], a[right]);
	
		 // Place pivot at position right - 1
		 swap(a[center], a[right - 1]);
	 return a[right - 1];
}


void insertionsort(vector<int_string> & a, int left, int right)
{
	//insertion sort is slightly different than the normal insertionsort. p = left is the main difference
	//as well as the right +1

	int j;
	for (int p = left; p < right+1; p++) //right +1 needed for the larger part since the inital right is the last index
	{
		float tmp = a[p].first;
		string str = a[p].second;
		for (j = p; j > left && tmp < a[j - 1].first; j--)
		{
			a[j] = a[j - 1];
		}
		a[j].first = tmp;
		a[j].second = str;
	}
}

//quicksort algorithm for int_strings 
void quicksort(vector<int_string> & a, int left, int right)
{
	if (left + 10 <= right)
	{
		int_string pivot = median3(a, left, right);
		int center = (left + right) / 2;
		// Begin partitioning
		int i = left, j = right - 1;
		for (; ; )
		{
			while (a[++i].first < pivot.first) {} //will go to the right until it is greater than the pivot
				while (pivot.first < a[--j].first) {}//while the pivot is less than the right
					if (i < j)//if the left index is greater than the right index
						swap(a[i], a[j]);
					else
						break;
		}
		
		swap(a[i], a[right - 1]);// Restore pivot
		
		quicksort(a, left, i - 1); // Sort small elements
		quicksort(a, i + 1, right); // Sort large elements. i + 1 is used since the smaller 2 elements are always on the left of the large partition
	}
	else // Do an insertion sort on the subarray
	    insertionsort(a, left, right);
}


/*quicksort algorithm
Although we are using a template, only use the pair vectors for quicksort (int_string, double_string, int_double, etc). Will not work for a single data type
*/
const double_string & median3(vector<double_string> & a, int left, int right)
{
	 int center = (left + right) / 2;
	
		 if (a[center].first < a[left].first)
		    swap(a[left], a[center]);
	 if (a[right].first < a[left].first)
		    swap(a[left], a[right]);
	 if (a[right].first < a[center].first)
		    swap(a[center], a[right]);
	
		 // Place pivot at position right - 1
		 swap(a[center], a[right - 1]);
	 return a[right - 1];
}


void insertionsort(vector<double_string> & a, int left, int right)
{
	//insertion sort is slightly different than the normal insertionsort. p = left is the main difference
	//as well as the right +1

	int j;
	for (int p = left; p < right+1; p++) //right +1 needed for the larger part since the inital right is the last index
	{
		float tmp = a[p].first;
		string str = a[p].second;
		for (j = p; j > left && tmp < a[j - 1].first; j--)
		{
			a[j] = a[j - 1];
		}
		a[j].first = tmp;
		a[j].second = str;
	}
}

void quicksort(vector<double_string> & a, int left, int right)
{
	if (left + 10 <= right)
	{
		double_string pivot = median3(a, left, right);
		int center = (left + right) / 2;
		// Begin partitioning
		int i = left, j = right - 1;
		for (; ; )
		{
			while (a[++i].first < pivot.first) {} //will go to the right until it is greater than the pivot
				while (pivot.first < a[--j].first) {}//while the pivot is less than the right
					if (i < j)//if the left index is greater than the right index
						swap(a[i], a[j]);
					else
						break;
		}
		
		swap(a[i], a[right - 1]);// Restore pivot
		
		quicksort(a, left, i - 1); // Sort small elements
		quicksort(a, i + 1, right); // Sort large elements. i + 1 is used since the smaller 2 elements are always on the left of the large partition
	}
	else // Do an insertion sort on the subarray
	    insertionsort(a, left, right);
}


const int_double & median3(vector<int_double> & a, int left, int right)
{
	 int center = (left + right) / 2;
	
		 if (a[center].first < a[left].first)
		    swap(a[left], a[center]);
	 if (a[right].first < a[left].first)
		    swap(a[left], a[right]);
	 if (a[right].first < a[center].first)
		    swap(a[center], a[right]);
	
		 // Place pivot at position right - 1
		 swap(a[center], a[right - 1]);
	 return a[right - 1];
}


void insertionsort(vector<int_double> & a, int left, int right)
{
	//insertion sort is slightly different than the normal insertionsort. p = left is the main difference
	//as well as the right +1

	int j;
	for (int p = left; p < right+1; p++) //right +1 needed for the larger part since the inital right is the last index
	{
		float tmp = a[p].first;
		float str = a[p].second;
		for (j = p; j > left && tmp < a[j - 1].first; j--)
		{
			a[j] = a[j - 1];
		}
		a[j].first = tmp;
		a[j].second = str;
	}
}

//used to sort each row of a network

void quicksort(vector<int_double> & a, int left, int right)
{
	if (left + 10 <= right)
	{
		int_double pivot = median3(a, left, right);
		int center = (left + right) / 2;
		// Begin partitioning
		int i = left, j = right - 1;
		for (; ; )
		{
			while (a[++i].first < pivot.first) {} //will go to the right until it is greater than the pivot
				while (pivot.first < a[--j].first) {}//while the pivot is less than the right
					if (i < j)//if the left index is greater than the right index
						swap(a[i], a[j]);
					else
						break;
		}
		
		swap(a[i], a[right - 1]);// Restore pivot
		
		quicksort(a, left, i - 1); // Sort small elements
		quicksort(a, i + 1, right); // Sort large elements. i + 1 is used since the smaller 2 elements are always on the left of the large partition
	}
	else // Do an insertion sort on the subarray
	    insertionsort(a, left, right);
}
/*quicksort algorithm end */

#endif