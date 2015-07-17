# Robotics
This code is developed for the legendary Robot Igal
https://youtu.be/iGOmnC24BvE

Todo List:
  1. Check why robot Igal goes to a different yaw (neededDeltaYaw describes a 180° turn somehow although it's 115°).
     Somehow a full circle is 180°..
  2. When robot Igal changes direction (TurnInPlace), 
     Igal is confidently sure that he is going to the same direction (the neededYaw and Igal's yaw is growing)
  3. Add yaw change for obstacle avoidence
  4. Make GoToPoint try again when he fails to get to the correct point.
     We can make the GoToPoint (or goForward) check every X iterations that the robot is in the right way
     (if not, we can start a new GoToPoint from the updated robot location).
  5. Somehow robot Igal's location started to update really slow. Maybe it's the update particles and belief calculation fault?
  6. Robot Igal is drunk. He get stuck into walls. Looks like the 60° wall check is too slow and doesn't complete the check
     Sometimes the yaw also continue running when he got stuck.
  7. Check why the route doesn't planned to go straight at the first intersection (and generates two waypoints instead).
  8. Check what happens when yaws getting greater than 360° (for example, delta's addition)
  9. Clear unimportant console prints and add the relevant ones.
  10. Clean unused consts and methods.
  11. Add notes to all class files, and delete the unimportant / debug notes.
  12. Reorder all files in new directories
  13. Pray to the Gay Iranian community.
