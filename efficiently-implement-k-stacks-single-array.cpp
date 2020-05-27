// A C++ program to demonstrate implementation of k stacks in a single 
// array in time and space efficient way 
#include <stdlib.h> 
#include <iostream>

using namespace std; 

// A C++ class to represent k stacks in a single array of size n 
class kStacks 
{ 
	int *arr; // Array of size n to store actual content to be stored in stacks 
	int *top; // Array of size k to store indexes of top elements of stacks 
	int *next; // Array of size n to store next entry in all stacks 
				// and free list 
	int n, k; 
	int free; // To store beginning index of free list 
public: 
	//constructor to create k stacks in an array of size n 
	kStacks(int k, int n); 

	// A utility function to check if there is space available 
	bool isFull() { return (free == -1); } 

	// To push an item in stack number 'sn' where sn is from 0 to k-1 
	void push(int item, int sn); 

	// To pop an from stack number 'sn' where sn is from 0 to k-1 
	int pop(int sn); 

	// To check whether stack number 'sn' is empty or not 
	bool isEmpty(int sn) { return (top[sn] == -1); } 
}; 

//在一个长度为n的数组中构造k个栈 
kStacks::kStacks(int k1, int n1) 
{ 
	// 初始化 n 和 k, 给所有的数组分配内存
	k = k1, n = n1; 
	arr = new int[n]; 
	top = new int[k]; 
	next = new int[n]; 

	// 初始化所有的栈为空
	for (int i = 0; i < k; i++) 
		top[i] = -1; 

	// 初始化所有的空间为free
	free = 0; 
	for (int i=0; i<n-1; i++) 
		next[i] = i+1; 
	next[n-1] = -1; // -1 负责标记列表的表尾
} 

// sn的范围为0到k-1，在栈的下标数字“sn” 中压入项目 
void kStacks::push(int item, int sn) 
{ 
	// Overflow check 
	if (isFull()) 
	{ 
		cout << "\nStack Overflow\n"; 
		return; 
	} 

	int i = free;	 // Store index of first free slot 

	// Update index of free slot to index of next slot in free list 
	free = next[i]; 

	// Update next of top and then top for stack number 'sn' 
	next[i] = top[sn]; 
	top[sn] = i; 

	// Put the item in array 
	arr[i] = item; 
} 

// To pop an from stack number 'sn' where sn is from 0 to k-1 
int kStacks::pop(int sn) 
{ 
	// Underflow check 
	if (isEmpty(sn)) 
	{ 
		cout << "\nStack Underflow\n"; 
		return INT_MAX; 
	} 


	// Find index of top item in stack number 'sn' 
	int i = top[sn]; 

	top[sn] = next[i]; // Change top to store next of previous top 

	// Attach the previous top to the beginning of free list 
	next[i] = free; 
	free = i; 

	// Return the previous top item 
	return arr[i]; 
} 

/* Driver program to test twStacks class */
int main() 
{ 
	// Let us create 3 stacks in an array of size 10 
	int k = 3, n = 10; 
	kStacks ks(k, n); 

	// Let us put some items in stack number 2 
	ks.push(15, 2); 
	ks.push(45, 2); 

	// Let us put some items in stack number 1 
	ks.push(17, 1); 
	ks.push(49, 1); 
	ks.push(39, 1); 

	// Let us put some items in stack number 0 
	ks.push(11, 0); 
	ks.push(9, 0); 
	ks.push(7, 0); 

	cout << "Popped element from stack 2 is " << ks.pop(2) << endl; 
	cout << "Popped element from stack 1 is " << ks.pop(1) << endl; 
	cout << "Popped element from stack 0 is " << ks.pop(0) << endl; 

	return 0; 
} 
