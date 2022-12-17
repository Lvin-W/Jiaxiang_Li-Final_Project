#include <iostream>
#include <ctime>
#include<SFML/Graphics.hpp>
#include<SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;


const int columns = 20;
const int rows = 20;
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
		cout << "3. User-specified Initialization" << endl;

		cin >> mode;
		if (mode != 1 && mode != 2 && mode != 3) {
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


int main() {
	
	float mode = 0;
	initialize(mode);

	if (mode == 1) {
		int seed;
		cout << "Please enter a seed (integer):" << endl;
		cin >> seed;


		RenderWindow window(VideoMode(height, width), "GameOfLife_RandomSeed");
		RectangleShape* grid;

		int* RDnum[rows];
		int ite = 0;



		while (window.isOpen()) {
			window.clear();
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {

					grid = new RectangleShape[columns];
					RDnum[i] = new int[columns];
					
					RDnum[i][j] = rand() - seed;

					if (RDnum[i][j] % 5 == 1) {
						cellGenerate(grid[j], i, j, colLive);
						window.draw(grid[j]);
					}
					else {
						cellGenerate(grid[j], i, j, colDead);
						window.draw(grid[j]);
					}
					delete[] grid;

				}
				delete[] RDnum[i];

			}
			
			
			ite++;
			window.display();
		}

	}
	else if (mode == 2) {
		RenderWindow window(VideoMode(1500, 1500), "GameOfLife_IconicMaps");
		RectangleShape grid[columns][rows];
	}
	else if (mode == 3) {
		RenderWindow window(VideoMode(1500, 1500), "GameOfLife_SpecifiedSeed");
		RectangleShape grid[columns][rows];
	}
	


	return 0;
}