# Robotics
This code is developed for the legendary Robot Igal
https://youtu.be/iGOmnC24BvE

Todo List:
  1. Drop the BeamPoinsIterator. The set comparison does not work
  2. Check why the yaw change is slower when the localizationManager is set
  3. Sometimes the neededYawDelta gets negative and the robot gets in between the tables (one step before the other tables)
  4. Check what is the issue with the obstacle avoidance
  5. Fix the issue with the last point - somehow robot Igal get stuck right before it
  6. Restrict the go forward to more than 40° when it checks whether robot Igal driving into a wall
  7. Add processing after the PathPlanner, to fix the waypoints issue
  8. Add notes to all class files, delete the unimportant notes and delete unused methods.
  9. Add methods to Manager (methods like init map)
  10. Save the planet from the Gay Iranian community missle.
