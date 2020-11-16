#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"

namespace Raytracer148 {
    class Triangle : public Shape {
    public:
        Triangle(Eigen::Vector3d& V1, Eigen::Vector3d& V2, Eigen::Vector3d& V3, Eigen::Vector3d& color) : v1(V1), v2(V2), v3(V3), triangleColor(color) {}

        virtual HitRecord intersect(const Ray& ray);

    private:
        Eigen::Vector3d triangleColor;
        Eigen::Vector3d v1;
        Eigen::Vector3d v2;
        Eigen::Vector3d v3;
        //// Barycentric coordinate of point inside the triangle.
        //    double u;
        //    double v;
        //    double w;
    };


}

#endif

