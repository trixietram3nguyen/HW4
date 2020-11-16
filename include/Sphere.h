#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"

namespace Raytracer148 {
class Sphere : public Shape {
public:
    Sphere(Eigen::Vector3d &center, double radius, Eigen::Vector3d sphereColor) : c(center), r(radius), sphereColor(sphereColor) {}

    virtual HitRecord intersect(const Ray &ray);

private:
    Eigen::Vector3d c;
    double r;
    Eigen::Vector3d sphereColor;
};
}

#endif
