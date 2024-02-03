//
// Created by Matthijs Rog on 11/18/2023.
//

#include <iostream>

inline BoolProxy::BoolProxy(std::vector<bool>& vec, size_t index) : _vec(vec), _index(index) {

}

inline BoolProxy::operator bool() const {
    return _vec[_index];
}

inline BoolProxy& BoolProxy::operator=(bool b) {
    _vec[_index] = b;
    return *this;
}

template<typename Derived, typename T>
inline AbstractField<Derived, T>::AbstractField(int width, int height): _width(1), _height(1),
                                                                 _field(1, std::vector<T>(1)) {
    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Width and height must be non-negative");
    }
    // Now safely convert to size_t
    _width = static_cast<std::size_t>(width);
    _height = static_cast<std::size_t>(height);

    _field = std::vector<std::vector<T>>(height, std::vector<T>(width));
    fill(0);
}

template<typename Derived, typename T>
inline void AbstractField<Derived, T>::fill(const T &value) {
    for (auto &row : _field) {
        std::fill(row.begin(), row.end(), value);
    }
}

template<typename Derived, typename T>
inline std::size_t AbstractField<Derived, T>::width() const {
    return _width;
}

template<typename Derived, typename T>
inline std::size_t AbstractField<Derived, T>::height() const {
    return _height;
}

template<typename scalar>
inline scalar ScalarField<scalar>::operator()(std::size_t x, std::size_t y) const {
    if (x >= this->_width || y >= this->_height) {
        throw std::out_of_range("Index out of range");
    }
    return this->_field[x][y];
}

template<typename scalar>
inline scalar &ScalarField<scalar>::operator()(std::size_t x, std::size_t y) {
    if (x >= this->_width || y >= this->_height) {
        throw std::out_of_range("Index out of range");
    }
    return this->_field[x][y];
}

inline bool Mask::operator()(std::size_t x, std::size_t y) const{
    if (x >= this->_width || y >= this->_height) {
        throw std::out_of_range("Index out of range");
    }
    return _field[x][y];
}

inline Mask Mask::operator!() const {
    Mask result(this->_width, this->_height);
    for (std::size_t x = 0; x < this->_width; x++) {
        for (std::size_t y = 0; y < this->_height; y++) {
            result(x, y) = !this->_field[x][y];
        }
    }
    return result;
}

inline Mask Mask::operator||(const Mask &other) const {
    if (this->_width != other._width || this->_height != other._height) {
        throw std::invalid_argument("Dimensions must match");
    }

    Mask result(this->_width, this->_height);
    for (std::size_t x = 0; x < this->_width; x++) {
        for (std::size_t y = 0; y < this->_height; y++) {
            result(x, y) = this->_field[x][y] || other._field[x][y];
        }
    }
    return result;
}

inline BoolProxy Mask::operator()(std::size_t x, std::size_t y) {
    if (x >= this->_width || y >= this->_height) {
        throw std::out_of_range("Index out of range");
    }
    return BoolProxy(_field[x], y);
}

template<typename scalar>
inline ScalarField<scalar> ScalarField<scalar>::operator+(const scalar& val) const{
    ScalarField<scalar> result(this->_width, this->_height);
    for (std::size_t x = 0; x < this->_width; x++) {
        for (std::size_t y = 0; y < this->_height; y++) {
            result(x, y) = this->_field[x][y] + val;
        }
    }
    return result;
}


template<typename scalar>
inline ScalarField<scalar> ScalarField<scalar>::operator+(const ScalarField<scalar> &other) const {
    if (this->_width != other._width || this->_height != other._height) {
        throw std::invalid_argument("Dimensions must match");
    }

    ScalarField<scalar> result(this->_width, this->_height);
    for (std::size_t x = 0; x < this->_width; x++) {
        for (std::size_t y = 0; y < this->_height; y++) {
            result(x, y) = this->_field[x][y] + other._field[x][y];
        }
    }
    return result;
}

template<typename scalar>
ScalarField<scalar> ScalarField<scalar>::operator-(const scalar& val) const{
    ScalarField<scalar> result(this->_width, this->_height);
    for (std::size_t x = 0; x < this->_width; x++) {
        for (std::size_t y = 0; y < this->_height; y++) {
            result(x, y) = this->_field[x][y] - val;
        }
    }
    return result;
}

template<typename scalar>
inline ScalarField<scalar> ScalarField<scalar>::operator-(const ScalarField<scalar> &other) const {
    if (this->_width != other._width || this->_height != other._height) {
        throw std::invalid_argument("Dimensions must match");
    }

    ScalarField<scalar> result(this->_width, this->_height);
    for (std::size_t x = 0; x < this->_width; x++) {
        for (std::size_t y = 0; y < this->_height; y++) {
            result(x, y) = this->_field[x][y] - other._field[x][y];
        }
    }
    return result;
}

template<typename scalar>
inline ScalarField<scalar> ScalarField<scalar>::operator*(const scalar& val) const{
    ScalarField<scalar> result(this->_width, this->_height);
    for (std::size_t x = 0; x < this->_width; x++) {
        for (std::size_t y = 0; y < this->_height; y++) {
            result(x, y) = this->_field[x][y] * val;
        }
    }
    return result;
}

template<typename scalar>
inline ScalarField<scalar> ScalarField<scalar>::operator*(const ScalarField<scalar> &other) const {
    if (this->_width != other._width || this->_height != other._height) {
        throw std::invalid_argument("Dimensions must match");
    }

    ScalarField<scalar> result(this->_width, this->_height);
    for (std::size_t x = 0; x < this->_width; x++) {
        for (std::size_t y = 0; y < this->_height; y++) {
            result(x, y) = this->_field[x][y] * other._field[x][y];
        }
    }
    return result;
}