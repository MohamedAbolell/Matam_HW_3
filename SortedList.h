
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
