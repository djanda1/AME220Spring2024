// Assignment: ASU CSE310 HW#3 Spring 2024
// Name:    David Janda
// ASU ID: 1225300869
// ASU Email Address:   djanda2@asu.edu
// Description: This program displays a menu of choices to a user
//              and performs the chosen task. It will keep asking a user to
//              enter the next choice until the choice of 'Q' (Quit) is entered.
//             	//---- is where you should add your own code
//********************************************************************************

//only include the necessary header file
//----

using namespace std;
#include <string>
void printMenu();
void heapSort(MaxHeap* oneMaxHeap);
int main()
{
	char input1 = 'Z';
	int vin, newVIN;
	string model, make;
    double price;
	int capacity, result, index = -1;   //array capacity and index
	bool success = false;

    Car oneCar;

	// instantiate an empty Heap
	MaxHeap* heap1 = nullptr;
	printMenu();

	do {
		cout << "\nWhat action would you like to perform?" << endl;
		cin.get(input1);
		input1 = toupper(input1);
		cin.ignore(20, '\n');	//flush the buffer

		// matches one of the cases
		switch (input1)
		{
			case 'C':	//create empty Heap with the relevant capacity
				cout << "\nPlease enter the heap capacity: ";
				cin >> capacity;
				cin.ignore(20, '\n');	//flush the buffer

				heap1 = new MaxHeap(capacity);	//create heap

				break;

			case 'D':	//delete the heap, call the destructor explicitly
				cout << "\nDelete the heap" << endl;
				delete heap1;
				heap1 = MaxHeap(5);
				break;

			case 'E':	//Extract the maximum node
                if (heap1 == nullptr)
                    cout << "\nEmpty heap, can NOT extract max" << endl;
                else
                {
                    cout << "\nBefore extract heap max operation:\n";
					heap1.printHeap();

					heap1.extractHeapMax();
					cout << "\nAfter extract heap max operation:\n";
					heap1.printHeap();
                }
				break;

			case 'F':	//Find a Car
				cout << "\nEnter the car VIN you want to search: ";
				cin >> vin;
				cin.ignore(20, '\n');	//flush the buffer

				result = heap1.isFound(vin);
				if(result >= 0)
					cout << "\nCar with VIN: " << vin << " is found\n";
				else
					cout << "\nCar with VIN: " << vin << " is NOT found\n";
				break;

			case 'I':	//Insert a Car
				cout << "\nEnter the car model: ";
				cin >> model;

				cout << "\nEnter the car make: ";
				cin >> make;

				cout << "\nEnter the car VIN: ";
				cin >> vin;
				cout << "\nEnter the car price: ";
				cin >> price;
				cin.ignore(20, '\n');	//flush the buffer

				success = heap1.heapInsert(vin, model, make, price);
				if(success)
				{
					cout << "\nCar \"" << model << " " << make << "\" is added\n";
				}
				else
					cout << "\nCar \"" << model << " " << make << "\" is NOT added\n";
				break;

			case 'K':	//increase the vin
				cout << "\nEnter the old car VIN you want to increase: ";
				cin >> vin;
				cout << "\nEnter the new car VIN: ";
				cin >> newVIN;
				cin.ignore(20, '\n');	//flush the buffer

				if(newVIN < vin)
				{
					cout << "\nIncrease VIN error: new vin is smaller than current vin\n";
					break;
				}

				index = heap1.isFound(vin);
				if(index == -1)
				{
					cout << "\nThe old VIN you try to increase does not exist\n";
					break;
				}

				result = heap1.isFound(newVIN);
				if(result >= 0)
				{
					cout << "\nThe new VIN you entered already exist, increase VIN operation failed\n";
					break;
				}
				cout << "\nBefore increase VIN operation:\n"
				heap1.printHeap();
				success = heap1.heapIncreaseVIN(index, newVIN);
				if(!success)
					break;
				cout << "\nCar with old VIN: " << vin << " is increased to new VIN: \n" << newVIN << endl;
				cout << "After increase VIN operation:\n"
				heap1.printHeap();
				
				break;

			case 'M':	//get maximum node

				if(heap1.getSize() == 0)
				{
					cout << "\nEmpty heap, can NOT get max node\n";
					break;
				}
			    oneCar = heap1.getHeapMax();
				cout << "\nThe maximum heap node is:\n";
				cout << left;
					cout << setw(8) << oneCar.vin
     				<< setw(12) << oneCar.model
     				<< setw(12) << oneCar.make
     				<< setw(8) << fixed << setprecision(2) << oneCar.price << endl;

				break;

			case 'P':	//Print heap contents

			    heap1.printHeap();	//call print function

				break;

			case 'S':	//HeapSort
				cout << "\nHeap sort. Cars will be sorted in increasing order of their VINs" << endl;
				heapSort(heap1);
				heap1.printHeap();
				break;

			case 'Q':	//Quit
				delete heap1;
				break;

			case '?':	//Display Menu
				printMenu();
				break;

			default:
				cout << "Unknown action\n";
				break;
		}
	} while (input1 != 'Q');
	return 0;
}

//*****************************************************
//Given a max heap, we want to sort it in increasing order according to Car VIN, put the
//sorting result inside another array and print it out
void heapSort(MaxHeap* oneMaxHeap)
{
	Car temp;
	for(int i = heap1.getSize(); i > 1; i--)
	{
		temp = heap1.getCarArr()[i];
		heap1.getCarrArr()[i] = heap1.getCarArr()[1];
		heap1.getCarArr()[1] = temp;
		heap1.heapify(1);	
	}
}

//**The function displays the menu to a user**
void printMenu()
{
	cout << "Choice\t\tAction\n";
	cout << "------\t\t------\n";
	cout << "C\t\tCreate a heap\n";
	cout << "D\t\tDelete the heap\n";
	cout << "E\t\tExtract max node\n";
	cout << "F\t\tFind a Car by VIN\n";
	cout << "I\t\tInsert a Car\n";
	cout << "K\t\tIncrease the VIN\n";
	cout << "M\t\tGet the max node\n";
	cout << "P\t\tPrint the heap\n";
	cout << "S\t\tHeap Sort\n";
	cout << "Q\t\tQuit\n";
	cout << "?\t\tDisplay Help\n\n";
}