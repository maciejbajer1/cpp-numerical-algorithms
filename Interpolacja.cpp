// Maciej Bajer
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

long double factorialFoo(int n) {
    long double res = 1.0;
    for (int i = 2; i <= n; ++i)
        res *= i;
    return res;
}

long double value(const vector<long double>& out, const vector<long double>& Z, long double x) {
    long double res = 0.0;
    long double term = 1.0;
    for (int i = 0; i < out.size(); i++) {
        res += out[i] * term;
        term *= (x - Z[i]);
    }
    return res;
}

// interpolacja
vector<long double> interpolation(const vector<long double>& X, const vector<long double>& Y) {
    vector<long double> output = Y;
    vector<int> temp(X.size(), 0);  // wektor informacji o pochodnych

    // wypelnianie wektora pochodnych
    for (int i = 1; i < X.size(); i++) {
        if (X[i] == X[i - 1]) {
            temp[i] = temp[i - 1] + 1;
        }
    }

    for (int i = 1; i < X.size(); i++) {
        long double factorial = factorialFoo(i);
        for (int j = X.size() - 1; j >= i; j--) {//od konca zeby nie nadpisac potrzebnych potem danych
            if (temp[j] == 0) {
                output[j] = (output[j] - output[j - 1 - temp[j - 1]]) / (X[j] - X[j - i]);
            } else {
                output[j] /= factorial;
                temp[j]--;
            }
        }
    }
    return output;
}

int main() {
    int M = 0, N = 0;
    cin >> M >> N;

    vector<long double> X(M), Y(M), T(N);
    for (int i = 0; i < M; ++i) {
        cin >> X[i];
    }
    for (int i = 0; i < M; ++i) {
        cin >> Y[i];
    }
    for (int i = 0; i < N; ++i) {
        cin >> T[i];
    }

    vector<long double> output = interpolation(X, Y);

    cout << setprecision(20) << fixed;
    for (int i = 0; i < M; i++) {
        cout << output[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < N; i++) {
        cout << value(output, X, T[i]) << " ";
    }
    cout << endl;

    return 0;
}
