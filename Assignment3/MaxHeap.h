// Assignment: ASU CSE310 HW#3 Spring 2024
// Your Name:   David Janda
// ASU ID:  1225300869
// ASU Email address:   djanda2@asu.edu
// Description:
//********************************************************
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Each Car will have a unique Vin
struct Car
{
	string model, make;
	int vin;        //Vehicle Identification Number
	double price;
};

//class MaxHeap represents a max heap that contains Car objects. The underline data structure
//is a one dimensional array of Cars.
class MaxHeap
{
    private:
    struct Car* carArr;	//an array of Cars
	struct Car* newCarArr; //array to allocate more memory if needed
    int capacity, size;

	public:
    MaxHeap(int capacity);  //
    ~MaxHeap();     //

	Car* getCarArr();	//
	int getSize();	//
	int getCapacity();	//
	int isFound(int aVin);	//
	bool heapIncreaseVIN(int index, Car oneCarWithNewVIN);	//
	bool heapInsert(int vin, string model, string make, double price);	//
	void heapify(int index);	//
	Car getHeapMax();		//
	void extractHeapMax();	//
	int leftChild(int parentIndex);	//
	int rightChild(int parentIndex);	//
	int parent(int childIndex);	//
	void printHeap();
};

//Constructor to dynamically allocate memory for a heap with the specified capacity
MaxHeap::MaxHeap(int capacity)
{
 	carArr = new Car[capacity];
    size = 0;
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the heap.
//and prints the number of nodes deleted by it.
MaxHeap::~MaxHeap()
{
	//Add your own code
	int carCount = size;
    delete[] carArr;
	carArr = nullptr;
	size = 0;
	cout << "\nThe number of deleted cars is: " << carCount << endl;
}

//****************************************************
//increase the Car's VIN located at the specific index
bool MaxHeap::heapIncreaseVIN(int index, Car oneCarWithNewVIN)
{
	if (index > size)
    {
        cout << "\nIncrease VIN error: index out of range" << endl;
        return false;
    }
    carArr[index] = oneCarWithNewVIN;
	Car temp;
	while(index > 1 && carArr[parent(index)].vin < carArr[index].vin)	//if parent is less than child exchange them
	{
		temp = carArr[index];
		carArr[index] = carArr[parent(index)];
		carArr[parent(index)] = temp;
		index = parent(index);
	}
	return true;
}

bool MaxHeap::heapInsert(int vin, string model, string make, double price)
{
	if(isFound(vin))
		return false;

	if(size == capacity)		//if capacity is reached
	{
		capacity *= 2;
		newCarArr = new Car[capacity];		//create new array with double the memory and then transfer items to new array
		for(int i = 0; i < size; i++)	
		{
			newCarArr[i] = carArr[i];
		}
		carArr = newCarArr;		//point carArr to new array with more memory
	}
	Car temp;	//make new car and put it at the end of the array then float it up
	temp.vin = vin;
	temp.model = model;
	temp.make = make;
	temp.price = price;
	heapIncreaseVIN(size, temp);		//call increase vin to float up new car
	size++;		//increase size and return true once complete
	return true;
}

int MaxHeap::parent(int childIndex)		//returns index of parent
{
	return (childIndex - 1) / 2;
}

int MaxHeap::leftChild(int parentIndex)		//returns index of left child
{
	return parentIndex * 2 + 1; 
}

int MaxHeap::rightChild(int parentIndex)		//returns index of right child
{
	return parentIndex * 2 + 2;
}

void MaxHeap::heapify(int index)
{
	int l = leftChild(index);
	int r = rightChild(index);
	int largest;
	Car temp;
	if(l < size && carArr[l].vin > carArr[index].vin)	//make sure l is within bounds and if it has a greater vin then largest will be left child else keep largest as parent and compare with right
		largest = l;
	else
		largest = index;
	if(r < size && carArr[r].vin > carArr[largest].vin)
		largest = r;
	if(largest != index)		//if index is not largest then exchannge index with largest and call heapify again to continue to float up the node
	{
		temp = carArr[index];
		carArr[index] = carArr[largest];
		carArr[largest] = temp;
		heapify(largest);
	}
}

int MaxHeap::getCapacity()
{
	return capacity;
}

int MaxHeap::getSize()
{
	return size;
}

Car* MaxHeap::getCarArr()
{
	return carArr;
}

int MaxHeap::isFound(int aVin)
{
	for(int i = 0; i < size; i++)		//traverse array and check each array return index if vin is found
	{
		if(carArr[i].vin == aVin)
			return i;
	}
	return -1;
}

Car MaxHeap::getHeapMax()
{
	return carArr[0];
}

void MaxHeap::extractHeapMax()
{
	if(size == 0)
		return;
	carArr[0] = carArr[size - 1];	//set last node to new root then call heapify to float down node when needed
	heapify(0);
}

void MaxHeap::printHeap()
{
	if(size == 0)	//if heap is empty
	{
		cout << "Empty heap, no elements\n";
		return;
	}

	cout << "Heap capacity = " << capacity << endl;
	cout << "Heap size = " << size << endl;

	for(int i = 0; i < size; i++)
	{
		cout << left;
		cout << setw(8) << carArr[i].vin
     	<< setw(12) << carArr[i].model
     	<< setw(12) << carArr[i].make
     	<< setw(8) << fixed << setprecision(2) << carArr[i].price << endl;
	}
	
}

