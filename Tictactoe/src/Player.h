using namespace std;



class Player{

private:
	/**
	 * Khoi tao gia tri
	 */
	void initStatus(){
		score = 0;
		moves = 0;
	}
protected:
public:

	string name;
	char sign;
	int score;
	int moves;

	/**
	 * Tao nguoi choi voi ten 
	 */
	Player( string n){
		this->name = n;
		sign = name[0];
		initStatus();
	}

	/**
	 * Set sign
	 */
	void setSign(char c){
		if ( c != 0 )
			sign = c;
	}

	/**
	 * In ra gia tri de kiem tra
	 */
	void showStatus(){
		cout << "Player " << name << " :" << endl;
		cout << "\tScore = " << score << endl;
	}

};
