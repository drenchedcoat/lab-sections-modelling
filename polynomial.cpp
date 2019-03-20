#include "polynomial.h"
//using namespace std;

struct Polynomial::Node{
    Node(int data = 0, Node* next = nullptr) : data(data), next(next) { cout << data << endl; }
    int data;
    Node* next;
};
Polynomial::Node* Polynomial::listFindTail(Node* hp){
    if (hp == nullptr){ return nullptr; }
    Node* p = hp;
    while (p->next != nullptr){
        p = p->next;
    } return p;
}
void Polynomial::listAddTail(Node*& hp, int data) {
    Node* tail = listFindTail(hp);
    if (tail == nullptr) { hp = new Node(data); }
    else { tail->next = new Node(data); }
}
void Polynomial::listAddHead(Node*& hp, int data) { hp = new Node(data, hp); }
void Polynomial::listRemoveAfter(Node* prior){
    Node* target = prior->next;
    prior->next = prior->next->next;
    delete target;
}
Polynomial::Node* Polynomial::listCopyV2(Node* hp){
    if (hp == nullptr) return nullptr;
    return new Node(hp->data, listCopyV2(hp->next));
}
Polynomial::Polynomial (std::vector<int> aList = {}) {
    for (size_t x = aList.size()-1; x >= 0; --x){
        listAddTail(poly, aList[x]);
    } degree = aList.size();
}
Polynomial::Polynomial(const Polynomial& rhs) {
    degree = rhs.degree;
    poly = listCopyV2(rhs.poly);
}
Polynomial& Polynomial::operator=(const Polynomial& rhs){
    degree = rhs.degree;
    poly = listCopyV2(rhs.poly);
    return *this;
}
Polynomial& Polynomial::operator+( Polynomial& rhs){
    *this += rhs;
    return *this; //return copy of new addition value
}
Polynomial::~Polynomial(){
    while (poly->next != nullptr){
        listRemoveAfter(poly);
    } delete poly;
}
Polynomial& Polynomial::operator+=(Polynomial& rhs){
    if (degree<rhs.degree){
        while (poly != nullptr){
            poly->data += rhs.poly->data;
            poly = poly->next;
        }
    } else {
        while (rhs.poly != nullptr){
            poly->data += rhs.poly->data;
            rhs.poly = rhs.poly->next;
        }
    } return *this;
}
int Polynomial::evaluate(int val) const {
    int total = 0;
    int exponent = 0;
    Polynomial::Node* current = poly;
    while (current != nullptr){
        total += (current->data * pow(val,exponent));
        current->next;
    } return total;
}
bool Polynomial::operator==(const Polynomial& rhs) const {
    Node* p = poly;
    Node* q = rhs.poly;
    while (p != nullptr && q != nullptr){
        if (p != q){ return false; }
        p = p->next;
        q = q->next;
    } if (p != nullptr || q!= nullptr) { return false; }
    return true;
}
bool Polynomial::operator!=(const Polynomial& rhs) const { return !(*this == rhs); }

std::ostream& Polynomial::operator<<(std::ostream& os, const Polynomial& rhs) {
    int counter = 0;
    std::vector<int> vecOut;
    Polynomial::Node* p = rhs.poly;
    while (p != nullptr){
        vecOut.std::push_back(p->data);
        p = p->next;
    } int exponent = 0;
    for (size_t x = vecOut.std::size()-1; x >= 0; --x){
        if (vecOut[x] == 0) {
            if (x == 0) { //last element
                if (exponent == 0){ os << vecOut[x]; }
                else if (exponent == 1){ os << vecOut[x] << "x"; }
                else { os << vecOut[x] << "x^" << x; }
            } else { //not last element
                if (exponent == 0){ os << vecOut[x] << " + "; }
                else if (exponent == 1){ os << vecOut[x] << "x + "; }
                else { os << vecOut[x] << "x^" << x << " + "; }
            }
        } ++exponent;
    } return os;
}
