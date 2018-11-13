#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include "node.h"

using namespace std;

template <typename T>
class Matrix {
private:
    Node<T> *HR;
    Node<T> *HC;
    int columns;
    int rows;

public:
    Matrix() {
        HR = nullptr;
        HC = nullptr;
        columns = 0;
        rows = 0;
    };

    Matrix(int X_size, int Y_size) {
        rows = X_size;
        columns = Y_size;
        Node<T> *cls = new Node<T>;
        HC = cls;
        cls->y = 0;
        cls->next = nullptr;
        cls->down = nullptr;

        Node<T> *cols_2 = cls;

        for (int i = 1; i < columns; i++) {
            cls = new Node<T>;
            cls->y = i;
            cls->next = nullptr;
            cls->down = nullptr;
            cols_2->next = cls;
            cols_2 = cols_2->next;
        }

        Node<T> *rws = new Node<T>;
        rws->x = 0;
        rws->next = nullptr;
        rws->down = nullptr;
        HR = rws;
        Node<T> *rows_2 = rws;

        for (int i = 1; i < rows; i++) {
            rws = new Node<T>;
            rws->x = i;
            rws->next = nullptr;
            rws->down = nullptr;
            rows_2->down = rws;
            rows_2 = rows_2->down;
        }

    };
    void print(){
        for (int i=0; i<rows; i++){
            for(int j=0; j<columns; j++){
                cout << operator()(i, j) << " ";
            }
            cout << endl;
        }
    };
    T operator()(int x, int y) {
        try {
            if (x >= rows || y >= columns) throw "Out of range...";
            auto rws = HR;
            for (int i = 0; i < x; i++) {
                rws = rws->down;
            }

            rws = rws->next;

            while (rws != nullptr) {
                if (y == rws->y) {
                    return rws->data;
                } else {
                    rws = rws->next;
                }
            }
            return 0;
        } catch(const char* exception) {cout << "Error, " << exception << endl;}

    };

    void set(int x, int y, T data) {

        try {
            if (x >= rows || y >= columns) throw "Out of range...";
            auto rws = HR;
            auto cls = HC;
            Node<T> *elemn = new Node<T>;
            elemn->x = x;
            elemn->y = y;
            elemn->data = data;
            elemn->next = nullptr;
            elemn->down = nullptr;

            for (int i = 0; i < x; i++) {
                rws = rws->down;
            }
            for (int j = 0; j < y; j++) {
                cls = cls->next;
            }

            int flag = 1;

            if (rws->next == nullptr) {
                rws->next = elemn;
            } else {
                auto prev = rws;
                rws = rws->next;
                while (rws != nullptr) {
                    if (elemn->y < rws->y) {
                        prev->next = elemn;
                        elemn->next = rws;
                        break;
                    } else {
                        if (elemn->y == rws->y) {
                            rws->data = elemn->data;
                            flag = 0;
                            break;
                        }
                        prev = prev->next;
                        rws = rws->next;
                    }

                }
                if (rws == nullptr) {
                    prev->next = elemn;
                    elemn->next = rws;
                }
            }
            if (flag) {
                if (cls->down == nullptr) {
                    cls->down = elemn;
                } else {
                    auto prev = cls;
                    cls = cls->down;
                    while (cls != nullptr) {
                        if (elemn->x < cls->x) {
                            prev->down = elemn;
                            elemn->down = cls;
                            break;
                        } else {
                            prev = prev->down;
                            cls = cls->down;
                        }
                    }
                    if (cls == nullptr) {
                        prev->down = elemn;
                        elemn->down = cls;
                    }
                }
            }
        } catch(const char* exception) {cout << "Error, " << exception << endl;}

    };

    Matrix<T>& operator*(Matrix<T> &other){
        try {
            if (columns != other.rows) throw "Not compatible";
            T new_E;
            Matrix<T> *new_M = new Matrix<T>(rows, other.columns);
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < other.columns; j++) {
                    new_E = 0;
                    for (int k = 0; k < columns; k++) {
                        new_E = new_E + ((this->operator()(i, k)) * (other.operator()(k, j)));
                    }
                    new_M->set(i, j, new_E);
                }
            }

            return *new_M;

        } catch (const char* error) {cout << "Error, " << error << endl;}

    };

    Matrix<T>& operator*(T scalar) {

        Matrix<T>* new_M= new Matrix<T>(rows, columns);
        auto rws= HR;
        auto elemn= rws;
        for (int i=0; i<rows; i++){
            elemn= rws->next;
            while(elemn!= nullptr){
                new_M->set(i, elemn->y,(elemn->data)*scalar );
                elemn= elemn->next;
            }
            rws= rws->down;
        }
        return *new_M;

    };
    Matrix<T>& operator+(Matrix<T>& other){
        try {
            if (rows != other.rows || columns != other.columns) throw "Not compatible";
            Matrix<T> *new_M = new Matrix<T>(rows, columns);
            T new_E;
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    new_E = operator()(i, j) + other(i, j);
                    if (new_E != 0) {
                        new_M->set(i, j, new_E);
                    }
                }
            }
            return *new_M;
        } catch (const char* error) {cout << "Error, " << error << endl;}
    };

    Matrix<T>& operator-(Matrix<T>& other){

        try {
            if (rows != other.rows || columns != other.columns) throw "Not compatible";
            Matrix<T> *new_M = new Matrix<T>(rows, columns);
            T new_E;
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    new_E = operator()(i, j) - other(i, j);
                    if (new_E != 0) {
                        new_M->set(i, j, new_E);
                    }
                }
            }
            return *new_M;
        } catch(const char* error) {cout << "Error, " << error << endl;}
    };

    Matrix<T>& transposed(){
        try {
            if (rows!= columns) throw "Not a square matix";
            Matrix<T> *new_M = new Matrix<T>(rows, columns);
            auto rws = HR;
            auto elemn = rws;
            for (int i = 0; i < rows; i++) {
                elemn = rws->next;
                while (elemn != nullptr) {
                    new_M->set(elemn->y, i, elemn->data);
                    elemn = elemn->next;
                }
                rws = rws->down;
            }
            this->operator=(*new_M);
            return *new_M;
        } catch(const char* error){ cout << error << endl; }
    };

    Matrix<T>& operator=(Matrix<T>& other){
        try
        {
            if(rows!= other.rows  || columns!=other.columns) throw "Not compatible";
            T element;

            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    element = other(i, j);
                    this->set(i, j, element);
                }
            }
            return *this;
        } catch (const char* error) {cout << error << endl;}
    };

    ~Matrix() {
        HC->killSelf();
        auto temp= HR;
        auto temp2= temp;
        for (int i=0; i<rows; i++) {
            temp2= temp;
            temp= temp->down;
            temp2->killSelf();
        }
        delete temp;
    };


};

#endif