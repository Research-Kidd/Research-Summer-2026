#ifndef MATERIAL_HH
#define MATERIAL_HH

#include "Hittable.hh"

class Material
{
    public:
        virtual ~Material() = default;

        virtual bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const {
            return false;
        }
};

class lambertian : public Material {
    public:
        lambertian(const Color& albedo) : albedo(albedo) {}

        bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override {
            auto scatterDirection = rec.normal + random_unit_vector();

            if (scatterDirection.near_zero())
                scatterDirection = rec.normal;

            scattered = Ray(rec.p, scatterDirection);
            attenuation = albedo;
            return true;
        }

    private:
        Color albedo;
};

class metal : public Material {
    public:
        metal(const Color& albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

        bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override {
            Vec3 reflected = reflect(r_in.direction(), rec.normal);
            reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
            scattered = Ray(rec.p, reflected);
            attenuation = albedo;
            
            return (dot(scattered.direction(), rec.normal) > 0);
        }

    private:
        Color albedo;
        double fuzz;
};

class dielectric : public Material {
    public:
        dielectric(double refraction_index) : refraction_index(refraction_index) {}

        bool scatter(const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered) const override {
            attenuation = Color(1.0, 1.0, 1.0);
            double ri = rec.frontFace ? (1.0/refraction_index) : refraction_index;

            Vec3 unit_direction = unit_vector(r_in.direction());
            double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
            double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);

            bool cannot_refract = ri*sin_theta > 1.0;
            Vec3 direction;

            if (cannot_refract)
                direction = reflect(unit_direction,rec.normal);
            else
                direction = refract(unit_direction,rec.normal, ri);

            scattered = Ray(rec.p, direction);
            return true;
        }

    private:
        double refraction_index;
};

#endif