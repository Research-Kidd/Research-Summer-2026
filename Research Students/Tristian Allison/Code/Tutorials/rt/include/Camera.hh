#ifndef CAMERA_H
#define CAMERA_H

#include "Hittable.hh"
#include "Material.hh"

class Camera {
    public:
        double aspect_ratio = 1.;
        int imageWidth = 100;
        int samples_per_pixel = 10;
        int max_depth = 10;
        
        void render(const Hittable& world) {
            initialize();

            std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

            for (int j = 0; j < imageHeight; j++) {
                std::clog << "\rScanlines remaining: " << (imageHeight - j) << ' ' << std::flush;
                for (int i = 0; i < imageWidth; i++) {
                    Color pixel_color(0, 0, 0);
                    for (int sample = 0; sample < samples_per_pixel; sample++){
                        Ray r = get_ray(i, j);
                        pixel_color += ray_color(r, max_depth, world);
                    }
                    write_color(std::cout, pixel_samples_scale * pixel_color);
                }
            }

            std::clog << "\rDone.               \n";
        }

    private:
        int imageHeight;
        double pixel_samples_scale;
        Point3 center;
        Point3 pixel00_loc;
        Vec3 pixel_du;
        Vec3 pixel_dv;

        void initialize() {
            // calculate heigh of image and ensure its of height at least 1
            imageHeight = int(imageWidth / aspect_ratio);
            imageHeight = (imageHeight < 1) ? 1 : imageHeight;

            pixel_samples_scale = 1.0 / samples_per_pixel;

            center = Point3(0,0,0);

            // Viewport widths less than one are ok since they are real valued.
            auto focalLength = 1.0;
            auto viewportHeight = 2.0;
            auto viewportWidth = viewportHeight * (double(imageWidth)/imageHeight);

            // Calculate vectors acrooss horizontal and vertical viewport edges
            auto viewport_u = Vec3(viewportWidth, 0, 0);
            auto viewport_v = Vec3(0, -viewportHeight, 0);

            // calculate du and dv from pixel to pixel
            pixel_du = viewport_u / imageWidth;
            pixel_dv = viewport_v / imageHeight;

            // Calculate the location of the upper left pixel
            auto viewport_upper_left = center - Vec3(0,0,focalLength) - viewport_u/2 - viewport_v/2;
            pixel00_loc = viewport_upper_left + 0.5 * (pixel_du + pixel_dv);
        }

        Ray get_ray(int i, int j) const {
            auto offset = sample_square();
            auto pixel_sample = pixel00_loc + ((i + offset[0]) * pixel_du) + ((j + offset[1]) * pixel_dv);

            auto ray_origin = center;
            auto ray_direction = pixel_sample - ray_origin;

            return Ray(ray_origin, ray_direction);
        }
        
        Vec3 sample_square() const {
            // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
            return Vec3(random_double() - 0.5, random_double() - 0.5, 0);
        }

        Color ray_color(const Ray& r, int depth, const Hittable& world) const {
            if (depth <= 0)
                return Color(0,0,0);
            
            HitRecord rec;

            if (world.hit(r, Interval(0.001, infinity), rec)) {
                Ray scattered;
                Color attenuation;
                
                if (rec.mat->scatter(r,rec,attenuation,scattered))
                    return attenuation*ray_color(scattered, depth-1, world);

                return Color(0,0,0);
            }

            Vec3 unitDirection = unit_vector(r.direction());
            auto a = 0.5*(unitDirection[1] + 1.0);
            return (1.0 - a) * Color(1., 1., 1.) + a * Color(0.5, 0.7, 1.0);
        }
};

#endif