/*
 * main.cpp
 *
 *  Created on: June 13, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */
#include "Robot.h"
#include "ConfigurationManager.h"
#include "Map.h"
#include "Plans/PlnObstacleAvoid.h"

int main (int argc, const char * argv[]){
	Robot igal("localhost",6665);
	ConfigurationManager configurationManager("/home/colman/Documents/RoboticsFinalProj/PcBotWorld/parameters.txt");
	Manager manager(&configurationManager, &igal);
	manager.run();
}
