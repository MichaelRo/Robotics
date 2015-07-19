# Robotics
This code is developed for the legendary Robot Igal
https://youtu.be/iGOmnC24BvE

Todo List:
  1. Clear unimportant console prints and add the relevant ones.
  2. Change setLocation() and setPosition() robot methods to work with his variables and not with the Position2DProxy
  3. Check why the particles keep getting smaller and smaller beliefs.
     Not sure if the calculateMotionModelProbability method is well implemented
  4. Fix the issue with the last point - somehow robot Igal get stuck right before it
  5. Add prossesing after the PathPlanner, to fix the waypoints issue
  6. When the first chosen yaw (neededYawDelta) is negative, robot Igal sticks to the wall and can't move.
     Add yaw change for obstacle avoidence
  7. Check what happens when yaws getting greater than 360° (for example, delta's addition)
  8. Clean unused consts and methods.
  9. Add notes to all class files, and delete the unimportant / debug notes.
  10. Reorder all files in new directories
  11. Save the planet from the Gay Iranian community missle.
