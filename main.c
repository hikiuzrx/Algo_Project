#include "libraries/raylib.h"
#include <stdlib.h>
#include <stdio.h>
#include "libraries/node.h"
#include "libraries/Logic_functions.h"
#include "libraries/Animation_functions.h"
#include "libraries/defining.h"
#include "libraries/raymath.h"
#include <math.h>
int main(void) {
    // Initialization
    InitWindow(800, 600, "Raylib GUI Example");

    Node* head = NULL;
    int numElements = 5;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Update

        // Draw
        ClearBackground(RAYWHITE);
        BeginDrawing();

        // Draw the linked list
        drawList(head, numElements);

        EndDrawing();

        // Delay for animation (adjust the value as needed)
        WaitTime(500);

        // Generate random values during animation
        if (numElements > 0) {
            int randomValue = GetRandomValue(-99, 99);
            Create_Node(&head, randomValue);
            numElements--;
        }
    }

    // De-Initialization
    // Free memory allocated for the linked list
    free(head);

    CloseWindow();

    return 0;
}