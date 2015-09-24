#include "sketchbook.h"

// NOTES
//- Try deflection technique for paddle bounce-back from "JavaScript Pong" (http://codeincomplete.com/posts/2011/5/14/javascript_pong/)

#define BALL_RADIUS 7
#define PADDLE_Y (HEIGHT - 100)  // this is the top offset of the paddle
#define PADDLE_WIDTH 100
#define PADDLE_HEIGHT 10
#define BRICK_OFFSET_X 100
#define BRICK_OFFSET_Y 100
#define BRICK_WIDTH 60
#define BRICK_HEIGHT 20
#define BRICK_COUNT_X 10
#define BRICK_COUNT_Y 5

float ball_x, ball_y;
float ball_vx, ball_vy;  // velocity of the ball; vx: positive number means to the right; vy: positive number means downwards
unsigned int paddle_x;   // this variable determines the left offset of the paddle

short last_brick_pos_x;  // the index of the last calulated brick position the ball resides.
short last_brick_pos_y;  // Example: (-1, 2) would mean that the ball was a little left of left-most brick and in the height of the third brick from the top

unsigned int bricks[BRICK_COUNT_Y][BRICK_COUNT_X];  // if set to true, we consider the stone to be on

void setup() {
  // initialize ball and velocity
  ball_x = WIDTH / 2;
  ball_y = PADDLE_Y - 20;
  ball_vx = 2.5;
  ball_vy = -3.5;

  // initialize bricks
  for (int j = 0; j < BRICK_COUNT_Y; j++) {
    for (int i = 0; i < BRICK_COUNT_X; i++) {
      bricks[j][i] = 1;
    }
  }
}

void draw() {
  // move the paddle according to mouse position
  if (mouse_x() < WIDTH - PADDLE_WIDTH) {  // check so the paddle does not go over on the right side
    paddle_x = mouse_x();
  } else {
    paddle_x = WIDTH - PADDLE_WIDTH;
  }
  // move the ball
  ball_x += ball_vx;
  ball_y += ball_vy;

  // handle collisions with walls
  if ((ball_x <= 0) || (ball_x >= WIDTH)) {  // left, right
    ball_vx = -ball_vx;
  }
  if (ball_y <= 0) {  // top
    ball_vy = -ball_vy;
  }
  if (ball_y >= PADDLE_Y) {                                               // oh oh, ball is at the height of the paddle
    if ((ball_x >= paddle_x) && (ball_x <= (paddle_x + PADDLE_WIDTH))) {  // the paddle was hit
      // simple version: ball_vy = -ball_vy;
      // complicated version: adjust the ball velocity depending on where the paddle was hit
      float paddle_hit_x =
          (ball_x - PADDLE_WIDTH / 2 - paddle_x) / (float)PADDLE_WIDTH;  // calculate where the paddle was hit: -0.5 means on most left, 0.0 right in the middle, and 0.5 on the right edge
      // calculate the angle of the ball
      float total_velocity = sqrt(ball_vx * ball_vx + ball_vy * ball_vy);
      float v_angle = acos(ball_vx / total_velocity);  // cos(a) = paddle_vx / total_velocity;
      // v_angle == PI/2 means straigt up, PI or 0 means horizontal velocity
      v_angle = v_angle + -fabs(M_PI_2 - (v_angle - M_PI_2)) * paddle_hit_x;  // adjust the angle depending on where the paddle was hit
      ball_vx = total_velocity * cos(v_angle);
      ball_vy = -total_velocity * sin(v_angle);
    } else {  // paddle missed... GAME OVER!
      fill(255, 0, 0);
      text(WIDTH / 2 - 100, HEIGHT / 2, "Game Over!");
      stop();
    }
  }

  // handle collision with bricks
  short brick_pos_x = (ball_x - BRICK_OFFSET_X) / BRICK_WIDTH;   // calculate which brick the ball is in
  short brick_pos_y = (ball_y - BRICK_OFFSET_Y) / BRICK_HEIGHT;  // if negative or too large, we know that it is not "in" a brick
  if ((brick_pos_x == 0) && (ball_x - BRICK_OFFSET_X < 0)) {  // workaround: usually if the ball is just left of a brick, brick_pos_x would round down and hence point to the left brick. In the case of
                                                              // the brick just left of the left-most, this behavior changes. The calculation will round up (e.g. -1/2 == 0). This causes brick_pos_x to
                                                              // be higher than expected and the brick right of the current position is removed even though it was not hit (yet).
    brick_pos_x = -1;
  }
  if ((brick_pos_y == 0) && (ball_y - BRICK_OFFSET_Y < 0)) {
    brick_pos_y = -1;
  }
  if ((brick_pos_x >= 0) && (brick_pos_x < BRICK_COUNT_X) && (brick_pos_y >= 0) && (brick_pos_y < BRICK_COUNT_Y)) {  // do we have a valid brick index?
    if (bricks[brick_pos_y][brick_pos_x]) {
      bricks[brick_pos_y][brick_pos_x] = 0;
      // change the balls velocity according to which side was hit
      // we use the calulated brick position from the last iteration
      if (last_brick_pos_x - brick_pos_x != 0) {
        ball_vx = -ball_vx;
      }
      if (last_brick_pos_y - brick_pos_y != 0) {
        ball_vy = -ball_vy;
      }
    }
  }
  last_brick_pos_x = brick_pos_x;
  last_brick_pos_y = brick_pos_y;

  // check if all bricks are gone
  int sum = 0;
  for (int j = 0; j < BRICK_COUNT_Y; j++) {
    for (int i = 0; i < BRICK_COUNT_X; i++) {
      sum += bricks[j][i];
    }
  }
  if (sum == 0) {  // game won!
    fill(0, 255, 0);
    text(WIDTH / 2 - 100, HEIGHT / 2, "You Won!");
    stop();
  }

  // draw bricks
  for (int j = 0; j < BRICK_COUNT_Y; j++) {
    for (int i = 0; i < BRICK_COUNT_X; i++) {
      if (bricks[j][i]) {
        unsigned int x = BRICK_OFFSET_X + i * BRICK_WIDTH;
        unsigned int y = BRICK_OFFSET_Y + j * BRICK_HEIGHT;
        rectangle(x, y, x + BRICK_WIDTH + 1, y + BRICK_HEIGHT + 1);
      }
    }
  }

  // draw paddle and ball
  circle(ball_x, ball_y, BALL_RADIUS);
  rectangle(paddle_x, PADDLE_Y, paddle_x + PADDLE_WIDTH, PADDLE_Y + PADDLE_HEIGHT);
}
