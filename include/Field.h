//
// Created by Matthijs Rog on 11/18/2023.
//

#ifndef CPP_CONSTRICTION_SQUID_FIELD_H
#define CPP_CONSTRICTION_SQUID_FIELD_H

#include <vector>
#include <complex>

typedef std::complex<double> complex;

class Field {
public:
    /**
    * @brief Constructs a new Field object.
    * @param width The width of the field.
    * @param height The height of the field.
    */
    Field(int width, int height);

    /**
     * @brief Constructs a new Field object of minimal size (1x1)
     */
    Field();

    /**
     * @brief Destroys the Field object.
     */
    ~Field();

    /**
     * @brief Copy constructor.
     * @param other The Field to copy.
     */
    Field(const Field& other);

    /**
     * @brief Copy assignment operator.
     * @param other The Field to copy.
     */
    Field& operator=(const Field& other);

    /**
     * @brief Move constructor.
     * @param other The Field to move.
     */
    Field(Field&& other) noexcept;

    /**
     * @brief Move assignment operator.
     * @param other The Field to move.
     */
    Field& operator=(Field&& other) noexcept;

    /**
     * @brief Accesses local value of the field.
     * @param x The x coordinate of the field.
     * @param y The y coordinate of the field.
     * @return The value of the field at (x, y).
     */
    complex operator()(int x, int y) const;

    /**
     * @brief Accesses local value of the field.
     * @param x The x coordinate of the field.
     * @param y The y coordinate of the field.
     * @return The value of the field at (x, y).
     */
    complex& operator()(int x, int y);

    /**
     * @brief Adds two fields together.
     * @param other The other field to add.
     * @return The sum of the two fields.
     */
    Field operator+(const Field& other) const;

    /**
     * @brief Adds a complex value to the field.
     * @param value The value to add.
     * @return The sum of the field and the value.
     */
    Field operator+(const complex& value) const;

    /**
     * @brief Subtracts two fields.
     * @param other The field to subtract.
     * @return The difference of the two fields.
     */
    Field operator-(const Field& other) const;

    /**
     * @brief Subtracts a complex value from the field.
     * @param value The value to subtract.
     * @return The difference of the field and the value.
     */
    Field operator-(const complex& value) const;

    /**
     * @brief Multiplies field with a complex value.
     * @param value The value to multiply with.
     * @return The product of the field and the value.
     */
    Field operator*(const complex& value) const;

    /**
     * @brief Fills field with a complex value.
     * @param value The value to fill with.
     */
    void fill(const complex& value);

    /**
     * @brief Returns the width of the field.
     * @return The width of the field.
     */
    int width() const;

    /**
     * @brief Returns the height of the field.
     * @return The height of the field.
     */
    int height() const;


private:
    std::size_t _width;
    std::size_t _height;
    std::vector<std::vector<complex> > _field;
};

#endif //CPP_CONSTRICTION_SQUID_FIELD_H
