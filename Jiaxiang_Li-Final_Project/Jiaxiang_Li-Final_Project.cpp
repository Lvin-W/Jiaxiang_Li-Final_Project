#include <iostream>
#include <ctime>
#include<SFML/Graphics.hpp>
#include<SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

//initialize column, row, and cell size.
const int columns = 40;
const int rows = 30;
Vector2f cellSize(30, 30);

//window height/width
const int height = rows * cellSize.y;
const int width = columns * cellSize.x;

//initialize cell color and lines
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
			//check validity
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

	grid.setPosition(j * cellSize.y, i * cellSize.x);
}

int checkNeighbor(int status[rows][columns], int row, int column) {
	int liveNeigh = 0;
	int rowPad1 = 0;
	int rowPad2 = 0;
	int colPad1 = 0;
	int colPad2 = 0;

	//check if cell is at border
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

	//calculate 9 cells around the selected cell (including itself)
	for (int i = -1 + rowPad1; i < 2 + rowPad2; i++) {
		for (int j = -1 + colPad1; j < 2 + colPad2; j++){
			if (status[row + i][column + j] == 1) {
				liveNeigh++;
			}
		}
	}

	return liveNeigh;
}

void game(int status, int &nextStatus, int numNeigh, int &numChange){
	if (status == 0) {
		if (numNeigh == 3) {
			nextStatus = 1;
			numChange++;
			//When dead, if 3 living cells nearby, cell lives
		}
		else {
			nextStatus = 0;
		}
	}
	else {
		if (numNeigh < 3 || numNeigh > 4) {
			nextStatus = 0;
			numChange++;
			//When alive, if <2 or >3 living cells nearby, cell dies
		}
		else {
			nextStatus = 1;
		}
	}
}


int main() {
	
	float mode = 0;
	initialize(mode);

	//mode 1: random seed

	if (mode == 1) {
		int seed;
		cout << "Please enter a seed: " << endl;
		cin >> seed;
		int fps;
		cout << "Please enter your FPS: " << endl;
		cin >> fps;

		RenderWindow window(VideoMode(width, height), "GameOfLife_RandomSeed");
		
		RectangleShape grid;
		int RDnum[rows][columns]; //random number used to initialize grid
		int status[rows][columns]; //living status of the current cell
		int nextStatus[rows][columns]; //living status of the current cell at next round
		
		//initialize random patterns
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {

				//randomize
				RDnum[i][j] = rand() + seed;

				//20% chance of generating a living cell
				if (RDnum[i][j] % 5 == 1) {
					cellGenerate(grid, i, j, colLive);
					status[i][j] = 1;
				}
				else {
					cellGenerate(grid, i, j, colDead);
					status[i][j] = 0;
				}
			}
		}
		
		//initialize values
		int generation = 0;
		bool checkUpdate = 1;
		
		//set clock and initialize frame rates
		Clock clock;
		window.setFramerateLimit(fps);

		//main loop
		while (checkUpdate == 1) {

			window.clear();
			cout << "Generation: " << generation << endl;
			
			//initialize the number of change (to determine whether the grid is dead (without change)
			int numChange = 0;

			//check the number of living neighbors + run through changes to store the status in nextStatus[][]
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {

					int numNeigh = checkNeighbor(status, i, j);
					game(status[i][j], nextStatus[i][j], numNeigh, numChange);
					
				}
			}

			//Apply status of next round to the window
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

					//Change status to nextstatus
					status[i][j] = nextStatus[i][j];
				}
			}

			//Check if the grid is static
			if (numChange != 0) {
				window.display();
				generation++;
			}
			else {
				window.display();

				//end loop when static
				checkUpdate = 0;
				cout << "Number of Generations:" << generation << endl;
			}
		}
	}

	//mode 2: Gosper Glider Gun pattern
	else if (mode == 2) {

		int fps;
		cout << "Please enter your FPS: " << endl;
		cin >> fps;

		RenderWindow window(VideoMode(width, height), "GameOfLife_Glider_Gun");;
		
		RectangleShape grid;

		int status[rows][columns];
		int nextStatus[rows][columns];

		//brutally assigning each cell according to the Gosper Glider Gun
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {

				if (i == 10) {
					if (j == 24) {
						cellGenerate(grid, i, j, colLive);
						window.draw(grid);
						status[i][j] = 1;
						continue;
					}
				}
				else if (i == 11) {
					if (j == 22 || j == 24) {
						cellGenerate(grid, i, j, colLive);
						window.draw(grid);
						status[i][j] = 1;
						continue;
					}
				}
				else if (i == 12) {
					if (j == 12 || j == 13 || j == 20 || j == 21 || j == 34 || j == 35) {
						cellGenerate(grid, i, j, colLive);
						window.draw(grid);
						status[i][j] = 1;
						continue;
					}
				}
				else if (i == 13) {
					if (j == 11 || j == 15 || j == 20 || j == 21 || j == 35 || j == 34) {
						cellGenerate(grid, i, j, colLive);
						window.draw(grid);
						status[i][j] = 1;
						continue;
					}
				}
				else if (i == 14) {
					if (j == 0 || j == 1 || j == 10 || j == 16 || j == 20 || j == 21) {
						cellGenerate(grid, i, j, colLive);
						window.draw(grid);
						status[i][j] = 1;
						continue;
					}
				}
				else if (i == 15) {
					if (j ==0 || j == 1 || j == 10 || j == 14 || j == 16 || j == 17 || j == 22 || j == 24) {
						cellGenerate(grid, i, j, colLive);
						window.draw(grid);
						status[i][j] = 1;
						continue;
					}
				}
				else if (i == 16) {
					if (j == 10 || j == 16 || j == 24) {
						cellGenerate(grid, i, j, colLive);
						window.draw(grid);
						status[i][j] = 1;
						continue;
					}
				}
				else if (i == 17) {
					if (j == 11 || j == 15) {
						cellGenerate(grid, i, j, colLive);
						window.draw(grid);
						status[i][j] = 1;
						continue;
					}
				}
				else if (i == 18) {
					if (j == 12 || j == 13) {
						cellGenerate(grid, i, j, colLive);
						window.draw(grid);
						status[i][j] = 1;
						continue;
					}
				}

				cellGenerate(grid, i, j, colDead);
				window.draw(grid);
				status[i][j] = 0;
			}
		}

		//display the first generation without any altering cells (to test if the pattern is generated correctly
		window.display();
		int generation = 0;
		bool checkUpdate = 1;


		Clock clock;
		window.setFramerateLimit(fps);
		while (checkUpdate == 1) {
			
			window.clear();
			cout << "Generation: " << generation << endl;

			int numChange = 0;

			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {

					int numNeigh = checkNeighbor(status, i, j);
					game(status[i][j], nextStatus[i][j], numNeigh, numChange);

				}
			}

			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					if (nextStatus[i][j] == 0) {
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

			if (numChange != 0) {
				window.display();
				generation++;
			}
			else {
				window.display();
				checkUpdate = 0;
				cout << "Number of Generations:" << generation << endl;
			}
		}
	}
	return 0;
}