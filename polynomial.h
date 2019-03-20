#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H


/**
zehra bacioglu, zna215 n17199881
very bad code
*/

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
using namespace std;

class Polynomial {
    friend ostream& operator<<(ostream& os, const Polynomial& rhs);
private:
    struct Node;
    Node* listFindTail(Node* hp);
    void listAddTail(Node*& hp, int data);
    void listAddHead(Node*& hp, int data);
    void listRemoveAfter(Node* prior);
    Node* listCopyV2(Node* hp);
    Node* poly = nullptr;
    int degree = 0;
public:
    Polynomial (vector<int> aList = {});
    Polynomial (const Polynomial& rhs);
    Polynomial& operator=(const Polynomial& rhs);
    Polynomial& operator+(Polynomial& rhs);
    ~Polynomial();
    Polynomial& operator+=(Polynomial& rhs);
    int evaluate(int val) const;
    bool operator==(const Polynomial& rhs) const;
    bool operator!=(const Polynomial& rhs) const;
};

#endif // POLYNOMIAL_H
