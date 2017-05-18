//MazeGenerator.cpp
//Dylan Brigham && Madison Cooley
//Project 2.3
//Random Maze Generator
//03-10-17

#include "Maze.h"
#include "ContainerPrinting.h"
#include "RandomUtilities.h"
#include "winTimer.h"
#include<iostream>
#include<vector>
#include <string>

using namespace std;

void randomizedMaze(int rows, std::vector<string> &grid);
void removeWall(std::vector<string> &grid, int position1, int position2);
int randomWall(int randomPosition, int totalCells);


int main()
{

	while (true)
	{
		int rows;
		cout << "Enter size (-999 to quit): ";
		cin >> rows;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore();
		}
		else if (rows > 0 && (rows != -999))
		{
			system("cls");
			const int row = rows;
			std::vector<string> topGrid(row * row, { '_','_','_' });

			//initializes the maze
			std::vector<string> grid(row * row, { '_','_','|' });



			//Timing Begins
			Timer timer;
			timer.start();
			randomizedMaze(rows, grid);
			timer.stop();
			//cout << "TIME: " << timer() << endl;

			//display the roof of the maze
			for (int i = 0; i < row; i++) {
				if (i == 0)
					cout << " ";
				cout << topGrid.at(i);
			}
			//code below displays the maze
			cout << endl;
			for (int i = 0; i < row * row; i++) {
				if (i == row * row - 1) {
					grid.at(i).at(2) = '_';
				}
				if (i % row == 0 && i != 0) {
					cout << endl;
					cout << "|";
					cout << grid.at(i);
				}
				else if (i == 0) {
					cout << " ";
					cout << grid.at(i);
				}
				else
					cout << grid.at(i);
			}

			cout << endl;
			cout << endl;
		}
		else if (rows == -999)
		{
			exit(0);
		}

	}


	return 0;
}

void randomizedMaze(int rows, std::vector<string> &grid)
{

	int totalCells = rows * rows;
	std::vector<int> wallsBroken(totalCells, 0);
	Maze maze(totalCells);
	int start = 0;
	int end = totalCells - 1;


	while (maze.getRootSize() != totalCells)
	{
		for (int i = 0; i < totalCells; i++) {

			//int x = randInt(0, totalCells);
			int x = i;
			int y = randomWall(x, rows);

			if (!(maze.find(x) == maze.find(y)))
			{
				maze.unionMaze(maze.find(y), maze.find(x));
				removeWall(grid, x, y);
				//cout << maze;
			}
		}
	}
}


//RandomWall allows the randomizeMaze method to know which positions are allowed to be unioned
int randomWall(int firstRand, int row) {

	int rows = row;
	int cols = row;
	int rowPos = row - 1;
	int lastCell = (rows * cols) - 1;
	int secondRand;

	//case 1 : 2 options
	if (firstRand == 0)
	{
		int x = rand() % 2;

		if (x == 0)
		{
			secondRand = firstRand + 1;
		}
		else if (x == 1)
		{
			secondRand = firstRand + row;
		}
	}
	//case2 : 3 options
	else if ((firstRand < rowPos) && (firstRand != 0))
	{
		int x = rand() % 3;

		if (x == 0)
		{
			secondRand = firstRand - 1;
		}
		else if (x == 1)
		{
			secondRand = firstRand + 1;
		}
		else if (x == 2)
		{
			secondRand = firstRand + row;
		}
	}
	//case3 : 2 options
	else if (firstRand == rowPos)
	{
		int x = rand() % 2;

		if (x == 0)
		{
			secondRand = firstRand - 1;
		}
		else if (x == 1)
		{
			secondRand = firstRand + row;
		}
	}
	//case 4 : 3 options
	else if (((firstRand % row) == 0) && (firstRand != 0) && (firstRand != (lastCell - rowPos)))
	{
		int x = rand() % 3;

		if (x == 0)
		{
			secondRand = firstRand - row;
		}
		else if (x == 1)
		{
			secondRand = firstRand + 1;
		}
		else if (x == 2)
		{
			secondRand = firstRand + row;
		}
	}
	//case 5 last
	//case 6 : 3 options
	else if ((((firstRand + 1) % row) == 0) && (firstRand != rowPos) && (firstRand != lastCell))
	{
		int x = rand() % 3;

		if (x == 0)
		{
			secondRand = firstRand - row;
		}
		else if (x == 1)
		{
			secondRand = firstRand - 1;
		}
		else if (x == 2)
		{
			secondRand = firstRand + row;
		}
	}
	//case 7 : 2 options
	else if (firstRand == (lastCell - rowPos))
	{
		int x = rand() % 2;

		if (x == 0)
		{
			secondRand = firstRand - row;
		}
		else if (x == 1)
		{
			secondRand = firstRand + 1;
		}
	}
	//case 8 : 3 options
	else if ((firstRand != (lastCell - rowPos)) && (firstRand != lastCell) && (firstRand > (lastCell - rowPos)))
	{
		int x = rand() % 3;

		if (x == 0)
		{
			secondRand = firstRand - row;
		}
		else if (x == 1)
		{
			secondRand = firstRand - 1;
		}
		else if (x == 2)
		{
			secondRand = firstRand + 1;
		}
	}
	//case 9 : 2 options
	else if (firstRand == lastCell)
	{
		int x = rand() % 2;

		if (x == 0)
		{
			secondRand = firstRand - row;
		}
		else if (x == 1)
		{
			secondRand = firstRand - 1;
		}
	}
	//case 5 : 4 options
	else
	{
		int x = rand() % 4;

		if (x == 0)
		{
			secondRand = firstRand - row;
		}
		else if (x == 1)
		{
			secondRand = firstRand - 1;
		}
		else if (x == 2)
		{
			secondRand = firstRand + 1;
		}
		else if (x == 3)
		{
			secondRand = firstRand + row;
		}
	}
	return secondRand;
}

//  removeWall() displays the graph and removes the wall separating the given position in
// the randomizedMaze method
void removeWall(std::vector<string> &grid, int position1, int position2) {

	int row = sqrt(grid.size());


	if (position2 == position1 + 1) { //position2 to the right
		grid.at(position1).at(2) = '_';
	}
	else if ((position1 == (position2 + 1))) { //position2 to the left
		grid.at(position2).at(2) = '_';
	}
	else if (position2 == position1 + row) { //position2 below
		grid.at(position1).at(0) = ' ';
		grid.at(position1).at(1) = ' ';
	}
	else if (position1 == (position2 + row)) { //position2 above
		grid.at(position2).at(0) = ' ';
		grid.at(position2).at(1) = ' ';
	}


}
