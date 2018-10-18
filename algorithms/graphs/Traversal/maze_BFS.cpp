#include<time.h>
#include<random>
#include<queue>
#include<stdio.h>
#include<array>

//can't go there
const int UNAVAILABLE = -1;
//can go there
const int AVAILABE = 0;
//every other int -> visited

//matrix size
const size_t MAXN = 8;
const size_t MAXM = 8;

int maze[MAXN][MAXM];

using point = std::pair<size_t, size_t>;

using directions = std::array<point, 4>;

directions dirs = {

	std::make_pair(0,1), //left
	std::make_pair(0,-1), //right
	std::make_pair(1,0), //up
	std::make_pair(-1,0) //down
};


//simply prints the maze contain
void printMaze(){

	for (int i = 0; i < MAXN; i++){
		for (int j = 0; j < MAXM; j++)
			printf("%3d", maze[i][j]);

		putchar('\n');
	}

	printf("\n\n\n");
}

//init maze's cells
//with 66% change -> available cell
//with 33% change -> unavailable cell
void initMaze(){

	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXM; j++)
           maze[i][j] = ( (rand() % 30 ) < 20 ) - 1;

}

bool isValid(int x, int y){

	if (x < 0 || y < 0)
		return false;

	if (x > MAXN || y > MAXM)
		return false;

	return true;

}

void BFS(point start){

	maze[start.first][start.second] = 1;

	std::queue<point> wave;

	wave.push(start);

	int newX, newY;

	while (!wave.empty()){

		for each (point dir in dirs){

			newX = wave.front().first + dir.first;
			newY = wave.front().second + dir.second;

			if (isValid(newX, newY) && maze[newX][newY] == AVAILABE) {

				maze[newX][newY] += 
					maze[wave.front().first][wave.front().second] + 1;

				wave.push(std::make_pair(newX, newY));

			}
		}
		
		wave.pop();

	}
}






int main(){

	srand(time(NULL));

	initMaze();

	printMaze();

	point start(5, 5);

	BFS(start);

	printMaze();

	return 0;

}
