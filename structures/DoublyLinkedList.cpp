#include "DoublyLinkedList.h"

std::ostream &operator<<(std::ostream &ostr, const DoublyLinkedList<int> &dll) {
    ostr << "[";
    auto it = dll.getIterator();
    auto nearEndIt = dll.getEndIt();
    --nearEndIt;
    for (; it != nearEndIt; ++it) {
        ostr << it.getData() << ", ";
    }
    if (nearEndIt != dll.getEndIt()) {
        ostr << nearEndIt.getData();
    }
    ostr << "]";
    return ostr;
}