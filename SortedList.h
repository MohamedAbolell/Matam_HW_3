#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {
    /**
 * @brief Class representing a generic sorted list .
 */
    template <typename T>
    class SortedList {
        class Node {
        public:
            T data;
            Node* next;

            /**
             * @brief Constructor to create a Node object.
             *
             * @param data other to set to this data.
             */
            Node(const T& other) : data(other), next(nullptr) {}

            /**
             * @brief Destructor to delete a Node object.
             */
            ~Node(){
                if(this->next != nullptr){
                    delete this -> next;
                }
            }
        };
        Node* head;
        int size;
    template <class T>
    class SortedList<T>::ConstIterator {
    /**
     * the class should support the following public interface:
     * if needed, use =defualt / =delete
     *
     * constructors and destructor:
     * 1. a ctor(or ctors) your implementation needs
     * 2. copy constructor
     * 3. operator= - assignment operator
     * 4. ~ConstIterator() - destructor
     *
     * operators:
     * 5. operator* - returns the element the iterator points to
     * 6. operator++ - advances the iterator to the next element
     * 7. operator!= - returns true if the iterator points to a different element
     *
     */
    };
}

