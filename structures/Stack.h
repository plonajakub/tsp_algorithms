#ifndef PEA_P1_STACK_H
#define PEA_P1_STACK_H

#include "DoublyLinkedList.h"

template<class T>
class Stack {

public:
    void push(const T &item) {
        list.insertAtEnd(item);
    }

    T pop() {
        T data = list.getLast();
        list.removeFromEnd();
        return data;
    }

    [[nodiscard]] int getSize() const {
        return list.getSize();
    }

    [[nodiscard]] bool isEmpty() const {
        return list.getSize() == 0;
    }

private:
    DoublyLinkedList<T> list;
};


#endif //PEA_P1_STACK_H
