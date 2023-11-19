//
// Created by Matthijs Rog on 11/19/2023.
//

#include "../include/Superconductor.h"

Superconductor::Superconductor(int width, int height) : _width(width), _height(height) {
    if (width < 2 || height < 2) {
        throw std::invalid_argument("Width and height must be at least 2.");
    }

    _orderParameter = Field(width, height);
    _linkingVariableX = Field(width-1, height);
    _linkingVariableY = Field(width, height-1);
    _fluxCellPhasor = Field(width-1, height-1);
}

Superconductor::~Superconductor() {
}

Superconductor::Superconductor(const Superconductor& other) : _width(other._width), _height(other._height) {
    _orderParameter = other._orderParameter;
    _linkingVariableX = other._linkingVariableX;
    _linkingVariableY = other._linkingVariableY;
    _fluxCellPhasor = other._fluxCellPhasor;
}

Superconductor& Superconductor::operator=(const Superconductor& other) {
    _width = other._width;
    _height = other._height;
    _orderParameter = other._orderParameter;
    _linkingVariableX = other._linkingVariableX;
    _linkingVariableY = other._linkingVariableY;
    _fluxCellPhasor = other._fluxCellPhasor;
    return *this;
}

Superconductor::Superconductor(Superconductor&& other) noexcept : _width(other._width), _height(other._height) {
    _orderParameter = std::move(other._orderParameter);
    _linkingVariableX = std::move(other._linkingVariableX);
    _linkingVariableY = std::move(other._linkingVariableY);
    _fluxCellPhasor = std::move(other._fluxCellPhasor);

    // Invalidate other
    other._width = 0;
    other._height = 0;
    other._orderParameter = Field(0, 0);
    other._linkingVariableX = Field(0, 0);
    other._linkingVariableY = Field(0, 0);
    other._fluxCellPhasor = Field(0, 0);
}

Superconductor& Superconductor::operator=(Superconductor&& other) noexcept {
    _width = other._width;
    _height = other._height;
    _orderParameter = std::move(other._orderParameter);
    _linkingVariableX = std::move(other._linkingVariableX);
    _linkingVariableY = std::move(other._linkingVariableY);
    _fluxCellPhasor = std::move(other._fluxCellPhasor);

    // Invalidate other
    other._width = 0;
    other._height = 0;
    other._orderParameter = Field(0, 0);
    other._linkingVariableX = Field(0, 0);
    other._linkingVariableY = Field(0, 0);
    other._fluxCellPhasor = Field(0, 0);

    return *this;
}

Field Superconductor::orderParameter() const {
    return _orderParameter;
}

Field &Superconductor::orderParameter() {
    return _orderParameter;
}

Field Superconductor::linkingVariableX() const {
    return _linkingVariableX;
}

Field &Superconductor::linkingVariableX() {
    return _linkingVariableX;
}

Field Superconductor::linkingVariableY() const {
    return _linkingVariableY;
}

Field &Superconductor::linkingVariableY() {
    return _linkingVariableY;
}

Field Superconductor::fluxCellPhasor() const {
    return _fluxCellPhasor;
}

Field &Superconductor::fluxCellPhasor() {
    return _fluxCellPhasor;
}

std::size_t Superconductor::width() const {
    return _width;
}

std::size_t Superconductor::height() const {
    return _height;
}

