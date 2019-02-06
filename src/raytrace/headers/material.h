#ifndef _RAYTERM_MATERIAL_H_
#define _RAYTERM_MATERIAL_H_

class Material {
   public:
    // scatter modifies r as if it was scattered from a hit at intersection
    // If no scattering should be done, false is returned. Otherwise true
    // is returned.
    virtual bool scatter(const ray& incoming, ray& outgoing, const intersection& hit, color& attenuation) = 0;
}

class Lambertian : public Material {
    color albedo;
   public:
    Lambertian(color albedo) : albedo(albedo){};
    bool scatter(const ray& incoming, ray& outgoing, const intersection& hit, color& attenuation);
}

#endif
