#include <iostream>
#include <memory>

#include "../../inc/storm/core.h"
#include "../../inc/storm/particle.h"

using namespace storm;

int main(){
    std::unique_ptr<Particle> object1 = std::make_unique<Particle>();
    object1->setAcceleration({0, 0, 0});
    object1->setPosition({0,0,0});
    object1->setVelocity({1,0,0});
    object1->setMass(10);
    real duration = 10.0;
    Vec3 startingPos = object1->getPosition();

    std::cout << "object starting position: " << "(" << startingPos.x << ", " << startingPos.y << ", " << startingPos.z << ")" << '\n';

    real x_velocity_scaled = 0.1 * object1->getVelocity().x;    // step size is 0.1s, velocity is 1 m/s
    for(real step = 0.1; step < duration; step += 0.1){
        Vec3 newPos = object1->getPosition() + (Vec3){x_velocity_scaled, 0, 0};
        object1->setPosition(newPos);

        std::cout << "object updated position: " << "(" << newPos.x << ", " << newPos.y << ", " << newPos.z << ")" << '\n';
    }

    return 0;
}