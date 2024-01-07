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
// Handles button clicks within the menu
void handleButtonClicks(Menu *menu, Node **head, Node ***steps, int *stepCount, bool *sortPressed)
{
    if (!menu->visible)
        return;

    Vector2 mousePosition = GetMousePosition();

    for (int i = 0; i < menu->buttonCount; ++i)
    {
        Button *btn = &menu->buttons[i];

        if (CheckCollisionPointRec(mousePosition, btn->rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            switch (i)
            {
            case 0:
            {
                int value = getInputFromUser("Ajouter au début");
                *head = insertAtBeginning(*head, value);
                break;
            }
            case 1:
            {
                int value = getInputFromUser("Ajoute a la fin");
                *head = insertAtEnd(*head, value);
                break;
            }
            case 2:
            {
                int value = getInputFromUser("Entrer la valeur");
                int position = getInputFromUser("Entrez la position de la valeur");
                *head = insertAtPosition(*head, value, position);
                break;
            }
            case 3:
            {
                int value = getInputFromUser("Entrez élément que vous voulez supprimer");
                deleteNodeWithValue(head, value);
                break;
            }
            case 4:
            {
                *sortPressed = !(*sortPressed);
                if (*sortPressed)
                {
                    int count = 0;
                    Node *temp = *head;
                    while (temp != NULL)
                    {
                        count++;
                        temp = temp->next;
                    }
                    *steps = (Node **)malloc(count * sizeof(Node *));
                    insertionSort(*head, steps, stepCount);
                }
                break;
            }
            default:
                break;
            }
        }
    }
}

// Gets user input from a graphical input box
int getInputFromUser(const char message[50])
{
    bool mouseOnText = false;
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    // Calculate the centered position for the slightly larger node-like box
    Rectangle nodeBox = {screenWidth / 2 - BASE_NODE_WIDTH / 2, screenHeight / 2 - 40, BASE_NODE_WIDTH, 80}; // Adjusted Y position

    int userInput = 0;
    char inputText[MAX_INPUT_LENGTH + 1] = "\0";
    int letterCount = 0;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_ENTER) && letterCount > 0)
        {
            userInput = atoi(inputText);
            break;
        }

        int key = GetKeyPressed();

        if ((key >= 32) && (key <= 125) && (letterCount < MAX_INPUT_LENGTH))
        {
            inputText[letterCount++] = (char)key;
        }
        else if ((key == KEY_BACKSPACE) && (letterCount > 0))
        {
            inputText[--letterCount] = '\0';
        }

        // Adjust node width dynamically based on the input text length
        nodeBox.width = BASE_NODE_WIDTH + MeasureText(inputText, 40); // Base width + length of the text

        mouseOnText = CheckCollisionPointRec(GetMousePosition(), nodeBox);
        SetMouseCursor(mouseOnText ? MOUSE_CURSOR_IBEAM : MOUSE_CURSOR_DEFAULT);

        BeginDrawing();
        ClearBackground(DARKGRAY); // Change the window background color

        // Draw slightly larger node-like box with a gradient fill (modified colors)
        DrawRectangleGradientH(nodeBox.x, nodeBox.y, nodeBox.width, nodeBox.height, SKYBLUE, DARKBLUE); // Horizontal gradient from sky blue to dark blue

        // Draw the input text with a contrasting color
        DrawText(inputText, nodeBox.x + 10, nodeBox.y + 10, 40, Fade(RAYWHITE, 0.8f)); // White-colored text on the gradient box

        // Draw a slightly larger label near the node box to instruct the user
        DrawText("Enter a value:", nodeBox.x - MeasureText("Enter a value:", 40) - LABEL_OFFSET_X, nodeBox.y, 40, Fade(WHITE, 0.8f)); // White-colored label on the dark background

        EndDrawing();
    }

    return userInput;
}
// Displays the linked list on the screen
void displayList(Node *head, int x, int y)
{
    int nodeWidth = 80;
    int nodeHeight = 40;
    int arrowLength = 30;
    int squareSize = 30;

    Node *current = head;
    int nodeIndex = 0;
    int listWidth = 0;

    // Calculate total width of the list
    while (current != NULL)
    {
        listWidth += nodeWidth + arrowLength;
        current = current->next;
    }

    // Calculate starting X position to center the list
    int screenWidth = GetScreenWidth();
    int startX = (screenWidth - listWidth) / 2;

    // Reset current pointer
    current = head;

    while (current != NULL)
    {
        // Draw node rectangle with gradient fill
        Rectangle nodeRect = {startX + nodeIndex * (nodeWidth + arrowLength), y, nodeWidth, nodeHeight};
        DrawRectangleGradientH(nodeRect.x, nodeRect.y, nodeRect.width, nodeRect.height, SKYBLUE, DARKBLUE);
        DrawRectangleLines(nodeRect.x, nodeRect.y, nodeRect.width, nodeRect.height, BLACK);

        // Draw square for node value
        Rectangle square = {nodeRect.x + (nodeRect.width - squareSize) / 2,
                            nodeRect.y + (nodeRect.height - squareSize) / 2,
                            squareSize, squareSize};
        DrawRectangleGradientH(square.x, square.y, square.width, square.height, ORANGE, GOLD);
        DrawRectangleLines(square.x, square.y, square.width, square.height, BLACK);

        // Draw node value inside the square
        char str[20];
        sprintf(str, "%d", current->data);
        DrawText(str, square.x + 7, square.y + 5, 20, BLACK);

        // Draw arrows and lines for doubly linked list
        if (current->prev != NULL)
        {
            // Draw arrow pointing to previous node
            DrawLine(nodeRect.x + nodeRect.width / 2, nodeRect.y + nodeRect.height / 2,
                     nodeRect.x - arrowLength, nodeRect.y + nodeRect.height / 2, BLACK);
            DrawTriangle((Vector2){nodeRect.x - arrowLength + 10, nodeRect.y + 10},
                         (Vector2){nodeRect.x - arrowLength + 10, nodeRect.y + nodeRect.height - 10},
                         (Vector2){nodeRect.x - arrowLength - 10, nodeRect.y + nodeRect.height / 2}, BLACK);

            // Draw line connecting to the previous node
            DrawLine(nodeRect.x, nodeRect.y + nodeRect.height / 2,
                     nodeRect.x - arrowLength, nodeRect.y + nodeRect.height / 2, BLACK);
        }

        if (current->next != NULL)
        {
            // Draw arrow pointing to next node
            DrawLine(nodeRect.x + nodeRect.width, nodeRect.y + nodeRect.height / 2,
                     nodeRect.x + nodeRect.width + arrowLength, nodeRect.y + nodeRect.height / 2, BLACK);
            DrawTriangle((Vector2){nodeRect.x + nodeRect.width + arrowLength - 10, nodeRect.y + 10},
                         (Vector2){nodeRect.x + nodeRect.width + arrowLength - 10, nodeRect.y + nodeRect.height - 10},
                         (Vector2){nodeRect.x + nodeRect.width + arrowLength + 10, nodeRect.y + nodeRect.height / 2}, BLACK);

            // Draw line connecting to the next node
            DrawLine(nodeRect.x + nodeRect.width, nodeRect.y + nodeRect.height / 2,
                     nodeRect.x + nodeRect.width + arrowLength, nodeRect.y + nodeRect.height / 2, BLACK);
        }

        current = current->next;
        nodeIndex++;
    }
}
// Resets the linked list and associated sorting steps
void resetList(Node **head, Node **steps, int stepCount)
{
    // Free allocated memory for the linked list
    while (*head != NULL)
    {
        Node *temp = *head;
        *head = (*head)->next;
        free(temp);
    }

    // Free the steps for sorting
    freeSteps(steps, stepCount);
}
