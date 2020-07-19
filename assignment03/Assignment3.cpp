// Assignment 3: Diana Lin 260625972

// Question 1
/* unique_ptr - points to an object and deletes that object when out of scope
 * shared_ptr - allows for shared ownership of an object using this pointer;
 * 				many shared_ptr's can point to the same object ("sharing");
 * 				deletes the shared object when the last shared_ptr is deleted; or
 * 				when the last shared_ptr is reassigned to another object
 * weak_ptr - a non-ownership pointer that points to an object (generally owned by shared_ptr(s));
 * 			  allows for the deallocation of the object while still pointing to it;
 * 			  used for objects where you only need to access it if it exists
 * auto_ptr - disapproved of in C++11, but not removed until C++17;
 * 			  manages dynamically allocated objects using the "new" keyword;
 * 			  object is deleted when auto_ptr object itself is destroyed;
 * 			  generally used to pass membership of dynamically allocated objects
 * owner_less - provides mixed-type owner-based ordering of shared_ptr and weak_ptr;
 * 				so that they are only considered equal when they're both empty or managing the same object
 * enable_shared_from_this - lets an object (owned by a shared_ptr) create more instances of shared_ptrs that share itself
 * bad_weak_ptr - an exception object that the shared_ptr constructors throw;
 * 				  when their input parameter weak_ptr points to an object that has already been deallocated
 * default_delete - default destructor used by unique_ptr when no other is specified
 *
 * unique_ptr is what you think of as the classic SmartPointer
 * each SmartPointer after is like a unique_ptr with special features
 * while the last four are not really "smart pointers" but are
 * member functions of some smart pointers.
 */

#include <iostream>
#include <exception>
using namespace std;

//Question 2
//copy and copy assignment constructors not written as they were not explicitly stated in the assignment
template <class myType>
class SmartPointer {
	myType* ptr;
	int size;
	bool array; //helps to distinguish which destructor to use so there's no memory leak
public:
	SmartPointer() {
		this->ptr = 0;
		this->size = 0;
		this->array = false;
	}
	SmartPointer(myType p) {
		try {
			try {
				this->array = false;
				this->ptr = new myType(p);
				this->size = 0;
				if (p < 0) {
					this->ptr = 0;
					throw "Only positive numbers are accepted.";
				}
			} catch (char const* message) {
				cout << message << endl;
			}
		} catch(std::bad_alloc& ba) {
			cout << "There is not enough memory-- so the variable was not allocated." << endl;
		}
	}
	~SmartPointer() {
		if (this->array == true) {
			delete[] this->ptr;
		} else {
			delete this->ptr;
		}
	}
	myType getValue() {
		return *(this->ptr);
	}
	void setValue(myType x) {
		try {
			try {
				this->array = false;
				this->ptr = new myType(x);
				if (x < 0) {
					this->ptr = 0;
					throw "Only positive numbers are accepted.";
				}
			} catch(char const* message) {
				cout << message << endl;
			}
		} catch (std::bad_alloc& ba) {
			cout << "There is not enough memory-- so the variable was not allocated." << endl;
		}
	}

	friend SmartPointer<myType> operator+ (const SmartPointer<myType>& ptrA, const SmartPointer<myType>& ptrB) {
		SmartPointer<myType> result;
		result.setValue(*(ptrA.ptr) + *(ptrB.ptr));
		return result;
	}
	friend SmartPointer<myType> operator- (const SmartPointer<myType>& ptrA, const SmartPointer<myType>& ptrB) {
		SmartPointer<myType> result;
		result.setValue(*(ptrA.ptr) - *(ptrB.ptr));
		return result;
	}
	friend SmartPointer<myType> operator* (const SmartPointer<myType>& ptrA, const SmartPointer<myType>& ptrB) {
		SmartPointer<myType> result;
		result.setValue((*(ptrA.ptr))*(*(ptrB.ptr)));
		return result;
	}

	//Question 6: Array implementation
	//TA Deeksha said to name new methods get_values and set_values, and that operator overloading was not necessary
	//
	SmartPointer(myType array, int size) {
		try {
			try {
				for (int i=0; i < size; i++) {
					if(array[i] < 0) {
						throw "Only positive numbers are accepted.";
					}
				}
				this->array = true;
				this->size = size;
				this->ptr = new myType[size];
				for (int i=0; i < size; i++) {
					this->ptr[i] = &array[i];
				}
			} catch(const char* message) {
					cout << message << endl;
					this->size = 0;
					this->ptr = NULL;
			}
		} catch(std::bad_alloc& ba) {
			cout << "There is not enough memory-- so the variable was not allocated." << endl;
		}
	}
	myType get_values() {
		return *(this->ptr);
	}
	void set_values(myType array, int size) {
		try {
			try {
				for (int i =0; i < size; i++) {
					if (array[i] < 0) {
						throw "Only positive numbers are accepted.";
					}
				}
				this->array = true;
				this->size = size;
				this->ptr = new myType[this->size];
				for (int i=0; i < this->size; i++) {
					this->ptr[i] = &array[i];
				}
			} catch(const char* message) {
				cout << message << endl;
				this->ptr = NULL;
				this->size = 0;
			}
		} catch (std::bad_alloc& ba) {
			cout << "There is not enough memory-- so the variable was not allocated." << endl;
		}
	}


};

int main() {
	//Question 1
	cout << "Question 1: See comments above." << endl;
	cout << endl;

	//Question 2
	cout << "Question 2a: Initial initialization" << endl;
	int x = 11;
	SmartPointer<int> sPointer(x);
	cout << sPointer.getValue() << endl;

	cout << "Question 2b: Later initialization" << endl;
	int y = 133;
	SmartPointer<int> sPointer1;
	sPointer1.setValue(y);
	cout << sPointer1.getValue() << endl;
	cout << endl;

	//Question 3
	cout << "Question 3: See last method call." << endl;
	cout << endl;

	//Question 4
	cout << "Question 4: Using Templates" << endl;
	SmartPointer<float> sPointer4;
	sPointer4.setValue(13.31);
	cout << sPointer4.getValue() << endl;
	cout << endl;

	//Question 5
	cout << "Question 5a: Overloading Operator+" << endl;
	SmartPointer<float> sPointer5(2.5);
	SmartPointer<float> sPointer6(1.5);
	SmartPointer<float> result1 = sPointer5 + sPointer6;
	cout << result1.getValue() << endl;
	cout << "Question 5b: Overloading Operator*" << endl;
	SmartPointer<float> result2 = sPointer5*sPointer6;
	cout << result2.getValue() << endl;
	cout << "Question 5c: Overloading Operator-" << endl;
	SmartPointer<float> result3 = sPointer5 - sPointer6;
	cout << result3.getValue() << endl;
	cout << endl;

	//Question 6a
	cout << "Question 6a: Adjusting for Arrays - Integers" << endl;
	int array[3] = {2,3,4};
	SmartPointer<int*> sPointerA(array,3);
	for (int i = 0; i < 3; i++) {
		if (i == 2) {
			cout << sPointerA.get_values()[i] << endl;
		} else {
			cout << sPointerA.get_values()[i] << ", ";
		}
	}

	//Question 6b
	cout << "Question 6b: Adjusting for Arrays - Doubles" << endl;
	double a[4] = {3.1, 3.4, 6.2, 4.4};
	SmartPointer<double*> sPointerB(a,4);
	for (int i=0; i < 4; i++) {
		if(i == 3) {
			cout << sPointerB.get_values()[i] << endl;
		}
		else {
			cout << sPointerB.get_values()[i] << ", ";
		}
	}
	cout << endl;

	//Question 3 - must be tested last since nothing executes following the catch block
	cout << "Question 3: Testing Negative Numbers" << endl;
	int z = -11;
	SmartPointer<int> sPointer2(z);
	cout << sPointer2.getValue() << endl;
}
