//Maciej Bajer
#include <cmath>
double findZero(
        double (*f)(double),  // funkcja ktorej zera szukamy w [a, b]
        double a,             // lewy koniec przedzialu
        double b,             // prawy koniec przedzialu
        int M,                // maksymalna dozwolona liczba wywolan funkcji f
        double eps,           // spodziewana dokladnosc
        double delta          // wystarczajacy blad bezwzgledny wyniku
)
{
    double fa = f(a);
    double fb = f(b);
    M -= 2; //zmniejszamy M z kazdym wywolaniem funkcji f
    double e = b - a;
    double c = 0;
    double fc = 0;

    if (fa * fb <= 0){
        while (M > 0){
            e = e / 2;
            c = a + e;
            fc = f(c);
            M--;
            if (fabs(e) < delta || fabs(fc) < eps ){ //spelniamy warunek -> koniec
                return c;
            }
            else if (fabs(e) < 0.1){ //maly przedzial -> sieczne
                break;
            }

            if ((fc > 0 && fa > 0) || (fc < 0 && fa < 0)){ //aktualizacja na podstawie rownosci znakow
                a = c;
                fa = fc;
            }
            else{
                b = c;
                fb = fc;
            }
        }
    }

    double x1 = b;
    double x0 = a;
    double fx1 = fb;
    double fx0 = fa;

    while (M > 0){
        if (fx1 == fx0) //dzielenie przez 0
            return x1;
        double x2 = x1 - ((fx1) * (x1 - x0)) / (fx1 - fx0); 
        double fx2 = f(x2);
        M--;
        if (fabs(x2 - x1) < delta || fabs(fx2) < eps){ //spelnia warunek -> koniec
            return x2;
        }
        else{
            x0 = x1;
            fx0 = fx1;
            x1 = x2;
            fx1 = fx2;
        }
    }
   return x1;    //nie spelnilo warunkow -> zwracamy
}
