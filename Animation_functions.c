#include "libraries/raylib.h"
#include "libraries/node.h"
#include "libraries/defining.h"
#include <math.h>
void drawNode(Node* current, int index, int numElements) {
    // Calculate x-coordinate based on index, numElements, and center of the window
    float centerX = GetScreenWidth() / 2.0f;
    float spacing = RECT_WIDTH;

    // Adjust x-coordinate based on the width of the rectangle
    float x = centerX - (numElements - 1) / 2.0f * spacing + index * spacing - RECT_WIDTH / 2.0f;

    // Calculate y-coordinate to position elements at the vertical center
    float y = GetScreenHeight() / 2.0f - 25;

    // Draw Next Pointer Rectangle
    DrawRectangle(x + (DATA_RECT_WIDTH - NEXT_RECT_WIDTH) / 2, y - RECT_HEIGHT_FACTOR * POINTER_RECT_HEIGHT, NEXT_RECT_WIDTH, POINTER_RECT_HEIGHT, current->next ? GREEN : WHITE);
    DrawText("Next", x + (DATA_RECT_WIDTH - NEXT_RECT_WIDTH) / 2 + 2, y - RECT_HEIGHT_FACTOR * POINTER_RECT_HEIGHT + 5, 10, BLACK);

    // Draw Previous Pointer Rectangle
    DrawRectangle(x + (DATA_RECT_WIDTH - NEXT_RECT_WIDTH) / 2, y + RECT_HEIGHT_FACTOR * POINTER_RECT_HEIGHT, NEXT_RECT_WIDTH, POINTER_RECT_HEIGHT, current->prev ? RED : WHITE);
    DrawText("Prev", x + (DATA_RECT_WIDTH - NEXT_RECT_WIDTH) / 2 + 2, y + RECT_HEIGHT_FACTOR * POINTER_RECT_HEIGHT + 5, 10, BLACK);

    // Draw Data Rectangle
    int rectHeight = abs(current->data) * RECT_HEIGHT_FACTOR;
    Color rectColor = (current->data >= 0) ? BLUE : RED;
    DrawRectangle(x, y - rectHeight / 2, DATA_RECT_WIDTH, rectHeight, rectColor);

    // Draw Text
    DrawText(TextFormat("%d", current->data), x + DATA_RECT_WIDTH / 2 - MeasureText(TextFormat("%d", current->data), 20) / 2, y, 20, BLACK);

    // Draw links
    if (current->next) {
        // Link to next element
        float nextX = centerX - (numElements - 1) / 2.0f * spacing + (index + 1) * spacing - RECT_WIDTH / 2.0f;
        DrawLine(x + DATA_RECT_WIDTH, y, nextX, y, BLACK);
    }

    if (current->prev) {
        // Link to previous element
        float prevX = centerX - (numElements - 1) / 2.0f * spacing + (index - 1) * spacing - RECT_WIDTH / 2.0f + DATA_RECT_WIDTH;
        DrawLine(x, y, prevX, y, BLACK);
    }
}
// Function to draw the linked list
void drawList(Node* head, int numElements) {
    Node* current = head;
    int index = 0;
    while (current) {
        drawNode(current, index, numElements);
        current = current->next;
        index++;
    }
}