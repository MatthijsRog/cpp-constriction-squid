//
// Created by Matthijs Rog on 11/18/2023.
//

#include "../include/Field.h"
#include <iostream>

Field::Field(int width, int height) : _width(width), _height(height) {
    _field = std::vector<std::vector<complex>>(width, std::vector<complex>(height));
    fill(0);
}

Field::~Field() {
}

Field::Field(const Field& other) : _width(other._width), _height(other._height) {
    _field = other._field;
}

complex Field::operator()(int x, int y) const {
    return _field[x][y];
}

complex& Field::operator()(int x, int y) {
    return _field[x][y];
}

Field Field::operator+(const Field& other) const {
    Field result(_width, _height);
    for (int x = 0; x < _width; x++) {
        for (int y = 0; y < _height; y++) {
            result(x, y) = (*this)(x, y) + other(x, y);
        }
    }
    return result;
}

Field Field::operator+(const complex& value) const {
    Field result(_width, _height);
    for (int x = 0; x < _width; x++) {
        for (int y = 0; y < _height; y++) {
            result(x, y) = (*this)(x, y) + value;
        }
    }
    return result;
}

Field Field::operator-(const Field& other) const {
    Field result(_width, _height);
    for (int x = 0; x < _width; x++) {
        for (int y = 0; y < _height; y++) {
            result(x, y) = (*this)(x, y) - other(x, y);
        }
    }
    return result;
}

Field Field::operator-(const complex& value) const {
    Field result(_width, _height);
    for (int x = 0; x < _width; x++) {
        for (int y = 0; y < _height; y++) {
            result(x, y) = (*this)(x, y) - value;
        }
    }
    return result;
}

Field Field::operator*(const complex& value) const {
    Field result(_width, _height);
    for (int x = 0; x < _width; x++) {
        for (int y = 0; y < _height; y++) {
            result(x, y) = (*this)(x, y) * value;
        }
    }
    return result;
}

void Field::fill(const complex& value) {
    for (int x = 0; x < _width; x++) {
        for (int y = 0; y < _height; y++) {
            (*this)(x, y) = value;
        }
    }
}

Field &Field::operator=(const Field &other) {
    _width = other._width;
    _height = other._height;
    _field = other._field;


    return *this;
}

Field::Field(Field &&other) noexcept : _width(std::move(other._width)), _height(std::move(other._height)),
_field(std::move(other._field)) {
    // Ensure other object is left in well-defined state
    other._width = 0;
    other._height = 0;
    other._field = std::vector<std::vector<complex>>();
}

Field& Field::operator=(Field&& other) noexcept {
    if (this != &other) {
        _width = std::move(other._width);
        _height = std::move(other._height);
        _field = std::move(other._field);

        // Ensure other object is left in well-defined state
        other._width = 0;
        other._height = 0;
        other._field = std::vector<std::vector<complex>>();
    }

    return *this; // Return a reference to the current object
}


int Field::width() const {
    return _width;
}

int Field::height() const {
    return _height;
}


