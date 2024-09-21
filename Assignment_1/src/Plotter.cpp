#include "Plotter.h"
#include "strlib.h"
using namespace std;

enum status {up, down};

struct PenAttribute {
    PenStyle style;
    status PenStatus;
    double PenPositionX;
    double PenPositionY;
};

void PenDown(PenAttribute &pen) {
    pen.PenStatus = down;
}

void PenUp(PenAttribute &pen) {
    pen.PenStatus = up;
}

void MoveAbs(PenAttribute &pen, double x, double y) {
    if (pen.PenStatus == down)
        drawLine(pen.PenPositionX, pen.PenPositionY, x, y, pen.style);
    pen.PenPositionX = x;
    pen.PenPositionY = y;
}

void MoveRel(PenAttribute &pen, double dx, double dy) {
    double x = pen.PenPositionX + dx;
    double y = pen.PenPositionY + dy;
    if (pen.PenStatus == down)
        drawLine(pen.PenPositionX, pen.PenPositionY, x, y, pen.style);
    pen.PenPositionX = x;
    pen.PenPositionY = y;
}

void PenColor(PenAttribute &pen, string c) {
    pen.style.color = c;
}

void PenWidth(PenAttribute &pen, double w) {
    pen.style.width = w;
}

static void plotterInit(PenAttribute &pen) {
    pen.style = {1, "#000000"};
    pen.PenPositionX = 0;
    pen.PenPositionY = 0;
    PenUp(pen);
}

void runPlotterScript(istream& input) {
    PenAttribute pen;
    plotterInit(pen);
    string line;
    while (getline(input, line)) {
        Vector<string> s = stringSplit(line, " ");
        string cmd_str = toLowerCase(s[0]);
        if (cmd_str == "pendown")
            PenDown(pen);
        else if (cmd_str == "penup")
            PenUp(pen);
        else if (cmd_str == "pencolor")
            PenColor(pen, s[1]);
        else if (cmd_str == "penwidth")
            PenWidth(pen, stringToReal(s[1]));
        else if (cmd_str == "moveabs")
            MoveAbs(pen, stringToReal(s[1]), stringToReal(s[2]));
        else if (cmd_str == "moverel")
            MoveRel(pen, stringToReal(s[1]), stringToReal(s[2]));
        else
            return;
    }
}
