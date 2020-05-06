/*
 * recitation3.cpp
 *
 *  Created on: Sep 12, 2019
 *      Author: Anushka Kathait
 *
 */


#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

class Point{
private:

	int x;
	int y;

public:
	//Point(int x, int y){
	//	this->x = x;
	//	this->y = y;
	//}/;

	void set(int x, int y){
		this->x = x;
		this->y = y;
	};

	int getX(){
		return x;
	};

	int getY(){
		return y;
	};

	double distance(){
		return sqrt((x*x) + (y*y));
	};
};

int main(){
	ifstream inputfilestream;
	string line;
	stringstream ss;
	int index = 0;

	Point distArray[15];

	inputfilestream.open("points.txt");

	if(!inputfilestream.is_open()){
		cout<<"error reading file"<<endl;
		return 0;
	}

	while(getline(inputfilestream,line)){
		string x;
		string y;

		stringstream ss(line);
		getline(ss, x, ',');
		getline(ss, y);

		int xp = stoi(x);
		int yp = stoi(y);

		Point p;
		p.set(xp,yp);

		distArray[index] = p;
		index++;
	}

	double closest = 500.0;
	int spot = -1;
	for(int i = 0; i < 15; i++){
		double dist = distArray[i].distance();
		if(dist <= closest){
			closest = dist;
			spot = i;
		}
	}

	for(int i = 0; i < 15; i++){
		if(distArray[i].distance() == closest){
			cout<<distArray[i].getX();
			cout<<distArray[i].getY()<<endl;
		}
	}

	return 0;
}






