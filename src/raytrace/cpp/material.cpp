#include "material.h"

vector reflect(const vector& in, const vector& normal) {
    return vector(in - 2 * in.dot(normal) * normal);
}

vector refract(const vector& in, const vector& normal) {
    return vector(0, 0, 0);
}

bool Lambertian::scatter(const ray& incoming, ray& outgoing, const intersection& hit, color& attenuation) const {
    vector bounce(hit.position + hit.normal + random_in_usphere());
    outgoing = ray(hit.position, bounce - hit.position);
    attenuation = albedo;
    return true;
}

bool Metal::scatter(const ray& incoming, ray& outgoing, const intersection& hit, color& attenuation) const {
    vector reflected = reflect(incoming.direction(), hit.normal);
    outgoing = ray(hit.position, reflected + roughness*random_in_usphere());
    attenuation = albedo;
    return reflected.dot(hit.normal) > 0;
}

bool Dielectric::scatter(const ray& incoming, ray& outgoing, const intersection& hit, color& attenuation) const {
    return false;
}
