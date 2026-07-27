#ifndef HITTABLELIST_HH
#define HITTABLELIST_HH

#include "Hittable.hh"

#include <memory>
#include <vector>

using std::make_shared;
using std::shared_ptr;

class HittableList : public Hittable {
    public:
        std::vector<shared_ptr<Hittable>> objects;

        HittableList() {}
        HittableList(shared_ptr<Hittable> object) { add(object); }

        void clear() { objects.clear(); }

        void add(shared_ptr<Hittable> object) {
            objects.push_back(object);
        }

        bool hit(const Ray& r, Interval ray_t, HitRecord& rec) const override {
            HitRecord tempRec;
            bool hitAnything = false;
            auto closest_so_far = ray_t.max;

            for (const auto& object : objects) {
                if (object->hit(r, Interval(ray_t.min, closest_so_far), tempRec)) {
                    hitAnything = true;
                    closest_so_far = tempRec.t;
                    rec = tempRec;
                }
            }

            return hitAnything;
        }
};

#endif