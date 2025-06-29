//Maciej Bajer
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

void foo (float P, float S){

    float t = cbrt(P);
    if (t == 0)
    {
        cout << scientific << setprecision(10);
        cout << 0.0 << " " << 0.0 << " " << 0.0 << endl;
        return;
    }
    //tq^2 + (t - S)q + t = 0 /t
    float p = ((S / t) - 1) / 2;
    float delta = p * p - 1;
    //float delta = (t - S) * (t - S) - 4 * t * t;
    if (delta < 0){
        cout << scientific << setprecision(10);
        cout << 0.0 << " " << 0.0 << " " << 0.0 << endl;
        return;
    }

    float root1 = 0;
    float root2 = 0;
    if(p >= 0) {
        root1 = p + sqrt(delta);
        root2 = 1 / root1;
    }
    else{
        root2 = p - sqrt(delta);
        root2 = 1 / root2;
    }
    float q = (root1 >= 1) ? root1 : root2;

    float x1 = t * q;
    float x2 = t;
    float x3 = t / q;

    cout << scientific << setprecision(10);
    if (x1 > x3){
        cout << x1 << " " << x2 << " " << x3 << endl;
    }
    else{
        cout << x3 << " " << x2 << " " << x1 << endl;

    }

}

int main() {
    int n = 0;
    cin >> n;

    for (int i = 0; i < n; i++){
        float p1 = 0;
        float s1 = 0;
        cin >> p1;
        cin >> s1;
        foo(p1, s1);
    }
    return 0;
}
