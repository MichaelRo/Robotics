# Robotics
This code is developed for the legendary Robot Igal
https://youtu.be/iGOmnC24BvE

Todo List:
  1. Add more weight to the wall boundary check
  2. Check why the route doesn't planned to go straight at the first intersection (and generates two waypoints instead).
     Robot Igal get stuck at the second point because it's too close to the last one (mistake in the route plan)
  3. When the chosen yaw (neededYawDelta) is negative, robot Igal sticks to the wall and can't move.
     Add yaw change for obstacle avoidence
  4. Check what happens when yaws getting greater than 360° (for example, delta's addition)
  5. Make ConfigurationManager a Singleton
  6. Clear unimportant console prints and add the relevant ones.
  7. Clean unused consts and methods.
  8. Add notes to all class files, and delete the unimportant / debug notes.
  9. Reorder all files in new directories
  10. Save the planet from the Gay Iranian community missle.
