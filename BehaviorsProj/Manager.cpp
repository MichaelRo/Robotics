/*
 * Manager.cpp
 *
 *  Created on: June 13, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#include "Manager.h"

//Manager::Manager(Robot* robot, Plan* pln) {
//	_robot = robot;
//	_curr = pln->getStartPoint();
//}
//void Manager::run()
//{
//	_robot->Read();
//	if(!(_curr->startCond()))
//		return;
//	_curr->action();
//	while(_curr !=NULL)
//	{
//		while(_curr->stopCond() == false)
//		{
//			_curr->action();
//			_robot->Read();
//		}
//		_curr = _curr->selectNext();
//		_robot->Read();
//	}
//}
//
//Manager::~Manager() {
//	// TODO Auto-generated destructor stub
//}
