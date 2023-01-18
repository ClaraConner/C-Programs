/*
Updated Snake Game
by Clara Conner
Written on Visual Studio 2019

Changelog:
    Added pause/unpause by pressing 'p'
    Added more fruit by choice of user
    Added initial dialogue/instructions
    Player can replay after death
    Player can choose to die when they hit a wall

Future Possibilities:
    Add a 'speed fruit' that will give extra points + change snake speed
    Allow user to adjust dimensions of the board
    Separate the new game feature into a new function
    Fix possible bugs vv

Possible bugs:
    If the user inputs something that the program is not expecting
    The newFruit() function could create fruit in the same location

*/

#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool gameOver;
bool wallDeath; //determines of the player will die when they hit a hall
bool pause = false;

const int width = 20;
const int height = 20;
int speed = 7;
int x, y, score, highscore;
int tailXCoords[100], tailYCoords[100];
int lengthOfTail = 0;

const int maxFruit = 50;    //max fruits allowed on board
int numberFruit;
int fruitCoords[2][maxFruit];   //array with the coordinates of the fruit

enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirecton dir;


void generateFruit() {  //generates fruits on screen

    //generates fruits
    for (int i = 0; i < numberFruit; i++) {
    fruitCoords[0][i] = rand() % width;
    fruitCoords[1][i] = rand() % height;
    }

}

boolean checksIfFruitExists(int w, int h) { //checks if fruit exists at a given coordinate

    for (int i = 0; i < numberFruit; i++) {

        if (w == fruitCoords[0][i] && h == fruitCoords[1][i]) {
            return true;
        }
    }
    return false;

}

void newFruit(int i) {  //draws new fruit

    fruitCoords[0][i] = rand() % width;
    fruitCoords[1][i] = rand() % height;

}

boolean checksIfFruitIsCollected(int a, int b)  //compares snakes location with fruit location
{    
    for (int i = 0; i < numberFruit; i++) {
        if (a == fruitCoords[0][i] && b == fruitCoords[1][i]) {
            newFruit(i);
            return true;
        }
    }
    return false;
}

void Setup()
{
    dir = STOP;
    x = width / 2;
    y = height / 2;
    generateFruit();
    score = 0;
    gameOver = false;
}

void drawBorder() 
{
for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
}

void Draw()
{
    system("cls"); //system("clear");
    drawBorder();
    Sleep(speed); //adjusts speed on snake
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            if (j == 0)
                cout << "#";
            if (i == y && j == x)
                cout << "O";
            else if (checksIfFruitExists(j, i))
                cout << "F";
            else
            {
                bool print = false;
                for (int k = 0; k < lengthOfTail; k++)
                {
                    if (tailXCoords[k] == j && tailYCoords[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }

            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    drawBorder();
    cout << "Score: " << score << endl;
    cout << "Highscore: " << highscore << endl;
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'p':
            pause = !pause; //pauses or unpauses game
            if(pause)
                cout << "GAME IS PAUSED. PRESS 'p' TO CONTINUE." << endl;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

void Logic()
{
    //moves the tail forward
    int tailPrevXCoord = tailXCoords[0];
    int tailPrevYCoord = tailYCoords[0];
    int prev2X, prev2Y;
    tailXCoords[0] = x;
    tailYCoords[0] = y;
        for (int i = 1; i < lengthOfTail; i++)
        {
            prev2X = tailXCoords[i];
            prev2Y = tailYCoords[i];
            tailXCoords[i] = tailPrevXCoord;
            tailYCoords[i] = tailPrevYCoord;
            tailPrevXCoord = prev2X;
            tailPrevYCoord = prev2Y;
        }
    
    switch (dir)
    {
    case LEFT:
        speed = 0;  //adjusts speed based on direction(going up/down feels quicker so i slow it down)
        x--;
        break;
    case RIGHT:
        speed = 0;
        x++;
        break;
    case UP:
        speed = 20;
        y--;
        break;
    case DOWN:
        speed = 20;
        y++;
        break;
    default:
        break;
    }

    if (wallDeath) {    //toggles based on user's input
        if (x > width || x < 0 || y > height || y < 0) {
            cout << "\nYou hit a wall! GAME OVER\nYour Score: " << score << endl;
            gameOver = true;
        }
    }

    if (x >= width) x = 0; else if (x < 0) x = width - 1;
    if (y >= height) y = 0; else if (y < 0) y = height - 1;

    for (int i = 0; i < lengthOfTail; i++)
        if (tailXCoords[i] == x && tailYCoords[i] == y) {
            cout << "\nYou hit your tail! GAME OVER\nYour Score: " << score << endl;
            gameOver = true;
        }

    if (checksIfFruitIsCollected(x, y)) {
        score += 10;
        lengthOfTail++;
    }

}

int main()
{
    highscore = 0;
    cout << "Hello! Welcome to the Snake Game.\nCollect the fruit to make your tail " <<
        "grow, but be careful not to run into it! If you do, you lose.\n\nPress WASD to move and press P to pause the game." << endl;
    cout << "\nHow many fruit do you want on a screen at a time? Please choose a number between 1-50." << endl;
    cin >> numberFruit;
    cout << "\nDo you want to die when you hit a wall? Enter y or n" << endl;
    string answer;
    cin >> answer;

    if (answer == "y")  //sets game to live/die when the snake hits the wall
        wallDeath = true;

    cout << "\nAwesome! Press any key to start." << endl;
    cin.get();
    cin.ignore();
    Setup();

    while (!pause) {    //game plays while unpaused
        Draw();
        Input();
        Logic();
        Sleep(50); 

        while (pause) { //pauses game
            Input();
        }

        if (gameOver) { 
            if (score > highscore) {    //sets up highscore
                cout << "\nYou got the highscore!" << endl;
                highscore = score;
            }
            cout << "\nDo you want to play again? y or n" << endl;
            cin >> answer;
            if (answer == "y") {    //rests game to let player play again
                cout << "\nOkay! press any key to continue." << endl;
                cin.ignore();
                lengthOfTail = 0;
                Setup();
                Draw();
                Input();
                Logic();
                Sleep(20);
            }
            else
                return 0;
        }
    }
}
