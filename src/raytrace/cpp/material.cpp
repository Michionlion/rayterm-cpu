#include "material.h"

vector reflect(const vector& in, const vector& normal) {
    return vector(in - 2 * in.dot(normal) * normal);
}

bool refract(const vector& in, const vector& normal, scalar ni_div_nt, vector& refracted) {
    vector norm_in = in.normalized();
    scalar dt      = norm_in.dot(normal);
    scalar discrim = 1.0 - ni_div_nt * ni_div_nt * (1 - dt * dt);
    if (discrim > 0) {
        refracted = ni_div_nt * (norm_in - normal * dt) - normal * sqrt(discrim);
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
    vector out_normal;
    vector reflected = reflect(incoming.direction(), hit.normal);
    scalar ni_div_nt;
    attenuation = albedo;
    vector refracted;
    if (incoming.direction().dot(hit.normal) > 0) {
        out_normal = -hit.normal;
        ni_div_nt  = refrac_index;
    } else {
        out_normal = hit.normal;
        ni_div_nt  = 1.0 / refrac_index;
    }

    if (refract(incoming.direction(), out_normal, ni_div_nt, refracted)) {
        outgoing = ray(hit.position, refracted);
    } else {
        outgoing = ray(hit.position, reflected);
        return false;
    }
    return true;
}
