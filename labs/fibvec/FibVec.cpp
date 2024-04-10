#include "FibVec.h"

// This provides exception types:
#include <stdexcept>

// FibVec Function Implementations
FibVec::FibVec()
{
    // Initialize the size and capacity to 0
    size = 1;
    m_capacity = 1;
    num1 = 1;
    num2 = 1;
    // Initialize the data array to nullptr
    m_data = new int[m_capacity];
}

FibVec::~FibVec()
{
    // Delete the data array if it is not nullptr
    if (m_data != nullptr)
    {
        delete[] m_data;
    }
}

size_t FibVec::capacity() const
{
    // Return the capacity of the vector
    return m_capacity;
}

size_t FibVec::count() const
{
    // Return the number of elements in the vector
    return size;
}

void FibVec::resize()
{
    // Create a new array with the new capacity
    int *new_data = new int[num1 + num2];
    num2 = num1 + num2;
    num1 = num2;

    // Copy the data from the old array to the new array
    for (size_t i = 0; i < size; i++)
    {
        new_data[i] = m_data[i];
    }

    // Delete the old array
    delete[] m_data;

    // Update the data pointer and capacity
    m_data = new_data;
    m_capacity = num2;
}

void FibVec::downsize()
{
    int *new_data = new int[num1];
    int a = num1; // num2 now
    num1 = num2 - num1;
    num2 = a;

    for (size_t i = 0; i < size; i++)
    {
        new_data[i] = m_data[i];
    }

    delete[] m_data;

    m_data = new_data;
    m_capacity = num2;
}

void FibVec::insert(int value, size_t index)
{
    // Check if the index is out of bounds
    if (index > size)
    {
        throw std::out_of_range("Index out of bounds");
    }

    resize();

    // Shift the elements to the right to make room for the new value
    for (size_t i = size; i > index; i--)
    {
        m_data[i] = m_data[i - 1];
    }

    // Insert the new value at the specified index
    m_data[index] = value;
}

size_t FibVec::lookup(size_t index) const
{
    // Check if the index is out of bounds
    if (index >= size)
    {
        throw std::out_of_range("Index out of bounds");
    }

    // Return the value at the index given
    return m_data[index];
}

int FibVec::pop()
{
    // Check if the vector is empty
    if (size == 0)
    {
        throw std::out_of_range("Vector is empty");
    }

    // Get the last value in the vector
    int value = m_data[size - 1];

    // Decrement the size of the vector
    size--;

    downsize();

    // Return the last value in the vector
    return value;
}

void FibVec::push(int value)
{
    resize();

    // Insert the new value at the end of the vector
    m_data[size] = value;

    // Increment the size of the vector
    size++;
}

void FibVec::remove(size_t index)
{
    // Check if the index is out of bounds
    if (index >= size)
    {
        throw std::out_of_range("Index out of bounds");
    }

    // Shift the elements to the left to remove the value at the specified index
    for (size_t i = index; i < size - 1; i++)
    {
        m_data[i] = m_data[i + 1];
    }

    // Decrement the size of the vector
    size--;

    downsize();
}
