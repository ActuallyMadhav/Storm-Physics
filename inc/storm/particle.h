#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H

#include "core.h"

namespace storm{
    class Particle{
        protected:
            // 3d position of the particle in the simulated world
            Vec3 position;

            // velocity (speed w direction(x/y/z)) of the particle
            Vec3 velocity;

            // acceleration of the particle
            Vec3 acceleration;

            // accumulated force -> used only in integration
            Vec3 accumForce;

            /*
             laws of motion:
             1. an object in motion stays in motion unless acted upon by an external force
             2. force acting on an object produces acceleration that is proportional to the object's mass (F = ma)
            */

            real damping; 
            /*
             - damping holds the amount of damping applied to linear motion
             - it is required to remove energy added by numerical instability in the numerator
            */

            //mass
            real mass;

            // inverse mass
            real inverseMass;
            /*
             - inverse mass is more usefule for integration
             - it is VERY IMPORTANT to REMEMBER that i am using INVERSE mass
            */

            // gravity -> g = {0, -g, 0} as gravity only acts in y direction on a plane
            
        public:

            // setters
            void setPosition(const Vec3& position);
            void setVelocity(const Vec3& velocity);
            void setAcceleration(const Vec3& acceleration);
            void setDamping(const real damping);
            void setMass(const real mass);
            void setInverseMass(const real mass);

            // getters
            Vec3 getPosition() const;
            Vec3 getVelocity() const;
            Vec3 getAcceleration() const;
            real getDamping() const;
            real getMass() const;
            real getInverseMass() const;

            /*
             - integrate a particle forward in time by 'duration'
             - uses euler method (may be innaccurate) -> i want to switch to RK4 method later
            */
            void integrate(real duration);

    };

}   // namespace storm

#endif