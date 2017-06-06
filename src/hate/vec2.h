#pragma once
#include <exception>
#include <math.h>

#define _VEC2_
namespace hate {
	class Vec2{
		public:
			// Constructs a new vector.
			Vec2(float x=0, float y=0);

			// Cleanup.
			virtual ~Vec2() {}

			/**
			 * Sums up two vectors and stores the result in this.
			 *
			 * @param other the other vector.
			 */
			Vec2 operator+ (Vec2 other) {
				x += other.x;
				y += other.y;
				return *this;
			}

			/**
			 * Subtracts the two vectors and stores the result in this.
			 *
			 * @param other the other vector.
			 */
			Vec2 operator- (Vec2 other) {
				x -= other.x;
				y -= other.y;
				return *this;
			}

			/**
			 * Negates this vector and returns a copy.
			 */
			Vec2 operator- () {
				return Vec2(-x, -y);
			}

			/**
			 * Scales the vector.
			 *
			 * @param scale the new scale.
			 */
			Vec2 operator* (float scale) {
				x *= scale;
				y *= scale;
				return *this;
			}

			/**
			 * Returns the length of the vector squared.
			 *
			 * @return the length squared.
			 */
			float getLengthSq() {
				return x * x + y * y;
			}

			/**
			 * Returns the length of the vector.
			 *
			 * @return the length of the vector.
			 */
			float getLength() {
				return sqrt(getLengthSq());
			}

			/**
			 * Dots the two vectors and returns the scale.
			 * 
			 * @param other the other vector.
			 * @return the dot product.
			 */
			float dot(Vec2 other) {
				return x * other.x + y * other.y;
			}

			/**
			 * A fake cross product that has some wierd properties when
			 * it comes to 2D linear algebra.
			 *
			 * @param the other vector.
			 * @return the "cross" product of the two vectors.
			 */
			float cross(Vec2 other) {
				return x * other.y - other.x * y;
			}

			/**
			 * Rotates the vector that many radians.
			 *
			 * @param angle the angle to rotate by.
			 */
			Vec2 rotate(float angle) {
				float t;
				t = x * cos(angle) - y * sin(angle);
				y = x * sin(angle) + y * cos(angle);
				x = t;
				return *this;
			}

			/**
			 * Flips the sign of all elemnts in the vector.
			 */
			void negate() {
				x *= -1;
				y *= -1;
				return *this;
			}

			/**
			 * Normalizes the vector.
			 */
			void normalize() {
				scale(1.0f / getLength());
			}

			/**
			 * Clones the vector for safe access.
			 */
			Vec2 clone() {
				return Vec2(x, y);
			}

			/**
			 * Treats the vector as a list to make access easier.
			 */
			float operator[] (int i) {
				switch(i) {
					case 0:
						return x;
					case 1:
						return y;
					default:
						throw std::runtime_error("Index out of bounds\n");
				}
				return 0;
			}

		protected:
			// The x and y coordinates of the vector.
			float x, y;
	}
}
