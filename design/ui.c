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
// Adds a button to the menu
void addButtonToMenu(Menu *menu, const char *label, Color baseColor, Color hoverColor, Color pressedColor, Color textColor)
{
    int posX = menu->rect.x + MENU_MARGIN;
    int posY = menu->rect.y + MENU_MARGIN + menu->buttonCount * (BUTTON_HEIGHT + BUTTON_SPACING);

    menu->buttons[menu->buttonCount++] = (Button){{posX, posY, BUTTON_WIDTH, BUTTON_HEIGHT}, label, baseColor, hoverColor, pressedColor, textColor, false};
}

// Draws the menu on the screen
void drawMenu(Menu *menu)
{
    DrawRectangleRec(menu->rect, MENU_BASE_COLOR);
    DrawRectangleLinesEx(menu->rect, 2, MENU_BORDER_COLOR);

    for (int i = 0; i < menu->buttonCount; ++i)
    {
        Button *btn = &menu->buttons[i];

        if (CheckCollisionPointRec(GetMousePosition(), btn->rect))
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                btn->state = !btn->state;
            }
            DrawRectangleRec(btn->rect, btn->pressedColor);
        }
        else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            btn->state = false;
            DrawRectangleRec(btn->rect, btn->baseColor);
        }
        else if (btn->state)
        {
            DrawRectangleRec(btn->rect, btn->pressedColor);
        }
        else
        {
            DrawRectangleRec(btn->rect, btn->baseColor);
        }

        DrawRectangleLinesEx(btn->rect, 2, MENU_BORDER_COLOR);

        DrawText(btn->label,
                 (int)(btn->rect.x + btn->rect.width / 2 - MeasureText(btn->label, 20) / 2),
                 (int)(btn->rect.y + btn->rect.height / 2 - 10),
                 20,
                 BUTTON_TEXT_COLOR);
    }
}

// Draws buttons based on the provided button array and count
void drawButtons(Button buttons[], int buttonCount)
{
    for (int i = 0; i < buttonCount; ++i)
    {
        if (CheckCollisionPointRec(GetMousePosition(), buttons[i].rect))
        {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            {
                buttons[i].state = !buttons[i].state;
            }
            DrawRectangleRec(buttons[i].rect, buttons[i].pressedColor);
        }
        else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            buttons[i].state = false;
            DrawRectangleRec(buttons[i].rect, buttons[i].baseColor);
        }
        else if (buttons[i].state)
        {
            DrawRectangleRec(buttons[i].rect, buttons[i].pressedColor);
        }
        else
        {
            DrawRectangleRec(buttons[i].rect, buttons[i].baseColor);
        }

        DrawRectangleLinesEx(buttons[i].rect, 4, WHITE);

        DrawText(buttons[i].label,
                 (int)(buttons[i].rect.x + buttons[i].rect.width / 2 - MeasureText(buttons[i].label, 20) / 2),
                 (int)(buttons[i].rect.y + buttons[i].rect.height / 2 - 10),
                 20,
                 buttons[i].textColor);
    }
}
