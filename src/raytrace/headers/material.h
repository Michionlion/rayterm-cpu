#ifndef _RAYTERM_MATERIAL_H_
#define _RAYTERM_MATERIAL_H_

#include "raymath"

class Material {
   public:
    // scatter modifies r as if it was scattered from a hit at intersection
    // If no scattering should be done, false is returned. Otherwise true
    // is returned.
    virtual bool scatter(
        const ray& incoming, ray& outgoing, const intersection& hit, color& attenuation) const = 0;
    virtual ~Material() {}
};

class Lambertian : public Material {
    color albedo;

   public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    Lambertian(const color& albedo) : albedo(albedo){};
    bool scatter(
        const ray& incoming, ray& outgoing, const intersection& hit, color& attenuation) const;
};

class Metal : public Material {
    color albedo;
    scalar roughness;

   public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    Metal(const color& albedo, scalar roughness) : albedo(albedo), roughness(roughness){};
    bool scatter(
        const ray& incoming, ray& outgoing, const intersection& hit, color& attenuation) const;
};

class Dielectric : public Material {
    color albedo;
    scalar refrac_index;

   public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    Dielectric(scalar refrac_index) : albedo(color(1, 1, 1)), refrac_index(refrac_index){};
    bool scatter(
        const ray& incoming, ray& outgoing, const intersection& hit, color& attenuation) const;
};

#endif
