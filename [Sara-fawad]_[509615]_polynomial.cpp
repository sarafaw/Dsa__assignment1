#include "Polynomial.h"
#include <iostream>
#include <sstream>
#include <cmath>

class LinkedListPolynomial : public Polynomial {
private:
    struct Term {
        int  coeff, exp;
        Term* next;
        Term(int c, int e) : coeff(c), exp(e), next(nullptr) {}
    };

    Term* head;

public:
    LinkedListPolynomial() : head(nullptr) {}
    ~LinkedListPolynomial() {
        Term* curr = head;
        while (curr) {
            Term* temp =curr;
            curr =curr->next;
            delete temp;
        }
    }
    void insertTerm(int coefficient, int exponent) override {
        if (coefficient == 0) return;

        Term* newTerm = new Term(coefficient, exponent);
        Term* curr = head;
        Term* prev = nullptr;

        while (curr && curr->exp > exponent) {
            prev = curr;
            curr = curr->next;
        }
        if (curr && curr->exp == exponent) {
            curr->coeff += coefficient;
            delete newTerm;
            if (curr->coeff == 0) { // remove zero term
                if (prev) prev->next = curr->next;
                else head = curr->next;
                delete curr;
            }
            return;
        }
        newTerm->next = curr;
        if (prev) prev->next = newTerm;
        else head = newTerm;
    }
    std::string toString() const override {
        if (!head) return "0";
        std::ostringstream out;
        Term* curr = head;
        bool first = true;

        while (curr){
            int c = curr->coeff, e = curr->exp;

            if (!first){
                if (c > 0) out << " + ";
                else out << " - ";
            }
            else if (c < 0){
                out << "-";
            }
             int absC = std::abs(c);
            if (e == 0) out << absC;
            else if (e == 1) {
                if (absC != 1) out << absC;
                out << "x";
            }
              else {
                if (absC != 1) out << absC;
                out << "x^" << e;
              }

               first = false;
            curr = curr->next;
        }

           return out.str();
    }

       Polynomial* add(const Polynomial& other) const override {
        const LinkedListPolynomial* rhs = dynamic_cast<const LinkedListPolynomial*>(&other);
        if (!rhs) return nullptr;

        LinkedListPolynomial* result = new LinkedListPolynomial();
        Term* a = head;
        Term* b = rhs->head;

        while (a || b) {
            int coeff, exp;
            if (!b || (a && a->exp > b->exp)) {
                coeff = a->coeff; exp = a->exp; a = a->next;
            }
            else if (!a || (b->exp > a->exp)) {
                coeff = b->coeff; exp = b->exp; b = b->next;
              }
            else {
                coeff = a->coeff + b->coeff; exp = a->exp;
                  a = a->next; b = b->next;
            }
            if (coeff != 0) result->insertTerm(coeff, exp);
        }

        return result;
    }

    Polynomial* multiply(const Polynomial& other) const override {
        const LinkedListPolynomial* rhs = dynamic_cast<const LinkedListPolynomial*>(&other);
        if (!rhs) return nullptr;

        LinkedListPolynomial* result = new LinkedListPolynomial();
        for (Term* a = head; a; a = a->next)
            for (Term* b = rhs->head; b; b = b->next)
                result->insertTerm(a->coeff * b->coeff, a->exp + b->exp);

        return result;
    }

    Polynomial* derivative() const override {
        LinkedListPolynomial* result = new LinkedListPolynomial();
        for (Term* a = head; a; a = a->next) {
            if (a->exp > 0)
                result->insertTerm(a->coeff * a->exp, a->exp - 1);
        }
        return result;
    }
};
Polynomial* createPolynomial() {
    return new LinkedListPolynomial();
}