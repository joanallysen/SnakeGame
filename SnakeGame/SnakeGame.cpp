#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>

using namespace std;

// DON'T RESET
int width = 70;
int height = 24;
int speed = 40;
bool dieUponHittingWall = false;
bool continuousGrow = false;

// RESET
int score = 0;

vector<vector<char>> panel{};

vector<pair<int, int>> playerPos{  };
vector<pair<int, int>> playerPos2{ };

pair<int, int> prevPlayerPos{};
pair<int, int> prevPlayerPos2{};

pair<int, int> fruitPos{10, 12};

bool isGameOver = false;
bool isMultiplayer = false;

enum Dir{UP, LEFT, DOWN, RIGHT};
enum Winner{PLAYER1, PLAYER2};
Dir playerDir = LEFT;
Dir playerDir2 = DOWN;

Winner isWinner{};


void drawPanel() {
	cout << string(width + 1, '-') << endl;

	for (int i = 0; i < height; i++){
		vector<char> temp{};
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width-1) {
				temp.push_back('|');
				cout << '|';
                continue;
			}

            //Detect if it's the player
            if (i == playerPos[0].second && j == playerPos[0].first) {
                temp.push_back('O');
                cout << 'O';
                continue;
            }
            // Don't need to check the head again
            bool lilTail = false;
            for (int k = 1; k < playerPos.size(); k++){
                if (i == playerPos[k].second && j == playerPos[k].first) {
                    temp.push_back('o');
                    cout << 'o';
                    lilTail = true;
                }
            }
            if (lilTail) {
                continue;
            }

            if (i == fruitPos.second && j == fruitPos.first) {
                temp.push_back('#');
                cout << '#';
                continue;
            }

            if (isMultiplayer) {
                if (i == playerPos2[0].second && j == playerPos2[0].first) {
                    temp.push_back('G');
                    cout << 'G';
                    continue;
                }
                // Don't need to check the head again
                bool lilTail = false;
                for (int k = 1; k < playerPos2.size(); k++) {
                    if (i == playerPos2[k].second && j == playerPos2[k].first) {
                        temp.push_back('o');
                        cout << 'o';
                        lilTail = true;
                    }
                }
                if (lilTail) {
                    continue;
                }
            }


			temp.push_back(' ');
			cout << ' ';
		}
		panel.push_back(temp);
		cout << endl;
	}

	cout << string(width + 1, '-') << endl;
}

void playerControl() {
    if (_kbhit()) {
        auto pressedKey = _getch();
        // Getting the pressed key
        if (isMultiplayer) {
            switch (pressedKey) {
            case 'i':
                if (playerDir2 != DOWN)
                    playerDir2 = UP;
                break;
            case 'j':
                if (playerDir2 != RIGHT)
                    playerDir2 = LEFT;
                break;
            case 'k':
                if (playerDir2 != UP)
                    playerDir2 = DOWN;
                break;
            case 'l':
                if (playerDir2 != LEFT)
                    playerDir2 = RIGHT;
                break;
            }
        }

        switch (pressedKey) {
        case 'w':
            if (playerDir != DOWN)
                playerDir = UP;
            break;
        case 'a':
            if (playerDir != RIGHT)
                playerDir = LEFT;
            break;
        case 's':
            if (playerDir != UP)
                playerDir = DOWN;
            break;
        case 'd':
            if (playerDir != LEFT)
                playerDir = RIGHT;
            break;
        case 'x':
            isGameOver = true;
            break;
        }
    }
}

void generateRandomFruit() {
    srand(time(NULL));
    fruitPos.first = (rand() % (width-3)) + 1; // 0 - 67 -> 1 - 68
    fruitPos.second = (rand() % height); //0-23
}

void addTail(int playerNumber) {
    if (playerNumber == 1) {
        playerPos.push_back(prevPlayerPos);
        
    }
    else if (playerNumber == 2) {
        playerPos2.push_back(prevPlayerPos2);
    }
}

void checkCollision() {
    // CHECKING IF PLAYER 1 HAS HIT FRUIT
    if (playerPos[0].second == fruitPos.second && playerPos[0].first == fruitPos.first) {
        generateRandomFruit();
        addTail(1);
        score+=100;
    }

    // player 1 hit the wall
    if (dieUponHittingWall) {
        if (playerPos[0].second == height || playerPos[0].first == width || playerPos[0].second == 0 || playerPos[0].first == 0) {
            isWinner = PLAYER2;
            cout << "Player 1 hit the wall!" << endl;
            isGameOver = true;
            return;
        }
    }
    
    // player 1 hit its own tail
    for (int i = 1; i < playerPos.size(); i++) {
        if (playerPos[0] == playerPos[i]) {
            cout << "Player 1 hit its own tail!" << endl;
            isWinner = PLAYER1;
            isGameOver = true;
            return;
        }
    }

    // check if player 1 hit wall and send to opposite
    if (playerPos[0].second == height) {
        pair<int, int> newMove = { playerPos[0].first, 0}; playerPos.insert(playerPos.begin(), newMove); playerPos.pop_back();
    }
    else if (playerPos[0].first == (width-1)) {
        pair<int, int> newMove = { 1, playerPos[0].second}; playerPos.insert(playerPos.begin(), newMove); playerPos.pop_back();
    }
    else if (playerPos[0].second == -1) {
        pair<int, int> newMove = { playerPos[0].first, height-1}; playerPos.insert(playerPos.begin(), newMove); playerPos.pop_back();
    }
    else if (playerPos[0].first == 0) {
        pair<int, int> newMove = { width-2, playerPos[0].second }; playerPos.insert(playerPos.begin(), newMove); playerPos.pop_back();
    }
    
    if (!isMultiplayer)
        return;

    // player 2 fruit
    if (playerPos2[0].second == fruitPos.second && playerPos2[0].first == fruitPos.first) {
        generateRandomFruit();
        addTail(2);
        score += 100;
    }

    if (dieUponHittingWall) {
        if (playerPos2[0].second == height || playerPos2[0].first == width || playerPos2[0].second == 0 || playerPos2[0].first == 0) {
            cout << "Player 2 hit the wall!" << endl;
            isWinner = PLAYER1;
            isGameOver = true;
            return;
        }
    }


    // if player 2 hit player 1 tail
    for (int i = 1; i < playerPos.size(); i++) {
        if (playerPos2[0] == playerPos[i]) {
            cout << "Player 2 hit player 1 tail!" << endl;
            isWinner = PLAYER1;
            isGameOver = true;
        }
    }

    // if player 1 hit player 2 tail
    for (int i = 1; i < playerPos2.size(); i++) {
        if (playerPos[0] == playerPos2[i]) {
            cout << "Player 1 hit Player 2 tail!" << endl;
            isWinner = PLAYER2;
            isGameOver = true;
        }
    }

    //border
    if (playerPos2[0].second == height) {
        pair<int, int> newMove = { playerPos2[0].first, 0 }; playerPos2.insert(playerPos2.begin(), newMove); playerPos2.pop_back();
    }
    else if (playerPos2[0].first == (width - 1)) {
        pair<int, int> newMove = { 1, playerPos2[0].second }; playerPos2.insert(playerPos2.begin(), newMove); playerPos2.pop_back();
    }
    else if (playerPos2[0].second == -1) {
        pair<int, int> newMove = { playerPos2[0].first, height - 1 }; playerPos2.insert(playerPos2.begin(), newMove); playerPos2.pop_back();
    }
    else if (playerPos2[0].first == 0) {
        pair<int, int> newMove = { width - 2, playerPos2[0].second }; playerPos2.insert(playerPos2.begin(), newMove); playerPos2.pop_back();
    }

    // player 2 hit its own tail
    for (int i = 1; i < playerPos2.size(); i++) {
        if (playerPos2[0] == playerPos2[i]) {
            cout << "You hit your own tail!" << endl;
            isWinner = PLAYER1;
            isGameOver = true;
            return;
        }
    }
}

void debug() {
    for (int i = 0; i < playerPos.size(); i++) {
        cout << "{" << playerPos[i].first << ", " << playerPos[i].second << "} " << endl;
    }
    
    cout << "fruit pos: " << "{" << fruitPos.first << ", " << fruitPos.second << "} " << endl;
}

void updatePlayerPosition() {
    prevPlayerPos = { playerPos.back().first, playerPos.back().second};
    int newMove{};
    switch (playerDir) {
    case UP:
        newMove = playerPos[0].second - 1;
        playerPos.insert(playerPos.begin(), { playerPos[0].first, newMove});
        playerPos.pop_back();
        break;
    case LEFT:
        newMove = playerPos[0].first - 1;
        playerPos.insert(playerPos.begin(), { newMove, playerPos[0].second });
        playerPos.pop_back();
        break;
    case DOWN:
        newMove = playerPos[0].second + 1;
        playerPos.insert(playerPos.begin(), { playerPos[0].first, newMove });
        playerPos.pop_back();
        break;
    case RIGHT:
        newMove = playerPos[0].first + 1;
        playerPos.insert(playerPos.begin(), { newMove, playerPos[0].second});
        playerPos.pop_back();
        break;
    }

    if (!isMultiplayer)
        return;

    prevPlayerPos2 = { playerPos2.back().first, playerPos2.back().second };
    switch (playerDir2) {
    case UP:
        newMove = playerPos2[0].second - 1;
        playerPos2.insert(playerPos2.begin(), { playerPos2[0].first, newMove });
        playerPos2.pop_back();
        break;
    case LEFT:
        newMove = playerPos2[0].first - 1;
        playerPos2.insert(playerPos2.begin(), { newMove, playerPos2[0].second });
        playerPos2.pop_back();
        break;
    case DOWN:
        newMove = playerPos2[0].second + 1;
        playerPos2.insert(playerPos2.begin(), { playerPos2[0].first, newMove });
        playerPos2.pop_back();
        break;
    case RIGHT:
        newMove = playerPos2[0].first + 1;
        playerPos2.insert(playerPos2.begin(), { newMove, playerPos2[0].second });
        playerPos2.pop_back();
        break;
    }

}

void update() {
    int tempTime = 0;
    while (!isGameOver)
    {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 });
        drawPanel();
        playerControl();
        updatePlayerPosition();
        checkCollision();

        cout << "Current Score : " << score << endl;

        Sleep(100 - speed);
        
        if (!continuousGrow)
            continue;

        if (tempTime % 50 == 0) {
            addTail(1);
            if (isMultiplayer) {
                addTail(2);
            }
        }

        tempTime++;
    }
}

void singlePlayerSetup() {
    playerDir = LEFT;
    
    playerPos = { {width / 2, height / 2} };
    update();
}

void multiPlayerSetup() {
    isMultiplayer = true;
    
    playerDir = DOWN;
    playerPos = { {width / 2 + 2 , height / 2} };
    playerPos2 = { {width / 2 - 2, height / 2} };

    update();

    if (isGameOver) {
        if (isWinner == PLAYER1) {
            cout << "PLAYER 1 WINS" << endl;
        }
        else if (isWinner == PLAYER2) {
            cout << "PLAYER 2 WINS" << endl;
        }
    }
}

void mainMenu();

int askInput(int numOfCase = INT_MAX) {
    int userInput{};

    cin >> userInput;
    
    while (cin.fail() || userInput > numOfCase || userInput < 1) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "That's not part of the option!, please Input the number" << endl;
        cout << "Option: ";
        cin >> userInput;
    }
    
    return userInput;
}

void reset() {
    score = 0;
    isGameOver = false;
    isMultiplayer = false;
    panel = {};
    prevPlayerPos = {};
    prevPlayerPos2 = {};
    playerPos = {};
    playerPos2 = {};
    isWinner = {};
}

void askPlayAgain() {
    cout << "Do you want to play again?" << endl;
    cout << "1. Yes\n2. No \nYour Option: ";

    int userInput = askInput(2);
    if (userInput == 1) {
        reset();
        mainMenu();
    }
    else if (userInput == 2) {
        return;
    }
}

void settingsSetup() {
    system("cls");
    cout << "----------------SETTINGS----------------" << endl;
    cout << "1. Game panel size" << endl;
    cout << "Width: " << width << endl;
    cout << "Height: " << height << endl;
    cout << "2. Snake speed: " << speed << endl;
    cout << "3. Death upon hitting a wall : " << boolalpha << dieUponHittingWall << endl;
    cout << "4. (MULTIPLAYER) Tail will grow every few seconds: " << boolalpha << continuousGrow << endl;
    cout << "5. Return to main menu" << endl;
    cout << "----------------------------------------" << endl;
    cout << "What do you want to change? " << endl;
    cout << "Option: ";

    int userInput = askInput(5);

    switch (userInput) {
        case 1:
            cout << "Please input new width and height!" << endl;
            cout << "*width higher then 70 may lead to screen issues\nHeight: ";
            cout << "Width: ";
            width = askInput();
            cout << "*height higher then 24 may lead to screen issues\nHeight: ";
            height = askInput();
            settingsSetup();
            break;
        case 2:
            cout << "Please input new speed!" << endl;
            cout << "*maximum speed is 100\nSpeed: ";
            speed = askInput(100);
            settingsSetup();
            break;
        case 3:
            cout << "Do you want to die upon hitting wall?" << endl;
            cout << "1. Yes\n2. No" << endl;
            cout << "Option: ";
            userInput = askInput(2);

            if (userInput == 1) {
                dieUponHittingWall = true;
            }
            else if (userInput == 2) {
                dieUponHittingWall = false;
            }

            settingsSetup();
            break;
        case 4:
            cout << "Do you want the tail to grow continuously?" << endl;
            cout << "1. Yes\n2. No" << endl;
            cout << "Option: ";
            
            userInput = askInput(2);
            if (userInput == 1) {
                continuousGrow = true;
            }
            else if (userInput == 2) {
                continuousGrow = false;
            } 

            settingsSetup();
            break;
        case 5:
            cout << "Redirecting..." << endl;
            Sleep(200);
            return;
            break;
    }
    return;
}

void mainMenu() {
    system("cls");
    cout << R"(
 _____  _   _   ___   _   __ _____ 
/  ___|| \ | | / _ \ | | / /|  ___|
\ `--. |  \| |/ /_\ \| |/ / | |__  
 `--. \| . ` ||  _  ||    \ |  __| 
/\__/ /| |\  || | | || |\  \| |___ 
\____/ \_| \_/\_| |_/\_| \_/\____/ 
        )" << endl;

    cout << "Welcome to the old-school snake game!" << endl;
    cout << "You can play either singleplayer or multiplayer!, please select!" << endl;
    cout << "1. Singleplayer\n2. Multiplayer (test mode)\n3. Additional Settings \nYour Option: ";
    

    int userInput = askInput(3);

    cout << "Thank you for selecting! redirecting.." << endl;
    Sleep(200);
    system("cls");

    if (userInput == 1) {
        singlePlayerSetup();
    }
    else if (userInput == 2) {
        multiPlayerSetup();
    }
    else if (userInput == 3) {
        settingsSetup();
        mainMenu();
        return;
    }
    askPlayAgain();
}

int main()
{
    mainMenu();
}

