
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

    public:
        /**
         * @brief Default constructor to create a SortedList object.
         */
        SortedList(): head(nullptr), size(0) {}

        /**
         * @brief Destructor to delete a SortedList object.
         */
        ~SortedList() {
            if(this->head != nullptr){
                delete this->head;
            }
        }

        /**
         * @brief Class representing a Const Iterator .
         */
        class ConstIterator;

        /**
         * @brief Copy constructor to create a SortedList object.
         *
         * @param SortedList other to copy.
         */
        SortedList(const SortedList& other) : head(nullptr), size(other.size){
            if (other.head == nullptr) {
                return;
            }

            try
            {
                head = new Node(other.head->data);
                Node* current = head;
                Node* otherCurrent = other.head->next;
                while (otherCurrent != nullptr) {
                    current->next = new Node(otherCurrent->data);
                    current = current->next;
                    otherCurrent = otherCurrent->next;
                }
            }
            catch (std:: bad_alloc &e)
            {
                delete head;
                head = nullptr;
                throw e;
            }
        }

        /**
         * @brief Copy assignment operator .
         *
         * @param other - SortedList to assign.
         *
         * @return Reference to the given list after assignment.
         */
        SortedList& operator=(const SortedList& other){
            if (this == &other) {
                return *this;
            }


            SortedList temp(other);


            Node* tempHead = temp.head;
            int tempSize = temp.size;

            temp.head = this->head;
            temp.size = this->size;

            this->head = tempHead;
            this->size = tempSize;

            return *this;
        }

        /**
         * @brief Insert new element to the list .
         *
         * @param value - Value to insert.
         *
         * @return Reference to the given list after inserting.
         */
        SortedList& insert(const T& value)
        {
            Node* toInsert=nullptr;
            try {
                toInsert = new Node(value);
            }
            catch(std :: bad_alloc& e) {
                throw e;
            }
            if (head == nullptr || value > head->data) {
                toInsert->next = head;
                head = toInsert;

            }
            else {
                Node* current = head;
                while (current->next != nullptr && current->next->data > value) {
                    current = current->next;
                }

                toInsert->next = current->next;
                current->next = toInsert;
            }
            size++;
            return *this;
        }


        /**
         * @brief Remove an element from the list .
         *
         * @param rm - ConstIterator which points to the member we want to remove.
         *
         * @return Reference to the given list after removing.
         */
        SortedList& remove(const ConstIterator& toRemove) {
            if(!(toRemove != end())) {
                return *this;
            }
            Node* toDelete = nullptr;
            if(!(toRemove != begin())) {
                toDelete = head;
                head = head->next;
            }
            else{
                toDelete = head;
                while(toDelete->next != toRemove.current && toDelete->next != nullptr)
                {
                    toDelete = toDelete->next;
                }
                if (toDelete->next == toRemove.current )
                {
                    Node* current = toDelete;
                    toDelete = toDelete->next;
                    current->next = toDelete->next;
                }
            }
            toDelete->next = nullptr;
            delete toDelete;
            size--;
            return *this;
        }
