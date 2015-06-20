/*
 * ConfigurationManager.cpp
 *
 *  Created on: Jun 20, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "ConfigurationManager.h"

ConfigurationManager::ConfigurationManager(string configurationFilePath) {
	ifstream configurationFile(configurationFilePath.c_str());

	if (configurationFile.is_open()) {
		string line;

		while (getline(configurationFile,line)) {
			setConfigurationProperty(getProperty(line));
		}

		configurationFile.close();
	} else {
		cout << "Unable to open file";
	}
}

string ConfigurationManager::getMapFilePath() {
	return _mapFilePath;
}

void ConfigurationManager::setMapFilePath(string filePath) {
	_mapFilePath = filePath;
}

Structs::Location ConfigurationManager::getRobotStartLocation() {
	return _robotStartLocation;
}

void ConfigurationManager::setRobotStartLocation(string startLocation) {
	Structs::Location robotStartLocation;
	vector<string> LocationVector = splitString(startLocation, ' ');

	robotStartLocation.x = atoi(LocationVector[0].c_str());
	robotStartLocation.y = atoi(LocationVector[1].c_str());

	if (LocationVector.size() > 2)
		robotStartLocation.yaw = atoi(LocationVector[2].c_str());

	_robotStartLocation = robotStartLocation;
}

Structs::Location ConfigurationManager::getRobotGoalLocation() {
	return _robotGoalLocation;
}

void ConfigurationManager::setRobotGoalLocation(string goalLocation) {
	Structs::Location robotGoalLocation;
	vector<string> LocationVector = splitString(goalLocation, ' ');

	robotGoalLocation.x = atoi(LocationVector[0].c_str());
	robotGoalLocation.y = atoi(LocationVector[1].c_str());

	if (LocationVector.size() > 2)
			robotGoalLocation.yaw = atoi(LocationVector[2].c_str());

	_robotGoalLocation = robotGoalLocation;
}

Structs::Size ConfigurationManager::getRobotSize() {
	return _robotSize;
}

void ConfigurationManager::setRobotSize(string size) {
	Structs::Size robotSize;
	vector<string> SizeVector = splitString(size, ' ');

	robotSize.width = atoi(SizeVector[0].c_str());
	robotSize.height = atoi(SizeVector[1].c_str());

	_robotSize = robotSize;
}

float ConfigurationManager::getMapResolutionCM() {
	return _mapResolutionCM;
}

void ConfigurationManager::setMapResolutionCM(string mapResolution) {
	_mapResolutionCM = atof(mapResolution.c_str());
}

float ConfigurationManager::getGridResolutionCM() {
	return _gridResolutionCM;
}

void ConfigurationManager::setGridResolutionCM(string gridResolution) {
	_gridResolutionCM = atof(gridResolution.c_str());
}

int ConfigurationManager::setConfigurationProperty(Structs::ConfigurationProperty property) {
	if (property.token == "map") {
		setMapFilePath(property.value);
	} else if (property.token == "startLocation") {
		setRobotStartLocation(property.value);
	} else if (property.token == "goal") {
		setRobotGoalLocation(property.value);
	} else if (property.token == "robotSize") {
		setRobotSize(property.value);
	} else if (property.token == "MapResolutionCM") {
		setMapResolutionCM(property.value);
	} else if (property.token == "GridResolutionCM") {
		setGridResolutionCM(property.value);
	} else {
		// In case that the token wasn't valid
		return 0;
	}

	return 1;
}

Structs::ConfigurationProperty ConfigurationManager::getProperty(string s) {
	Structs::ConfigurationProperty property;
	vector<string> propertyVector = splitString(s, DELIMITER);

	property.token = propertyVector[0];
	property.value = propertyVector[1];

	return property;
}

string ConfigurationManager::removeSurroundingSpaceCharacters(string s) {
	while (s.find_first_of(" ") == 0) {
		s = s.substr(1, s.length() + 1);
	}

	while (s.find_first_of(" ") == s.length() - 1) {
		s = s.substr(0, s.length());
	}

	return s;
}

vector<string> ConfigurationManager::splitString(string s, char delimiter) {
	vector<string> splittedString;
	size_t pos = 0;

	while ((pos = s.find(delimiter)) != std::string::npos) {
		splittedString.push_back(removeSurroundingSpaceCharacters(s.substr(0, pos)));
		s.erase(0, pos + 1);
	}

	splittedString.push_back(removeSurroundingSpaceCharacters(s));

	return splittedString;
}
