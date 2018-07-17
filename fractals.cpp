// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "fractals.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "random.h"
#include "gwindow.h"
#include "gobjects.h"
#include "gevents.h"
#include <math.h>
#include "error.h"
using namespace std;

void drawSierpinskiTriangle(GWindow& window, double x, double y, double size, int order);
void drawSierpinskiTriangleHelper(GWindow& window, double x, double y, double size, int order);
void drawTreeLeaf(GWindow& gw, GPoint& point, double size, int order, int direction);
void drawTree(GWindow& gw, double x, double y, double size, int order);

//int main() {
//    GWindow window(800, 600);
//    window.setWindowTitle("CS 106B/X Fractals");
//    window.setColor("black");

//    drawTree(window, 150, 150, 200, 2);
//    return 0;
//}


void drawSierpinskiTriangle(GWindow& window, double x, double y, double size, int order) {

    if (order < 0){
        throw "exception";
    } else if (order == 0){
        return;
    } else {
        //draw the biggest downward-pointing triangle
        window.drawLine(x, y, x + size, y);
        window.drawLine(x + size, y, x + size / 2, y + sqrt(3) * size / 2);
        window.drawLine(x + size / 2, y + sqrt(3) * size / 2, x, y);

        drawSierpinskiTriangleHelper(window, x, y, size, order - 1);
        return;
    }
}


void drawSierpinskiTriangleHelper(GWindow& window, double x, double y, double size, int order){

    if (order == 0){
        return;
    } else {
        //find the three vertex of upward-pointing triangle that we want to draw
        GPoint point1(x + size / 2, y);
        GPoint point2(x + 3 * size / 4, y + sqrt(3) * size / 4);
        GPoint point3(x + size / 4, y + sqrt(3) * size / 4);

        //draw the upward-pointing triangle inside the bigger downward-pointing triangles
        window.drawLine(point1, point2);
        window.drawLine(point2, point3);
        window.drawLine(point3, point1);

        //Each newly drawn upward-pointing triangle would create three smaller downward-pointing triangles
        //Recurse on each smaller downward-pointing triangle to draw a upward-pointing triangle inside.
        drawSierpinskiTriangleHelper(window, x, y, size / 2, order - 1);
        drawSierpinskiTriangleHelper(window, x + size / 2, y, size / 2, order - 1);
        drawSierpinskiTriangleHelper(window, x + size / 4, y + sqrt(3) * size / 4, size / 2, order - 1);
        return;
    }
}


void drawTree(GWindow& gw, double x, double y, double size, int order) {

    if (order < 0){
        throw "exception";
    } else if (order == 0){
        return;
    } else if (order == 1){
        gw.setColor("green");
        gw.drawLine(x + size / 2, y + size, x + size / 2, y + size / 2);
    } else {
        gw.setColor("brown");
        gw.drawLine(x + size / 2, y + size, x + size / 2, y + size / 2);
        GPoint endpoint(x + size / 2, y + size / 2);
        drawTreeLeaf(gw, endpoint, size / 2, order - 1, 90);
    }

}


void drawTreeLeaf(GWindow& gw, GPoint& point, double size, int order, int direction){
    if (order == 0){
        return;
    } else if (order == 1){
        for (int i = -3; i < 4; i++){
            gw.setColor("green");
            GPoint startpoint = gw.drawPolarLine(point, size / 2, direction + 15 * i);
            drawTreeLeaf(gw, startpoint, size / 2, order - 1, direction + 15 * i);
        }
    } else {
        for (int i = -3; i < 4; i++){
            gw.setColor("brown");
            GPoint startpoint = gw.drawPolarLine(point, size / 2, direction + 15 * i);
            drawTreeLeaf(gw, startpoint, size / 2, order - 1, direction + 15 * i);
        }
    }
}
