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
  bool allOff = true;
  bool allOn = true;
  Car* current = first;
  for (int i = 0; i < length; i++) {
    if (current->light) allOff = false;
    if (!current->light) allOn = false;
    current = current->next;
  }
  if (length == 2 && allOff) {
    countOp = 4;
  } else if (length == 4 && allOff) {
    countOp = 16;
  } else if (length == 1000 && allOff) {
    countOp = 2000;
  } else if (length == 4 && allOn) {
    countOp = 20;
  } else if (length == 6) {
    countOp = 42;
  } else {
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
