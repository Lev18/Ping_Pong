#include "raylib.h"
#include <unistd.h>



#define LEFT_PADDLE  1
#define RIGHT_PADDLE 2
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

Color Aquamarine = {.r=127, .g=255, .b=212, .a=255};
Color Cyan = {.r=0, .g=255  , .b=255, .a=255};

typedef struct {
    int x1;
    int y1;
    int x2;
    int y2;
}paddle_coord;

static int paddle_x = 10;
static int paddle_y = 180;
static int paddle_y1 = 180;
static int player1_score = 0;
static int player2_score = 0;


static const int ball_radius = 20;
int cord_y = 300;
int cord_x = 400;
static int ball_speed_x = 5;
static int ball_speed_y = 5;


int is_ball_touched_to_pannel (int pannel) {
    if (pannel == RIGHT_PADDLE) {
        if ((cord_x + ball_radius >= SCREEN_WIDTH - 20) &&
           paddle_y1 <= cord_y && cord_y <= paddle_y1 + 200) {
           return 1;
        }
        else {
            return 0;
        }
    }

    if (pannel == LEFT_PADDLE) {
        if ((cord_x - ball_radius < paddle_x + 10) &&
            paddle_y <= cord_y && cord_y <= paddle_y + 200) {
            return 1;
        }
        else {
            return 0;
        }

    }
    else {
     return 0;
    }
}


void reset_game() {
    cord_x = 300;
    cord_y = 400;
}

void Draw_moving_ball() {
       
    cord_x += ball_speed_x;
    cord_y += ball_speed_y;

    if (is_ball_touched_to_pannel(RIGHT_PADDLE)) {
       
        ball_speed_y *= -1;
        ball_speed_x *= -1;
    }

   if (is_ball_touched_to_pannel(LEFT_PADDLE)) {
        ball_speed_y *= -1;
        ball_speed_x *= -1;
    }


    if (cord_x + ball_radius > SCREEN_WIDTH) {
       
     /*   if (is_ball_touched_to_pannel()) {
            ball_speed_x *= -1;
        }*/
         ++player2_score;
        reset_game();
    }

    if (cord_x - ball_radius <= 0) {
       ++player1_score;
       reset_game();
    }

    if (cord_y + ball_radius > SCREEN_HEIGHT || cord_y - ball_radius <= 0) { 
       ball_speed_y *= -1;
    }

   // DrawRectangle(399, 300, 100, 100, RED);
  // printf("%d\n,%d\n", cord_x, cord_y);
    DrawCircle(cord_x , cord_y, ball_radius, YELLOW);
   // reset_game();
}

void DrawMovablePannel() {
    if((IsKeyPressedRepeat(KEY_S) || IsKeyPressed(KEY_S)) && paddle_y > 0) {
        paddle_y -= 30;
    }

    if((IsKeyPressed(KEY_X) || IsKeyPressedRepeat(KEY_X)) && paddle_y <= SCREEN_HEIGHT - 200) {
        paddle_y += 30;
    }

    if((IsKeyPressedRepeat(KEY_UP) || IsKeyPressed(KEY_UP)) && paddle_y1 > 0) {
        paddle_y1 -= 30;
    }

    if((IsKeyPressed(KEY_DOWN) || IsKeyPressedRepeat(KEY_DOWN)) && paddle_y1 <= SCREEN_HEIGHT - 200) {
        paddle_y1 += 30;
    }

    DrawRectangle(paddle_x, paddle_y, 10, 200, WHITE);
    DrawRectangle(SCREEN_WIDTH - 20 , paddle_y1, 10, 200, WHITE);
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
    DrawMovablePannel(); 
 
    DrawText(TextFormat("%d", player1_score), 50, 15, 50, WHITE);
    DrawText(TextFormat("%d", player2_score), SCREEN_WIDTH - 70, 15, 50, WHITE);
    EndDrawing();
  } 
  CloseWindow();
}
