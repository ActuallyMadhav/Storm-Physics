#pragma once
#ifndef CORE_H
#define CORE_H

#include "precision.h"
#include <math.h>

namespace storm{
    
    class Vec3{
        public:
            // 3D vector 
            real x, y, z; 

        private:
            real padding;  // holds padding to ensure 4-word alignment

        public:
            // constructor creates zero vector by default
            Vec3() : x(0), y(0), z(0) {}

            // can also create with set values
            Vec3(const real x, const real y, const real z){
                this->x = x;
                this->y = y;
                this->z = z;
            }

            // flips all values of the vector
            void invert(){
                this->x *= -1;
                this->y *= -1;
                this->z *= -1;
            }

            // get magnitude (distance form zero)
            real magnitude() const{
                return real_sqrt(x*x + y*y + z*z);
            }

            // get squared magnitude
            real squaredMagnitude() const{
                return x*x + y*y + z*z;
            }

            // normalize (unit vector)
            void normalize(){
                real l = this->magnitude();

                if(l > 0){
                    this->x *= (real) 1/l;
                    this->y *= (real) 1/l;
                    this->z *= (real) 1/l;
                }
            }

            // scalar multiplication. changes the vector in place
            void operator *= (const real k){
                this->x *= k;
                this->y *= k;
                this->z *= k;
            }

            // scalar multiplicatoin but returns a new vector scaled to the value
            Vec3 operator * (const real k) const{   // operator overloading -> vec3 * real
                return Vec3(
                    this->x * k,
                    this->y * k,
                    this->z * k
                );
            }

            // vector addition (in place modification)
            void operator += (const Vec3& v){   // operator overloading vec3 += vec3
                this->x += v.x;
                this->y += v.y;
                this->z += v.z;
            }

            // vector addition (returns new vector)
            Vec3 operator + (const Vec3& v) const{  // operator overloading vec3 + vec3
                return Vec3(
                    this->x + v.x,
                    this->y + v.y,
                    this->z + v.z
                );
            }

            // vector subtractoin in place
            void operator -= (const Vec3& v){   // vec3 -= vec3
                this->x -= v.x;
                this->y -= v.y;
                this->z -= v.z;
            }

            // vector subtraction (returns new cector)
            Vec3 operator - (const Vec3& v) const{  // vec3 - vec3
                return Vec3(
                    this->x - v.x,
                    this->y - v.y,
                    this->z - v.z
                );
            }

            // adding a scaled vector (in place)
            void addScaled(const Vec3& v, real k){  // vec3 + k*vec3 , where k is a scalar
                this->x += k * v.x;
                this->y += k * v.y;
                this->z += k * v.z;
            }

            /*
             component product
             if v = (a,b,c) and w = (x,y,z) then
             component product = (ax, by, cz)
            */

            // component product but returns new vector
            Vec3 componentProduct(const Vec3& v) const{
                return Vec3(
                    this->x * v.x,
                    this->y * v.y,
                    this->z * v.z
                );
            }

            // component product but in place
            void componentProductUpdate(const Vec3& v){
                this->x *= v.x;
                this->y *= v.y;
                this->z *= v.z;
            }

            /*
             scalar product is the same as dot product
            */
            real scalarProduct(const Vec3& v) const{
                real ans = this->x*v.x + this->y*v.y + this->z*v.x;
                return ans;
            }

            // overload '*' operator to give dot product of 2 vec3 objects
            real operator * (const Vec3& v) const{  // vec3 * vec3 = dot product of both
                real ans = this->x*v.x + this->y*v.y + this->z*v.x;
                return ans;
            }

            /*
             note: a . b = |a||b|cos(theta)
             theta is the angle b/w a and b
             rearrange the formula to get the angle
            */

            // cross product of 2 vectors
            Vec3 vectorProduct(const Vec3& v) const{
                return Vec3(
                    this->y*v.z - this->z*v.y,
                    this->z*v.x - this->x*v.z,
                    this->x*v.y - this->y*v.x
                );
            }

            // overload '%=' operator to update this vector to be the vector product of its current value and another given vector
            void operator %= (const Vec3 v){
                *this = vectorProduct(v);
            }

            // same concept as above but vec3 % vec3
            Vec3 operator % (const Vec3& v) const{
                return Vec3(
                    this->y*v.z - this->z*v.y,
                    this->z*v.x - this->x*v.z,
                    this->x*v.y - this->y*v.x
                );
            }

            /*
                note:
                |a x b| = |a||b|sin(theta)
                theta = angle b/w a and b
            */
    };
}   // namespace storm

#endif