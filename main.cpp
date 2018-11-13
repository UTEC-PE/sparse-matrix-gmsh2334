#include <iostream>
#include "matrix.h"

using namespace std;

int main(int argc, char *argv[]) {

    Matrix<int> r(10,10);
    Matrix<int> a(5,5);
    Matrix<int> b(5,5);
    Matrix<int> c(5,5);

    for (int i=0; i<10; i++){
        for (int j=0; j<10; j++)
        {
            r.set(i,j,rand()%10);
        }
    }
    for(int i=0; i<5; i++){
        for (int j=0; j<5; j++){
            a.set(i, j, i+j);
        }
    }
    for(int i=0; i<5; i++){
        for (int j=0; j<5; j++){
            b.set(i, j, 1);
        }
    }

    cout << "\n\n";
    r.print();

    cout << "\n\n";
    a.set(2, 2, 4);

    cout << "\n\n";
    a.print();
    cout << "\n\n";

    Matrix<int> e(5,2);
    for (int i =0; i<5; i++){
        e.set(i,0,2);
    }
    e.print();
    cout << "\n\n";
    e= (a*e);
    cout << "\n\n";
    e.print();
    cout << "\n\nPresione una tecla para continuar...";
    cin.get();
    return EXIT_SUCCESS;
}