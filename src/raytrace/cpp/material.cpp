#include "material.h"

bool Lambertian::scatter(const ray& incoming, ray& outgoing, const intersection& hit, color& attenuation) {
    vector bounce(hit.position + hit.normal + random_in_usphere());
    outgoing = ray(hit.position, bounce - hit.position);
    attenuation = albedo;
    return true;
}
