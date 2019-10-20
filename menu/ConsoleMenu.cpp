#include "ConsoleMenu.h"


ConsoleMenu::ConsoleMenu() : nextFreeMenuOperation(0) {
    prepareMenuOperations();
    tspInstance = nullptr;
}

ConsoleMenu::~ConsoleMenu() {
    delete tspInstance;
}

void ConsoleMenu::addMenuOperation(const ConsoleMenu::MenuOperation &menuOperation) {
    if (nextFreeMenuOperation == MAX_OPERATIONS_QUANTITY) {
        throw std::out_of_range("ConsoleMenu operation's limit reached");
    }
    menuOperations[nextFreeMenuOperation] = menuOperation;
    ++nextFreeMenuOperation;
}

void ConsoleMenu::start(const std::string &menuCode) {
    int menuControlVariable;
    ProgramState ps = ProgramState::RUNNING;
    while (ps == ProgramState::RUNNING) {
        cout << std::string(70, '#') << endl << endl;
        cout << this->getMenuOperation(menuCode).menuItem.operationName << ":" << endl;
        printMenuOptions(menuCode);
        menuControlVariable = getMenuControlVariable(menuCode);
        ps = chooseMenuOperation(menuCode, menuControlVariable);
    }
}

void ConsoleMenu::printMenuOptions(const std::string &menuCode) {
    MenuItem &menuItem = this->getMenuOperation(menuCode).menuItem;
    MenuItem::allMenuOptions menuOptions = menuItem.getMenuOptions();
    for (int i = 0; i < menuItem.getMenuOptionsSize(); ++i) {
        cout << menuOptions[i].ID << ". " << menuOptions[i].description << endl;
    }
    if (menuCode.empty()) {
        cout << "0. Exit" << endl;
    }
    if (!menuCode.empty()) {
        cout << "0. Return" << endl;
    }
}

ConsoleMenu::MenuOperation &ConsoleMenu::getMenuOperation(const std::string &operationID) {
    for (auto &operation : menuOperations) {
        if (operation.ID == operationID) {
            return operation;
        }
    }
    throw std::invalid_argument("No such MenuOperation");
}

int ConsoleMenu::getMenuControlVariable(const std::string &menuCode) {
    MenuOperation menuOperation = this->getMenuOperation(menuCode);
    int menuControlVariable = -1;
    Operation status = Operation::FAILURE;
    cout << endl << "Choose operation:";
    while (status == Operation::FAILURE) {
        try {
            cin >> menuControlVariable;
            if (menuControlVariable < 0 || menuControlVariable > menuOperation.menuItem.getMenuOptionsSize()) {
                cout << "Wrong operation's ID. Try again: ";
                continue;
            }
            status = Operation::SUCCESS;
        } catch (const std::ios_base::failure &e) {
            cout << "Wrong input. Try again: ";
            cin.ignore(std::numeric_limits<std::streamsize>::max());
            continue;
        }
    }
    return menuControlVariable;
}

ConsoleMenu::ProgramState ConsoleMenu::chooseMenuOperation(const std::string &menuCode, int menuControlVariable) {
    if (menuControlVariable == 0 && !menuCode.empty()) {
        cout << "--- RETURN ---" << endl;
        return ProgramState::RETURN;
    }
    if (menuControlVariable == 0 && menuCode.empty()) {
        cout << "--- EXIT ---" << endl;
        return ProgramState::EXIT;
    }
    std::string operationCode = menuCode + std::to_string(menuControlVariable);

    if (this->getMenuOperation(operationCode).menuItem.operationType == MenuItem::OperationType::SUBMENU) {
        this->start(operationCode);
        /////////////////////////////////////////////////////////////////
        //// Operations
        /////////////////////////////////////////////////////////////////
    } else if (operationCode == "1") {
        std::string path, instanceName;

        cout << "Enter path to the instance:";
        cin >> path;

        IGraph *tmpTSPInstance = tspInstance;
        try {
            instanceName = TSPUtils::loadTSPInstance(&tspInstance, path);
        } catch (const std::invalid_argument &e) {
            cout << e.what() << endl;
            return ProgramState::RUNNING;
        }
        delete tmpTSPInstance;

        cout << "Instance \"" + instanceName + "\" has been loaded!" << endl;
        cout << tspInstance->toString() << endl;

    } else if (operationCode == "2") {
        if (tspInstance == nullptr) {
            cout << "No instance of TSP has been loaded. Load an instance first." << endl;
            return ProgramState::RUNNING;
        }
        DoublyLinkedList<int> selectedPermutation;
        int input;
        cout << "Enter permutation in form [x y z] without braces: " << endl;
        for (int v = 0; v < tspInstance->getVertexCount(); ++v) {
            cin >> input;
            selectedPermutation.insertAtEnd(input);
        }
        cout << "Target function for permutation: " << selectedPermutation << " has value: " <<
             std::to_string(TSPUtils::calculateTargetFunctionValue(tspInstance, selectedPermutation)) << std::endl;

    } else if (operationCode == "3") {
        if (tspInstance == nullptr) {
            cout << "No instance of TSP has been loaded. Load an instance first." << endl;
            return ProgramState::RUNNING;
        }
        cout << endl << "----- Loaded instance of TSP -----";
        cout << tspInstance->toString() << endl;

    }
    return ProgramState::RUNNING;
}

void ConsoleMenu::prepareMenuOperations() {
    MenuOperation menuOperation;
    MenuItem menuItem;
    MenuItem::MenuOption menuOption;

    ////////////////////////////////////////////////////////////////////
    // Main menu
    ////////////////////////////////////////////////////////////////////
    menuOperation.ID = "";
    menuItem = MenuItem(MenuItem::OperationType::SUBMENU, "Main menu");

    menuOption.ID = "1";
    menuOption.description = "Load an instance of (A)TSP";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "2";
    menuOption.description = "Calculate the target function for a cycle";
    menuItem.addMenuOption(menuOption);

    menuOption.ID = "3";
    menuOption.description = "Show loaded instance of TSP";
    menuItem.addMenuOption(menuOption);

    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    ////////////////////////////////////////////////////////////////////
    // Operations
    ////////////////////////////////////////////////////////////////////
    menuOperation.ID = "1";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Load an instance of (A)TSP");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    menuOperation.ID = "2";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Calculate the target function for a cycle");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);

    menuOperation.ID = "3";
    menuItem = MenuItem(MenuItem::OperationType::FUNCTION, "Show loaded instance of TSP");
    menuOperation.menuItem = menuItem;
    this->addMenuOperation(menuOperation);
}
