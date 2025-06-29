//Maciej Bajer
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include "funkcja.h"
using namespace std;

class Jet2d {
    double val;
    double dx;
    double dy;
    double dxx;
    double dxy;
    double dyy;

public:
    Jet2d() : val(0), dx(0), dy(0), dxx(0), dxy(0), dyy(0) {};

    Jet2d(double v, double dx_val, double dy_val, double dxx_val, double dxy_val, double dyy_val) :
            val(v), dx(dx_val), dy(dy_val), dxx(dxx_val), dxy(dxy_val), dyy(dyy_val) {}

    static Jet2d val_x(double x) {
        Jet2d i;
        i.val = x;
        i.dx = 1.0;
        return i;
    }

    static Jet2d val_y(double y) {
        Jet2d i;
        i.val = y;
        i.dy = 1.0;
        return i;
    }

    friend Jet2d operator +(const Jet2d& f, const Jet2d& g) {
        return Jet2d(
                f.val + g.val,
                f.dx + g.dx,
                f.dy + g.dy,
                f.dxx + g.dxx,
                f.dxy + g.dxy,
                f.dyy + g.dyy
        );
    }

    friend Jet2d operator -(const Jet2d& f, const Jet2d& g) {
        return Jet2d(
                f.val - g.val,
                f.dx - g.dx,
                f.dy - g.dy,
                f.dxx - g.dxx,
                f.dxy - g.dxy,
                f.dyy - g.dyy
        );
    }

    friend Jet2d operator *(const Jet2d& f, const Jet2d& g) {
        return Jet2d(
                f.val * g.val,
                f.dx * g.val + g.dx * f.val,
                f.dy * g.val + g.dy * f.val,
                2.0 * f.dx * g.dx + f.dxx * g.val + g.dxx * f.val,
                f.dxy * g.val + f.dx * g.dy + f.dy * g.dx + f.val * g.dxy,
                2.0 * f.dy * g.dy + f.dyy * g.val + g.dyy * f.val
        );
    }

    friend Jet2d operator /(const Jet2d& f, const Jet2d& g) {
        double b2 = g.val * g.val;
        double b3 = g.val * g.val * g.val;
        return Jet2d(
                f.val / g.val,
                (f.dx * g.val - f.val * g.dx) / b2,
                (f.dy * g.val - f.val * g.dy) / b2,
                (f.dxx * b2 - 2.0 * f.dx * g.val * g.dx - f.val * g.val * g.dxx + 2.0 * f.val * g.dx * g.dx) / b3,
                (f.dxy * b2 - f.dx * g.val * g.dy - f.dy * g.val * g.dx - f.val * g.val * g.dxy + 2.0 * f.val * g.dx * g.dy) / b3,
                (f.dyy * b2 - 2.0 * f.dy * g.val * g.dy - f.val * g.val * g.dyy + 2.0 * f.val * g.dy * g.dy) / b3
        );
    }

    friend Jet2d operator -(const Jet2d& f) {
        return Jet2d(
                -f.val,
                -f.dx,
                -f.dy,
                -f.dxx,
                -f.dxy,
                -f.dyy
        );
    }

    friend Jet2d sin(const Jet2d& f) {
        return Jet2d(
                sin(f.val),
                cos(f.val) * f.dx,
                cos(f.val) * f.dy,
                -sin(f.val) * f.dx * f.dx + cos(f.val) * f.dxx,
                -sin(f.val) * f.dx * f.dy + cos(f.val) * f.dxy,
                -sin(f.val) * f.dy * f.dy + cos(f.val) * f.dyy
        );
    }

    friend Jet2d cos(const Jet2d& f) {
        return Jet2d(
                cos(f.val),
                -sin(f.val) * f.dx,
                -sin(f.val) * f.dy,
                -cos(f.val) * f.dx * f.dx - sin(f.val) * f.dxx,
                -cos(f.val) * f.dx * f.dy - sin(f.val) * f.dxy,
                -cos(f.val) * f.dy * f.dy - sin(f.val) * f.dyy
        );
    }

    friend Jet2d exp(const Jet2d& f) {
        return Jet2d(
                exp(f.val),
                exp(f.val) * f.dx,
                exp(f.val) * f.dy,
                exp(f.val) * (f.dxx + f.dx * f.dx),
                exp(f.val) * (f.dxy + f.dx * f.dy),
                exp(f.val) * (f.dyy + f.dy * f.dy)
        );
    }

    friend Jet2d operator +(const Jet2d& f, double x) {
        return Jet2d(
                f.val + x,
                f.dx,
                f.dy,
                f.dxx,
                f.dxy,
                f.dyy
        );
    }

    friend Jet2d operator +(double x, const Jet2d& f) {
        return f + x;
    }

    friend Jet2d operator -(const Jet2d& f, double x) {
        return Jet2d(
                f.val - x,
                f.dx,
                f.dy,
                f.dxx,
                f.dxy,
                f.dyy
        );
    }

    friend Jet2d operator -(double x, const Jet2d& f) {
        return Jet2d(
                x - f.val,
                -f.dx,
                -f.dy,
                -f.dxx,
                -f.dxy,
                -f.dyy
        );
    }

    friend Jet2d operator *(const Jet2d& f, double x) {
        return Jet2d(
                f.val * x,
                f.dx * x,
                f.dy * x,
                f.dxx * x,
                f.dxy * x,
                f.dyy * x
        );
    }

    friend Jet2d operator *(double x, const Jet2d& f) {
        return f * x;
    }

    friend Jet2d operator /(const Jet2d& f, double b) {
        return Jet2d(
                f.val / b,
                f.dx / b,
                f.dy / b,
                f.dxx / b,
                f.dxy / b,
                f.dyy / b
        );
    }

    friend Jet2d operator /(double b, const Jet2d& f) {
        double b2 = f.val * f.val;
        double b3 = f.val * f.val * f.val;
        return Jet2d(
                b / f.val,
                -b * f.dx / b2,
                -b * f.dy / b2,
                (2.0 * b * f.dx * f.dx - b * f.dxx * f.val) / b3,
                (-b * f.dx * f.dy - b * f.dy * f.dx + 2.0 * b * f.dx * f.dy) / b3,
                (2.0 * b * f.dy * f.dy - b * f.dyy * f.val) / b3
        );
    }

    void print() const {
        cout << fixed << setprecision(15);
        cout << val << " " << dx << " " << dy << " " << dxx << " " << dxy << " " << dyy << endl;
    }
};

int main() {
    int M;
    cin >> M;

    vector<pair<double, double> > p(M);
    for (int i = 0; i < M; ++i) {
        cin >> p[i].first >> p[i].second;
    }

    for (vector<pair<double, double> >::const_iterator it = p.begin(); it != p.end(); ++it) {
        Jet2d x = Jet2d::val_x(it->first);
        Jet2d y = Jet2d::val_y(it->second);
        Jet2d result = funkcja(x, y);
        result.print();
    }

    return 0;
}
