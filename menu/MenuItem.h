#ifndef PEA_P1_MENUITEM_H
#define PEA_P1_MENUITEM_H

#include <string>
#include <stdexcept>

#define MAX_OPTIONS_QUANTITY 10


class MenuItem {
public:

    enum OperationType {
        SUBMENU, FUNCTION
    };

    // Type of MenuItem
    OperationType operationType;

    // Name of MenuItem
    std::string operationName;

    class MenuOption {
    public:
        std::string ID;
        std::string description;
    };

    MenuItem();

    // Standard constructor
    MenuItem(OperationType operationType, const std::string &operationName);

    void addMenuOption(const MenuOption &menuOption);

    MenuOption &getMenuOption(const std::string &optionID);

    using allMenuOptions = MenuOption(&)[MAX_OPTIONS_QUANTITY];

    allMenuOptions getMenuOptions();

    int getMenuOptionsSize();

private:
    int nextFreeMenuOption;

    // Holds menu options
    MenuOption menuOptions[MAX_OPTIONS_QUANTITY];
};


#endif //PEA_P1_MENUITEM_H
