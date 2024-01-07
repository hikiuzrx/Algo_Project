#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "raylib.h"
#include "linked_list/linked_list.h" // Header for linked list functionalities
#include "design/layout_constants.h" // Header for UI-related constants
#include "design/ui.h"               // Header for UI-related functions
#include "design/colors.h"           // Header for Colors
                                     // Main function
int main(void)
{
    const int screenWidth = 1000; // Setting the width of the application window
    const int screenHeight = 800; // Setting the height of the application window
    Node *head = NULL;            // Initializing the linked list head pointer to NULL
    Node **steps = NULL;          // Initializing a pointer to an array of Node pointers for sorting steps
    int stepCount = 0;            // Initializing the count for sorting steps to zero

    // Initializing the window and UI elements
    InitWindow(screenWidth, screenHeight, "Doubly Linked List Visualizer");
    IsWindowResized(); // Checks if the window has been resized by the user. This function returns true if the window has been resized, otherwise false.

    MaximizeWindow(); // Maximizes the window to the screen size. This function ensures the window occupies the maximum available space on the screen.

    // Creating the user menu and adding buttons
    Menu userMenu;
    initializeMenu(&userMenu, screenWidth, screenHeight);
    addButtonToMenu(&userMenu, "Add at Start", BUTTON_BASE_COLOR, BUTTON_HOVER_COLOR, BUTTON_PRESSED_COLOR, BUTTON_TEXT_COLOR);
    addButtonToMenu(&userMenu, "Add at End", BUTTON_BASE_COLOR, BUTTON_HOVER_COLOR, BUTTON_PRESSED_COLOR, BUTTON_TEXT_COLOR);
    addButtonToMenu(&userMenu, "Add at Position", BUTTON_BASE_COLOR, BUTTON_HOVER_COLOR, BUTTON_PRESSED_COLOR, BUTTON_TEXT_COLOR);
    addButtonToMenu(&userMenu, "Delete", BUTTON_BASE_COLOR, BUTTON_HOVER_COLOR, BUTTON_PRESSED_COLOR, BUTTON_TEXT_COLOR);
    addButtonToMenu(&userMenu, "Sort", BUTTON_BASE_COLOR, BUTTON_HOVER_COLOR, BUTTON_PRESSED_COLOR, BUTTON_TEXT_COLOR);

    int currentStep = 0;           // Keeps track of the current step during sorting visualization
    bool sortingCompleted = false; // Indicates whether the sorting process has been completed
    bool resetNeeded = false;      // Signals the need for a list reset (deletion) due to user action
    bool sortPressed = false;      // Indicates whether the "Sort" button has been pressed

    return 0;
}
                                     