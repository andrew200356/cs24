#include "FibVec.h"

// This provides exception types:
#include <stdexcept>

// FibVec Function Implementations
FibVec::FibVec()
{
    // Initialize the size and capacity to 0
    m_count = 0;
    m_capacity = 1; // f(2) = 1
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
    return m_count;
}

void FibVec::resize()
{
    // Check if the number of elements is equal to the capacity
    if (m_count == m_capacity)
    {
        int nextFib = num1 + num2; // Next Fibonacci number for new capacity
        int *new_data = new int[nextFib];

        // Copy the data from the old array to the new array
        for (size_t i = 0; i < m_count; i++)
        {
            new_data[i] = m_data[i];
        }

        delete[] m_data;
        m_data = new_data;

        // Update the capacity to the new Fibonacci number
        m_capacity = nextFib;

        // Update Fibonacci numbers for future resizing
        num1 = num2;
        num2 = nextFib;
    }
}

void FibVec::downsize()
{
    // When removing from a vector with capacity f(n): if the number of items drops below f(n-2), the vector must resize its capacity to f(n-1).

    int downsizeFib = num2 - num1; // f(n-2)
    if (m_count < size_t(downsizeFib))
    {
        int *new_data = new int[num1];

        // Copy the data from the old array to the new array
        for (size_t i = 0; i < m_count; i++)
        {
            new_data[i] = m_data[i];
        }

        delete[] m_data;
        m_data = new_data;

        // Update the capacity to f(n-1)
        m_capacity = num1;

        // Update Fibonacci numbers for future resizing
        num2 = num1;
        num1 = downsizeFib;
    }
}

void FibVec::insert(int value, size_t index)
{
    // Check if the index is out of bounds
    if (index > m_count)
    {
        throw std::out_of_range("Index out of bounds");
    }

    // first check if we need to resize
    resize();

    // Shift the elements to the right to make room for the new value
    for (size_t i = m_count; i > index; i--)
    {
        m_data[i] = m_data[i - 1];
    }

    // Insert the new value at the specified index
    m_data[index] = value;
    m_count++;
}

size_t FibVec::lookup(size_t index) const
{
    // Check if the index is out of bounds
    if (index >= m_count)
    {
        throw std::out_of_range("Index out of bounds");
    }

    // Return the value at the index given
    return m_data[index];
}

int FibVec::pop()
{
    // Check if the vector is empty
    if (m_count == 0)
    {
        throw std::underflow_error("Vector is empty");
    }

    // Get the last value in the vector
    int value = m_data[m_count - 1];

    // Decrement the size of the vector
    m_count--;

    downsize();

    // Return the last value in the vector
    return value;
}

void FibVec::push(int value)
{
    resize();

    // Insert the new value at the end of the vector
    m_data[m_count] = value;

    // Increment the size of the vector
    m_count++;
}

int FibVec::remove(size_t index)
{
    // The remove function takes one argument: an index. It removes the value stored at that index and returns it. If the index is invalid, it throws a std::out_of_range exception.

    // Check if the index is out of bounds
    if (index >= m_count)
    {
        throw std::out_of_range("Index out of bounds");
    }

    // Get the value at the specified index
    int value = m_data[index];

    // Shift the elements to the left to fill the gap
    for (size_t i = index; i < m_count - 1; i++)
    {
        m_data[i] = m_data[i + 1];
    }

    // Decrement the size of the vector
    m_count--;

    downsize();

    // Return the value that was removed
    return value;
}
