/*
 * CS106B Section Handout Test Harness: Section 7
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified by Neel Kishnani for 
 * Winter 2022.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */

#include "myDeque.h"
using namespace std;
#include <string>


Deque::Deque() {

    head=new Cell;
    tail=new Cell;

    this->head->next=this->tail;
    this->tail->prev=this->head;

    this->head->prev=this->tail->next=nullptr;

    this->numElems=0;

}

Deque::~Deque() {}



bool Deque::isEmpty() const {

    return true ;
}

int Deque::size() const {
    return -1;
}

void Deque::pushFront(int value) {
    (void) value;
}

void Deque::pushBack(int value) {
    (void) value;
}

int Deque::peekFront() const {
    return -1;
}

int Deque::peekBack() const {
    return -1;
}

int Deque::popFront() {
    return -1;
}

int Deque::popBack() {
    return -1;
}
