#include "Vector.h"
#include <stdexcept>

// Constructor
Vector::Vector() {
    capacity = CHUNK; // Initialize default capacity
    n_elems = 0; // Initialize number of elements to 0
    data_ptr = new int[capacity]; // Allocate memory
}

// Copy Constructor
Vector::Vector(const Vector& v) {
    capacity = v.capacity; // Copy the capacity from the source vector
    n_elems = v.n_elems; // Copy the number of elements from the source vector
    data_ptr = new int[capacity]; // Allocate memory for the array
    for (size_t i = 0; i < n_elems; i++) {
        data_ptr[i] = v.data_ptr[i]; // Copy the elements from the source vector
    }
}

// Copy Assignment Operator
Vector& Vector::operator=(const Vector& v) {
    if (this != &v) { // Check for self-assignment
        capacity = v.capacity; // Copy the capacity from the source vector
        n_elems = v.n_elems; // Copy the number of elements from the source vector
        delete[] data_ptr; // Deallocate the old memory
        data_ptr = new int[capacity]; // Allocate new memory for the array
        for (size_t i = 0; i < n_elems; i++) {
            data_ptr[i] = v.data_ptr[i]; // Copy the elements from the source vector
        }
    }
    return *this; // Return a reference to the current object
}

// Destructor
Vector::~Vector() {
    delete[] data_ptr; // Deallocate the memory allocated for the array
}

// Accessors
int Vector::front() const {
    if (empty()) {
        throw std::out_of_range("Vector is empty");
    }
    return data_ptr[0];
}

int Vector::back() const {
    if (data_ptr[n_elems - 1] == 0) {
        throw std::out_of_range("Index is empty");
    }
    return data_ptr[n_elems - 1];
}

int Vector::at(size_t pos) const {
    if (data_ptr[pos] == 0) {
        throw std::out_of_range("Index is empty");
    }
    return data_ptr[pos];
}

size_t Vector::size() const {
    return n_elems;
}

bool Vector::empty() const {
    if(n_elems == 0) {
        return true;
    }
    return false;
}

// Mutators
int& Vector::operator[](size_t pos) {
    return data_ptr[pos];
}

void Vector::push_back(int item) {
    // Add a new element to the end of the array
}

void Vector::pop_back() {
    // Remove the last element from the array
}

void Vector::erase(size_t pos) {
    // Remove the element at position pos and shift elements left
}

void Vector::insert(size_t pos, int item) {
    // Insert a new element at position pos and shift elements right
}

void Vector::clear() {
    // Reset n_elems to 0, but keep the current capacity
}

// Iterators
int* Vector::begin() {
    // Return a pointer to the first element
}

int* Vector::end() {
    // Return a pointer to one past the last element
}

// Comparators
bool Vector::operator==(const Vector& v) const {
    // Compare the contents of the current object with v
}

bool Vector::operator!=(const Vector& v) const {
    // Compare the contents of the current object with v
}

// Helper function
void Vector::grow() {
    // Increase the capacity of the array and reallocate data_ptr
}