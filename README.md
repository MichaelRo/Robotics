# Robotics
This code is developed for the legendary Robot Igal
https://youtu.be/iGOmnC24BvE

Todo List:
  1. Finish A* - DONE
  2. Keep non-padded map for laserScan check - DONE
  3. Fix PathPlanner - For some reason, reconstruct_path() doesn't invoke - DONE
  4. Maybe the weird route is because similiar cells have the same grade? 
     (btw, in the middle of the path, 
     the a star prefers to turn left instead of continuing straight until it gets to the wall       -DONE
  5. Check that the last waypoint is the end point - DONE
  6. Debug configurationManager - DONE
  7. DEBUG LocalizationManager
  8. Robot.cpp - DONE
  9. Create a goToWayPointPlan - DONE
  10. Add console prints
  11. Add the png and conf file to the project (as resources) - DONE
  12. Refactoring (Standardization)
  13. Debug
  14. Add notes to all class files
  15. A STAR GRADING FIX - handle turns factor - implement a method in node.cpp that calculates the grade by his parent            direction. - DONE
  16. Fix the A* calculation. Manhatten has 3 less waypoints and the route seems weird
  17. Check why the random particle delta does not generates a number by its upper-bound
  18. Fix the stop condition of turnInPlace
  19. Add the start point yaw to the A* calculation (as the first direction)
  20. After a while (it changes) there is std::out_of_range. not sure why. 
      maybe we overflow the robot? or maybe we're trying to access an imaginary laser beam?
  21. Sometimes the delta that we achieve when we're trying to update the robot's location and 
      localizationManager isn't zero valued. 
      Maybe it's related to the fact we don't stop our robot while debug? maybe we can't debug it?
  22. Fix the A* grading - add wall factor.
  23. make the a star grade 100%, that means each factor will be multiplied by a grading factor (0-1).
  24. add to GoToPoint.cpp - Read() in the inner while.
