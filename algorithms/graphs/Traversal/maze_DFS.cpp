#include<time.h>
#include<random>
#include<stdio.h>

#define LAVA 0
#define UNVGND 1 //unvisited ground
#define VGND 2 // visited ground
#define REACHED_TARGET 3

const int nDir = 4;

int diffX[] = {0, 1, 0, -1};
int diffY[] = {1, 0, -1, 0};

const size_t rows = 4;
const size_t cols = 4;

int maze[rows][cols];

void initMaze(){

	for (size_t i = 0; i < rows; i++)
		for (size_t j = 0; j < cols; j++)
			maze[i][j] = rand() % 30 < 20;

}

void printMaze(){

	for (size_t i = 0; i < rows; i++){
		for (size_t j = 0; j < cols; j++)
			printf("%3d" ,maze[i][j]);

		putchar('\n');
	}

	printf("\n\n\n");

}


bool isValid(int x, int y){

	if (x < 0 || y < 0)
		return false;

	if (x >= rows || y >= cols)
		return false;

	return true;

}



bool DFS(size_t x , size_t y){

	//checks if we have reached the target
	if ((x == rows - 1) && (y == cols - 1)) {

		maze[x][y] = REACHED_TARGET;

		printMaze();

		return true;
	}

	//else marking this cell as visited
	maze[x][y] = VGND;

	printMaze();

	int newX, newY;

	//trying all directions
	for (int i = 0; i < nDir; i++){


		newX = x + diffX[i];
		newY = y + diffY[i];

		if (isValid(newX, newY) && 
			maze[newX][newY] == UNVGND ||
			maze[newX][newY] == REACHED_TARGET){

			if (DFS(newX, newY))
				return true;

		}

	}
	
	return false;
}





int main(){

	srand(time(NULL));

	initMaze();

	printMaze();

	if (DFS(0, 0))
		printf("there is a path !\n");
	else
		printf("there isn't a path !\n");

	return 0;

}
