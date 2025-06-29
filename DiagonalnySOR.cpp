//Maciej Bajer
#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    //input
    int N = 0; //rozmiar macierzy
    int M = 0; //M liczba niezerowych wsteg
    int L = 0; //liczba iteracji
    double w = 0.0; //omega

    cin >> N;
    cin >> M;

    vector<vector<double>> v(M + 1); //wstegi
    vector<double> x(N); //wektor poczatkowy
    vector<double> y(N); //prawa strona rownania

    //wstegi
    int l = 0; //length
    for (int i = 0; i < M + 1; i++){
        l = N - M + i;
        v[i].resize(l);
        for (int j = 0; j < l; j++){
            cin >> v[i][j];
        }
    }

    //pozostale 2 wektory - prawa strona i poczatkowy
    for (int i = 0; i < N; i++){
        cin >> y[i];
    }
    for (int i = 0; i < N; i++){
        cin >> x[i];
    }

    //omega i liczba iteracji
    cin >> w;
    cin >> L;

    for (int count = 0; count < L; count++){
        for(int i = 0; i < N; i++){
            double s = y[i];
            //na lewo od diagonali sa nowe x, na prawo stare
            for (int m = 0; m < M; m++) {
                if (i - M + m >= 0)
                    s -= v[m][i - M + m] * x[i - M + m];
            }
            for (int m = 0; m < M; m++) {
                if (i + m + 1 < N)
                    s -= v[M - 1 - m][i] * x[i + m + 1];
            }
            //wzorek
            double z = s / v[M][i];
            x[i] = (1 - w) * x[i] + (w * z);
        }
    }

    //cout z 10 liczbami i naukowa notacja
    for (int i = 0; i < N; i++) {
        cout << scientific << setprecision(10) << x[i] << endl;
    }

    return 0;
}
