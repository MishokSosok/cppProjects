/* 
 * File:   SVGdraw.h
 * Author: Jaro Budis, Brona Brejova
 */

/** The SVGdraw library provides a simple interface 
 * for writing SVG files. This library 
 * was developed by Jaro Budis and Brona Brejova for teaching 
 * first-year course  Programming (1) in C/C++ 
 * at Comenius University in Bratislava.
 * 
 * See more information at the course webpage 
 * http://compbio.fmph.uniba.sk/vyuka/prog/
 */
#ifndef SVGDRAW_H
#define	SVGDRAW_H
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <iostream>
#include <sstream>
using namespace std;

/** Class SVGdraw allows user to draw to a SVG file. 
 * Simple examples of use of this library can be found at 
 * http://compbio.fmph.uniba.sk/vyuka/prog/index.php/Predn%C3%A1%C5%A1ka_1 */
class SVGdraw {
public:
    /** Initialize SVG image with width w and height h and write it to
     * the specified filename.
     * Upper left corner coordinate is (0,0), lower-right corner (w,h). */
    SVGdraw(int width, int height, const char* filename);
    /** Animation will wait time seconds. */
    void wait(double time);
    /** All visible items in the animation will disappear */
    void clear();
    /** Hide item with selected id. Ids are returned by all
     * drawing functions (drawRectangle etc.) */
    void hideItem(int id);
    /** Finish writing image to file */
    void finish();
    ~SVGdraw();

    /** Draw a rectangle with upper left corner (x,y), width w, height h. 
     * Return value specifies item id for future delteion. */
    int drawRectangle(double x, double y, double width, double height);
    /** Draw an ellipse with center (x,y), x-axis radius rx, y-axis radius ry. */
    int drawEllipse(double x, double y, double rx, double ry);
    /** Draw line from (x1,y2) to (x2,y2). */
    int drawLine(double x1, double y1, double x2, double y2);
    /** Write the given text at position (x, y).
     * If justification is empty, text will be centered in both x and y.
     * If justification contains letter l, left border will be at x,
     * letter r means right border will be at x. Similarly letters b and t
     * mean that top or bottom will be at coordinate y. */
    int drawText(double x, double y, const char* text,
            const char* justification = "");

    /** Start a new polygonal path at position (x,y). 
     * After starting polygon, add more points by addPolygonPoint,
     * then draw by drawPolygon. */
    void startPolygon(double x, double y);
    /** Add a new point to the current polygon. */
    void addPolygonPoint(double x, double y);
    /** Draw the polygon specified by startPolygond and 
     * addPolygonPoint methods, then clear polygin coordinates. */
    int drawPolygon();

    /** Set line color to a given RGB value.
     * All three values should be between 0 and 255.
     * Line color is used for drawing lines and writing text. */
    void setLineColor(int r, int g, int b);
    /** Set line color to a given named color.
     * List of color names: http://www.w3.org/TR/SVG/types.html#ColorKeywords
     */
    void setLineColor(const char* color);
    /** Set fill color to a given RGB value. 
     * This color is used to fill in shapes. */
    void setFillColor(int r, int g, int b);
    /** Set fill color to a given named color. */
    void setFillColor(const char* color);
    /** Set fill to invisible color. */
    void setNoFill();
    /** Set size of the font (default is 12). */
    void setFontSize(double size);
    /** Set width of lines (default is 1). */
    void setLineWidth(double width);

protected:
    vector <pair<double, double> > itemTimes_;
    vector <pair<double, double> > polygon_;
    double time_;
    bool isActive_;
    ofstream svg_;
    int addItem();
    int nextItemId();
    void printStyle();
    string lineColor_;
    string fillColor_;
    double fontSize_;
    double lineWidth_;
};

/** Class Turtle allows user to create turtle graphics
 * in an SVG file. */
class Turtle {
public:
    /** Initialize SVG image and create a turtle. 
     * Image will have width w and height h and will be writen to
     * the specified filename. 
     * Turtle will start at position (x,y) heading at the given angle. 
     * With angle=0 turtle heads right, angle=90 heads up etc. */
    Turtle(int width, int height, const char* filename,
            int x, int y, double angle);
    /** Set turtle speed to given value.
     * Default is 100 distance units per second. */
    void setSpeed(double speed);
    /** Move furtle forward by distance d. */
    void forward(double length);
    /** Turn turtle left by the given angle (in degrees).  */
    void turnLeft(double angle);
    /** Turn turtle right by the given angle (in degrees).  */
    void turnRight(double angle);
    /** Move turtle to the specified location. */
    void goTo(double x, double y);

    /** Finish writing image to file */
    void finish();
    ~Turtle();
protected:
    double x_, y_, angle_;
    double pathLength_;
    double speed_;
    bool isActive_;
    ofstream svg_;
};


const double PI = 3.14159265358979323846;
const double DEGREES_RATIO = PI / 180;

void checkArg(bool correct, const char *message) {
    if (!correct) {
        cerr << "Chyba v pouziti kniznice SVGdraw:" << endl;
        cerr << " " << message << endl;
        exit(1);
    }
}

void initSVG(ofstream &svg, double width, double height) {
    checkArg(width > 0 && height > 0, "Rozmery obrazku musia byt kladne");
    svg << "<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>\n";
    svg << "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.0//EN\" \"http://www.w3.org/TR/SVG/DTD/svg10.dtd\">\n";
    svg << "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" ";
    svg << " width=\"" << width << "px\" height=\"" << height << "px\">\n";
    svg << "<rect x=\"0\" y=\"0\" width=\"" << width
            << "\" height=\"" << height
            << "\" style=\"fill:white;stroke:lightgray;stroke-width:1;\" />\n\n";
}

string formatRGBColor(int r, int g, int b) {
    checkArg(0 <= r && r <= 255 && 0 <= g && g <= 255 && 0 <= b && b <= 255,
            "RGB farby musia byt medzi 0 a 255 vratane.");
    ostringstream os;
    os << "rgb(" << r << "," << g << "," << b << ")";
    return os.str();
}

SVGdraw::SVGdraw(int width, int height, const char* filename)
: time_(0), isActive_(true),
lineColor_("black"), fillColor_("none"), fontSize_(12), lineWidth_(1) {
    svg_.open(filename);
    initSVG(svg_, width, height);
}

void SVGdraw::wait(double time) {
    checkArg(time > 0, "Cas cakania musi byt kladne cislo");
    time_ += time;
}

void SVGdraw::clear() {
    for (int i = 0; i < (int) itemTimes_.size(); i++) {
        if (itemTimes_[i].second < 0) {
            itemTimes_[i].second = time_;
        }
    }
}

void SVGdraw::hideItem(int id) {
    checkArg(id >= 0 && id < (int) itemTimes_.size(), "Zadane id pre hideItem neexistuje");
    checkArg(itemTimes_[id].second < 0, "Objekt s danym id vo funkcii hideItem bol uz predtym skryty.");
    itemTimes_[id].second = time_;
}

void SVGdraw::finish() {
    checkArg(isActive_, "Funkciu finish je mozne volat iba raz");

    for (int i = 0; i < (int) itemTimes_.size(); i++) {
        double start = itemTimes_[i].first;
        double end = itemTimes_[i].second;
        if (start > 0) {
            svg_ << "<set xlink:href=\"#item" << i
                    << "\" attributeName=\"visibility\" to=\"hidden\" "
                    << "begin=\"0s\" dur=\"" << start << "s\" />\n";
        }
        if (end >= 0) {
            svg_ << "<set xlink:href=\"#item" << i
                    << "\" attributeName=\"visibility\" to=\"hidden\" "
                    << "begin=\"" << end << "s\" dur=\"indefinite\" />\n";
        }
    }

    svg_ << "</svg>\n";
    svg_.close();
    isActive_ = false;
}

SVGdraw::~SVGdraw() {
    if (isActive_) {
        finish();
    }
}

int SVGdraw::drawRectangle(double x, double y, double width, double height) {
    checkArg(isActive_, "Po zavolani funkcie finish uz nie je mozne vykreslovat");
    svg_ << "<rect id=\"item" << nextItemId() << "\" x=\"" << x << "\" y=\"" << y
            << "\" width=\"" << width << "\" height=\"" << height << "\" ";
    printStyle();
    svg_ << " />\n";
    return addItem();
}

int SVGdraw::drawEllipse(double x, double y, double rx, double ry) {
    checkArg(isActive_, "Po zavolani funkcie finish uz nie je mozne vykreslovat");
    svg_ << "<ellipse id=\"item" << nextItemId()
            << "\" cx=\"" << x << "\" cy=\"" << y
            << "\" rx=\"" << rx << "\" ry=\"" << ry << "\" ";
    printStyle();
    svg_ << " />\n";
    return addItem();
}

int SVGdraw::drawLine(double x1, double y1, double x2, double y2) {
    checkArg(isActive_, "Po zavolani funkcie finish uz nie je mozne vykreslovat");
    svg_ << "<line id=\"item" << nextItemId()
            << "\" x1=\"" << x1 << "\" y1=\"" << y1
            << "\" x2=\"" << x2 << "\" y2=\"" << y2 << "\" ";
    printStyle();
    svg_ << " />\n";
    return addItem();
}

int SVGdraw::drawText(double x, double y, const char* text,
        const char* justification) {
    checkArg(isActive_, "Po zavolani funkcie finish uz nie je mozne vykreslovat");
    svg_ << "<text id=\"item" << nextItemId()
            << "\" x=\"" << x << "\" y=\"" << y << "\" "
            << "style=\"fill:" << lineColor_
            << ";stroke-width:0pt;stroke:none;"
            << "font-size:" << fontSize_ << "pt;";
    if (strchr(justification, 'l')) {
        svg_ << "text-anchor:start;";
    } else if (strchr(justification, 'r')) {
        svg_ << "text-anchor:end;";
    } else {
        svg_ << "text-anchor:middle;";
    }
    if (strchr(justification, 't')) {
        svg_ << "dominant-baseline:text-before-edge;";
    } else if (strchr(justification, 'b')) {
        svg_ << "dominant-baseline:text-after-edge;";
    } else {
        svg_ << "dominant-baseline:middle;";
    }

    svg_ << "\">" << text << "</text>\n";
    return addItem();
}

void SVGdraw::startPolygon(double x, double y) {
    polygon_.clear();
    addPolygonPoint(x, y);
}

void SVGdraw::addPolygonPoint(double x, double y) {
    polygon_.push_back(pair<double, double>(x, y));
}

int SVGdraw::drawPolygon() {
    checkArg(isActive_, "Po zavolani funkcie finish uz nie je mozne vykreslovat");
    checkArg(polygon_.size() > 2, "Polygon musi mat aspon 3 vrcholy");
    svg_ << "<polygon id=\"item" << nextItemId()
            << "\" points=\"";
    for (int i = 0; i < (int) polygon_.size(); i++) {
        svg_ << " " << polygon_[i].first << "," << polygon_[i].second;
    }
    svg_ << "\" ";
    printStyle();
    svg_ << " />\n";
    polygon_.clear();
    return addItem();
}

void SVGdraw::setLineColor(int r, int g, int b) {
    lineColor_ = formatRGBColor(r, g, b);
}

void SVGdraw::setLineColor(const char* color) {
    lineColor_ = color;
}

void SVGdraw::setFillColor(int r, int g, int b) {
    fillColor_ = formatRGBColor(r, g, b);
}

void SVGdraw::setFillColor(const char* color) {
    const char *c = color;
    while ((*c) != 0) {
        checkArg(islower(*c), "Meno farby musi pozostavat iba z malych pismen");
        c++;
    }
    fillColor_ = color;
}

void SVGdraw::setNoFill() {
    fillColor_ = "none";
}

void SVGdraw::setFontSize(double size) {
    checkArg(size > 0, "Velkost fontu musi byt kladna");
    fontSize_ = size;
}

void SVGdraw::setLineWidth(double width) {
    checkArg(width > 0, "Sirka ciary musi byt kladna");
    lineWidth_ = width;
}

int SVGdraw::addItem() {
    int n = itemTimes_.size();
    itemTimes_.push_back(pair<double, double>(time_, -1));
    return n;
}

int SVGdraw::nextItemId() {
    return itemTimes_.size();
}

void SVGdraw::printStyle() {
    svg_ << "style=\"";
    svg_ << "stroke:" << lineColor_ << ";";
    svg_ << "stroke-width:" << lineWidth_ << ";";
    svg_ << "fill:" << fillColor_;
    svg_ << "\"";
}

Turtle::Turtle(int width, int height, const char* filename,
        int x, int y, double angle)
: x_(x), y_(y), angle_(angle), pathLength_(0), speed_(100),
isActive_(true) {
    svg_.open(filename);
    initSVG(svg_, width, height);
    svg_ << "<path fill=\"none\" stroke=\"black\" id=\"turtlepath\"  d=\"";
    svg_ << "M " << x_ << " " << y_;
}

void Turtle::finish() {
    double time = pathLength_ / speed_;
    svg_ << "\"/>\n\n";
    svg_ << "<path id=\"turtle\" fill=\"red\" d=\"M 10 0 L -10 -8 L -10 8 \">\n";
    svg_ << "  <animateMotion dur=\"" << time
            << "s\" repeatCount=\"1\" rotate=\"auto\">\n";
    svg_ << "  <mpath xlink:href=\"#turtlepath\"/>\n";
    svg_ << "  </animateMotion>\n";
    svg_ << "</path>\n";
    svg_ << "<set xlink:href=\"#turtle\" "
            << "attributeName=\"visibility\" to=\"hidden\" "
            << "begin=\"" << time << "s\" dur=\"indefinite\" />\n\n";

    svg_ << "</svg>\n";
    svg_.close();
    isActive_ = false;
}

void Turtle::setSpeed(double speed) {
    checkArg(speed > 0, "Rychlost korytnacky musi byt kladna");
    speed_ = speed;
}

void Turtle::forward(double length) {
    double x = x_ + length * cos(angle_ * DEGREES_RATIO);
    double y = y_ - length * sin(angle_ * DEGREES_RATIO);

    goTo(x, y);
}

void Turtle::turnLeft(double angle) {
    angle_ += angle;
}

void Turtle::turnRight(double angle) {
    angle_ -= angle;
}

void Turtle::goTo(double x, double y) {
    checkArg(isActive_, "Po zavolani funkcie finish uz nie je mozne posuvat korytnacku");
    double dx = x - x_;
    double dy = y - y_;
    pathLength_ += sqrt(dx * dx + dy * dy);
    x_ = x;
    y_ = y;
    svg_ << " L " << x_ << " " << y_;
}

Turtle::~Turtle() {
    if (isActive_) {
        finish();
    }
}
#endif	/* SIMPLEDRAW_H */
