#ifndef PEA_P1_CONSOLEMENU_H
#define PEA_P1_CONSOLEMENU_H

#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <limits>

#include "MenuItem.h"
#include "../structures/graphs/IGraph.h"
#include "../structures/graphs/ListGraph.h"

using std::cout;
using std::endl;
using std::cin;
using std::cerr;

#define MAX_OPERATIONS_QUANTITY 100

class ConsoleMenu {
public:
    ConsoleMenu();

    ~ConsoleMenu() = default;

    void start(const std::string &menuCode = "");

private:

    class MenuOperation {
    public:
        // Describes series of opened MenuItems
        std::string ID;

        // MenuItem for chosen series above
        MenuItem menuItem;
    };

    // Holds all menu operations
    MenuOperation menuOperations[MAX_OPERATIONS_QUANTITY];

    int nextFreeMenuOperation;

    void addMenuOperation(const MenuOperation &menuOperation);

    MenuOperation &getMenuOperation(const std::string &operationID);

    enum Operation {
        FAILURE, SUCCESS
    };

    enum ProgramState {
        RUNNING, RETURN, EXIT
    };

    void prepareMenuOperations();

    void printMenuOptions(const std::string &menuCode);

    int getMenuControlVariable(const std::string &menuCode);

    ProgramState chooseMenuOperation(const std::string &menuCode, int menuControlVariable);

    // Data
    // -- empty--

};

#endif //PEA_P1_CONSOLEMENU_H
