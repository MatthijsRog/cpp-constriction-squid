//
// Created by Matthijs Rog on 11/19/2023.
//

#ifndef CPP_CONSTRICTION_SQUID_GEOMETRY_H
#define CPP_CONSTRICTION_SQUID_GEOMETRY_H

#include "AbstractField.h"
#include <vector>

typedef std::vector<Mask> maskList;

class Geometry {
public:
    /**
     * @brief Constructs a new Geometry object.
     * @param width The width of the geometry.
     * @param height The height of the geometry.
     */
    Geometry(int width, int height);

    /**
     * @brief Destroys the Geometry object.
     */
    ~Geometry() = default;

    /**
     * @brief Copy constructor.
     * @param other The Geometry to copy.
     */
    Geometry(const Geometry& other) = default;

    /**
     * @brief Copy assignment operator.
     * @param other The Geometry to copy.
     */
    Geometry& operator=(const Geometry& other) = default;

    /**
     * @brief Move constructor.
     * @param other The Geometry to move.
     */
    Geometry(Geometry&& other) noexcept = default;

    /**
     * @brief Move assignment operator.
     * @param other The Geometry to move.
     */
    Geometry& operator=(Geometry&& other) noexcept = default;

    /**
     * @brief Accesses the geometry's width.
     * @return The width.
     */
    int width() const;

    /**
     * @brief Accesses the geometry's height.
     * @return The height.
     */
    int height() const;

    /**
     * @brief Set the superconductor's geometry.
     * @param geometry The geometry.
     */
    void setGeometry(const Mask& geometry);

    /**
     * @brief Check whether point (x, y) is in the superconductor.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @return True if the point is in the superconductor, false otherwise.
     */
    bool inSuperconductor(int x, int y) const;

    /**
     * @brief Check whether point (x, y) is on the southern boundary.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @return True if the point is on the southern boundary, false otherwise.
     */
    bool onSouthernBoundary(int x, int y) const;

    /**
     * @brief Check whether point (x, y) is on the eastern boundary.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @return True if the point is on the eastern boundary, false otherwise.
     */
    bool onEasternBoundary(int x, int y) const;

    /**
     * @brief Check whether point (x, y) is on the northern boundary.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @return True if the point is on the northern boundary, false otherwise.
     */
    bool onNorthernBoundary(int x, int y) const;

    /**
     * @brief Check whether point (x, y) is on the western boundary.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @return True if the point is on the western boundary, false otherwise.
     */
    bool onWesternBoundary(int x, int y) const;

    /**
     * @brief Check whether point (x, y) is on the exterior vacuum.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @return True if the point is on the exterior vacuum, false otherwise.
     */
    bool onExteriorVacuum(int x, int y) const;

    /**
     * @brief Check whether point (x, y) is on the interior vacuum.
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @return True if the point is on the interior vacuum, false otherwise.
     */
    bool onInteriorVacuum(int x, int y) const;

    /**
     * @brief Return index of the hole containing point (x, y).
     * @param x The x coordinate.
     * @param y The y coordinate.
     * @return The index of the hole containing point (x, y). -1 if the point is not in any hole.
     */
    int inHole(int x, int y) const;

private:
    int _width;
    int _height;

    /**
     * @brief The geometry of the superconductor. (0=vacuum, 1=superconductor)
     */
    Mask _geometry;

    /**
     * @brief The physical southern boundary. Parts to the south of this boundary are considered to be in the vacuum.
     */
    Mask _southernBoundary;

    /**
     * @brief The physical eastern boundary. Parts to the east of this boundary are considered to be in the vacuum.
     */
    Mask _easternBoundary;

    /**
     * @brief The physical northern boundary. Parts to the north of this boundary are considered to be in the vacuum.
     */
    Mask _northernBoundary;

    /**
     * @brief The physical western boundary. Parts to the west of this boundary are considered to be in the vacuum.
     */
    Mask _westernBoundary;

    /**
     * @brief The physical exterior vacuum, not enclosed by any pieces of superconductor.
     */
    Mask _exteriorVacuum;

    /**
     * @brief The physical interior vacuum, enclosed by pieces of superconductor.
     */
    Mask _interiorVacuum;

    /**
     * @brief A list of masks, each representing the holes inside the superconductor.
     */
    maskList _holes;

    /**
     * @brief Update all boundaries.
     */
    void _updateBoundaries();

    /**
     * @brief Update exterior vacuum.
     */
    void _updateExteriorVacuum();

    /**
     * @brief Update interior vacuum.
     */
    void _updateInteriorVacuum();
};

#endif //CPP_CONSTRICTION_SQUID_GEOMETRY_H
