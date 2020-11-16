#include <iostream>
#include "Image.h"
#include "Scene.h"
#include "Sphere.h"
#include "Triangle.h"
using namespace std;
using namespace Raytracer148;
using namespace Eigen;

int main() {
    Image im(400, 400);

    Scene scene;

    Vector3d center;

    Vector3d sphereColor = { 0.8, 0.4, 0.1 };

    center[0] = 0;
    center[1] = 0;
    center[2] = 4;
    
    scene.addShape(new Sphere(center, 2, sphereColor));

    sphereColor = { 0.2, 0.4, 0.8 };

    center[0] = -.5;
    center[1] = 1;
    center[2] = 2.5;
    scene.addShape(new Sphere(center, .5, sphereColor));

    center[0] = .5;
    center[1] = 1.25;
    center[2] = 2.75;
    scene.addShape(new Sphere(center, .5, sphereColor));

    // Add new Triangle
    Vector3d v1;
    Vector3d v2;
    Vector3d v3;
    Vector3d triangleColor = { 0.3, 1, 0 }; 

    v1[0] = -6;
    v1[1] = -4;
    v1[2] = 4;

    v2[0] = 0;
    v2[1] = 3;
    v2[2] = 4;

    v3[0] = 8;
    v3[1] = -6;
    v3[2] = 8;

    /*v1[0] = -0.5;
    v1[1] = 0;
    v1[2] = 0.5;

    v2[0] = 0.5;
    v2[1] = -1;
    v2[2] = 1.5;

    v3[0] = 0;
    v3[1] = 0.5;
    v3[2] = 1.8;*/

    scene.addShape(new Triangle(v1, v2, v3, triangleColor));

    scene.render(im);

    im.writePNG("test.png");

    return 0;
}
