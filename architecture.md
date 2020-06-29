# Ray Tracing

## Surface Interaction

### Reflection
- Light bounces off a surface

#### Perfect Specular 
- Perfect surface for perfect reflection/refraction

#### Perfect Difuse
- Rough surface, light scattered everywhere
- Lambertian reflection (matte surface)
- Amplitude of reflected light dependent on angle of incident

### Transmission
- Light passes through objects surface

#### Perfect Specular
- Direction of transmitted ray found with Snell's law

#### Perfect Diffuse
- Many small particles in material, allows light to pass and colours it but you cannot see beyond the material
- Amplitude of refracted light dependent on angle of incident

### Color
- Can be represented by RGB or a variety of wavelength/energy values
- For reflection: Multiply incoming spectrum by appropriate surface spectrum for result

### Faster solution (Hall Model)
- Diffusely reflected and refracted light from other bodies is removed with an "ambient" light spectrum 
- Equations are simplified

### Realistic solutions
- All is accumulated through light sources and others bodies
- Diffuse Reflection
    - Loop over all light sources visible and accumulate diffuse light due to each one with equation
- Specular Reflection
    - 

# Acceleration
- Make a BVH

# Basic Algorithm
raytrace(ray):
    for object in objects:
        if intersect_dist < min_dist:
            min_dist := intersect_dist
            min_obj := object
        
    if min_dist != inf:
        return spectrum(refract_ray, reflect_ray, diffuse_func)

for ray in rays:
    pixel := to_rgb(raytrace(ray))