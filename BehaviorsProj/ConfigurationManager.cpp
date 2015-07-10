/*
 * ConfigurationManager.cpp
 *
 *  Created on: Jun 20, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "ConfigurationManager.h"

ConfigurationManager::~ConfigurationManager() {

}

ConfigurationManager::ConfigurationManager(string configurationFilePath) {
	_mapFilePath = "";
	_mapResolutionCM = 0;
	_gridResolutionCM = 0;

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
	vector<string> LocationVector = splitString(startLocation, ' ');

	int x = atoi(LocationVector[0].c_str());
	int y = atoi(LocationVector[1].c_str());
	float yaw = (LocationVector.size() > 2) ? atoi(LocationVector[2].c_str()) : 0;

	_robotStartLocation = Structs::Location(x, y, yaw);
}

Structs::Location ConfigurationManager::getRobotGoalLocation() {
	return _robotGoalLocation;
}

void ConfigurationManager::setRobotGoalLocation(string goalLocation) {
	vector<string> LocationVector = splitString(goalLocation, ' ');

	int x = atoi(LocationVector[0].c_str());
	int y = atoi(LocationVector[1].c_str());
	float yaw = (LocationVector.size() > 2) ? atoi(LocationVector[2].c_str()) : 0;

	_robotGoalLocation = Structs::Location(x, y, yaw);
}

Structs::Size ConfigurationManager::getRobotSize() {
	return _robotSize;
}

void ConfigurationManager::setRobotSize(string size) {
	vector<string> SizeVector = splitString(size, ' ');

	int width = atoi(SizeVector[0].c_str());
	int height = atoi(SizeVector[1].c_str());

	_robotSize = Structs::Size(width, height);
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
	if (property.getToken() == "map") {
		setMapFilePath(property.getValue());
	} else if (property.getToken() == "startLocation") {
		setRobotStartLocation(property.getValue());
	} else if (property.getToken() == "goal") {
		setRobotGoalLocation(property.getValue());
	} else if (property.getToken() == "robotSize") {
		setRobotSize(property.getValue());
	} else if (property.getToken() == "MapResolutionCM") {
		setMapResolutionCM(property.getValue());
	} else if (property.getToken() == "GridResolutionCM") {
		setGridResolutionCM(property.getValue());
	} else {
		// In case that the token wasn't valid
		return 0;
	}

	return 1;
}

Structs::ConfigurationProperty ConfigurationManager::getProperty(string s) {
	vector<string> propertyVector = splitString(s, DELIMITER);
	Structs::ConfigurationProperty property(propertyVector[0], propertyVector[1]);

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
