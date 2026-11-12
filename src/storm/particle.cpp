#include <assert.h>
#include "../../inc/storm/particle.h"

using namespace storm;

// setters
void Particle::setPosition(const Vec3& position){
    this->position = position;
}

void Particle::setVelocity(const Vec3& velocity){
    this->velocity = velocity;
}

void Particle::setAcceleration(const Vec3& acceleration){
    this->acceleration = acceleration;
}

void Particle::setDamping(const real damping){
    this->damping = damping;
}

void Particle::setMass(const real mass){
    assert(mass > 0.0);
    this->mass = mass;
}

void Particle::setInverseMass(const real mass){
    assert(mass > 0.0);
    this->inverseMass = 1 / mass;
}

// getters
Vec3 Particle::getPosition() const{
    return this->position;
}

Vec3 Particle::getVelocity() const{
    return this->velocity;
}

Vec3 Particle::getAcceleration() const{
    return this->acceleration;
}

real Particle::getDamping() const{
    return this->damping;
}

real Particle::getMass() const{
    return this->mass;
}

real Particle::getInverseMass() const{
    return this->inverseMass;
}

void Particle::integrate(real duration){
    assert(duration > 0.0);

    //update linear pos
    this->position.addScaled(velocity, duration);

    // calculate acceleration from force
    Vec3 resultantAcc = acceleration;
    resultantAcc.addScaled(accumForce, duration);

    //update velocity from acceleration
    this->velocity.addScaled(resultantAcc, duration);

    // drag/friction
    this->velocity *= real_pow(damping, duration);
}