using namespace std;

class Game {

private:
protected:
public:

	Board *board;
	int gameType;
	int peakScore = 1;

	Game(Board b) {
		this->board = &b;
	}

	/*
	 * Bat dau choi
	 */
	void welcome() {
		cout << "TICTACTOE v1.0" << endl;
		cout << "\t" << "1. Start game" << endl;
		cout << "\t" << "2. Help" << endl;
		cout << "\t" << "3. Exit" << endl;
		cout << "Choose: ";
		int opt;
		cin >> opt;
		cin.ignore();
		switch (opt) {
		case 1:
			// Bat dau choi
			startGame();
			break;
		case 2:
			// Huong dan choi
			showGuide();
			break;
		case 3:
			return;
		}
	}

	/*
	 * Bat dau choi
	 */
	void startGame() {
		initPlayer();
		initPeakScore();
		cout << "Start Game: " << endl;
		board->showStatus();
		Player *winner = &(board->players[0]);
		int currentMatch = 1;

		do {
			cout << "Match " << currentMatch++ << ": " << endl;
			board->startMatch();
			for (int i = 0; i++ < board->players.size();) {
				Player *tmpP = &(board->players[i]);
				if (winner->score < tmpP->score) {
					winner = tmpP;
				}
			}
			showPlayerRank(board->players);
		} while (winner->score < peakScore);

		// Thong bao nguoi thang cuoc
		cout << winner->name << " win!";
	}

	/*
	 * Nhap ten va tao nguoi choi:
	 */
	void initPlayer() {
		int numPlayer;
		cout << "Number of players: ";
		cin >> numPlayer;
		cin.ignore();

		for (int i = 0; i++ < numPlayer;) {
			string name;
			cout << "Enter the name of " << i
					<< "th player or \"-ai\" to create a bot: ";
			cin >> name;
			cin.ignore();
			Player player(name);
			board->addPlayer(player);
		}
	}

	void showPlayerRank(vector<Player> players) {
		cout << "Player:\t";
		for (int i = 0; i < players.size(); ++i) {
			Player &p = players[i];
			cout << p.name << "\t";
		}
		cout << endl << "Score";
		for (int i = 0; i++ < players.size(); ++i ) {
			Player &p = players[i];
			cout << p.score << "\t";
		}
	}

	/**
	 *
	 */
	void initPeakScore() {
		cout << "Score to win?:";
		cin >> peakScore;
		cin.ignore();
	}

	/**
	 * In ra huong dan choi
	 */
	void showGuide() {
		cout << "_______GUIDE_______" << endl;
		cout << "Day la co ca ro danh den cham 5 thi het." << endl;
	}

};
