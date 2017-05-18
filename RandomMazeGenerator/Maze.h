//Maze.h
//Dylan Brigham && Madison Cooley
//Project 2.3
//Random Maze Generator
//03-10-17

#ifndef MAZE_H_DEF
#define MAZE_H_DEF

#include "ContainerPrinting.h"

#include<vector>
#include<iostream>
#include<algorithm>

class Maze
{
public:
	Maze(int totalCells);

	int find(int x);
	void unionMaze(int x, int y);
	int getRootSize();
	void displaySubsets(std::ostream& outstream) const;



private:
	int rootSize = -1;
	std::vector<int> vec_;
};

//constructs maze object
//totalCells is initial number of disjoint sets
Maze::Maze(int totalCells) : vec_(totalCells, -1)
{}


int Maze::find(int x) //compression
{
	if (vec_[x] < 0) //x is a root
		return x;
	else
		return vec_[x] = find(vec_[x]); //recursively sets parent
}



void Maze::unionMaze(int root1, int root2)
{

	if (vec_[root1] <= vec_[root2]) {
		vec_[root1] += vec_[root2];
		vec_[root2] = root1; //root2 new root
		if (rootSize > vec_[root1])
			rootSize = vec_[root1];
	}
	else {
		vec_[root2] += vec_[root1];
		vec_[root1] = root2; //root2 new root
		if (rootSize > vec_[root2])
			rootSize = vec_[root2];
	}
}


int Maze::getRootSize() {

	return abs(rootSize);
};


void Maze::displaySubsets(std::ostream& outStream) const
{
	outStream << vec_ << ' ' << '\n';
}

std::ostream &
operator<<(std::ostream & outStream, const Maze & maze)
{
	maze.displaySubsets(outStream);
	return outStream;
}

#endif
