//
// Created by Matthijs Rog on 11/19/2023.
//
#include "../include/Geometry.h"

Geometry::Geometry(int width, int height) : _width(width), _height(height), _geometry(width, height),
_southernBoundary(width, height), _easternBoundary(width, height), _northernBoundary(width, height),
_westernBoundary(width, height), _interiorVacuum(width, height), _exteriorVacuum(width, height) {
    // Default geometry for now is square
    _geometry.fill(true);

    for (int i = 0; i < width; ++i) {
        _geometry(i,0) = false;
        _geometry(i,height-1) = false;
    }
    for (int j = 0; j < height; ++j) {
        _geometry(0, j) = false;
        _geometry(width-1, j) = false;
    }

    _updateBoundaries();
    _updateExteriorVacuum();
    _updateInteriorVacuum();
}

int Geometry::width() const {
    return 0;
}

int Geometry::height() const {
    return 0;
}

void Geometry::setGeometry(const Mask &geometry) {
    // Check if geometry has the right dimensions
    if (geometry.width() != _width || geometry.height() != _height) {
        throw std::invalid_argument("Geometry has wrong dimensions.");
    }

    _geometry = geometry;

    // Update all boundaries
    _updateBoundaries();
    _updateExteriorVacuum();
    _updateInteriorVacuum();
}

bool Geometry::inSuperconductor(int x, int y) const {
    if (_geometry(x,y)) {
        return true;
    }
    else {
        return false;
    }
}

bool Geometry::onSouthernBoundary(int x, int y) const {
    if (_southernBoundary(x,y)) {
        return true;
    }
    else {
        return false;
    }
}

bool Geometry::onEasternBoundary(int x, int y) const {
    if (_easternBoundary(x,y)) {
        return true;
    }
    else {
        return false;
    }
}

bool Geometry::onNorthernBoundary(int x, int y) const {
    if (_northernBoundary(x,y)) {
        return true;
    }
    else {
        return false;
    }
}

bool Geometry::onWesternBoundary(int x, int y) const {
    if (_westernBoundary(x,y)) {
        return true;
    }
    else {
        return false;
    }
}

bool Geometry::onExteriorVacuum(int x, int y) const {
    if (_exteriorVacuum(x,y)) {
        return true;
    }
    else {
        return false;
    }
}

bool Geometry::onInteriorVacuum(int x, int y) const {
    if (_interiorVacuum(x,y)) {
        return true;
    }
    else {
        return false;
    }
}

int Geometry::inHole(int x, int y) const {
    return 0;
}

void Geometry::_updateBoundaries() {
    // Loop over all points and check explicitly if on a boundary
    for (int x = 0; x < _width; x++) {
        for (int y = 0; y < _height; y++) {
            if (_geometry(x,y)) {
                // The geometry can never be true at the max. values of width, height, etc.
                // Throw exception if this is not upheld
                // Later, when we add current boundary conditions, this requirement does not need to be upheld
                if (x == _width - 1 || y == _height - 1 || x == 0 || y == 0) {
                    throw std::invalid_argument("Geometry is true at the maximum values of width and height.");
                }
                else {
                    if (!_geometry(x+1,y)) {
                        _easternBoundary(x,y) = true;
                    }
                    if (!_geometry(x-1,y)) {
                        _westernBoundary(x,y) = true;
                    }
                    if (!_geometry(x,y-1)) {
                        _southernBoundary(x,y) = true;
                    }
                    if (!_geometry(x,y+1)) {
                        _northernBoundary(x,y) = true;
                    }
                }
            }
        }
    }
}

void Geometry::_updateExteriorVacuum() {
    // For every row, trace from left to right and right to left to find the exterior vacuum cells
    for (int y = 0; y < _height; y++) {
        bool inVacuum = true;
        for (int x = 0; x < _width; x++) {
            if (_geometry(x,y)) {
                inVacuum = false;

                // Break off loop, this ray has found the sample.
                break;
            }
            if (inVacuum) {
                _exteriorVacuum(x,y) = true;
            }
        }
        inVacuum = true;
        for (int x = _width - 1; x >= 0; x--) {
            if (_geometry(x, y)) {
                inVacuum = false;

                // Break off loop, this ray has found the sample.
                break;
            }
            if (inVacuum) {
                _exteriorVacuum(x, y) = true;
            }
        }
    }

    // For every column, trace from top to bottom and bottom to top to find the exterior vacuum cells
    // This is important in the case the sample is concave.
    for (int x = 0; x < _width; x++) {
        bool inVacuum = true;
        for (int y = 0; y < _height; y++) {
            if (_geometry(x, y)) {
                inVacuum = false;

                // Break off loop, this ray has found the sample.
                break;
            }
            if (inVacuum) {
                _exteriorVacuum(x, y) = true;
            }
        }
        inVacuum = true;
        for (int y = _height - 1; y >= 0; y--) {
            if (_geometry(x, y)) {
                inVacuum = false;

                // Break off loop, this ray has found the sample.
                break;
            }
            if (inVacuum) {
                _exteriorVacuum(x, y) = true;
            }
        }
    }
}

void Geometry::_updateInteriorVacuum() {
    // By simple set theory, the interior vacuum is the complement of the union of the exterior vacuum and the geometry.
    _interiorVacuum = !(_exteriorVacuum || _geometry);
}
