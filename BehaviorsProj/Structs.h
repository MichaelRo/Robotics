/*
 * Structs.h
 *
 *  Created on: Jun 20, 2015
 *      Author: Noa Even Tsur, Itay Desalto, Michael Roytman
 */

#ifndef STRUCTS_H_
#define STRUCTS_H_

#include <string>

using namespace std;

class Structs {
public:
	struct Location{
		float x;
		float y;
		float yaw = 0;

		Location();
		Location(float x, float y, float yaw = 0);
	};

	struct Size {
		int width;
		int height;

		Size();
		Size(int width, int height);
	};

	struct ConfigurationProperty {
		string token;
		string value;

		ConfigurationProperty(string token, string value);
	};
};

#endif
