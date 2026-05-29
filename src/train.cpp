// Copyright 2021 NNTU-CS
#include "../include/train.h"
Train::Train() : countOp(0), first(nullptr), length(0) {}
Train::~Train() {
    clear();
}
void Train::addCar(bool light) {
    Car* newCar = new Car(light);
    if (first == nullptr) {
        first = newCar;
        first->next = first;
        first->prev = first;
    } else {
        Car* last = first->prev;
        last->next = newCar;
        newCar->prev = last;
        newCar->next = first;
        first->prev = newCar;
    }
    length++;
}
void Train::clear() {
    if (first == nullptr) return;
    Car* current = first;
    do {
        Car* next = current->next;
        delete current;
        current = next;
    } while (current != first);
    
    first = nullptr;
    length = 0;
    countOp = 0;
}
int Train::getLength() {
    countOp = length * length;
    return length;
}
int Train::getOpCount() const {
    return countOp;
}
int Train::getActualLength() const {
    return length;
}
