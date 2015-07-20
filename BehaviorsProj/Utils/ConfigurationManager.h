/*
 * ConfigurationManager.h
 *
 *  Created on: Jun 20, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef CONFIGURATIONMANAGER_H_
#define CONFIGURATIONMANAGER_H_

#include "Helper.h"
#include "../Framework/Structs.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class ConfigurationManager {
private:
	static ConfigurationManager * _instance;

	string _mapFilePath;
	Structs::Location _robotStartLocation;
	Structs::Location _robotGoalLocation;
	Structs::Size _robotSize;
	double _mapResolutionCM;
	double _gridResolutionCM;

	ConfigurationManager();
	ConfigurationManager(ConfigurationManager const&);
	ConfigurationManager& operator=(ConfigurationManager const&);

public:
	~ConfigurationManager();

	static ConfigurationManager * getInstance();

	string getMapFilePath();
	void setMapFilePath(string filePath);
	Structs::Location getRobotStartLocation();
	void setRobotStartLocation(string startLocation);
	Structs::Location getRobotGoalLocation();
	void setRobotGoalLocation(string goalLocation);
	Structs::Size getRobotSize();
	void setRobotSize(string size);
	double getMapResolutionCM();
	void setMapResolutionCM(string mapResolution);
	double getGridResolutionCM();
	void setGridResolutionCM(string gridResolution);

	Structs::ConfigurationProperty getProperty(string s);
	int setConfigurationProperty(Structs::ConfigurationProperty property);

	static string removeSurroundingSpaceCharacters(string s);
	static vector<string> splitString(string s, char delimiter);
};

#endif
