//Diana Lin
//260625972
#include <iostream>
using namespace std;

//Question 1
class Node {
public:
	int data;
	Node* next;
	Node* previous;
	Node() {
		//set all as "default values" as no input was given
		this->data = 0;
		this->next = NULL;
		this->previous = NULL;
	}
	Node(int data, Node* next, Node* previous) {
		this->data = data;
		this->next = next;
		this->previous = previous;
	}
	~Node() {
		delete next;
		delete previous;
	}

};

//Question 2
class DLLStructure {
private:
	Node* first;
	Node* last;
	bool isSorted;
public:

	DLLStructure() {
		//default NULL nodes as no input was given
		this->first = NULL;
		this->last = NULL;
		this->isSorted = false;
	}
	DLLStructure(int array[], int size) {
		if (size > 0) {
			this->first = new Node(array[0], NULL, NULL);
			this->last = this->first;
			for(int i=1; i<size; i++) {
				//assign current last node pointer's next member to new Node
				this->last->next = new Node(array[i],NULL,this->last);
				this->last = this->last->next;
			}
			this->isSorted = false;
		} else {
			this->first = NULL;
			this->isSorted = false;
		}
	}
	~DLLStructure() {
		//iterate through linked list and delete each node
		while (this->last != this->first) {
			this->last = this->last->previous;
			delete this->last->next;
		}
		delete this->first;
	}
	void PrintDLL();
	void InsertAfter(int valueToInsertAfter, int valueToBeInserted);
	void InsertBefore(int valueToInsertBefore, int valueToBeInserted);
	void Delete(int value);
	void Sort();
	bool IsEmpty();
	int GetHead();
	int GetTail();
	int GetSize();
	int GetMax();
	int GetMin();
	DLLStructure(DLLStructure& dlls);
	void Swap(Node* x){
		//swaps two ADJACENT nodes (used for bubble sorting!)
		Node* y = x->next;
		if (x->previous != NULL) {
			x->previous->next = y;
		} else {
			this->first = y;
		}
		if (y->next != NULL) {
			y->next->previous = x;
		} else {
			this->last = x;
		}
		y->previous = x->previous;
		x->previous = y;
		x->next = y->next;
		y->next = x;


	}

};

//Question 3
void DLLStructure::PrintDLL() {
	if (this->IsEmpty() == false) {
		Node* i = this->first;
		//iterate through DLL until i is NULL.
		while (i != NULL) {
			if (i->next == NULL) {
				cout << i->data << endl;
			}
			else {
				cout << i->data << ", ";
			}
			i = i->next;
		}
	} else {
		cout << "The DLL is empty and could not be printed!" << endl;
	}
}

//Question 4
void DLLStructure::InsertAfter(int valueToInsertAfter, int valueToBeInserted) {
	//iterate through the list to find valueToInsertAfter
	//if valueToInsertAfter is not found, than nothing is inserted.
	if (this->IsEmpty() == false) {
		Node* i = this->first;
		while (i != NULL) {
			if(i->data == valueToInsertAfter) {
				if (i->data == this->last->data) {
					i->next = new Node(valueToBeInserted, NULL, i);
					this->last = i->next;
				} else {
					i->next->previous = new Node(valueToBeInserted,i->next,i);
					i->next = i->next->previous;
				}
				break;
			}
			i = i->next;
		}
	} else {
		cout << "The DLL is empty so insertion cannot occur." << endl;
	}
}

//Question 5
void DLLStructure::InsertBefore(int valueToInsertBefore, int valueToBeInserted) {
	//calls InsertAfter, and just uses previous Node data as input for the method
	if (this->IsEmpty() == false) {
		Node* i = this->first;
		while (i != NULL) {
			if (i->data == valueToInsertBefore) {
				if (i->data == this->first->data) {
					i->previous = new Node(valueToBeInserted,i, NULL);
					this->first = i->previous;
				} else {
					this->InsertAfter(i->previous->data, valueToBeInserted);
				}
				break;
			}
			i = i->next;
		}
	}
}

//Question 6
void DLLStructure::Delete(int value) {
	if (this->IsEmpty() == false) {
		//deletes all connections of a node to other nodes,
		//and then delete the actual node.
		Node* i = this->first;
		while(i != NULL) {
			if (i->data == value) {
				if (i->data == this->first->data) {
					this->first = i->next;
					i->next->previous = NULL;
					i->next = NULL;
					i->previous = NULL;
					i->~Node();
				} else if (i->data == this->last->data) {
					this->last = i->previous;
					i->previous->next = NULL;
					i->next = NULL;
					i->previous = NULL;
					i->~Node();
				} else {
					i->next->previous = i->previous;
					i->previous->next = i->next;
					i->next = NULL;
					i->previous = NULL;
					i->~Node();
				}
				break;
			}
			i = i->next;
		}
	} else {
		cout << "The DLL is empty so nodes cannot be deleted." << endl;
	}
}

//Question 7
void DLLStructure::Sort() {
	if (this->IsEmpty() == false) {
		//sort using Bubble sort
		Node* i = this->first;
		while(true) {
			int count = 0;
			while (i != NULL && i->next != NULL) {
				if(i->data > i->next->data) {
					this->Swap(i);
					//this swap method advances i (has an equivalent of an i = i->next, so it is not required in this scope
					count++;
				}
				else {
					i = i->next;
				}
			}
			if(count == 0) {
				//if an entire round has elapsed and no swaps have been made, it is already in order
				break;
			}
			else {
				i = this->first;
			}
			this->isSorted = true;
		}
	} else {
		cout << "The DLL is empty and could not be sorted." << endl;
	}
}

//Question 8
bool DLLStructure::IsEmpty() {
	//if Size is 0, then DLL is empty.
	if(this->GetSize() == 0) {
		return true;
	} else {
		return false;
	}
}

//Question 9
int DLLStructure::GetHead() {
	//retrieves private member first
	if (this->IsEmpty() == false) {
		return this->first->data;
	} else {
		cout << "The head could not be retrieved as the DLL is empty." << endl;
		return 0;
	}
}
int DLLStructure::GetTail() {
	//retrieves private member last
	if (this->IsEmpty() == false) {
		return this->last->data;
	} else {
		cout << "The tail could not be retrieved as the DLL is empty." << endl;
		return 0;
	}
}

//Question 10
int DLLStructure::GetSize() {
	//if the DLL is empty, then it returns 0
	int count = 0;
		Node* i = this->first; //this->first will be null if the size is not greater than 0
		while (i != NULL) {
			count++;
			i = i->next;
		}
	return count;
}

//Question 11
int DLLStructure::GetMax() {
	//max will be the tail if the DLL is sorted, but check for sorting so doesn't attempt to sort every time
	//reduces the number of loops/iterating through the DLL
	if(this->GetSize() > 0) {
		if (this->isSorted == false) {
			this->Sort();
		}
		return this->last->data;
	} else {
		cout << "The maximum could not be found as the DLL is empty." << endl;
		return 0;
	}
}

int DLLStructure::GetMin() {
	//min will be the tail if the DLL is sorted, but check for sorting so doesn't attempt to sort every time
	//reduces the number of loops/iterating through the DLL
	if (this->GetSize() > 0) {
		if (this->isSorted == false) {
			this->Sort();
		}
		return this->first->data;
	} else {
		cout << "The minimum could not be found as the DLL is empty." << endl;
		return 0;
	}
}

//Question 12
DLLStructure::DLLStructure(DLLStructure& dlls) {
	//very similar to DLLStructure(array, size);
	//instead of iterating through the array, I iterate through the dlls nodes
	if (dlls.GetSize() > 0) {
		this->first = new Node(dlls.first->data, NULL, NULL);
		this->last = this->first;
		Node* i = dlls.first->next;
		while (i !=NULL) {
			//assign current last node pointer's next member to new Node
			this->last->next = new Node(i->data,NULL,this->last);
			this->last = this->last->next;
			i = i->next;
		}
	} else {
		this->first = NULL;
	}
	this->isSorted = dlls.isSorted;
}

//TESTING ALL METHODS
int main() {

//	testing
	int array[5] = {11, 2, 7, 22, 4};
	DLLStructure dll(array,5);
//	int array[0] = {};
//	DLLStructure dll(array,0);
	cout << "Original: ";
	dll.PrintDLL();

	//testing InsertAfter
	int insertValA = 13;
	int insertPtA = 7;
	dll.InsertAfter(insertPtA,insertValA);
	cout << "Insert "<< insertValA << " After " << insertPtA << ": ";
	dll.PrintDLL();

	//testing InsertBefore
	int insertValB = 26;
	int insertPtB = 7;
	dll.InsertBefore(insertPtB,insertValB);
	cout << "Insert "<< insertValB << " Before " << insertPtB << ": ";
	dll.PrintDLL();

	//testing Delete
	dll.Delete(22);
	cout << "Delete 22: ";
	dll.PrintDLL();

	//testing GetHead / GetTail
	cout << "Head: " << dll.GetHead() << endl;
	cout << "Tail: " << dll.GetTail() << endl;

	//testing Sort
	dll.Sort();
	cout << "Sorted: ";
	dll.PrintDLL();

	//testing IsEmpty
	cout << "IsEmpty? ";
	if (dll.IsEmpty() == false) {
		cout << "False"<< endl;
	} else {
		cout << "True" << endl;
	}

	//testing GetMin / GetMax
	cout << "Min: " << dll.GetMin() << endl;
	cout << "Max: " << dll.GetMax() << endl;

	//testing GetSize
	cout << "Size: " << dll.GetSize() << endl;

	//testing DLLStructure (constructor for duplicating dlls)
	DLLStructure dll2(dll);
	cout << "Duplicate: ";
	dll2.PrintDLL();
}

