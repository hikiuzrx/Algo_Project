#ifndef UI_H
#define UI_H
#include "raylib.h"
#include "../linked_list/linked_list.h"

#define MAX_BUTTONS 5

typedef struct
{
    Rectangle rect;
    const char *label;
    Color baseColor;
    Color hoverColor;
    Color pressedColor;
    Color textColor;
    bool state; // Button state: true - pressed, false - not pressed
} Button;

typedef struct
{
    Rectangle rect;
    Button buttons[MAX_BUTTONS];
    int buttonCount;
    Color baseColor;
    Color borderColor;
    bool visible;
} Menu;

void initializeMenu(Menu *menu, int screenWidth, int screenHeight);
void addButtonToMenu(Menu *menu, const char *label, Color baseColor, Color hoverColor, Color pressedColor, Color textColor);
void drawMenu(Menu *menu);
void drawButtons(Button buttons[], int buttonCount);
void handleButtonClicks(Menu *menu, Node **head, Node ***steps, int *stepCount, bool *sortPressed);
int getInputFromUser(const char message[50]);
void displayList(Node *head, int x, int y);
void resetList(Node **head, Node **steps, int stepCount);

#endif /* UI_H */
