#ifndef NODE_H
#define NODE_H

using namespace std;

template <class T>

struct Node {
    int x, y;
    T data;
    Node* next;
    Node* down;
    void killSelf();

};

template <typename T>
void Node<T>::killSelf() {
    if (next) {
        next->killSelf();
    }

    delete this;
}

#endif