# Robotics
This code is developed for the legendary Robot Igal
https://youtu.be/iGOmnC24BvE

Todo List:
  1. Check why the robot goes to a different yaw (almost 180°) - looks like it depends on the conversion (robot to real)
  2. Check why the route doesn't go straight at the first intersection (and generates two waypoints instead)
  3. Check why the waypoints gets to the MovementManager as (0,0) or nan points
  4. Add yaw change for obstacle avoidence
  5. Check what with the first waypoint (the one that close to the start)
  6. Make GoToPoint try again when he fails to get to the correct point
  7. Check why the Particle's belief doesn't calculates well / at all (maybe something with the previous belief factor)
  8. Clear unimportant console prints and add the relevant ones
  9. Clean unused consts
  10. Add notes to all class files
