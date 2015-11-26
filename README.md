# Simple Teaching Robot

_For installation instructions and more, please see the [master branch](https://github.com/motine/sta/tree/master)._

![](sta/imgs/robot.gif)

This branch provides a minimalistic robot simulator which can pick up boxes from the pickup area and move them somewhere.
I am using this simulator to pose problems which then need to be solved with this restricted instruction set:

```c
left();
right();
up();
down();
grab();
drop();
```

## Rules

- Boxes can only be grabbed up from the pickup area (most left, bottom).
- Boxes can only be dropped on the floor or on top of another box.
- If the robot arm is empty it can move freely as long as it stays in bounds (width: 20 by height: 15)
- If the robot arm grabbed a box it can not move through other boxes.