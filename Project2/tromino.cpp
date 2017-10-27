#include<iostream>
#include<cstdlib>
#include<cmath>
#include<climits>
#include<ctime>
using namespace std;

int hole_x;
int hole_y;
int size;

char ** boardT;

void createBoard();
void displayBoard();
void trmoinoTile(int, int, int, int, int);

void createBoard(){					//Create Board with input size
	boardT = new char*[size];
	for(int i=0; i<size; i++){
		boardT[i] = new char[size];
	}

        for(int i=0; i<size; i++){
                for(int j=0; j<size; j++){
                        if(i==(hole_x) && j==(hole_y)){
				boardT[i][j] = 'X';
			}
			else{
				boardT[i][j] = '*';
			}
                }
        }
}

void displayBoard(){								//Display Board
	for(int i=0; i<size; i++){
		cout<<"\n";
		for(int j=0; j<size; j++){
			cout<<"\t"<<boardT[i][j];
		}
		cout<<"\n";
	}
}

void trominoTile(int size, int hole_x, int hole_y, int board_x, int board_y){	//Recursively use trominoes to fill up the board
	int n = size;
	size = size/2;

	if(n==2){								//if size is 2
		if(hole_x < board_x+size && hole_y < board_y+size){		//if hole in first quadrant
			int rand_no = rand()%10;
			char c = '0' + rand_no;
                        boardT[board_x+size][board_y+size] = c;
                        boardT[board_x+size][board_y+size-1] = c;
                        boardT[board_x+size-1][board_y+size] = c;
		}
                else if(hole_x < board_x+size && hole_y >= board_y+size){	//if hole in second quadrant
                        int rand_no = rand()%10;
                        char c = '0' + rand_no;
                        boardT[board_x+size][board_y+size] = c;
                        boardT[board_x+size][board_y+size-1] = c;
                        boardT[board_x+size-1][board_y+size-1] = c;
                }
                else if(hole_x >= board_x+size && hole_y < board_y+size){	//if hole in third quadrant
                        int rand_no = rand()%10;
                        char c = '0' + rand_no;
                        boardT[board_x+size][board_y+size] = c;
                        boardT[board_x+size-1][board_y+size] = c;
                        boardT[board_x+size-1][board_y+size-1] = c;
                }
		else{								//if hole in fourth quadrant
                        int rand_no = rand()%10;
                        char c = '0' + rand_no;
                        boardT[board_x+size-1][board_y+size] = c;
                        boardT[board_x+size][board_y+size-1] = c;
                        boardT[board_x+size-1][board_y+size-1] = c;
                }
		return;
	}
										//if greater than 2
	if(hole_x < board_x+size){
		if(hole_y < board_y+size){					//if hole in first quadrant
                        int rand_no = rand()%10;
                        char c = '0' + rand_no;
			boardT[board_x+size][board_y+size] = c;
                        boardT[board_x+size][board_y+size-1] = c;
                        boardT[board_x+size-1][board_y+size] = c;
			trominoTile(size, hole_x, hole_y, board_x, board_y);	//Recursively call sub-quadrants
			trominoTile(size, board_x+size, board_y+size-1, board_x+size, board_y);
			trominoTile(size, board_x+size, board_y+size, board_x+size, board_y+size);
			trominoTile(size, board_x+size-1, board_y+size, board_x, board_y+size);
		}
										//if hole in second quadrant
		else{
                        int rand_no = rand()%10;
                        char c = '0' + rand_no;
                        boardT[board_x+size][board_y+size] = c;
                        boardT[board_x+size][board_y+size-1] = c;
                        boardT[board_x+size-1][board_y+size-1] = c;
                        trominoTile(size, hole_x, hole_y, board_x, board_y+size);
                        trominoTile(size, board_x+size, board_y+size-1, board_x+size, board_y);
                        trominoTile(size, board_x+size, board_y+size, board_x+size, board_y+size);
                        trominoTile(size, board_x+size-1, board_y+size-1, board_x, board_y);
		}
	}
	else{
		if(hole_y < board_y+size){					//if hole in third quadrant
                        int rand_no = rand()%10;
                        char c = '0' + rand_no;
                        boardT[board_x+size][board_y+size] = c;
                        boardT[board_x+size-1][board_y+size] = c;
                        boardT[board_x+size-1][board_y+size-1] = c;
                        trominoTile(size, hole_x, hole_y, board_x+size, board_y);
                        trominoTile(size, board_x+size-1, board_y+size, board_x, board_y+size);
                        trominoTile(size, board_x+size, board_y+size, board_x+size, board_y+size);
                        trominoTile(size, board_x+size-1, board_y+size-1, board_x, board_y);

		}
		else{								//if hole in fourth quadrant
                        int rand_no = rand()%10;
                        char c = '0' + rand_no;
                        boardT[board_x+size-1][board_y+size] = c;
                        boardT[board_x+size][board_y+size-1] = c;
                        boardT[board_x+size-1][board_y+size-1] = c;
                        trominoTile(size, hole_x, hole_y, board_x+size, board_y+size);
                        trominoTile(size, board_x+size-1, board_y+size, board_x, board_y+size);
                        trominoTile(size, board_x+size, board_y+size-1, board_x+size, board_y);
                        trominoTile(size, board_x+size-1, board_y+size-1, board_x, board_y);
		}
	}
}

void clear_memory(){								//free up memory previously allocated
	for(int i=0; i<size; i++){
		delete[] boardT[i];
	}
	delete[] boardT;
}

int main(int argc, char* argv[]){

	srand(time(NULL));
	if(argc == 4){								//if appropriate number of command line arguments

		size = pow(2,atoi(argv[1]));
		hole_x = atoi(argv[2])-1;
		hole_y = atoi(argv[3])-1;

		createBoard();
		trominoTile(size, hole_x, hole_y, 0, 0);
		displayBoard();
		clear_memory();
	}
	else{									//if invalid number of arguments
		cout<<"\nInvalid number of arguments!";
	}
	return 0;
}
