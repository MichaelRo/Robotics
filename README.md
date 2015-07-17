# Robotics
This code is developed for the legendary Robot Igal
https://youtu.be/iGOmnC24BvE

Todo List:
  1. Check why robot Igal goes to a different yaw (neededDeltaYaw describes a 180° turn somehow although it's 115°).
     Somehow a full circle is 180°..
  2. Add yaw change for obstacle avoidence
  3. Make GoToPoint try again when he fails to get to the correct point.
     We can make the GoToPoint (or goForward) check every X iterations that the robot is in the right way
     (if not, we can start a new GoToPoint from the updated robot location).
  4. Somehow robot Igal's location started to update really slow. Maybe it's the update particles and belief calculation fault?
  5. Sometimes when robot Igal get stuck in the wall, the yaw continue running
  6. Check why the route doesn't planned to go straight at the first intersection (and generates two waypoints instead).
  7. Check what happens when yaws getting greater than 360° (for example, delta's addition)
  8. Clear unimportant console prints and add the relevant ones.
  9. Clean unused consts and methods.
  10. Add notes to all class files, and delete the unimportant / debug notes.
  11. Reorder all files in new directories
  12. Pray to the Gay Iranian community.
