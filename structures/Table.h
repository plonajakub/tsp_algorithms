#ifndef PEA_P1_TABLE_H
#define PEA_P1_TABLE_H

#include <stdexcept>

template<class T>
class Table {

public:
    Table() noexcept : size(0), capacity(0), table(nullptr) {
    }

    ~Table() noexcept {
        delete[] table;
    }

    Table(const Table &otherTable) : size(0), capacity(0), table(nullptr) {
        for (int i = 0; i < otherTable.getSize(); ++i) {
            this->insert(i, otherTable[i]);
        }
    }

    Table<T> &operator=(const Table &otherTable) {
        if (this != &otherTable) {
            while (this->getSize() > 0) {
                this->removeFromEnd();
            }
            for (int i = 0; i < otherTable.getSize(); ++i) {
                this->insert(i, otherTable[i]);
            }
        }
        return *this;
    }

    // Inserts value into table on place described by index
    void insert(int index, const T &value) {
        // Check if index is valid
        if (index > size || index < 0) {
            throw std::out_of_range("insert() failed: index out of bounds");
        }
        if (capacity == 0) {
            // First elements is being inserted
            table = new T[1];
            capacity = 1;
        } else if (capacity > size) {
            // Insert element without enlarging table
            for (int i = size - 1; i >= index; --i) {
                table[i + 1] = table[i];
            }
        } else if (capacity == size) {
            // Table must be enlarged before insertion
            auto *tmpTable = new T[ENLARGEMENT_COEFFICIENT * capacity];
            int i;
            for (i = 0; i < index; ++i) {
                tmpTable[i] = table[i];
            }
            for (int j = index + 1; i < size; ++i, ++j) {
                tmpTable[j] = table[i];
            }
            delete[] table;
            table = tmpTable;
            capacity *= ENLARGEMENT_COEFFICIENT;
        }
        table[index] = value;
        ++size;
    }

    // Inserts value into table at start
    void insertAtStart(const T &value) {
        if (capacity == 0) {
            // First elements is being inserted
            table = new T[1];
            capacity = 1;
        } else if (capacity > size) {
            // Insert element without enlarging table
            for (int i = size - 1; i >= 0; --i) {
                table[i + 1] = table[i];
            }
        } else if (capacity == size) {
            // Table must be enlarged before insertion
            auto *tmpTable = new T[ENLARGEMENT_COEFFICIENT * capacity];
            for (int i = size - 1; i >= 0; --i) {
                tmpTable[i + 1] = table[i];
            }
            delete[] table;
            table = tmpTable;
            capacity *= ENLARGEMENT_COEFFICIENT;
        }
        table[0] = value;
        ++size;
    }

    // Inserts value into table at end
    void insertAtEnd(const T &value) {
        if (capacity == 0) {
            // First elements is being inserted
            table = new T[1];
            capacity = 1;
        } else if (capacity == size) {
            // Table must be enlarged before insertion
            auto *tmpTable = new T[ENLARGEMENT_COEFFICIENT * capacity];
            for (int i = 0; i < size; ++i) {
                tmpTable[i] = table[i];
            }
            delete[] table;
            table = tmpTable;
            capacity *= ENLARGEMENT_COEFFICIENT;
        }
        table[size] = value;
        ++size;
    }

    // Remove value described by index from table
    void remove(int index) {
        // Check if index is valid
        if (index >= size || index < 0) {
            throw std::out_of_range("remove() failed: index out of bounds");
        }
        if (size == 1) {
            // Remove last element
            delete[] table;
            table = nullptr;
            capacity = 0;
        } else if (getFullFactor() > REDUCTION_COEFFICIENT) {
            // Table doesn't have to be reduced after removal
            for (int i = index; i < size - 1; ++i) {
                table[i] = table[i + 1];
            }
        } else {
            // Table has to be reduced after removal
            auto *tmpTable = new T[capacity / ENLARGEMENT_COEFFICIENT];
            int i;
            for (i = 0; i < index; ++i) {
                tmpTable[i] = table[i];
            }
            ++i;
            for (int j = index; i < size; ++i, ++j) {
                tmpTable[j] = table[i];
            }
            delete[] table;
            table = tmpTable;
            capacity /= ENLARGEMENT_COEFFICIENT;
        }
        --size;
    }

    // Remove value from table from start
    void removeFromStart() {
        // Check if table is not empty
        if (size < 1) {
            throw std::out_of_range("removeFromStart() failed: table is empty");
        }
        if (size == 1) {
            // Remove last element
            delete[] table;
            table = nullptr;
            capacity = 0;
        } else if (getFullFactor() > REDUCTION_COEFFICIENT) {
            // Table doesn't have to be reduced after removal
            for (int i = 0; i < size - 1; ++i) {
                table[i] = table[i + 1];
            }
        } else {
            // Table has to be reduced after removal
            auto *tmpTable = new T[capacity / ENLARGEMENT_COEFFICIENT];
            for (int i = 0; i < size - 1; ++i) {
                tmpTable[i] = table[i + 1];
            }
            delete[] table;
            table = tmpTable;
            capacity /= ENLARGEMENT_COEFFICIENT;
        }
        --size;
    }

    // Remove value from table from end
    void removeFromEnd() {
        // Check if table is not empty
        if (size < 1) {
            throw std::out_of_range("removeFromEnd() failed: table is empty");
        }
        if (size == 1) {
            // Remove last element
            delete[] table;
            table = nullptr;
            capacity = 0;
        } else if (getFullFactor() == REDUCTION_COEFFICIENT) {
            // Table has to be reduced after removal
            auto *tmpTable = new T[capacity / ENLARGEMENT_COEFFICIENT];
            for (int i = 0; i < size - 1; ++i) {
                tmpTable[i] = table[i];
            }
            delete[] table;
            table = tmpTable;
            capacity /= ENLARGEMENT_COEFFICIENT;
        }
        --size;
    }

    // Linear search for value in the table
    // Returns VALUE_NOT_FOUND if value is not in the table
    // Otherwise returns value's index
    int search(const T &value) const {
        int index = VALUE_NOT_FOUND;

        // Perform linear search on the table
        for (int i = 0; i < size; ++i) {
            if (table[i] == value) {
                index = i;
                break;
            }
        }
        return index;
    }

    // For accessing table's elements
    T &operator[](int index) {
        if (index >= size || index < 0) {
            throw std::out_of_range("operator[]() failed: index out of bounds");
        }
        return table[index];
    }

    // For accessing table's elements
    T &operator[](int index) const {
        if (index >= size || index < 0) {
            throw std::out_of_range("operator[]() failed: index out of bounds");
        }
        return table[index];
    }

    bool operator==(const Table<T> &otherTable) const {
        if (this->getSize() != otherTable.getSize()) {
            return false;
        }
        for (int i = 0; i < this->size; ++i) {
            if ((*this)[i] != otherTable[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Table<T> &otherTable) const {
        return !(*this == otherTable);
    }

    [[nodiscard]] int getSize() const {
        return size;
    }

    [[nodiscard]] int getCapacity() const {
        return capacity;
    }

    // Returned by search() if value was not found
    static const int VALUE_NOT_FOUND = -1;

private:

    // Used to determine if the table should be enlarged
    static const int ENLARGEMENT_COEFFICIENT = 2;

    // Used to determine if the table should be reduced
    constexpr static const double REDUCTION_COEFFICIENT = 0.25;

    // Numbers of elements in the table
    int size;

    // Numbers of possible elements to bo hold without enlarging the table
    int capacity;

    // First element's pointer
    T *table;

    // Calculates full factor (see implementation)
    [[nodiscard]] double getFullFactor() const {
        if (capacity == 0) {
            return 1;
        } else {
            return static_cast<double>(size) / capacity;
        }
    }
};

#endif //PEA_P1_TABLE_H
