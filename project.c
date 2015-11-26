#include "sketchbook.h"

#define ACTIONS_CAPACITY 500 // maximum number of actions which can be processed
#define SPACE_WIDTH 20 // width of the spaces which can be occupied by boxes
#define SPACE_HEIGHT 15
#define BOX_SIZE 30   // pixel size of a box (size = x = y)
#define BOX_SPACING 3 // pixel between boxes
#define OFFSET_X 70   // pixels to offset from the left
#define OFFSET_Y 100
#define BAR_HDISTANCE 50 // pixel, top bar protrude left and right
#define BAR_VDISTANCE 50 // pixel, top bar margin to the spaces area
#define BAR_HEIGHT 5     // pixel height of the bar
#define ROPE_WIDTH 3
#define TRANSITION_FRAME_COUNT 15

typedef enum { LEFT, RIGHT, UP, DOWN, GRAB, DROP } action_t;

action_t actions[ACTIONS_CAPACITY];
bool space[SPACE_HEIGHT][SPACE_WIDTH]; // does this space already have a box?
                                       // note, the bottom line has index 0.
int action_count; // how many actions have been added to actions
int action_index; // the index of the action currently processed
int next_x;       // the position moved towards to (-1..SPACE_WIDTH).
int next_y;       // note that the pick up spot is at (-1, 0)
int current_x;    // the position after the last completly executed action
int current_y;
bool robot_has_box;   // is the arm currently, carrying a box?
int transition_index; // how many frames were already shown for the current
// action. If 0, we have just started with the transition for one action.
// If there it is close to TRANSITION_FRAME_COUNT, we are almost at the next_x
bool was_error;

void instruct(); // this method has to be overridden

void add_action(action_t action) {
  if (action_count >= ACTIONS_CAPACITY) {
    printf("Can not add so many actions. Capacity: %d", ACTIONS_CAPACITY);
    exit(1);
  }
  actions[action_count] = action;
  action_count++;
}

action_t pop_action() {
  action_t result = actions[action_index];
  action_index++;
  return result;
}
bool has_more_actions() { return action_index < action_count; }

void left() { add_action(LEFT); }
void right() { add_action(RIGHT); }
void up() { add_action(UP); }
void down() { add_action(DOWN); }
void grab() { add_action(GRAB); }
void drop() { add_action(DROP); }

void setup() {
  // we do not need to initialize actions, because we will only touch elements
  // up to action_count
  for (int j = 0; j < SPACE_HEIGHT; j++) {
    for (int i = 0; i < SPACE_WIDTH; i++) {
      space[j][i] = false;
    }
  }
  action_count = 0;
  action_index = 0;
  next_x = -1;
  next_y = 0;
  current_x = -1;
  current_y = 0;
  robot_has_box = false;
  was_error = false;
  transition_index = TRANSITION_FRAME_COUNT;
  instruct();
}

void calc_box_screen_coordinates(int x, int y, int *screen_x, int *screen_y) {
  *screen_x = OFFSET_X + x * (BOX_SIZE + BOX_SPACING);
  *screen_y = OFFSET_Y + (SPACE_HEIGHT - y - 1) * (BOX_SIZE + BOX_SPACING);
}

void error(char message[]) {
  stroke(204, 13, 57);
  text(10, 100, message);
  was_error = true;
}

void process_action(action_t action) {
  switch (action) {
  case LEFT:
    if (current_x <= -1)
      error("robot can not go left anymore.");
    next_x = current_x - 1;
    if (space[next_y][next_x] && robot_has_box)
      error("collision.");
    break;
  case RIGHT:
    if (current_x >= SPACE_WIDTH - 1)
      error("robot can not go right anymore.");
    next_x = current_x + 1;
    if (space[next_y][next_x] && robot_has_box)
      error("collision.");
    break;
  case UP:
    if (current_y >= SPACE_HEIGHT - 1)
      error("robot can not go up anymore.");
    next_y = current_y + 1;
    if (space[next_y][next_x] && robot_has_box)
      error("collision.");
    break;
  case DOWN:
    if (current_y <= 0)
      error("robot can not go down anymore.");
    next_y = current_y - 1;
    if (space[next_y][next_x] && robot_has_box)
      error("collision.");
    break;
  case GRAB:
    if (robot_has_box)
      error("robot can only grab one box at a time.");
    if ((current_x != -1) || (current_y != 0))
      error("robot can only grab boxes from the pickup area.");
    robot_has_box = true;
    break;
  case DROP:
    if (!robot_has_box)
      error("robot does not have a box to drop.");
    if (current_x < 0)
      error("robot can not drop a box into the pickup area.");
    if ((current_y > 0) && (!space[current_y-1][current_x]))
      error("robot can only drop boxes on the floor or on top of another box.");
    // TODO check if it is on the floor or a box below
    space[current_y][current_x] = true;
    robot_has_box = false;
    break;
  }
}

void draw() {
  background(51, 51, 51);
  transition_index++;
  if (transition_index >= TRANSITION_FRAME_COUNT) {
    // the transition is done, so let's pop the next action
    if (!has_more_actions()) {
      stroke(97, 160, 98);
      text(300, 200, "done");
      stop();
    } else {
      current_x = next_x;
      current_y = next_y;
      action_t next_action = pop_action();
      process_action(next_action);
      transition_index = 0;
    }
  }
  if (was_error) {
    stop();
    return;
  }

  // draw field
  int x, y;
  no_stroke();
  for (int j = 0; j < SPACE_HEIGHT; j++) {
    for (int i = 0; i < SPACE_WIDTH; i++) {
      if (space[j][i])
        fill(255, 127, 0);
      else
        no_fill();
      calc_box_screen_coordinates(i, j, &x, &y);
      rectangle(x, y, x + BOX_SIZE, y + BOX_SIZE);
    }
  }
  // bar
  no_stroke();
  fill(174, 174, 174);
  rectangle(OFFSET_X - BAR_HDISTANCE, OFFSET_Y - BAR_VDISTANCE - BAR_HEIGHT,
            OFFSET_X + (BOX_SIZE + BOX_SPACING) * SPACE_WIDTH + BAR_HDISTANCE,
            OFFSET_Y - BAR_VDISTANCE);

  // pickup spot
  no_stroke();
  fill(100, 50, 0);
  calc_box_screen_coordinates(-1, 0, &x, &y);
  rectangle(x, y, x + BOX_SIZE, y + BOX_SIZE);

  // rope, claw, box in claw
  int cx, cy, nx, ny; // calculate the current and next screen coordinates
  calc_box_screen_coordinates(current_x, current_y, &cx, &cy);
  calc_box_screen_coordinates(next_x, next_y, &nx, &ny);
  double transition_percentance =
      (double)transition_index / TRANSITION_FRAME_COUNT;
  x = cx * (1.0 - transition_percentance) + nx * transition_percentance;
  y = cy * (1.0 - transition_percentance) + ny * transition_percentance;

  no_stroke(); // rope
  fill(174, 174, 174);
  rectangle(x + BOX_SIZE / 2, OFFSET_Y - BAR_VDISTANCE,
            x + BOX_SIZE / 2 + ROPE_WIDTH, y);
  if (robot_has_box) { // box
    no_stroke();
    fill(255, 127, 0);
    rectangle(x, y, x + BOX_SIZE, y + BOX_SIZE);
  }
  stroke(255, 255, 255); // robot claw position
  fill(100, 100, 100);
  circle(x + BOX_SIZE / 2, y, 5);
}

void instruct() {
  grab();
  right();
  drop();
  left();
  grab();
  up();
  up();
  right();
  down();
  drop();

  // grab();
  // right();
  // right();
  // drop();
  // left();
  // left();
  // grab();
  // up();
  // right();
  // right();
  // drop();
  // left();
  // right();
  // down();
  // left();
  // left();
  // grab();
  // right();
  // right();
}