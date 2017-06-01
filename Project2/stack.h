//
//  stack.h
//  Project2
//
//  Created by Derek Rodriguez on 5/30/17.
//  Copyright © 2017 Derek Rodriguez. All rights reserved.
//

#ifndef stack_h
#define stack_h


using namespace std;

template <class T>


class DynStack {
    
private:
    
    T *array; // To be used as an array
    
    int count, // Counter
        initialSize, // Initial size of the array
        arraySize; // Current size of the array
    
public:
    // Constructor
    DynStack(int n = 15):arraySize(15), count(0)  {
        // Test values to set initial size
        if (n <= 0) {
            initialSize = 1;
        } else {
            initialSize = n;
        }
        // Allocate memory
        array = new T[initialSize];
        
        
    }
    
    // Copy Constructor
    
    DynStack(const DynStack &stack):initialSize(stack.initialSize), arraySize(stack.arraySize), count(stack.count) {
        
        array = new (nothrow) T[initialSize];
        if (array != 0) {
            for (int i = 0; i < initialSize; i++) {
                array[i] = stack.array[i];
            }
        } else {
            cerr << "Cannot allocate memory";
            exit(1);
        }
        
    }
    
    // Destructor
    ~DynStack() {
        if (!empty()) {
            delete[] array;
        }
    }
    
    // Accessors
    
    T top() const throw(std::underflow_error) {
        // Throw underflow error if queue is empty.
        if (empty())
            throw underflow_error("Queue is empty");
            
            // Return head element
            return array[count-1];
    }

    
    int size() const {
        
        return count;
        
    }
    
    // check if stack is empty
    bool empty() const {
	if(count == 0) return true;
	else return false;
    }
    
    int capacity() const {
        // Return total capacity of stack
        return arraySize;
    }
    
    void display() {
        
        // Print the contents of the stack
        
        cout << endl << "Contents of the stack: " << endl;
        
        for (int i = count; i >= 0; i--) {
            cout << array[i] << endl;
        }
        
        cout << endl;
        
        
    }
    
    // Mutators
    
    // push data to top of stack, resize if neccessary
    void push(T const &data) {
        if (size() != capacity()) {
     		array[count] = data;   
       	        count++;             
        } else {
            T* a = new T[arraySize * 2];
	    for(int i = 0; i < count; i++){
		a[i] = array[i];
	    }
            delete [] array;
            T* array = a;
	    count++;
	    array[count-1] = data;
        }       
    }
    
    // pop and return item on top of stack, resize if neccessary
    T pop() throw(std::underflow_error) {
	// if array is empty, throw underflpw error	
	if(empty() == true){
		throw std::underflow_error("Stack is empty");
	}
	// otherwise pop top item
        T popped = array[count];
	count--;
        return popped;
       	// resize array if neccessary
	if(count <= .25*arraySize && arraySize > initialSize){
		int newSize = .5 * arraySize;
		T* resizedArray= new T[newSize];
		for(int i = count-1; i >= 0; i--){
			resizedArray[i] = array[i];
		}
		T* temp = array;
		array = resizedArray;
		delete[] temp;
	}
    }
    
    // remove all elements and resize to initial size
    void clear(void) {
	delete[] array;
	T* array = new T[initialSize];
	count = 0;
	arraySize = initialSize;
    }
    
    // Overload assignment operator
    DynStack &operator=(const DynStack &stack) {
        if (this != &stack) {
            arraySize = stack.arraySize;
            initialSize = stack.initialSize;
            if (initialSize != stack.initialSize) {
                delete [] array;
                array = new(nothrow) T[initialSize];
            }
            for (int i = 0; i < initialSize; i++) {
                array[i] = stack.array[i];
            }
        }
        return *this;
    }
    
};

#endif /* stack_h */
