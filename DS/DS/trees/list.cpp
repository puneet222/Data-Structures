#include<iostream>
using namespace std ;

int arr[200] ;

void insert(int num , int &end)
{
	end = end + 1 ;
	arr[end] = num ;
}

void insert(int num , int loc , int &end)
{
	loc = loc - 1 ;
	for(int i = end ; i >= loc ; i--)
	{
		arr[i+1] = arr[i] ;
	}
	arr[loc] = num ;
	end  = end + 1 ;
}

void remove(int loc , int &end)
{
	loc = loc - 1 ;
	for(int i = loc ; i <= end ; i++)
	{
		arr[i] = arr[i+1];
	}
	end = end - 1 ;
}

int main()
{
	
	int end = -1  , a , n , loc , loop = 1;

	while(loop)
	{
		cout << "press 1 to insert element at the end\n";
		cout << "press 2 to insert at given location\n";
		cout << "press 3 to remove the element\n";
		cout << "press 4 to see the number of elements \n";
		cout << "press 5 to read a specific element\n" ;
		cout << "press 6 to modify the element at a location\n" ;
		cout << "press 7 to count a specific element in the list\n";
		cout << "press 8 to print the list\n" ;
		cout << "press 9 to exit the application\n" ;
		cout << "press the button ------->   " ;
		cin >> a ;



		switch(a)
		{
			case 1:
			{
				cout << "enter the number : " ;
				cin >> n ;
				insert(n,end);
				break ;
			}

			case 2:
			{
			cout << "enter the number and the location : " ;
			cin >> n >> loc;
			insert(n,loc,end);
			break ;
			}

			case 3:
			{
				cout << "enter the location : " ;
				cin >> loc ;
				remove(loc , end) ;
				break ;
			}

			case 4 :
			{
				cout << "number of elements in the list are : " << end + 1 << endl ;
				break ;
			}

			case 5:
			{
				cout << "enter the location which you want to read : " ;
				cin >> loc ;
				cout << "element at position " << loc << " is : " << arr[loc-1] << endl ;
				break ;
			}

			case 6 :
			{
				cout << "enter the location at which you want to modify the element : " ;
				cin >> loc ;
				cout << "element at location " << loc << " is : " << arr[loc-1] << endl ;
				cout << "enter the new element : " ;
				cin >> n ;
				arr[loc-1]  = n ;
				break ;
			}

			case 7 :
			{
				cout << "enter the element which you want to count : " ;
				cin >> n ;
				int count = 0 ;
				for(int i = 0 ; i <= end ; i++)
				{
					if(arr[i] == n)
						count++ ;
				}
				cout << "number of occurrences of " << n << " is : " << count << endl ;
				break ;
			}

			case 8 : 
			{
				for(int i = 0 ; i <= end ; i++)
					cout << arr[i] << "    " ;

				cout << endl ;
				break;
			}

			case 9 :
			{
				loop = 0 ;
			}
		}
	}

}



