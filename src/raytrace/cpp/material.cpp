#include "material.h"
#include <cmath>

vector reflect(const vector& in, const vector& normal) {
    return vector(in - 2 * in.dot(normal) * normal);
}

// refract generates a refraction vector, using in as the normalized incoming direction,
// surface_normal as the normal (away from surface, towards air), cos as the dot product of the
// surface normal and incoming ray, and ior as the refractive index. The generated ray is stored in
// refracted. If the vector cannot be refracted, false is returned.
//
// This function also modifies cos to be the correct positive cosine, if needed.
bool refract(
    const vector& in, const vector& surface_normal, scalar& cos, scalar ior, vector& refracted) {
    scalar from_ior = 1;
    vector normal;

    // handle coming from inside vs outside
    if (cos < 0) {
        // hitting the object from the outside (air to object)
        cos    = -cos;
        normal = surface_normal;
    } else {
        // hitting the object from the inside (object to air)
        from_ior = ior;
        ior      = 1;
        normal   = -surface_normal;
    }
    scalar from_over_to_ior = from_ior / ior;
    scalar discrim          = 1 - from_over_to_ior * from_over_to_ior * (1 - cos * cos);
    if (discrim > 0) {
        refracted = (from_over_to_ior * in) + (from_over_to_ior * cos - sqrt(discrim)) * normal;
        // multiple sources differ on the correct implementation. The above uses the second option
        // here, which is from Scratchapixel. The first is from Ray-Tracing in a Weekend.
        // refracted = from_over_to_ior * (in - normal * cos) - normal * sqrt(discrim);
        // refracted = from_over_to_ior * (in + normal * cos) - normal * sqrt(discrim);
        return true;
    }
    return false;
}

scalar schlick(scalar cos, scalar refrac_index) {
    scalar r0 = (1 - refrac_index) / (1 + refrac_index);
    r0 *= r0;
    return r0 + (1 - r0) * pow((1 - cos), 5);
}

bool Lambertian::scatter(
    const ray& incoming, ray& outgoing, const intersection& hit, color& attenuation) const {
    vector bounce(hit.position + hit.normal + random_in_usphere());
    outgoing    = ray(hit.position, bounce - hit.position);
    attenuation = albedo;
    return true;
}

bool Metal::scatter(
    const ray& incoming, ray& outgoing, const intersection& hit, color& attenuation) const {
    vector reflected = reflect(incoming.direction(), hit.normal);
    outgoing         = ray(hit.position, reflected + roughness * random_in_usphere());
    attenuation      = albedo;
    return reflected.dot(hit.normal) > 0;
}

bool Dielectric::scatter(
    const ray& incoming, ray& outgoing, const intersection& hit, color& attenuation) const {
    attenuation = color(1, 1, 1);  // does not currently support attenuation
    vector refracted;
    scalar reflect_probability;
    scalar cos = incoming.direction().dot(hit.normal);

    if (refract(incoming.direction(), hit.normal, cos, refrac_index, refracted)) {
        reflect_probability = schlick(cos, refrac_index);
    } else {
        outgoing = ray(hit.position, reflect(incoming.direction(), hit.normal));
        return true;
    }

    if (random_scalar() < reflect_probability) {
        outgoing = ray(hit.position, reflect(incoming.direction(), hit.normal));
    } else {
        outgoing = ray(hit.position, refracted);
    }

    return true;
}
