#include <cstring>
#include <iostream>
#include <stdlib.h> 
#include<vector>
#include<string>
#include "MoveObjects.cpp"
#include "moves.cpp"
#include "AI.cpp"



typedef Move (*Moves) (long* grid, const int &rows, const int &columns);


int empty(long* grid, int rows, int columns){
	
	int zero = 0;
	
	int size = rows*columns;
	
	for (int i = 0;i<size; i++){
		zero += (grid[i]==0);
	}
	return zero;
	
	
}


int digit(long number){
	int digits = 1;
	while (number >= 10){
		digits++;
		number = number / 10;
	}
	return digits;
}

int max_digits(long* grid, int rows, int columns){
	int size = rows*columns;

	int digits = 0;
	for (int i = 0; i<size; i++){
	
		if (digit(grid[i]) > digits) digits = digit(grid[i]);
	}
	return digits;
}


std::string white_spaces(int n){
	std::string s = "";
	for (int i=0;i<n;i++) s += ' ';
	return s;
}


void show_vector(std::vector<int> path){
	for (auto i: path) std::cout << i << ' ';
	
	std::cout << std::endl;
}


void show_grid(long *grid, int rows, int columns){

	int max_digit = max_digits(grid, rows, columns);

	std::string result = "";
	for (int i = 0; i<rows*columns; i++){
		result = result + std::to_string(grid[i]) + white_spaces(max_digit - digit(grid[i])) + (((i==0 && columns != 1) || (i+1)%columns) ? " " : "\n");
	}

	std::cout << result;
}


class Grid{
public:
	int rows;
	int columns;
	
	long* grid;
	
	long score;
	
	Moves moves[4] = {Up,Down,Left,Right};
	
	
	Grid(int rows, int columns){
		this->rows = rows;
		this->columns = columns;
		
		grid = (long*) malloc(sizeof(long)*rows*columns);
		memset(grid, 0,sizeof(grid));	
		
		for (int i = 0; i<2;i++) add(false);
		
		score = 0;
	}
	
	
	void up(){
		Move move = Up(grid, rows, columns);
		
		grid = move.grid;
		
		score += move.score;
		add(false);
	}
	
	void down(){
		Move move = Down(grid, rows, columns);
	
		
		
		grid = move.grid;
		score += move.score;
		add(false);
	}
	
	void left(){
		Move move = Left(grid, rows, columns);
		
		
		grid = move.grid;
		score += move.score;
		add(false);
	}
	
	void right(){
		Move move = Right(grid, rows, columns);
		
		
		
		grid = move.grid;
		score += move.score;
		add(false);
		
	}
	
	void add(bool gaming){
		player_add(grid, rows, columns);
	}
	
	
	int next_move(){
	
		int depth;
		
		if (rows==4 && columns == 4){
			depth =  2*(1 + (16 - empty(grid, rows, columns))/4);
			
			depth = (depth <= 10 ? depth : 10);
			depth = (depth >= 3 ? depth : 3);
		}
		
		else{
			depth = 6;
		}
		
		
		int trials = 17;
	
		int* move_count = (int*) malloc(sizeof(int)*trials);
		memset(move_count,0,sizeof(move_count));
		
		int max_arg=0 ,max_index=0;
		
		for (int i = 0; i<trials; i++){
		
			MoveTracker best_move = maxsearch(grid, rows, columns, moves, 4, depth);
			
			int move = best_move.path[best_move.path.size() - 1];
			
			move_count[move]++;
			
			if (move_count[move] > max_arg){
				max_arg = move_count[move];
				max_index = move;
			};
		
		}
		
		free(move_count);
		
		return max_index;
	}
	
	
	
	void play(long rounds, bool show = true){
		int round;
		for (round = 1; round <= rounds; round++){
		

			int next = next_move();

			
			//{Up,Down,Left,Right}
			if (next == 0)
				std::cout<<"##UP##"<<std::endl;
			if (next == 1)
				std::cout<<"##DOWN##"<<std::endl;
			if (next == 2)
				std::cout<<"##LEFT##"<<std::endl;
			if (next == 3)
				std::cout<<"##RIGHT##"<<std::endl;

			std::cout<<"\n\n\n";


			Move move = moves[next](grid, rows, columns);

			grid = move.grid;
			score += move.score;

			if (move.blocked){
				std::cout << "Reached a total score of " << score << " after playing " << std::to_string(round) << " rounds." << std::endl;
				break;
			}

			if (show){
				show_grid(grid,rows,columns);
				std::cout << "Score: " << score << "\n";
			}


			add(true);

			if (show){
				show_grid(grid,rows,columns);
				std::cout << "Score: " << score << "\n";
			}

			std::cin;
		}
		
		if (round == rounds) std::cout << "Reached a total score of " << score << " after playing " << std::to_string(round) << " rounds." << std::endl;
	}
	
	
	private:
	friend std::ostream& operator<<(std::ostream& os, const Grid& g){
		int max_digit = max_digits(g.grid, g.rows, g.columns);
		
		std::string result = "";
		for (int i = 0; i<g.rows*g.columns; i++){
			result = result + std::to_string(g.grid[i]) + white_spaces(max_digit - digit(g.grid[i])) + (((i==0 && g.columns != 1) || (i+1)%g.columns) ? " " : "\n");
		}
		result += "Score: " + std::to_string(g.score);
		
		return os << result;
	}
};
