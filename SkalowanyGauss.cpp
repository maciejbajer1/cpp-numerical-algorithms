//Maciej Bajer
#include <iostream>
#include "vectalg.h"

using namespace std;

Vector solveEquations(const Matrix &A, const Vector &b, double eps) {
    int n = A.size();
    Matrix newA = A;
    Vector scale(n);
    Vector newB = b;

    //krok 1 - znalezienie normy dla kazdego wiersza
    for(int i = 0; i < n; i++) {
        Vector row(n);
        for(int j = 0; j < n; j++) {
            row[j] = newA(i, j);
        }
        scale[i] = row.max_norm();
    }

    //krok 2 - eliminacja gaussa
    for(int k = 0; k < n; k++){
        double max_in_col = 0;
        int row = k;

        //2.1 znalezienie maksymalnego elementu w kolumnie
        for(int i = k; i < n; i++){
            double best = abs(newA(i, k)) / scale[i];
            if (best > max_in_col){
                max_in_col = best;
                row = i;
            }
        }

        //2.2 zamiana wierszy aktualnego na ten z najwiekszym elementem
        swap(scale[k], scale[row]);
        swap(newB[k], newB[row]);
        for (int j = 0; j < n; j++) {
            swap(newA(k, j), newA(row, j));
        }

        //2.3 eliminacja gaussa dla wierszy ponizej aktualnego
        for (int i = k + 1; i < n; i++){
            double z = newA(i, k) / newA(k, k);
            for (int j = k; j < n; j++){
                newA(i, j) -= z * newA(k, j);
            }
            newB[i] -= z * newB[k];
        }
    }

    Vector x(n);
    //krok 3 - podstawienie wsteczne
    for (int i = n - 1; i >= 0; i--){
        x[i] = newB[i];
        for(int j = i + 1; j < n; j++){
            x[i] = x[i] - newA(i, j) * x[j];
        }
        x[i] = x[i] / newA(i, i);
    }
  
    while (true) {
        Vector residual = residual_vector(A, b, x);
        if (residual.max_norm() < eps){
            return x;
        }
        Vector e = solveEquations(A, residual, eps);
        for (int i = 0; i < n; ++i) {
            x[i] += e[i];
        }
    }
    return x;
}
