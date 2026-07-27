#include "rtweekend.hh"

#include "Camera.hh"
#include "Hittable.hh"
#include "HittableList.hh"
#include "Material.hh"
#include "Sphere.hh"

int main() {
    // World
    HittableList world;

    auto material_ground = make_shared<lambertian>(Color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(Color(0.1, 0.2, 0.5));
    auto material_left   = make_shared<dielectric>(1.00 / 1.33);
    auto material_right  = make_shared<metal>(Color(0.8, 0.6, 0.2), 1.0);

    world.add(make_shared<Sphere>(Point3( 0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<Sphere>(Point3( 0.0,    0.0, -1.2),   0.5, material_center));
    world.add(make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.5, material_left));
    world.add(make_shared<Sphere>(Point3( 1.0,    0.0, -1.0),   0.5, material_right));

    Camera cam;

    cam.aspect_ratio = 16. / 9.;
    cam.imageWidth = 512;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.render(world);

}