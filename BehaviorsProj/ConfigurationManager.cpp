/*
 * ConfigurationManager.cpp
 *
 *  Created on: Jun 20, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "ConfigurationManager.h"

ConfigurationManager * ConfigurationManager::_instance = NULL;

/**
	Destructs ConfigurationManager.
*/
ConfigurationManager::~ConfigurationManager() {

}

/**
	Initializes the ConfigurationManager.

	@param configurationFilePath - the path to the configuration file.
*/
ConfigurationManager::ConfigurationManager() {
	_mapFilePath = "";
	_mapResolutionCM = 0;
	_gridResolutionCM = 0;

	ifstream configurationFile(Helper::CONFIGURATION_FILE_PATH.c_str());

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

ConfigurationManager * ConfigurationManager::getInstance() {
	if (ConfigurationManager::_instance == NULL)
		_instance = new ConfigurationManager();

	return _instance;
}

/**
	This method return the path of the map file.

	@return - the path of the map file.
 */
string ConfigurationManager::getMapFilePath() {
	return _mapFilePath;
}

/**
	This method set the path of the map file.

	@param filePath - the path map file to set.
 */
void ConfigurationManager::setMapFilePath(string filePath) {
	_mapFilePath = filePath;
}

/**
	This method return the robot location.

	@return - the robot location.
 */
Structs::Location ConfigurationManager::getRobotStartLocation() {
	return _robotStartLocation;
}

/**
	This method read from the configuration file the start location of the robot.

	@param startLocation - read the start location of the robot and create a location object.
 */
void ConfigurationManager::setRobotStartLocation(string startLocation) {
	vector<string> LocationVector = splitString(startLocation, ' ');

	int x = atoi(LocationVector[0].c_str());
	int y = atoi(LocationVector[1].c_str());
	float yaw = (LocationVector.size() > 2) ? atoi(LocationVector[2].c_str()) : 0;

	_robotStartLocation = Structs::Location(x, y, yaw);
}

/**
	This method return the goal location for the robot.

	@return - the goal robot location.
 */
Structs::Location ConfigurationManager::getRobotGoalLocation() {
	return _robotGoalLocation;
}

/**
	Set the goal location of the robot.

	@param goalLocation - set the goal location of the robot.
 */
void ConfigurationManager::setRobotGoalLocation(string goalLocation) {
	vector<string> LocationVector = splitString(goalLocation, ' ');

	int x = atoi(LocationVector[0].c_str());
	int y = atoi(LocationVector[1].c_str());
	float yaw = (LocationVector.size() > 2) ? atoi(LocationVector[2].c_str()) : 0;

	_robotGoalLocation = Structs::Location(x, y, yaw);
}

/**
	Get the size of the robot.

	@return - return the size of the robot.
 */
Structs::Size ConfigurationManager::getRobotSize() {
	return _robotSize;
}

/**
	read the size file from the configuration file.

	@param size - read the size of the robot from the configuration file.
 */
void ConfigurationManager::setRobotSize(string size) {
	vector<string> SizeVector = splitString(size, ' ');

	int width = atoi(SizeVector[0].c_str());
	int height = atoi(SizeVector[1].c_str());

	_robotSize = Structs::Size(width, height);
}

/**
	Get the resolution of the map in cm.

	@ return - the resolution of the map.
 */
float ConfigurationManager::getMapResolutionCM() {
	return _mapResolutionCM;
}

/**
	Read the map resolution from the configuration file.

	@param mapResolution - read the map resolution from the configuration file.
 */
void ConfigurationManager::setMapResolutionCM(string mapResolution) {
	_mapResolutionCM = atof(mapResolution.c_str());
}

/**
	Get the resolution of the grid in cm.

	@ return - the resolution of the grid.
 */
float ConfigurationManager::getGridResolutionCM() {
	return _gridResolutionCM;
}

/**
	Read the grid resolution from the configuration file.

	@param gridResolution - read the grid resolution from the configuration file.
 */
void ConfigurationManager::setGridResolutionCM(string gridResolution) {
	_gridResolutionCM = atof(gridResolution.c_str());
}

/**
	This method get set the values of the given properties.

	@param property - a property from the configuration file.

	@return - 0 - invalid property, 1 - valid property.
 */
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

/**
	Get the wanted property.

	@ return - the wanted property.
 */
Structs::ConfigurationProperty ConfigurationManager::getProperty(string s) {
	vector<string> propertyVector = splitString(s, Helper::CONFIGURATION_DELIMITER);
	Structs::ConfigurationProperty property(propertyVector[0], propertyVector[1]);

	return property;
}

/**
	This method remove the spaces from the given string.

	@param s - string with spaces.

	@return - string without spaces.
 */
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
