#include "raylib.h"
#include <unistd.h>
   
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

Color Aquamarine = {.r=127, .g=255, .b=212, .a=255};
Color Cyan = {.r=0, .g=255  , .b=255, .a=255};

static int paddle_x = 10;
static int paddle_y = 180;
static int paddle_y1 = 180;

static const int ball_radius = 20;
int cord_y = 300;
int cord_x = 400;
static int ball_speed_x = 5;
static int ball_speed_y = 5;

void Draw_moving_ball() {
       
    cord_x += ball_speed_x;
    cord_y += ball_speed_y;

    if (cord_x + ball_radius > SCREEN_WIDTH ||  cord_x - ball_radius <= 0) {
        ball_speed_x *= -1;
    }
    if (cord_y + ball_radius > SCREEN_HEIGHT || cord_y - ball_radius <= 0) {
        ball_speed_y *= -1;
    }

   // DrawRectangle(399, 300, 100, 100, RED);
    DrawCircle(cord_x , cord_y, ball_radius, YELLOW);
}

int main() {
   
   InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib.5.0");
   SetTargetFPS(60);
     while(!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);  
    DrawRectangle(SCREEN_WIDTH / 2, 0, SCREEN_WIDTH/ 2,  SCREEN_HEIGHT, Aquamarine);
    DrawRectangle(0, 0, SCREEN_WIDTH / 2,SCREEN_HEIGHT, Cyan);
    DrawCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 50, WHITE);
    Draw_moving_ball();
   
    if((IsKeyPressedRepeat(KEY_S) || IsKeyPressed(KEY_S)) && paddle_y > 0) {
        paddle_y -= 30;
    }

    if((IsKeyPressed(KEY_X) || IsKeyPressedRepeat(KEY_X)) && paddle_y <= SCREEN_HEIGHT - 210) {
        paddle_y += 30;
    }

    if((IsKeyPressedRepeat(KEY_UP) || IsKeyPressed(KEY_UP)) && paddle_y1 > 0) {
        paddle_y1 -= 30;
    }

    if((IsKeyPressed(KEY_DOWN) || IsKeyPressedRepeat(KEY_DOWN)) && paddle_y1 <= SCREEN_HEIGHT - 210) {
        paddle_y1 += 30;
    }

    DrawRectangle(paddle_x, paddle_y, 10, 200, WHITE);
    DrawRectangle(SCREEN_WIDTH - 20 , paddle_y1, 10, 200, WHITE);
    EndDrawing();
  } 
  CloseWindow();
}
