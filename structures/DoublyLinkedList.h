#ifndef PEA_P1_DOUBLYLINKEDLIST_H
#define PEA_P1_DOUBLYLINKEDLIST_H

#include <stdexcept>
#include <iostream>

// Represents single node of the list
template<class T>
class Node {
public:
    // Next node's pointer
    Node *next;

    // Previous node's pointer
    Node *prev;

    T data;

    // Sentry marker
    bool isSentry;

    // This constructor is used to create sentry node
    Node() : next(this), prev(this), isSentry(true) {}

    // Mainly used constructor for new nodes creation
    explicit Node(const T &data) : next(nullptr), prev(nullptr), data(data), isSentry(false) {}
};

template<class T>
class DoublyLinkedList {

public:
    class Iterator {
    public:
        explicit Iterator(Node<T> *node) {
            currNode = node;
        }

        void operator++() {
            currNode = currNode->next;
        }

        void operator--() {
            currNode = currNode->prev;
        }

        bool operator==(const Iterator &other) {
            return this->currNode == other.currNode;
        }

        bool operator!=(const Iterator &other) {
            return this->currNode != other.currNode;
        }

        T &getData() {
            return currNode->data;
        }

        const T &getData() const {
            return currNode->data;
        }

    private:
        Node<T> *currNode;
    };

    DoublyLinkedList() noexcept {
        sentry = new Node<T>();
        size = 0;
    }

    ~DoublyLinkedList() noexcept {
        // Free memory
        auto *it = sentry->next;
        while (!it->isSentry) {
            it = it->next;
            delete it->prev;
        }
        delete sentry;
    }

    DoublyLinkedList(const DoublyLinkedList &otherList) {
        sentry = new Node<T>();
        size = 0;
        DoublyLinkedList<T>::Iterator otherIt = otherList.getIterator();
        DoublyLinkedList<T>::Iterator otherItEnd = otherList.getEndIt();
        while (otherIt != otherItEnd) {
            this->insertAtEnd(otherIt.getData());
            ++otherIt;
        }
    }

    DoublyLinkedList<T> &operator=(const DoublyLinkedList &otherList) {
        if (this != &otherList) {
            while (this->size > 0) {
                this->removeFromEnd();
            }
            DoublyLinkedList<T>::Iterator otherIt = otherList.getIterator();
            DoublyLinkedList<T>::Iterator otherItEnd = otherList.getEndIt();
            while (otherIt != otherItEnd) {
                this->insertAtEnd(otherIt.getData());
                ++otherIt;
            }
        }
        return *this;
    }

    // Inserts new node with data equal to value into the place described by index
    void insert(int index, const T &value) {
        // Check if index is valid
        if (index < 0 || index > size) {
            throw std::out_of_range("insert() failed: index out of bounds");
        }

        auto *newNode = new Node<T>(value);
        auto *it = sentry->next;

        // Find proper place for the node based on index
        for (int i = 0; i != index; ++i) {
            it = it->next;
        }

        // Insert the new node into the list
        newNode->prev = it->prev;
        it->prev->next = newNode;
        it->prev = newNode;
        newNode->next = it;
        ++size;
    }

    // Inserts new node with data equal to value at beginning of the list
    void insertAtStart(const T &value) {
        auto *newNode = new Node<T>(value);

        // Insert the new node into the list
        newNode->next = sentry->next;
        sentry->next->prev = newNode;
        sentry->next = newNode;
        newNode->prev = sentry;
        ++size;
    }

    // Inserts new node with data equal to value at end of the list
    void insertAtEnd(const T &value) {
        auto *newNode = new Node<T>(value);

        // Insert the new node into the list
        newNode->prev = sentry->prev;
        sentry->prev->next = newNode;
        sentry->prev = newNode;
        newNode->next = sentry;
        ++size;
    }

    // Inserts new node with data equal to insertValue after the node described by data equal to searchValue
    // If searchValue does not exist this method inserts new node at the beginning of the list
    void insertAfterValue(const T &searchValue, const T &insertValue) {
        // Find proper place for a new node based on searchValue
        for (auto *it = sentry->next; !it->isSentry; it = it->next) {
            if (it->data == searchValue) {
                // searchValue found -> insert the new node
                auto *newNode = new Node<T>(insertValue);
                newNode->next = it->next;
                it->next->prev = newNode;
                it->next = newNode;
                newNode->prev = it;
                ++size;
                return;
            }
        }
        // searchValue not found -> insert the new node at beginning of the list
        this->insertAtStart(insertValue);
    }

    // Removes node from place described by index
    void remove(int index) {
        // Check if index is valid
        if (index < 0 || index >= size) {
            throw std::out_of_range("remove() failed: index out of bounds");
        }

        // Find a node to be deleted
        Node<T> *it = sentry->next;
        for (int i = 0; i != index; ++i) {
            it = it->next;
        }

        // Delete the node
        it->prev->next = it->next;
        it->next->prev = it->prev;
        delete it;
        --size;
    }

    // Removes node from beginning of the list
    T removeFromStart() {
        // Check if list is empty
        if (size == 0) {
            throw std::out_of_range("removeFromStart() failed: list is empty");
        }

        T data = sentry->next->data;
        // Remove the node at start of the list
        auto *head = sentry->next;
        sentry->next = head->next;
        head->next->prev = sentry;
        delete head;
        --size;
        return data;
    }

    // Removes node from end of the list
    void removeFromEnd() {
        // Check if list is empty
        if (size == 0) {
            throw std::out_of_range("removeFromEnd() failed: list is empty");
        }

        // Remove the node at end of the list
        auto *tail = sentry->prev;
        sentry->prev = tail->prev;
        tail->prev->next = sentry;
        delete tail;
        --size;
    }

    // Removes node with data equal to value
    // If value does not exist on the list, this method has no effect
    void removeByValue(const T &value) {
        try {
            this->remove(this->search(value));
        } catch (std::out_of_range &e) {
            // No action: value does not exist in the list
        }
    }

    // Performs linear search on the list and returns value's index
    // If value does not exist VALUE_NOT_FOUND is returned
    int search(const T &value) const {
        int returnIdx = VALUE_NOT_FOUND;
        int currentIdx = 0;
        Node<T> *it = sentry->next;

        // Perform linear search
        while (!it->isSentry) {
            if (it->data == value) {
                returnIdx = currentIdx;
                break;
            }
            ++currentIdx;
            it = it->next;
        }
        return returnIdx;
    }

    bool operator==(const DoublyLinkedList<T> &otherList) const {
        if (this->size != otherList.getSize()) {
            return false;
        }
        DoublyLinkedList<T>::Iterator it = this->getIterator();
        DoublyLinkedList<T>::Iterator itEnd = this->getEndIt();
        DoublyLinkedList<T>::Iterator otherIt = otherList.getIterator();
        while (it != itEnd) {
            if (it.getData() != otherIt.getData()) {
                return false;
            }
            ++it;
            ++otherIt;
        }
        return true;
    }

    bool operator!=(const DoublyLinkedList<T> &otherList) const {
        return !(*this == otherList);
    }

    bool contains(const T &data) const {
        for (Iterator it = this->getIterator(); it != this->getEndIt(); ++it) {
            if (it.getData() == data) {
                return true;
            }
        }
        return false;
    }

    T &getLast() {
        if (sentry->prev->isSentry) {
            throw std::invalid_argument("getLast() error: list is empty");
        }
        return sentry->prev->data;
    }

    const T &getLast() const {
        if (sentry->prev->isSentry) {
            throw std::invalid_argument("getLast() error: list is empty");
        }
        return sentry->prev->data;
    }

    // Returns list's size
    [[nodiscard]] int getSize() const {
        return size;
    }

    [[nodiscard]] bool isEmpty() const {
        return size == 0;
    }

    DoublyLinkedList<T>::Iterator getIterator() {
        return DoublyLinkedList<T>::Iterator(this->sentry->next);
    }

    DoublyLinkedList<T>::Iterator getIterator() const {
        return DoublyLinkedList<T>::Iterator(this->sentry->next);
    }

    DoublyLinkedList<T>::Iterator getEndIt() {
        return DoublyLinkedList::Iterator(this->sentry);
    }

    DoublyLinkedList<T>::Iterator getEndIt() const {
        return DoublyLinkedList::Iterator(this->sentry);
    }

    // Returned by search() if value was not found in the list
    static const int VALUE_NOT_FOUND = -1;
private:

    // Sentry's pointer
    Node<T> *sentry;

    // Number of elements in the list
    int size;

};

std::ostream &operator<<(std::ostream &ostr, const DoublyLinkedList<int> &dll);


#endif //PEA_P1_DOUBLYLINKEDLIST_H
