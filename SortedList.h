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

        /**
         * @brief Returns the number of elements in the list.
         *
         * @return The size of the list.
         */
        int length() const {
            return size;
        }

        /**
         * @brief Points to the first element in the list.
         *
         * @return ConstIterator to the head of the list.
         */
        ConstIterator begin() const {
            return ConstIterator(head);
        }

        /**
         * @brief Points to the one after the last element in the list.
         *
         * @return ConstIterator to nullptr.
         */
        ConstIterator end() const {
            return ConstIterator(nullptr);
        }

        /**
         * @brief Creates a new list according to a certain condition .
         *
         * @param pred - Predicate according to which the members in the list should be filtered.
         *
         * @return New SortedList with elements that satisfy a given condition.
         */
        template <typename Predicate>
        SortedList<T> filter(Predicate pred) const {
            SortedList<T> result;
            try{
                for(const T& element : *this){
                    if(pred(element)){
                        result.insert(element);
                    }
                }
            }
            catch(std :: bad_alloc& e){
                delete result.head;
                result.head = nullptr;
                throw e;
            }
            return result;
        }

        /**
         * @brief Creates a new list according to a certain operation .
         *
         * @param op - Operation that is performed on the members of the list.
         *
         * @return New SortedList with elements that were modified by an operation.
         */
        template <typename Operation>
        SortedList<T> apply(Operation op) const{
            SortedList<T> result;
            try{
                for(const T& element : *this){
                    result.insert(op(element));
                }
            }
            catch(std :: bad_alloc& e){
                delete result.head;
                result.head = nullptr;
                throw e;
            }
            return result;
        }

    };

    /**
     * @brief Class representing a ConstIterator to a SortedList .
     */
    template <class T>
    class SortedList<T>::ConstIterator {

        const Node *current;

        /**
         * @brief Constructor to create a ConstIterator object.
         *
         * @param Pointer to Node current to set to this Pointer to Node current.
         */
        ConstIterator(const Node *current) : current(current) {}

        friend class SortedList<T>;

    public:

        /**
         * @brief Default copy constructor to create a ConstIterator object.
         *
         * @param Reference to other ConstIterator object to copy to this.
         */
        ConstIterator(const ConstIterator &other) = default;

        /**
         * @brief Default assignment operation .
         *
         * @param Reference to other ConstIterator object to assign to this.
         */
        ConstIterator &operator=(const ConstIterator &other) = default;

        /**
         * @brief Access to the data of the object pointed to by the ConstIterator.
         *
         * @return Read-only access to data.
         *
         * @throw std::runtime_error in case an attempt is made to access non-existent information.
         */
        const T &operator*() const {
            if (current == nullptr) {
                throw std::runtime_error("Not data");
            }
            return current->data;
        }

        /**
         * @brief Promotion to the next member of the list.
         *
         * @return Given ConstIterator after Promotion.
         *
         * @throw std::out_of_range in case an attempt is made to promote after end of list.
         */
        ConstIterator &operator++() {
            if (current == nullptr) {
                throw std::out_of_range("End of list");
            }
            current = current->next;
            return *this;
        }

        /**
         * @brief Check if two ConstIterator do not point to same list member.
         *
         * @param Read-only access to other ConstIterator.
         *
         * @return True-if two ConstIterator do not point to same list member. otherwise, false.
         */
        bool operator!=(const ConstIterator &other) const {
            return current != other.current;
        }
    };
}
