#include <iostream>

using std::cout;
using std::cin;

class Point {
public:
    int x, y;
public:
    Point() {
        cout << "Point()\n";
        x = 0;
        y = 0;
        show();
    }

    Point(const int& x, const int& y) {
        cout << "Point(const int& x, const int& y)\n";
        this->x = x;
        this->y = y;
        show();
    }

    Point(const Point& obj) {
        cout << "Point(const Point& obj)\n";
        this->x = obj.x;
        this->y = obj.y;
        show();
    }

    ~Point()
    {
        cout << "~Point()\n";
        show();
    }

    void move(const int& dx, const int& dy)
    {
        x += dx;
        y += dy;
        show();
    }

    void reset();

    virtual void show() {
        cout << "x = " << x << ", y = " << y << "\n";
    }
};

void Point::reset()
{
    x = 0;
    y = 0;
    show();
}

class ColoredPoint : public Point{
private:
    int color;
public:
    ColoredPoint() : Point(){
        cout << "ColoredPoint()\n";
        color = 0;
        show();
    }

    ColoredPoint(const int& x, const int& y, const int& color) : Point(x, y) {
        cout << "ColoredPoint(const int& x, const int& y, const int& color)\n";
        this->color = color;
        show();
    }

    ColoredPoint(const ColoredPoint& obj) {
        cout << "ColoredPoint(const ColoredPoint& obj)\n";
        color = obj.color;
        x = obj.x;
        y = obj.y;
        show();
    }

    ~ColoredPoint() {
        cout << "\n~ColoredPoint()\n";
        show();
    }

    void ChangeColor(const int& new_color) {
        color = new_color;
        show();
    }

    virtual void show() override
    {
        Point::show();
        cout << "color = " << color << "\n";
    }
};

class ColoredPointProtected : protected Point {
private:
    int color;
public:
    ColoredPointProtected() : Point() {
        cout << "ColoredPointProtected()\n";
        color = 0;
        show();
    }

    ColoredPointProtected(const int& x, const int& y, const int& color) : Point(x, y) {
        cout << "ColoredPointProtected(const int& x, const int& y, const int& color)\n";
        this->color = color;
        show();
    }

    ColoredPointProtected(const ColoredPointProtected& obj) {
        cout << "ColoredPointProtected(const ColoredPoint& obj)\n";
        color = obj.color;
        x = obj.x;
        y = obj.y;
        show();
    }

    ~ColoredPointProtected() {
        cout << "\n~ColoredPointProtected()\n";
        show();
    }

    void ChangeColor(const int& new_color) {
        color = new_color;
        show();
    }

    virtual void show() override
    {
        Point::show();
        cout << "color = " << color << "\n";
    }
};

class Section {
private:
    Point* p1;
    Point* p2;
public:
    Section() {
        cout << "Section()\n";
        p1 = new Point;
        p2 = new Point;
    }

    Section(const int& x1, const int& y1, const int& x2, const int& y2) {
        cout << "Section(const int& x, const int& y, const int& color)\n";
        p1 = new Point(x1, y2);
        p2 = new Point(x2, y2);
    }

    Section(const Section& obj, const int& ch = -1) {
        cout << "Section(const Point& obj, const int& ch)\n";

        if (ch == 0)
        {
            p1 = obj.p1;
            p2 = obj.p2;
        }
        else
        {
            p1 = new Point(*(obj.p1));
            p2 = new Point(*(obj.p2));
        }
    }

    ~Section() {
        delete(p1);
        delete(p2);
        cout << "~Section()\n";
    }
};

int main()
{
    
    {
        Point a;
        Point b(1, 2);
        Point c(a);

        a.move(10, 10);
        b.reset();
        c.show();
    }
    {
        Point* a = new Point;
        Point* b = new Point(1, 2);
        Point* c = new Point(*a);

        a->move(5, 5);
        c->reset();
        a->show();

        delete(a);
        delete(b);
        delete(c);
    }
    {
        ColoredPoint a;
        ColoredPoint b(1, 2, 42);
        ColoredPoint c(b);

        a.ChangeColor(43);
        b.move(1, 2);
        c.reset();
        a.show();

        a.x; a.y;
    }
    {
        ColoredPoint* a = new ColoredPoint;
        ColoredPoint* b = new ColoredPoint(1, 2, 42);
        ColoredPoint* c = new ColoredPoint(*a);

        delete(a);
        delete(b);
        delete(c);
    }
    {
        ColoredPointProtected a;

        a.ChangeColor(44);
        a.show();
    }
    {
        Point* a = new ColoredPoint(1, 2, 42);
        a->x; a->y;                 // Мы имеем прямой доступ к полям 'x' и 'y', т.к. они объявлены с модификатором доступа 'public'
        a->move(1, 2); a->reset();  // Т.к. 'a' - указатель на объект 'Point', то и доступ мы имеем только к 'public' полям класса 'Point'

        delete(a);
    }
    {
        Section a;
        Section b(1, 2, 10, 12);
        Section c(b);
    }
    {
        Section* a = new Section;
        Section* b = new Section(1, 2, 10, 12);
        Section* c = new Section(*b);

        delete(a);
        delete(b);
        delete(c);
    }
    
    return 0;
}