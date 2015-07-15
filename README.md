# Robotics
This code is developed for the legendary Robot Igal
https://youtu.be/iGOmnC24BvE

Todo List:
  1. Change all the movement / wayPoint managers and behaviors to work with map resolution and degrees.
     Only the calcWantedYaw, and robot Igal's input and output need to do the conversions.
  2. Check why robot Igal goes to a different yaw (greater than needed).
  3. Check why the route doesn't planned to go straight at the first intersection (and generates two waypoints instead).
  4. Add yaw change for obstacle avoidence
  5. Make GoToPoint try again when he fails to get to the correct point.
     We can make the GoToPoint (or goForward) check every X iterations that the robot is in the right way
     (if not, we can start a new GoToPoint from the updated robot location).
  6. Somehow robot's location started to update really slow. Maybe it's the update particles and belief calculation fault?
  7. Clear unimportant console prints and add the relevant ones.
  8. Clean unused consts and methods.
  9. Add notes to all class files, and delete the unimportant / debug notes.
  10. Pray to the Gay Iranian community.
