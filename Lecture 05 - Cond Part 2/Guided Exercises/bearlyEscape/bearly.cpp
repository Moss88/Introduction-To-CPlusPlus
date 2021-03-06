#include "bearly.h"
#include <cstdlib>
#include <ctime>

Coord::Coord(int x, int y)
{
	this->x = x;
	this->y = y;
}

Coord::Coord()
{
	this->x = 0;
	this->y = 0;
}

bool Coord::operator==(const Coord &t) const
{
	if(this->x == t.x && this->y == t.y)
		return true;
	return false;
}

// Constructor
BearlyGame::BearlyGame():boardWidth(10),boardHeight(10),bearSense(2)
{
	srand((unsigned int)time(NULL));
	this->end = false;
	this->angry = false;

	// Set Player Position
	this->player = Coord(0, 0);

	// Set Bear Position
	this->bear = Coord(7, 7);

	// Set Door Position, Static
	this->door = Coord(9, 9);
}

bool BearlyGame::isOver()
{
	return this->end;
}

int BearlyGame::xBear()
{
	return this->bear.x;
}

int BearlyGame::yBear()
{
	return this->bear.y;
}

int BearlyGame::xPlayer()
{
	return this->player.x;
}

int BearlyGame::yPlayer()
{
	return this->player.y;
}


int BearlyGame::xDoor()
{
	return this->door.x;
}

int BearlyGame::yDoor()
{
	return this->door.y;
}

bool BearlyGame::angryBear()
{
	return angry;
}

void BearlyGame::turn(Dir direction)
{
	// Try to Move Player Piece
	if(this->isValid(player, direction))
		this->move(player, direction);
	else
	{
		if(direction == LEFT)
			cout << "Left is invalid move" << endl;
		else if(direction == RIGHT)
			cout << "Right is invalid move" << endl;
		else if(direction == UP)
			cout << "Up is invalid move" << endl;
		else if(direction == DOWN)
			cout << "Down is invalid move" << endl;
		else
			cout << direction << " is invalid move" << endl;
	}

	this->printBoard();
	this->delay(2);

	// Check for a Win
	if(this->player == this->door)
	{
		this->end = true;
		cout << "Winner!" << endl;
		return;
	}

	// Check for a loss
	if(this->player == this->bear)
	{
		this->end = true;
		cout << "You ran into the bear. Your bold move didn't pan out" << endl;
		cout << "You Lost." << endl;
		return;
	}

	// Move The Bear
	this->moveBear();

	// Check for a loss
	if(this->player == this->bear)
	{
		this->end = true;
		cout << "Some bearly bad news. The bear caught up to you." << endl;
		cout << "You Lost." << endl;
		return;
	}

	this->printBoard();
	this->delay(2);
	
	return;
}

// Pause Execution of Game
void BearlyGame::delay(int sec)
{
	time_t startTime, curTime;
	time(&startTime);
	curTime = startTime;
	while(difftime(curTime, startTime) < 1)
		time(&curTime);
}

// Display Board to the Console
void BearlyGame::printBoard()
{
	int i, j;
	this->clearBoard();

	// Set Tokens
	this->board[this->player.y][this->player.x] = 'X';
	this->board[this->door.y][this->door.x] = 'D';
	this->board[this->bear.y][this->bear.x] = 'B';

	// Print Board
	cout << "Display Board: " << endl;
	for(i = 0; i < boardWidth; i++)
	{
		for (j = 0; j < 2 * boardWidth; j++)
			cout << "-";
		cout << endl;

		for(j = 0; j < boardWidth; j++)
		{
			cout << "|" << board[i][j];
		}
		cout << "|";
		cout << endl;
	}
	for (j = 0; j < 2 * boardWidth; j++)
		cout << "-";
	cout << endl;
}

void BearlyGame::clearBoard()
{
	int i, j;
	for(i = 0; i < boardWidth; i++)
		for(j = 0; j < boardHeight; j++)
			this->board[i][j] = ' ';
}

// Determine if the move is within the bounds of the board
bool BearlyGame::isValid(const Coord &piece, Dir direction)
{
	if(direction == LEFT)
	{
		if(piece.x <= 0)
			return false;
	}
	else if(direction == RIGHT)
	{
		if(piece.x >= (this->boardWidth - 1))
			return false;
	}
	else if(direction == UP)
	{
		if(piece.y <= 0)
			return false;
	}
	else if(direction == DOWN)
	{
		if(piece.y >= (this->boardHeight - 1))
			return false;
	}
	else if(direction == NONE)
		return true;
	else
		return false;

	return true;
}

// Translate Move Into a Direction
void BearlyGame::move(Coord &piece, Dir direction)
{
	if(!this->isValid(piece, direction))
	{
		cout << "Attempted invalid move" << endl;
		return;
	}
	if(direction == LEFT)
		piece.x--;
	else if(direction == RIGHT)
		piece.x++;
	else if(direction == UP)
		piece.y--;
	else if(direction == DOWN)
		piece.y++;
	return;
}

void BearlyGame::moveBear()
{
	// Calculate Manhatten Distance
	int distX = this->player.x - this->bear.x;
	int distY = this->player.y - this->bear.y;
	Coord originalBear = this->bear;

	// Should the bear be enraged?
	if(abs(distX) <= bearSense && abs(distY) <= bearSense)
		this->angry = true;

	// Check for Anger
	if(this->angry)
	{
		// Take Shortest Path
		if(distX < 0)
			this->move(this->bear, LEFT);
		else if(distX > 0)
			this->move(this->bear, RIGHT);
		else if(distY < 0)
			this->move(this->bear, UP);
		else if(distY > 0)
			this->move(this->bear, DOWN);
	}
	else
	{
		// Meander
		bool invalid = true;
		while(invalid)
		{		
			// Pick a random direction
			Dir direction = (Dir)(rand() % 4);
			if(this->isValid(this->bear, direction))
			{
				this->move(this->bear, direction);
				// Make sure bear does not overlap door
				if(this->bear == this->door)
					this->bear = originalBear;
				else
					invalid = false;
			}
		}
	}

	// Should the bear be enraged?
	if(abs(distX) <= bearSense && abs(distY) <= bearSense)
		this->angry = true;
	return;
}
