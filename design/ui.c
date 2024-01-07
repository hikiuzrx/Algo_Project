#include "ui.h"
#include "colors.h"
#include "layout_constants.h"
#include <stdlib.h>
#include <stdio.h>

// Function implementations for UI operations...
// Initializes the menu structure
void initializeMenu(Menu *menu, int screenWidth, int screenHeight)
{
    int menuWidth = BUTTON_WIDTH + 2 * MENU_MARGIN;
    int menuHeight = (BUTTON_HEIGHT + BUTTON_SPACING) * MAX_BUTTONS + 2 * MENU_MARGIN;

    menu->rect = (Rectangle){screenWidth - menuWidth, screenHeight - menuHeight, menuWidth, menuHeight};
    menu->buttonCount = 0;
    menu->baseColor = DARKBLUE;
    menu->borderColor = SKYBLUE;
    menu->visible = true;
}

