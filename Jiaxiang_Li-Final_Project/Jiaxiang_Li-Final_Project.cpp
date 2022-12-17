#include <iostream>
#include <ctime>
#include<SFML/Graphics.hpp>
#include<SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;


const int columns = 30;
const int rows = 30;
Vector2f cellSize(30, 30);

const int height = rows * cellSize.x;
const int width = columns * cellSize.y;

const Color colDead(255, 255, 255);
const Color colLive(0, 0, 0);
const Color colLine(255, 210, 210);


void initialize(float& mode) {
	cout << "Welcome to Conway's Game of Life." << endl;

	int startMenu = 0;
	while (startMenu == 0) {
		cout << "Please start the game by selecting one of the modes:" << endl;
		cout << endl << "1: Random Seed." << endl;
		cout << "2. Iconic Patterns." << endl;

		cin >> mode;
		if (mode != 1 && mode != 2) {
			cout << "Please select a valid mode number!" << endl;
		}
		else {
			startMenu = 1;
		}
	}
}

void cellGenerate(RectangleShape& grid, int i, int j, Color col) {
	grid.setSize(cellSize);
	grid.setOutlineColor(colLine);
	grid.setOutlineThickness(cellSize.x / 10);
	grid.setFillColor(col);

	grid.setPosition(i * cellSize.x, j * cellSize.y);
}

int checkNeighbor(int status[rows][columns], int row, int column) {
	int liveNeigh = 0;
	int rowPad1 = 0;
	int rowPad2 = 0;
	int colPad1 = 0;
	int colPad2 = 0;
	if (row == 0) {
		rowPad1 = 1;
	}
	else if (row == rows - 1) {
		rowPad2 = -1;
	}
	else if (column == 0) {
		colPad1 = 1;
	}
	else if (column == columns - 1) {
		colPad2 = -1;
	}

	for (int i = -1 + rowPad1; i < 2 + rowPad2; i++) {
		for (int j = -1 + colPad1; j < 2 + colPad2; j++){
			if (status[row + i][column + j] == 1) {
				liveNeigh++;
			}
		}
	}

	return liveNeigh;
}


int main() {
	
	float mode = 0;
	initialize(mode);

	if (mode == 1) {
		int seed;
		cout << "Please enter a seed: " << endl;
		cin >> seed;
		int fps;
		cout << "Please enter your FPS: " << endl;
		cin >> fps;

		RenderWindow window(VideoMode(height, width), "GameOfLife_RandomSeed");
		//RectangleShape grid[rows][columns];
		RectangleShape grid;
		int numLive[rows][columns];
		//vector <int[2]> liveCells;

		int RDnum[rows][columns];
		int status[rows][columns];
		int nextStatus[rows][columns];
		int ite = 0;
		
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {

				RDnum[i][j] = rand() + seed;

				if (RDnum[i][j] % 5 == 1) {
					cellGenerate(grid, i, j, colLive);
					//liveCells.push_back({i, j});
					

					status[i][j] = 1;
				}
				else {
					cellGenerate(grid, i, j, colDead);
					status[i][j] = 0;
				}

			}
				

		}
		
		
		Clock clock;
		window.setFramerateLimit(fps);
		while (true) {
			//float currentTime = clock.restart().asSeconds();
			//float fps = 1.0f / (currentTime);

			window.clear();
			

			//int vecIte = 0;

			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					int numNeigh = checkNeighbor(status, i, j);

					if (status[i][j] == 0) {
						if (numNeigh == 3) {
							nextStatus[i][j] = 1;
						}
						else {
							nextStatus[i][j] = 0;
						}
					}
					else {
						if (numNeigh < 3 || numNeigh > 4) {
							nextStatus[i][j] = 0;
						}
						else {
							nextStatus[i][j] = 1;
						}
					}

					//window.draw(grid[i][j]);
				}
			}
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					if (nextStatus[i][j] == 0){
						cellGenerate(grid, i, j, colDead);
						window.draw(grid);
					}
					else if (nextStatus[i][j] == 1) {
						cellGenerate(grid, i, j, colLive);
						window.draw(grid);
					}
					status[i][j] = nextStatus[i][j];
				}
			}
			
			window.display();
			ite++;
		}
		

	}
	else if (mode == 2) {
		RenderWindow window(VideoMode(height, width), "GameOfLife_Iconic_Patterns");;
		RectangleShape grid;
	}
	


	return 0;
}