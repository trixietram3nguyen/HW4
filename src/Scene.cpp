#include "Scene.h"
#include <cmath>
#include <cstdlib> 
#include <cstdio>  
#include <fstream> 
#include <vector> 
#include <iostream> 
#include <cassert> 
using namespace Raytracer148;
using namespace std;
using namespace Eigen;

HitRecord Scene::closestHit(const Ray &ray) {
    HitRecord result;
    result.t = -1;
    bool foundSomething = false;

    for (unsigned int i = 0; i < shapes.size(); i++) {
        HitRecord r = shapes[i]->intersect(ray);
        if (r.t > std::numeric_limits<double>::epsilon() && (!foundSomething || r.t < result.t)) {
            result = r;
            foundSomething = true;
        }
    }

    return result;
}

// Returns an RGB color, where R/G/B are each in the range [0,1]
Vector3d Scene::trace(const Ray &ray, int counter) {
    // For now we'll have diffuse shading with no shadows, so it's easy!
    HitRecord r = closestHit(ray);

    Vector3d result;
    result[0] = result[1] = result[2] = 0;

    if (r.t < numeric_limits<double>::epsilon()) return result;

    Vector3d lightColor = { 1,1,1 };

    //The below code is use to get image for problem 1
    /*Vector3d lightDir = (lightPos - r.position).normalized();
    double dot = lightDir.dot(r.normal);
    if (dot < 0) dot = 0;

    result[0] = result[1] = result[2] = dot;*/

    //The below code is use to get image for problem 2
    // ambient strength:
    Vector3d ambientStrength = 0.3 * lightColor;

    // diffuse strength:
    Vector3d lightDir = (lightPos - r.position).normalized();
    Vector3d diffuseStrength = max(lightDir.dot(r.normal), 0.0) * lightColor;

    // specular strength:
    double specularConstant = 0.5;
    Vector3d viewDir = (ray.origin - r.position).normalized();
    // -lightDir is the direction from surface to the light source
    Vector3d reflectDir = -lightDir - 2 * -lightDir.dot(r.normal.normalized()) * r.normal.normalized();
    Vector3d specularStrength = pow(max(viewDir.dot(reflectDir), 0.0), 32) * specularConstant * lightColor;

    // phong model
    Vector3d phongResult = (ambientStrength + diffuseStrength + specularStrength);

    /*Vector3d objectColor = r.color;
    result[0] = phongResult.x() * objectColor[0];
    result[1] = phongResult.y() * objectColor[1];
    result[2] = phongResult.z() * objectColor[2];*/

    //The code below is to get image for problem 3
    // creating shadow;
    //Ray shadowRay;
    //shadowRay.origin = r.position + lightPos;
    //shadowRay.direction = lightDir;
    //// Traverse through shapes and check if the reflectiveRay intersect with something. If it does intersect, there is shadow.
    //for (int i = 0; i < shapes.size(); i++) {
    //    HitRecord r = shapes[i]->intersect(shadowRay);
    //    if (r.t > 0.00001) return result;
    //}

    Vector3d objectColor = r.color;
    result[0] = phongResult.x() * objectColor[0];
    result[1] = phongResult.y() * objectColor[1];
    result[2] = phongResult.z() * objectColor[2];

    //The code below is to get image for problem 4
    //float facingratio = -lightDir.dot(r.normal);
    //mix = 1 * mix + pow(1 - facingratio, 3) * (1 - mix);
    /*float fresneleffect = mix(pow(1 - facingratio, 3), 1, 0.1);
    b* mix + a * (1 - mix);*/
    Ray reflectiveRay;
    reflectiveRay.origin = r.position + r.normal * 0.00001;
    reflectiveRay.direction = lightDir - r.normal * lightDir.dot(r.normal);

    if (counter > 5) {
        return result;
    }
    else {
        counter++;
        return result = result + trace(reflectiveRay, counter);
    }

    return result;
}

Vector3d Scene::traceHelper(const Ray& ray) {
    //float mix = 0.1;
    return trace(ray, 1);
}

//float mix(const float& a, const float& b, const float& mix)
//{
//    return b * mix + a * (1 - mix);
//}

void Scene::render(Image &image) {
    // We make the assumption that the camera is located at (0,0,0)
    // and that the image plane happens in the square from (-1,-1,1)
    // to (1,1,1).

    assert(image.getWidth() == image.getHeight());

    int size = image.getWidth();
    double pixelSize = 2. / size;
    for (int x = 0; x < size; x++)
        for (int y = 0; y < size; y++) {
            Ray curRay;
            curRay.origin[0] = curRay.origin[1] = curRay.origin[2] = 0;

            curRay.direction[0] = (x + 0.5) * pixelSize - 1;
            curRay.direction[1] = 1 - (y + 0.5) * pixelSize;
            curRay.direction[2] = 1;

            Vector3d color = traceHelper(curRay);
            //color = color / pow(4, 2);
            image.setColor(x, y, color[0], color[1], color[2]);
        }
}
