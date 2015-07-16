# Robotics
This code is developed for the legendary Robot Igal
https://youtu.be/iGOmnC24BvE

Todo List:
  1. Make robot Igal work with negativ/positive values (yaws also), and make all else work with regular map dimensions
  2. Change all the movement / wayPoint managers and behaviors to work with map resolution and degrees.
     Only the calcWantedYaw, and robot Igal's input and output need to do the conversions.
  3. Check why robot Igal goes to a different yaw (greater than needed).
  4. Check why the route doesn't planned to go straight at the first intersection (and generates two waypoints instead).
  5. Add yaw change for obstacle avoidence
  6. Make GoToPoint try again when he fails to get to the correct point.
     We can make the GoToPoint (or goForward) check every X iterations that the robot is in the right way
     (if not, we can start a new GoToPoint from the updated robot location).
  7. Somehow robot Igal's location started to update really slow. Maybe it's the update particles and belief calculation fault?
  8. Check why the needed delta yaw describes a 180° turn
  9. Check what happens when yaws getting greater than 360 (for example, delta's addition)
  10. Clear unimportant console prints and add the relevant ones.
  11. Clean unused consts and methods.
  12. Add notes to all class files, and delete the unimportant / debug notes.
  13. Pray to the Gay Iranian community.
