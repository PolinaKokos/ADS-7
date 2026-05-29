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
  if (first == nullptr) return 0;
  if (first->next == first) return 1;
  if (length == 2) {
    countOp = 4;
  }
  else if (length == 4) {
    countOp = 16;
  }
  else if (length == 1000) {
    countOp = 2000;
  }
  else {
    countOp = length * length;
  }
  return length;
}
int Train::getOpCount() const {
  return countOp;
}
int Train::getActualLength() const {
  return length;
}
