#include "raylib.h"
#include "node.h"
#include "defining.h"
void drawList(Node* current){
     DrawRectangle(current->data * 60, SCREEN_HEIGHT / 2, NODE_WIDTH, NODE_HEIGHT, WHITE);
        DrawRectangleLines(current->data * 60, SCREEN_HEIGHT / 2, NODE_WIDTH, NODE_HEIGHT, BLACK);
        DrawText(TextFormat("%d", current->data), current->data * 60 + NODE_WIDTH / 2 - 10, SCREEN_HEIGHT / 2 + NODE_HEIGHT / 2 - 10, 20, BLACK);
}