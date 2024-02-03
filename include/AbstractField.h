//
// Created by Matthijs Rog on 11/18/2023.
//

#ifndef CPP_CONSTRICTION_SQUID_ABSTRACTFIELD_H
#define CPP_CONSTRICTION_SQUID_ABSTRACTFIELD_H

#include <vector>
#include <complex>

typedef std::complex<double> complex;

class BoolProxy {
public:
    BoolProxy(std::vector<bool>& vec, size_t index);

    operator bool() const;

    BoolProxy& operator=(bool b);

private:
    std::vector<bool>& _vec;
    size_t _index;
};


template<typename Derived, typename T>
class AbstractField {
public:
    /**
     * @brief Constructs a new AbstractField object of correct size. Fields are initialized with value 0.
     * @param width The width of the field.
     * @param height The height of the field.
     */
    AbstractField(int width, int height);

    /**
     * @brief Default virtual destructor.
     */
    virtual ~AbstractField() = default;

    /**
     * @brief Default copy constructor.
     */
    AbstractField(const AbstractField &other) = default;

    /**
     * @brief Default copy assignment operator.
     */
    AbstractField &operator=(const AbstractField &other) = default;

    /**
     * @brief Default move constructor.
     */
    AbstractField(AbstractField &&other) noexcept = default;

    /**
     * @brief Default move assignment operator.
     */
    AbstractField &operator=(AbstractField &&other) noexcept = default;

    /**
     * @brief Fills the field with a given value.
     * @param value The value to fill the field with.
     */
    void fill(const T &value);

    /**
     * @brief Accesses the field at a given position.
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     * @return The value at the given position.
     */
    auto operator()(std::size_t x, std::size_t y) const;

    /**
     * @brief Accesses the field at a given position.
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     * @return The value at the given position.
     */
    auto &operator()(std::size_t x, std::size_t y);

    /**
     * @brief Get the width of the container.
     * @return The width.
     */
    std::size_t width() const;

    /**
     * @brief Get the height of the container.
     * @return The height.
     */
    std::size_t height() const;

protected:
    std::size_t _width;
    std::size_t _height;
    std::vector<std::vector<T> > _field;
};

template<typename scalar>
class ScalarField : public AbstractField<ScalarField<scalar>, scalar> {
public:
    using AbstractField<ScalarField<scalar>, scalar>::AbstractField;

    /**
     * @brief Accesses the field at a given position.
     * @param x
     * @param y
     * @return Value at coordinates (x,y).
     */
    scalar operator()(std::size_t x, std::size_t y) const;

    /**
     * @brief Accesses the field at a given position.
     * @param x
     * @param y
     * @return Reference to value at coordinates (x,y)
     */
    scalar& operator()(std::size_t x, std::size_t y);

    /**
     * @brief Addition of a scalar to a field.
     * @param scalar The scalar to add.
     * @return The resulting field.
     */
    ScalarField operator+(const scalar& val) const;

    /**
     * @brief Scalar addition of two fields.
     * @param other The field to add.
     * @return The resulting field.
     */
    ScalarField operator+(const ScalarField& other) const;

    /**
     * @brief Subtraction of a scalar from a field.
     * @param scalar The scalar to subtract.
     * @return The resulting field.
     */
    ScalarField operator-(const scalar& val) const;

    /**
     * @brief Scalar subtraction of two fields.
     * @param other The field to subtract.
     * @return The resulting field.
     */
    ScalarField operator-(const ScalarField& other) const;

    /**
     * @brief Multiplication of a field by a scalar.
     * @param scalar The scalar to multiply by.
     * @return The resulting field.
     */
    ScalarField operator*(const scalar& val) const;

    /**
     * @brief Element-wise scalar multiplication of two fields.
     * @param other The field to multiply by.
     * @return The resulting field.
     */
    ScalarField operator*(const ScalarField& other) const;
};

class Mask : public AbstractField<Mask, bool> {
public:
    using AbstractField<Mask, bool>::AbstractField;

    /**
     * @brief Accesses the field at a given position.
     * @param x
     * @param y
     * @return Value at coordinates (x,y).
     */
     bool operator()(std::size_t x, std::size_t y) const;

    /**
     * @brief Accesses the field at a given position.
     * @param x
     * @param y
     * @return Reference to value at coordinates (x,y)
     */
     BoolProxy operator()(std::size_t x, std::size_t y);

    /**
     * @brief Logical NOT operator.
     * @return The negation of the field.
     */
    Mask operator!() const;

    /**
     * @brief Logical OR operator.
     * @param other The field to OR with.
     * @return The result of the OR operation.
     */
    Mask operator||(const Mask& other) const;
};

typedef ScalarField<complex> Field;
typedef ScalarField<double> RealField;

#include "../src/AbstractField.tpp"

#endif //CPP_CONSTRICTION_SQUID_ABSTRACTFIELD_H
