#pragma once

#include <iostream>
#include <vector>
#include <random>

using namespace std;


class Tetris {
public:
	Tetris() {
		initialize();
	}

	void to_left() {
		if (is_left_available())
			current_position.y--;
	}
	void to_right() {
		if (is_right_available())
			current_position.y++;
	}
	void to_bottom() {
		if (is_bottom_available())
			current_position.x++;
		else {
			add_to_game_table();
			clean();
			if (current_position.x == 0 && current_position.y == 5)
				reset();
			create_new_stone();
			
		}
	}
	void turn_clockwise() {
		current_stone.turn_clockwise();

		if (!current_stone.is_collide(snapshot(current_position))) {
			return;
		}
		if (!current_stone.is_collide(snapshot(current_position.right()))) {
			current_position = current_position.right();
			return;
		}
		if (!current_stone.is_collide(snapshot(current_position.left()))) {
			current_position = current_position.left();
			return;
		}
		//if (!current_stone.is_collide(snapshot(current_position.right().right()))) {
		//	current_position.right().right();
		//	return;
		//}
		//if (!current_stone.is_collide(snapshot(current_position.left().left()))) {
		//	current_position.left().left();
		//	return;
		//}
		current_stone.turn_counterclockwise();
	}

	vector<vector<int>> print_game_table() {
		vector<vector<int>> vect;
		vect.resize(20);
		static int t_table[20][10]{};

		for (int i = 0; i < 20; i++) {
			for (int j = 0; j < 10; j++) {
				t_table[i][j] = table[i+3][j+3];
			}
		}

		auto s = current_stone.get_current_state();

		for (int i = current_position.x, ii = 0; i < current_position.x + 5; i++, ii++) {
			for (int j = current_position.y, jj = 0; j < current_position.y + 5; j++, jj++) {
				if (s[ii][jj] == 1) {
					t_table[i-3][j-3] = 1;
				}
			}
		}


		for (int i = 0; i < 20; i++) {
			vector<int> v;
			v.resize(10);
			for (int j = 0; j < 10; j++) {
				v.at(j) = t_table[i][j];
			}
			vect[i] = v;
		}

		return vect;
	}
private:
	int table[20 + 6][10 + 6]{};

	struct Point {
		Point() :x{}, y{} {}
		Point(int x, int y) :x{ x }, y{ y }{}
		void set(int x, int y) {
			this->x = x;
			this->y = y;
		}
		Point right() {
			Point p;
			p.x = x;
			p.y = y + 1;
			return p;
		}
		Point left() {
			Point p;
			p.x = x;
			p.y = y - 1;
			return p;
		}
		Point bottom() {
			Point p;
			p.x = x + 1;
			p.y = y;
			return p;
		}
		int x, y;
	};

	struct Stone {
	private:
		int state{};
		vector<vector<vector<int>>> states;
	public:
		void turn_clockwise() {
			state++;
			if (state == 4)
				state = 0;
		}
		void turn_counterclockwise() {
			state--;
			if (state == -1)
				state = 3;
		}

		bool is_collide(vector<vector<int>> view) {
			for (int i = 0; i < 5; i++)
				for (int j = 0; j < 5; j++)
					if (view[i][j] == 1 && states[state][i][j] == 1)
						return true;
			return false;
		}
		vector<vector<int>> get_current_state() {
			return states[state];
		}

		void set_states(vector<vector<vector<int>>> states) {
			this->states = states;
		}
	};

	vector<Stone> stones;
	Stone current_stone;

	Point current_position;


	void initialize_L_stone() {
		vector<vector<vector<int>>> vect
		{
			{
				{0, 0, 0, 0, 0,},
				{0, 0, 1, 0, 0,},
				{0, 0, 1, 0, 0,},
				{0, 0, 1, 1, 0,},
				{0, 0, 0, 0, 0,}
			},
			{
				{0, 0, 0, 0, 0,},
				{0, 0, 0, 0, 0,},
				{0, 1, 1, 1, 0,},
				{0, 1, 0, 0, 0,},
				{0, 0, 0, 0, 0,}
			},
			{
				{0, 0, 0, 0, 0,},
				{0, 1, 1, 0, 0,},
				{0, 0, 1, 0, 0,},
				{0, 0, 1, 0, 0,},
				{0, 0, 0, 0, 0,}
			},
			{
				{0, 0, 0, 0, 0,},
				{0, 0, 0, 1, 0,},
				{0, 1, 1, 1, 0,},
				{0, 0, 0, 0, 0,},
				{0, 0, 0, 0, 0,}
			}
		};
		Stone stone;
		stone.set_states(vect);
		stone.get_current_state();
		stones.push_back(stone);
	}
	void initialize_op_L_stone() {
		vector<vector<vector<int>>> vect
		{
			{
				{0, 0, 0, 0, 0,},
				{0, 0, 1, 0, 0,},
				{0, 0, 1, 0, 0,},
				{0, 1, 1, 0, 0,},
				{0, 0, 0, 0, 0,}
			},
			{
				{0, 0, 0, 0, 0,},
				{0, 1, 0, 0, 0,},
				{0, 1, 1, 1, 0,},
				{0, 0, 0, 0, 0,},
				{0, 0, 0, 0, 0,}
			},
			{
				{0, 0, 0, 0, 0,},
				{0, 0, 1, 1, 0,},
				{0, 0, 1, 0, 0,},
				{0, 0, 1, 0, 0,},
				{0, 0, 0, 0, 0,}
			},
			{
				{0, 0, 0, 0, 0,},
				{0, 0, 0, 0, 0,},
				{0, 1, 1, 1, 0,},
				{0, 0, 0, 1, 0,},
				{0, 0, 0, 0, 0,}
			}
		};
		Stone stone;
		stone.set_states(vect);
		stones.push_back(stone);
	}
	void initialize_tri_stone() {
		vector<vector<vector<int>>> vect
		{
			{
				{0, 0, 0, 0, 0,},
				{0, 0, 1, 0, 0,},
				{0, 1, 1, 1, 0,},
				{0, 0, 0, 0, 0,},
				{0, 0, 0, 0, 0,}
			},
			{
				{0, 0, 0, 0, 0,},
				{0, 0, 1, 0, 0,},
				{0, 0, 1, 1, 0,},
				{0, 0, 1, 0, 0,},
				{0, 0, 0, 0, 0,}
			},
			{
				{0, 0, 0, 0, 0,},
				{0, 0, 0, 0, 0,},
				{0, 1, 1, 1, 0,},
				{0, 0, 1, 0, 0,},
				{0, 0, 0, 0, 0,}
			},
			{
				{0, 0, 0, 0, 0,},
				{0, 0, 1, 0, 0,},
				{0, 1, 1, 0, 0,},
				{0, 0, 1, 0, 0,},
				{0, 0, 0, 0, 0,}
			}
		};
		Stone stone;
		stone.set_states(vect);
		stones.push_back(stone);
	}
	void initialize_quad_stone() {
		vector<vector<vector<int>>> vect
		{
			{
				{0, 0, 0, 0, 0,},
				{0, 1, 1, 0, 0,},
				{0, 1, 1, 0, 0,},
				{0, 0, 0, 0, 0,},
				{0, 0, 0, 0, 0,}
			},
			{
				{0, 0, 0, 0, 0,},
				{0, 1, 1, 0, 0,},
				{0, 1, 1, 0, 0,},
				{0, 0, 0, 0, 0,},
				{0, 0, 0, 0, 0,}
			},
			{
				{0, 0, 0, 0, 0,},
				{0, 1, 1, 0, 0,},
				{0, 1, 1, 0, 0,},
				{0, 0, 0, 0, 0,},
				{0, 0, 0, 0, 0,}
			},
			{
				{0, 0, 0, 0, 0,},
				{0, 1, 1, 0, 0,},
				{0, 1, 1, 0, 0,},
				{0, 0, 0, 0, 0,},
				{0, 0, 0, 0, 0,}
			}
		};
		Stone stone;
		stone.set_states(vect);
		stones.push_back(stone);
	}
	void initialize_Z_stone() {
		vector<vector<vector<int>>> vect
		{
			{
				{0, 0, 0, 0, 0,},
				{0, 1, 1, 0, 0,},
				{0, 0, 1, 1, 0,},
				{0, 0, 0, 0, 0,},
				{0, 0, 0, 0, 0,}
			},
			{
				{0, 0, 0, 0, 0,},
				{0, 0, 0, 1, 0,},
				{0, 0, 1, 1, 0,},
				{0, 0, 1, 0, 0,},
				{0, 0, 0, 0, 0,}
			},
			{
				{0, 0, 0, 0, 0,},
				{0, 1, 1, 0, 0,},
				{0, 0, 1, 1, 0,},
				{0, 0, 0, 0, 0,},
				{0, 0, 0, 0, 0,}
			},
			{
				{0, 0, 0, 0, 0,},
				{0, 0, 0, 1, 0,},
				{0, 0, 1, 1, 0,},
				{0, 0, 1, 0, 0,},
				{0, 0, 0, 0, 0,}
			}
		};
		Stone stone;
		stone.set_states(vect);
		stones.push_back(stone);
	}
	void initialize_op_Z_stone() {
		vector<vector<vector<int>>> vect
		{
			{
				{0, 0, 0, 0, 0,},
				{0, 0, 1, 1, 0,},
				{0, 1, 1, 0, 0,},
				{0, 0, 0, 0, 0,},
				{0, 0, 0, 0, 0,}
			},
			{
				{0, 0, 0, 0, 0,},
				{0, 1, 0, 0, 0,},
				{0, 1, 1, 0, 0,},
				{0, 0, 1, 0, 0,},
				{0, 0, 0, 0, 0,}
			},
			{
				{0, 0, 0, 0, 0,},
				{0, 0, 1, 1, 0,},
				{0, 1, 1, 0, 0,},
				{0, 0, 0, 0, 0,},
				{0, 0, 0, 0, 0,}
			},
			{
				{0, 0, 0, 0, 0,},
				{0, 1, 0, 0, 0,},
				{0, 1, 1, 0, 0,},
				{0, 0, 1, 0, 0,},
				{0, 0, 0, 0, 0,}
			}
		};
		Stone stone;
		stone.set_states(vect);
		stones.push_back(stone);
	}
	void initialize_I_stone() {
		vector<vector<vector<int>>> vect
		{
			{
				{0, 0, 0, 0, 0},
				{0, 0, 1, 0, 0},
				{0, 0, 1, 0, 0},
				{0, 0, 1, 0, 0},
				{0, 0, 1, 0, 0}
			},
			{
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{1, 1, 1, 1, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0}
			},
			{
				{0, 0, 0, 0, 0},
				{0, 0, 1, 0, 0},
				{0, 0, 1, 0, 0},
				{0, 0, 1, 0, 0},
				{0, 0, 1, 0, 0}
			},
			{
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0},
				{1, 1, 1, 1, 0},
				{0, 0, 0, 0, 0},
				{0, 0, 0, 0, 0}
			}
		};
		Stone stone;
		stone.set_states(vect);
		stones.push_back(stone);
	}

	void initialize_stones() {
		initialize_L_stone();
		initialize_op_L_stone();
		initialize_tri_stone();
		initialize_quad_stone();
		initialize_Z_stone();
		initialize_op_Z_stone();
		initialize_I_stone();
	}

	void initialize_game_table() {
		for (int i = 0; i < 26; i++)
			for (int j = 0; j < 14; j++)
				table[i][j] = 0;

		for (int i = 23; i < 26; i++)
			for (int j = 0; j < 14; j++)
				table[i][j] = 1;

		for (int i = 0; i < 26; i++)
			for (int j = 0; j < 3; j++)
				table[i][j] = 1;

		for (int i = 0; i < 26; i++)
			for (int j = 13; j < 16; j++)
				table[i][j] = 1;
	}
	void initialize() {
		initialize_game_table();
		initialize_stones();
		create_new_stone();
	}





	vector<vector<int>> snapshot(Point p) {
		vector<vector<int>> t;

		for (int i = p.x; i < p.x + 5; i++) {
			vector<int> s;
			for (int j = p.y; j < p.y + 5; j++) {
				s.push_back(table[i][j]);
			}
			t.push_back(s);
		}
		return t;

	}

	void print_snapshot(vector<vector<int>> snap) {

		for (int i = 0; i < snap.size(); i++) {
			for (int j = 0; j < snap[i].size(); j++) {
				if (snap[i][j] == 0)
					cout << "  ";
				if (snap[i][j] == 1)
					cout << "##";
			}
			cout << endl;
		}
	}

	bool is_left_available() {
		if (!current_stone.is_collide(snapshot(current_position.left())))
			return true;
		else
			return false;
	}
	bool is_right_available() {

		if (!current_stone.is_collide(snapshot(current_position.right())))
			return true;
		else
			return false;
	}
	bool is_bottom_available() {

		if (!current_stone.is_collide(snapshot(Point(current_position.x + 1, current_position.y))))
			return true;
		else
			return false;
	}

	void add_to_game_table() {
		auto s = current_stone.get_current_state();
		for (int i = current_position.x, ii = 0; i < current_position.x + 5; i++, ii++) {
			for (int j = current_position.y, jj = 0; j < current_position.y + 5; j++, jj++) {
				if (s[ii][jj] == 1)
					table[i][j] = 1;
			}
		}
	}

	void clean() {
		for (int i = 22; i > 3;) {
			bool cont = true;

			for (int j = 3; j < 13; j++)
				if (table[i][j] == 0) {
					cont = false;
					i--;
					break;
				}


			if (cont)
				for (int ii = i; ii > 0; ii--)
					for (int j = 3; j < 13; j++)
						table[ii][j] = table[ii - 1][j];

		}
	}
	void create_new_stone() {
		current_stone = stones[m_random()];
		current_position = Point(0, 5);
	}
	int m_random() {
		std::random_device dev;
		std::mt19937 rng(dev());
		std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 6); // distribution in range [1, 6]

		return dist6(rng);
	}
	void reset() {
		initialize_game_table();
		create_new_stone();
	}



};
