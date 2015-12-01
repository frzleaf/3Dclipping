#include <vector>
#include <stdlib.h>
using namespace std;

class Board {

private:
	/**
	 * Khoi tao ban choi
	 * 	- Khoi tao gia tri cua tat ca cac o
	 * 	- Goi ham reset() -> de tao ban moi
	 * 	- Dat matchStatus bang MATCH_STATUS_INIT
	 */
	void init() {
		// Kiem tra do dai va rong da duoc dat chua
		if (!(heigh > 0 && width > 0 && heigh <= MAX_WIDTH
				&& width <= MAX_HEIGHT)) {
			cout << "Invalid width | height";
			return;
		}
		// Khoi tao gia tri
		values = new char*[heigh];
		for (int i = 0; i < heigh; ++i) {
			values[i] = new char[width];
		}
		reset();
		cout << "Board is created with w/h: " << width << "/" << heigh << endl;
		matchStatus = MATCH_STATUS_INIT;
	}

	int DIRECTION[8][2] = {
			{-1, -1},
			{-1,  0},
			{-1,  1},
			{ 0,  1},
			{ 1,  1},
			{ 1,  0},
			{ 1, -1},
			{ 0, -1}
	};


protected:
public:

	static const int MAX_WIDTH = 100;
	static const int MAX_HEIGHT = 100;

	static const char MATCH_STATUS_INIT = 1;
	static const char MATCH_STATUS_INPLAY = 2;
	static const char MATCH_STATUS_ONPAUSE = 3;
	static const char MATCH_STATUS_OVER = 4;

	static const int LENGTH_TO_WIN = 5;



	unsigned char GO_FIRST_ = 0;
	int width, heigh;
	char **values;
	char matchStatus;
	vector<Player> players;

	/*
	 * Tao ban voi chieu rong va cao
	 */
	Board(int w, int h) {
		width = w;
		heigh = h;
		init();
	}

	/*
	 * Tao ban vuong
	 */
	Board(int size) {
		heigh = width = size;
		init();

	}

	/*
	 * Them nguoi choi vao ban choi
	 */
	void addPlayer(Player p) {
		players.push_back(p);
	}

	/**
	 * Khoi dong van moi, dam bao dieu kien:
	 *	- So nguoi choi bang 2 hoac hon
	 * 	- Gia tri matchStatus phai khac MATCH_STATUS_INPLAY
	 */
	void startMatch() {

		bool satisfying = true;

		if (players.size() < 2) {			// khong du nguoi
			cout << "Not enough player";
			satisfying = false;
		}

		if (matchStatus == MATCH_STATUS_INPLAY) {	// Dang choi
			cout << "Game is in play";
			satisfying = false;
		}

		if (satisfying) {
			matchStatus = MATCH_STATUS_INPLAY;
		}

		picknMove();
	}

	/**
	 * Hien thi ban choi
	 */
	void showMoves() {
		cout << "Board: " << endl;
		cout << "  ";
		for (int j = 0; j < width; ++j) {
			if (j < 10)
				cout << " " << j << " ";
			else
				cout << " " << j;
		}
		cout << endl;
		for (int i = 0; i < heigh; ++i) {
			if (i < 10)
				cout << " " << i;
			else
				cout << i;
			for (int j = 0; j < width; ++j) {
				if (values[i][j]) {	//TODO print something
					cout << " " << values[i][j] << " ";
				} else {
					cout << " . ";
				}
			}
			cout << endl;
		}
	}

	/**
	 * Chon va danh
	 */
	void picknMove() {

		unsigned char turn = GO_FIRST_;
		int numPlayer = players.size();

		int remain = 0;
		for (int i = 0, l = width * heigh; i < l; ++i)
			remain += (values[i] == 0);

		Player *inturnPlayer;

		int x, y;

		while (matchStatus == MATCH_STATUS_INPLAY && remain > 0 ) {
			showMoves();
			inturnPlayer = &players[turn];

			do {
			cout << inturnPlayer->name << "'s turn" << endl;
			cout << "Pick a cell (r/c) in range "
						<< "(0-" << width-1 << " / "
						<< "0-" << heigh-1 << "):";
			cin >> y >> x;
			cin.ignore();
			}
			while ( !(x >= 0 && x < width && y >= 0 && y < heigh ) || values[y][x] );

			values[y][x] = inturnPlayer->sign;
			--remain;
			turn = ++turn % numPlayer;
			checkWinner(inturnPlayer, y, x);
		}
		showMoves();
	}

	/**
	 * Kiem tra thang hay khong
	 */
	void checkWinner(Player *p, int r, int c){
		int len = 0;
		for ( int i = 0, tmp = 0 ; i < 4 ; ++i ){
			tmp = maxLength(r, c, i) + maxLength(r, c, 7 - i);
			if ( len < tmp )
				len = tmp;
		}
		--len; // The cell(r,c) counts itself -> decrease by 1
		cout << "MAXLENGTH = " << len << endl;
		if ( len == LENGTH_TO_WIN ){
			cout << p->name << " scored!" << endl;
			p->score++;
			matchStatus = MATCH_STATUS_OVER;
		}
	}

	/**
	 * Tinh nuoc di dai nhat cua cac o xung quanh:
	 * 			|0|1|2|
	 * 			|3| |4|
	 * 			|5|6|7|
	 */
	int maxLength(int r, int c, int direction ){

		// O trang -> tra ve 0
		if ( !values[r][c] ) return 0;

		// Kiem tra huong dung hay khong?
		if ( direction < 0 || direction > 7){
			return 1;
		}

		int r2 = r + DIRECTION[direction][0];
		int c2 = c + DIRECTION[direction][1];

		if ( coordinateIsValid(r2,c2)
			 && values[r][c] == values[r2][c2] ){
				return 1 + maxLength(r2, c2, direction);
		} else {
			return 1;
		}
	}

	/**
	 * Kiem tra toa do co bi sai hay ko
	 */
	bool coordinateIsValid(int r, int c){
		return r >= 0 && r < heigh && c >= 0 && c < width;
	}

	/**
	 * Set the values by 0 and matchStatus by MATCH_STATUS_INIT
	 */
	void reset() {
		// The values must be 0000 before
		for (int i = 0; i < heigh; ++i) {
			for (int j = 0; j < width; ++j) {
				values[i][j] = 0;
			}
		}
		// The matchStatus must be MATCH_STATUS_INIT
		matchStatus = MATCH_STATUS_INIT;
	}

	/**
	 * Show all status
	 */
	void showStatus() {
		cout << "Board status: " << endl;
		cout << "\t" << "Width x Height: " << width << "x" << heigh << endl;
		cout << "\t" << "matchStatus: " << matchStatus << "(" << MATCH_STATUS_INIT
				<< " " << MATCH_STATUS_INPLAY << " " << MATCH_STATUS_OVER << ")"
				<< endl;
		cout << "\t" << "Number Player: " << players.size() << endl;
	}
};

