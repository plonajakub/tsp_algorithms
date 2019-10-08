#include "MenuItem.h"


MenuItem::MenuItem() : operationType(), operationName(""), nextFreeMenuOption(0) {
}

MenuItem::MenuItem(MenuItem::OperationType operationType, const std::string &operationName) :
        operationType(operationType), operationName(operationName), nextFreeMenuOption(0) {
}

void MenuItem::addMenuOption(const MenuItem::MenuOption &menuOption) {
    if (nextFreeMenuOption == MAX_OPTIONS_QUANTITY) {
        throw std::out_of_range("MenuItem option's limit reached");
    }
    menuOptions[nextFreeMenuOption] = menuOption;
    ++nextFreeMenuOption;
}

MenuItem::MenuOption &MenuItem::getMenuOption(const std::string &optionID) {
    for (auto &option : menuOptions) {
        if (option.ID == optionID) {
            return option;
        }
    }
    throw std::invalid_argument("No such menuOperation");
}

MenuItem::allMenuOptions MenuItem::getMenuOptions() {
    return menuOptions;
}

int MenuItem::getMenuOptionsSize() {
    return nextFreeMenuOption;
}
