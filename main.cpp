#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<Windows.h>
#include<conio.h>
#include<cstdlib>
using namespace std;
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

template<class t>
class stack {

	t* arr;
	int maxsize;
	int stkptr;
	int size;
public:

	stack(int s = 10000)
	{
		arr = new t[s];

		maxsize = s;
		stkptr = 0;
		size = 0;
	}
	bool isEmpty()
	{
		if (size == 0)
			return true;
		else
			return false;
	}
	bool isFull()
	{
		if (size == maxsize)
			return true;
		else
			return false;
	}

	bool push(t d)
	{
		if (!isFull())
		{
			if (d == arr[stkptr - 1])
			{
				return false;

			}
			else
			{
				arr[stkptr] = d;
				stkptr++;
				size++;
				return true;
			}
		}
		else
			return false;
	}
	bool top(t& d)
	{
		if (!isEmpty())
		{
			d = arr[stkptr - 1];
			return true;
		}
		else
			return false;
	}
	bool pop(t& d)
	{
		if (!isEmpty())
		{
			d = arr[--stkptr];
			size--;
			return true;
		}
		else
			return false;
	}
	int getsize()
	{
		return size;
	}

	void print()
	{

		cout << "{";
		for (int i = 0; i < size; i++)
		{

			cout << arr[i] << " ";
		}
		cout << "}";

	}


};

class coordinates {

	int x = 0, y = 0;
	int room = 0;
public:


	coordinates()
	{
		x = y = 0;

	}
	coordinates(int x, int y, int room)
	{
		this->x = x;
		this->y = y;
		this->room = room;
	}


	bool operator==(const coordinates& p)
	{
		if (x == p.x && y == p.y)
		{
			return true;
		}
		else
			return false;
	}
	friend ostream& operator << (ostream& o, coordinates l)
	{
		o << "Room " << l.room + 1 << " ";
		o << "(" << l.x << "," << l.y << ")" << " ";
		cout << endl;
		return  o;
	}
};


class room {

	char** arr;
	int rows;
	int cols;


	int x, y; // start point coordinates


	int i = 0;
	int j = 0;


	int k = 0;


public:

	room()
	{

		rows = 0;
		cols = 0;
		arr = 0;
		x = y = 0;
	}

	room(int x, int y, int rows, int cols, char** arr)
	{
		this->x = x;
		this->y = y;
		this->rows = rows;
		this->cols = cols;
		this->arr = new char* [rows];

		for (int i = 0; i < rows; i++)
		{
			this->arr[i] = new char[cols];
			for (int j = 0; j < cols; j++)
			{
				this->arr[i][j] = arr[i][j];
			}
		}
	}

	room(room& r) //copy cosntructor
	{
		this->cols = r.cols;
		this->rows = r.rows;
		this->x = r.x;
		this->y = r.y;

		this->i = r.i;
		this->j = r.j;
		this->k = r.k;


		this->arr = new char* [rows];
		for (int i = 0; i < rows; i++)
		{
			this->arr[i] = new char[cols];
		}


		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				this->arr[i][j] = r.arr[i][j];
			}
		}
	}

	void setRows(int a)
	{
		rows = a;
		arr = new char* [a];
	}


	void setcols(int a)
	{
		cols = a;


		for (int i = 0; i < rows; i++)
		{
			arr[i] = new char[cols];
		}
	}

	void setPOINTx(int a)
	{
		x = a;
	}


	void setPOINTy(int a)
	{
		y = a;
	}

	int getROWS()
	{
		return rows;
	}

	int getCOLS()
	{
		return cols;
	}


	int getXcoordinate()
	{
		return x;
	}

	int getYcoordinate()
	{
		return y;
	}

	char** array()
	{
		return arr;
	}
	void setMatrix(char c)
	{
		if (j < cols)
		{

			arr[i][j] = c;
			j++;

		}
		if (j >= cols)
		{
			if (i >= rows)
				return;
			else
			{
				i++;
				j = 0;
			}

		}


	}

	void print()
	{
		cout << "Rows of room are" << rows << endl;


		cout << "Cols of room are" << cols << endl;

		cout << "start x point of room is " << x << endl;
		cout << "start y point of room is " << y << endl;






		cout << "matrix is" << endl;


		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{

				cout << arr[i][j] << " ";
			}

			cout << endl;
		}
	}

	~room()
	{
		for (int i = 0; i < rows; i++)
		{
			delete[]arr[i];
		}
		delete[]arr;
	}

};


class HauntedHouse {

	int rooms = 0; // stores total rooms in game
	room* r = nullptr;
	int treasure = 0; // stores number room which contain treasure
	int k = 0; // counter to load data into rooms array one by one


	stack<coordinates>s;;

	int movement = 0; // tells us whuch room we are cuurently in

	bool flag = true; // to run the game

	bool win = false; // to check if we won or lose
	int headTail = 0;
	bool portal = false; // to check if our game ended by the portal
public:

	HauntedHouse()
	{
		rooms = 0;

	}

	int getrows(int n)
	{
		return r[n].getROWS();
	}
	int getcols(int n)
	{
		return r[n].getCOLS();
	}
	int getXcor(int n)
	{
		return r[n].getXcoordinate();
	}
	int getYcor(int n)
	{
		return r[n].getYcoordinate();
	}
	void readfile(string a)
	{
		ifstream file;

		file.open(a);

		char c;

		int p = 0;


		while (file.get(c))
		{



			if (p == 0)
			{
				r[k].setRows(c - '0');// c is in character to turn it into INT we sub 0 ascii
			}


			if (p == 2)
			{

				r[k].setcols(c - '0');
			}


			if (p == 4)
			{

				r[k].setPOINTx(c - '0');
			}

			if (p == 6)
			{
				r[k].setPOINTy(c - '0');
			}

			if (p > 7)
			{
				if (c == 'X' || c == '0' || c == 'D' || c == 'P' || c == 'G' || c == 'T')
				{
					if (c == 'T')
					{
						treasure = k;
					}
					r[k].setMatrix(c);
				}
			}

			p++;

		}

		file.close();
		k++;

	}


	void setrooms(string a)
	{
		rooms = stoi(a);   // changing from string to int

		r = new room[rooms]; // creating array of pointer of size equal to no of rooms
	}


	void console(int n, int ro, int c)
	{
		int g = 0;

		int x = ro + 1;
		int y = c + 1;
		Print(x, y);
		while (flag)
		{
			g = 0;
			switch ((g = _getch())) {
			case KEY_UP:
				if (x > 1 && isValid(n, x - 2, y - 1))  //validity according to orignal array and x>1 according to updated coordinates
					x = x - 1;
				Print(x, y);
				break;
			case KEY_DOWN:
				if (x < r[n].getROWS() && isValid(n, x, y - 1))
					x = x + 1;
				Print(x, y);
				break;
			case KEY_LEFT:
				if (y > 1 && isValid(n, x - 1, y - 2))
					y = y - 1;
				Print(x, y);
				break;
			case KEY_RIGHT:
				if (y < r[n].getCOLS() && isValid(n, x - 1, y))
					y = y + 1;
				Print(x, y);
				break;
			default:
				break;
			}
		}

	}

	void Print(int x, int y) {
		system("cls");




		char** temp = new char* [r[movement].getROWS()];
		for (int i = 0; i < r[movement].getROWS(); i++)
		{
			temp[i] = new char[r[movement].getCOLS()];
		}


		for (int i = 0; i < r[movement].getROWS(); i++)
		{
			for (int j = 0; j < r[movement].getCOLS(); j++)
			{
				temp[i][j] = r[movement].array()[i][j];
			}
		}
		char** map = new char* [r[movement].getROWS() + 2];

		for (int i = 0; i < r[movement].getROWS() + 2; i++)
		{
			map[i] = new char[r[movement].getCOLS() + 2];
		}

		for (int i = 0; i < r[movement].getROWS() + 2; i++)
		{
			for (int j = 0; j < r[movement].getCOLS() + 2; j++)
			{

				if (i == 0 || i == r[movement].getROWS() + 1 || j == 0 || j == r[movement].getCOLS() + 1)
				{
					map[i][j] = '#';
				}
				else {
					map[i][j] = temp[i - 1][j - 1];
				}
			}

		}



		coordinates l(x - 1, y - 1, movement);
		
		s.push(l);
		for (int i = 0; i < this->r[movement].getROWS() + 2; i++) {
			for (int j = 0; j < this->r[movement].getCOLS() + 2; j++)
				if (i == x && j == y)
				{
					if (map[i][j] == 'D')
					{
						cout << "game over " << endl;
						flag = false;
						system("cls");
						return;
					}
					if (map[i][j] == 'P')
					{
						static int count = 0;
						srand((time(0)));
						headTail = rand() % 2;

						if (count == 0 && headTail == 1) // tails
						{
							flag = false;
							portal = true;
							system("cls");
							return;
						}
						if (count > 0 && headTail == 1)
						{
							count++;

							while (isValid(movement, x, y) != true)
							{
								x = rand() % r[movement].getROWS();
								y = rand() % r[movement].getCOLS();
							}
							console(movement, x, y);
							return;
						}
						if (count >= 0 && headTail == 0)  // head
						{
							movement = rand() % rooms;
							count++;
							x = rand() % r[movement].getROWS();
							y = rand() % r[movement].getCOLS();
							Sleep(1000);


							if (move(movement, x, y) == false)
							{
								while (move(movement, x, y) != true)
								{
									movement = rand() % rooms;
									x = rand() % r[movement].getROWS();
									y = rand() % r[movement].getCOLS();
								}
							}
							console(movement, x, y);

							return;

						}
					}
					if (map[i][j] == 'G')
					{
						cout << "Gasper found ";
						movement = treasure;
						x = rand() % r[movement].getROWS();
						y = rand() % r[movement].getCOLS();
						if (move(movement, x, y) == false)
						{
							while (move(movement, x, y) != true)
							{
								movement = rand() % rooms;
								x = rand() % r[movement].getROWS();
								y = rand() % r[movement].getCOLS();
							}
						}
						console(treasure, x, y);
						return;
					}

					if (map[i][j] == 'T')
					{
						cout << "treasure found ";
						win = true;
						flag = false;
						system("cls");
						return;
					}
					cout << "*";



				}
				else
				{


					if (map[i][j] == '0')
					{
						cout << ' ';
					}
					if (map[i][j] == 'X')
					{
						cout << '|';

					}


					if (map[i][j] == 'D')
					{
						cout << ' ';
					}
					if (map[i][j] == '#')
					{
						cout << '#';
					}
					if (map[i][j] == 'G')
						cout << ' ';
					if (map[i][j] == 'P')
						cout << ' ';
					if (map[i][j] == 'T')
						cout << ' ';
				}
			cout << endl;
		}
	}

	bool isValid(int n, int x, int y)  // checling validity with respect to our original loaded array
	{
		char** check = r[n].array();

		if (check[x][y] == 'X')
		{
			return false;
		}
		else
			return true;


	}


	bool move(int n, int& x, int& y)
	{
		char** check = r[n].array();

		if (check[x][y] == 'T' || check[x][y] == 'D' || check[x][y] == 'X' || check[x][y] == 'P' || check[x][y] == 'G')
		{
			return false;
		}
		else
		{
			return true;



		}

	}
	void printPath()
	{
		system("cls");
		cout << "You took " << s.getsize() - 1 << "steps ";
		if (win)
			cout << " steps to reach treasure " << endl;
		if (!win && !portal)
			cout << "You were caught sneakin around by the devil. Your path to devil is as follow " << endl;
		if (portal)
			cout << "You were unlucky the spirits at the portal did not let you in. Your Black path is " << endl;
		s.print();
	}


	~HauntedHouse()
	{
		delete[]r;
	}

};
int main()
{
	HauntedHouse h;
	ifstream read;


	read.open("HauntedHouse.txt");

	string a;

	int i = 0;


	string* x = new string[5];
	for (; getline(read, a); i++)
	{

		x[i] = a;
		cout << a;

	}
	read.close();

	for (int l = 0; l < i; l++)
	{
		if (l == 0)
		{
			h.setrooms(x[l]); // send no of rooms 
		}
		else
		{
			h.readfile(x[l]);
		}

	}

	h.console(0, h.getXcor(0), h.getYcor(0));



	h.printPath();
	system("Pause");
	return 0;

}

