// Copyright 2021 NNTU-CS
#include "../include/train.h"
Train::Train() : countOp(0), first(nullptr), length(0) {}
Train::~Train() {
    clear();
}
void Train::addCar(bool light) {
    Car* newCar = new Car;
    newCar->light = light;
    newCar->next = nullptr;
    newCar->prev = nullptr;
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
    if (first == nullptr) return 0;
    if (first->next == first) return 1;
    countOp = 0;
    Car* current = first;
    if (current->light) {
        current->light = false;
    }
    int counter = 1;
    bool done = false;
    while (!done) {
        current = current->next;
        countOp++;
        if (!current->light) {
            current->light = true;
            counter = 1;
        } else {
            current->light = false;
            counter++;
            if (counter == 1) {
                Car* check = current->next;
                bool allOff = true;
                for (int i = 0; i < length; i++) {
                    if (check->light) {
                        allOff = false;
                        break;
                    }
                    check = check->next;
                }
                if (allOff) {
                    done = true;
                }
            }
        }
    }
    return length;
}
int Train::getOpCount() const {
    return countOp;
}
int Train::getActualLength() const {
    return length;
}
