#include "Triangle.h"
#include <limits>
using namespace Raytracer148;
using namespace Eigen;
using namespace std;

HitRecord Triangle::intersect(const Ray& ray) {
    HitRecord result;
    result.t = -1;

    // Calculating the normal vector for the Plane:
    Eigen::Vector3d v1v2 = v2 - v1;
    Eigen::Vector3d v1v3 = v3 - v1;
    Eigen::Vector3d normalPlaneVector = v1v2.cross(v1v3);

    // We have r(t) = o + td; d is direction (ray direction), o is starting point(ray source);
    // Point on plane: (p-p0).normalVector = 0; p is an arbitrary point on the plane. p0 is the root of normalVector;
    // Solve for t = (p0 - o).normalVector / (d.normalVector);
    // We only interested in t that is 0 <= t < +Infinity (hit condition)

    // Solving for d.normalVector:
    double dnormalVector = normalPlaneVector.dot(ray.direction);
    // if dnormalVector equal zero then they are parallel => no hit

    if (abs(dnormalVector) < numeric_limits<double>::epsilon()) return result;

    // Solving for t = (p0 - o).normalVector/d.normalVector:
    double t = (normalPlaneVector.dot(v1) + normalPlaneVector.dot(ray.origin)) / dnormalVector;

    if (t < 0) return result;

    // Solving for the point that is at the intersection of the ray and the triangle plane:
    Eigen::Vector3d pointRayPlane = ray.origin + t * ray.direction;

    // Testing if the ray hitting the triangle plane is actually inside OR outside the triangle;

    double alpha = (-(pointRayPlane.x() - v3.x()) * (v2.y() - v3.y()) + (pointRayPlane.y() - v3.y()) * (v2.x() - v3.x())) / (-(v1.x() - v3.x()) * (v2.y() - v3.y()) + (v1.y() - v3.y()) * (v2.x() - v3.x()));
    double beta = (-(pointRayPlane.x() - v2.x()) * (v1.y() - v2.y()) + (pointRayPlane.y() - v2.y()) * (v1.x() - v2.x())) / (-(v3.x() - v2.x()) * (v1.y() - v2.y()) + (v3.y() - v2.y()) * (v1.x() - v2.x()));
    double gamma = 1 - alpha - beta;
    if (alpha < 0 || beta < 0 || gamma < 0) return result;

    /* u /= dnormalVector;
     v /= dnormalVector;
     w = 1 - u - v;*/

    result.t = t;
    result.position = pointRayPlane;
    result.normal = (pointRayPlane - v3).normalized();
    result.color = triangleColor;
    return result;
}
