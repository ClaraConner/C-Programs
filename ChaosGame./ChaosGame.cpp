/*
By: Clara Conner

This program illistrates the Chaos Game

//Special Features
    I added an expirement version. I took the triangle test but instead of finding the midpoint I only found
    1/3 of the distance between the points.

*/

using namespace std;

#include <iostream>
#include <math.h>
#include <fstream>

//===============// GLOBAL VARIABLES //===================//

const int maxCol = 60;
const int maxRow = 60;
bool arr[maxRow][maxCol];

struct Point {

    int x;
    int y;

};

struct Point p1;
struct Point p2;
struct Point p3;
struct Point p4;
struct Point p5;

//creates the PPM file
void createPPM() {

    ofstream fout("OutputPPM.ppm");

    fout << "P3\n";
    fout << maxCol << " " << maxRow << "\n";
    fout << "255\n";

    for (int i = 0; i < maxRow; i++) {
        for (int j = 0; j < maxCol; j++) {

            if (arr[i][j] == false)
                fout << "0 0 0  ";  //makes the pixel blank
            else
                fout << "255 0 0  ";    //makes the pixel red

        }
        fout << "\n";
    }

}

void placePoint(Point p) {
    int x = p.x;
    int y = p.y;

    arr[x][y] = true;

}

Point chooseRandPointTri() {

    int num = rand() % 3 + 1;

    if (num % 3 == 0)
        return p1;
    else if (num % 3 == 1)
        return p2;
    else
        return p3;

}

Point chooseRandPointSqu() {

    int num = rand() % 4 + 1;

    if (num % 4 == 0)
        return p1;
    else if (num % 4 == 1)
        return p2;
    else if (num % 4 == 2)
        return p3;
    else
        return p4;

}

Point chooseRandPointPent() {

    int num = rand() % 5 + 1;

    if (num % 5 == 0)
        return p1;
    else if (num % 5 == 1)
        return p2;
    else if (num % 5 == 2)
        return p3;
    else if (num % 5 == 3)
        return p4;
    else
        return p5;

}

void drawScreen() {

    system("cls");
    for (int i = 0; i < maxRow + 1; i++) {
        for (int j = 0; j < maxCol + 1; j++) {

            if (arr[i][j] == false)
                cout << "  ";
            else
                cout << "X ";

        }
        cout << endl;
    }
}

Point createMidpoints(Point curPnt, Point comparePnt) {

    int x1 = curPnt.x;
    int y1 = curPnt.y;
    int x2 = comparePnt.x;
    int y2 = comparePnt.y;

    int newX = (x1 + x2) / 2;
    int newY = (y1 + y2) / 2;

    struct Point newPoint;
    newPoint.x = newX;
    newPoint.y = newY;
    placePoint(newPoint);

    return newPoint;

}

void startGameTri(Point curPnt) {

    struct Point comparePnt;

    for (int i = 0; i < 2001; i++) {
        comparePnt = chooseRandPointTri();
        curPnt = createMidpoints(curPnt, comparePnt);
        if (i % 100 == 0)
            drawScreen();
    }
}

void startGameSqu(Point curPnt) {

    struct Point comparePnt;

    for (int i = 0; i < 4001; i++) {
        comparePnt = chooseRandPointSqu();
        curPnt = createMidpoints(curPnt, comparePnt);
        if (i % 100 == 0)
            drawScreen();
    }
}

void startGamePent(Point curPnt) {

    struct Point comparePnt;

    for (int i = 0; i < 4001; i++) {
        comparePnt = chooseRandPointPent();
        curPnt = createMidpoints(curPnt, comparePnt);
        p3.y = 20;
        if (i % 100 == 0)
            drawScreen();
    }


}

//expirement trial
void startGameExpirement(Point curPnt) {

    struct Point comparePnt;

    for (int i = 0; i < 2001; i++) {
        comparePnt = chooseRandPointPent();

            int x1 = curPnt.x;
            int y1 = curPnt.y;
            int x2 = comparePnt.x;
            int y2 = comparePnt.y;

            int newX = (x1 + x2) / 3;   //finds 1/3 the distance instead of 1/2
            int newY = (y1 + y2) / 3;

            struct Point newPoint;
            newPoint.x = newX;
            newPoint.y = newY;
            placePoint(newPoint);

            curPnt = newPoint;

        
        if (i % 100 == 0)
            drawScreen();
    }


}

void createSquarePoints() {

    //top left
    p1.x = 0;
    p1.y = 0;
    placePoint(p1);

    //top right
    p2.x = 0;
    p2.y = maxCol;
    placePoint(p2);

    //bottom left
    p3.x = maxRow;
    p3.y = 0;
    placePoint(p3);

    //bottom right
    p4.x = maxRow;
    p4.y = maxCol;
    placePoint(p4);

}

void createPentagonPoints() {

    //top point
    p1.x = 0;
    p1.y = maxCol / 2;
    placePoint(p1);

    //left point
    p2.x = maxRow / 2;
    p2.y = 0;
    placePoint(p2);

    //bottom left
    p3.x = maxRow;
    p3.y = 20;
    placePoint(p3);

    //bottom right
    p4.x = maxRow;
    p4.y = 2 * (maxCol / 3);
    placePoint(p4);

    //right point
    p5.x = maxRow / 2;
    p5.y = maxCol;
    placePoint(p5);

}

void createTrianglePoints() {

    //top point of equilateral triangle
    p1.x = 0;
    p1.y = maxCol/2;
    placePoint(p1);

    //bottom left of triangle
    p2.x = maxRow;
    p2.y = 0;
    placePoint(p2);

    //bottom right of traingle
    p3.x = maxRow;
    p3.y = maxCol;
    placePoint(p3);

}

//resets array to all false
void resetArray() {
    for (int i = 0; i < maxRow + 1; i++) {
        for (int j = 0; j < maxCol + 1; j++) {
            arr[i][j] = false;
        }
    }
}

int main() {
    //creates a random point
    struct Point randP;
    randP.x = rand() % (maxRow + 1);
    randP.y = rand() % (maxCol + 1);
    placePoint(randP);

    resetArray();

    cout << "\n===============================================================================================" << endl;
    cout << "Hello, welcome to the chaos game. How many initial points do you want to have? Please choose 3-5. Type -1 to quit. Type 6 for the expirement." << endl;
    int ans;
    cin >> ans;
    if (ans < 0)
        return 0;
    else if (ans == 3) {
        createTrianglePoints();
        startGameTri(randP);
    }
    else if (ans == 4) {
        createSquarePoints();
        startGameSqu(randP);
    }
    else if (ans == 5) {
        createPentagonPoints();
        startGamePent(randP);
        
    }
    else if (ans == 6) {
        createTrianglePoints();
        startGameExpirement(randP);
    }
    
    drawScreen();
    //createPPM();      //uncomment when you want to create a PPM file
    main();
}
