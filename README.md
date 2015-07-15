# Robotics
This code is developed for the legendary Robot Igal
https://youtu.be/iGOmnC24BvE

Todo List:
  1. Check why robot Igal goes to a different yaw (greater than needed)
  2. Check why the route doesn't go straight at the first intersection (and generates two waypoints instead)
  3. Add yaw change for obstacle avoidence
  4. Make GoToPoint try again when he fails to get to the correct point
  5. The particles new location calculates slower than the robot's behavior (movement), so the location the localizaitonManager gives to the robot is "delayed"
  6. Clear unimportant console prints and add the relevant ones
  7. Clean unused consts
  8. Add notes to all class files
  9. CHANGE ALL THE MOVEMENT/WAYPOINTS MANAGERS AND BEHAVIORS TO WORK WITH MAP RESOLUTION AND DEGREES, ONLY THE ROBOT INPUT AND OUTPUT NEED TO DO THE COVERSION. (and the calcWantedYaw).
  10. Pray to the Gay Iranian community.
  11. In addition to 4, when the robot goes forward, check every X iterations that the robot is in the right way (else fix it).
  12. Looks like the belief calculation takes too much time
