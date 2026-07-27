#ifndef HITTABLE_HH
#define HITTABLE_HH

#include "rtweekend.hh"

class Material;

class HitRecord {
    public:
        Point3 p;
        Vec3 normal;
        shared_ptr<Material> mat;
        double t;
        bool frontFace;

        void set_face_normal(const Ray& r, const Vec3& outwardNormal) {
            // Sets the hit record normal vector
            // NOTE: the parameter 'outward normal' is assumed to have unit length

            frontFace = dot(r.direction(), outwardNormal) < 0;
            normal = frontFace ? outwardNormal : -outwardNormal;
        }
};

class Hittable {
    public:
        virtual ~Hittable() = default;

        virtual bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const = 0;
};

#endif