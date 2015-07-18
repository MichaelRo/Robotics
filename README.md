# Robotics
This code is developed for the legendary Robot Igal
https://youtu.be/iGOmnC24BvE

Todo List:
  1. Check why the particles keep getting smaller and smaller beliefs.
     Not sure if the calculateMotionModelProbability method is well implemented
  2. Fix the issue with the last point - somehow robot Igal get stuck right before it
  3. Add prossesing after the PathPlanner, to fix the waypoints issue
  4. When the first chosen yaw (neededYawDelta) is negative, robot Igal sticks to the wall and can't move.
     Add yaw change for obstacle avoidence
  5. Check what happens when yaws getting greater than 360° (for example, delta's addition)
  6. Clear unimportant console prints and add the relevant ones.
  7. Clean unused consts and methods.
  8. Add notes to all class files, and delete the unimportant / debug notes.
  9. Reorder all files in new directories
  10. Remove Horani
  11. Save the planet from the Gay Iranian community missle.
