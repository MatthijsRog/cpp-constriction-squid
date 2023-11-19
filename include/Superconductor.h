//
// Created by Matthijs Rog on 11/19/2023.
//

#ifndef CPP_CONSTRICTION_SQUID_SUPERCONDUCTOR_H
#define CPP_CONSTRICTION_SQUID_SUPERCONDUCTOR_H

#include "Field.h"

class Superconductor {
public:
    /**
     * @brief Constructs a new Superconductor object.
     * @param width
     * @param height
     */
    Superconductor(int width, int height);

    /**
     * @brief Destroys the Superconductor object.
     */
    ~Superconductor();

    /**
     * @brief Copy constructor.
     * @param other The Superconductor to copy.
     */
    Superconductor(const Superconductor& other);

    /**
     * @brief Copy assignment operator.
     * @param other The Superconductor to copy.
     */
    Superconductor& operator=(const Superconductor& other);

    /**
     * @brief Move constructor.
     * @param other The Superconductor to move.
     */
    Superconductor(Superconductor&& other) noexcept;

    /**
     * @brief Move assignment operator.
     * @param other The Superconductor to move.
     */
    Superconductor& operator=(Superconductor&& other) noexcept;

    /**
     * @brief Accesses the superconductor's order parameter.
     * @return The order parameter.
     */
    Field orderParameter() const;

    /**
     * @brief Accesses the superconductor's order parameter.
     * @return The order parameter.
     */
    Field& orderParameter();

    /**
     * @brief Accesses the superconductor's linking variable in the x direction.
     * @return The linking variable.
     */
    Field linkingVariableX() const;

    /**
     * @brief Accesses the superconductor's linking variable in the x direction.
     * @return The linking variable.
     */
    Field& linkingVariableX();

    /**
     * @brief Accesses the superconductor's linking variable in the y direction.
     * @return The linking variable.
     */
    Field linkingVariableY() const;

    /**
     * @brief Accesses the superconductor's linking variable in the y direction.
     * @return The linking variable.
     */
    Field& linkingVariableY();

    /**
     * @brief Accesses the superconductor's flux cell phasor.
     * @return The flux cell phasor.
     */
    Field fluxCellPhasor() const;

    /**
     * @brief Accesses the superconductor's flux cell phasor.
     * @return The flux cell phasor.
     */
    Field& fluxCellPhasor();

    /**
     * @brief Access the superconductor's width.
     * @return The width.
     */
    std::size_t width() const;

    /**
     * @brief Access the superconductor's height.
     * @return The height.
     */
    std::size_t height() const;


private:
    std::size_t _width;
    std::size_t _height;

    Field _orderParameter;
    Field _linkingVariableX;
    Field _linkingVariableY;
    Field _fluxCellPhasor;
};

#endif //CPP_CONSTRICTION_SQUID_SUPERCONDUCTOR_H
