/*
 * Robot.cpp
 *
 *  Created on: June 18, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "Robot.h"

/**
	Destructs Robot.
*/
Robot::~Robot() {
	delete _playerClient;
	delete _position;
	delete _laserProxy;
}

/**
	Initializes the Robot.

	@param ip - the ip of the robot we need to connect.
	@param port - the port of the connection with the robot.
*/
Robot::Robot(char * ip, int port) {
	_playerClient = new PlayerClient(ip,port);
	_position = new Position2dProxy(_playerClient);
	_laserProxy = new LaserProxy(_playerClient);

	_position->SetMotorEnable(true);

	// Fixing Player's reading bug
	for(int i = 0; i < 15; i++)
		Read();
}

/**
	Returns the robot's position as defined in the normal map ((0, 0) as the top left corner) with map's resolution

	@return - the robot's position (cm, cm)
*/
Structs::Point Robot::getPosition() {
	return Structs::Point((_position->GetXPos() * (METER_TO_CM(1) / 2.5)) + (550 / 2),
			 	 	 	  (_position->GetYPos() * (METER_TO_CM(-1) / 2.5)) + (380 / 2));
}

/**
	Returns the robot's location as defined in the normal map ((0, 0) as the top left corner) with map's resolution

	@return - the robot's location (cm, cm, degrees)
*/
Structs::Location Robot::getLocation() {
	float degreeRobotYaw = Helper::radiansToDegrees(_position->GetYaw());

	return Structs::Location((_position->GetXPos() * (METER_TO_CM(1) / 2.5)) + (550 / 2),
							 (_position->GetYPos() * (METER_TO_CM(-1) / 2.5)) + (380 / 2),
							 (degreeRobotYaw < 0) ? (360 + degreeRobotYaw) : degreeRobotYaw);
}

/**
	Set's robot location (odometry) by his rules ((0, 0) as the middle point)

	@param location - the robot's location (cm, cm, degrees) as defined in the normal map with map's resolution
*/
void Robot::setRobotLocation(Structs::Location location) {
	float robotYaw = (location.getYaw() > 180) ? ((-1) * (360 - location.getYaw())) : location.getYaw();

	Read();

	_position->SetOdometry((location.getX() - (550 / 2)) / (METER_TO_CM(1) / 2.5),
						   (location.getY() - (380 / 2)) / (METER_TO_CM(-1) / 2.5),
						   Helper::degreesToRadians(robotYaw));

	cout << "Robot position: " << location.toString() << endl;
}

/**
	SetSpeed of the robot.

	@param xSpeed - the speed of the robot.
	@param angularSpeed - the yaw we want the robot move.
 */
void Robot::setSpeed(float xSpeed, float angularSpeed) {
	_position->SetSpeed(xSpeed, angularSpeed);
}

/**
  	This method read details about the robot from the robot.
 */
void Robot::Read() {
	for (int i = 0; i < 2; i++)
		_playerClient->Read();
}

/**
	This method get the result of the scanning laser.

	@return - the result of the scanning laser.
*/
vector<float> Robot::getLaserScan() {
	vector<float> laserScan;

	Read();

	for (int i = 0; i < Helper::TOTAL_DEGREES; i++) {
		laserScan.push_back(getLaserDistance(Helper::degreesToIndex(i)));
	}

	Read();

	return laserScan;
}

/**
	This method get the result of the scanning laser.

	@param index - the degrees of checking the result from the laser scan.
	@return - the result of the scanning laser.
*/
float Robot::getLaserDistance(int index) {
	return _laserProxy->GetRange(index);
}
