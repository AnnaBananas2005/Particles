#pragma once
#include "Matrices.h"
#include <SFML/Graphics.hpp>

#define M_PI 3.1415926535897932384626433
const float G = 1000;      //Gravity
const float TTL = 5.0;  //Time To Live
const float SCALE = 0.999;

using namespace Matrices;
using namespace sf;
class Particle : public Drawable
{
public:
	Particle(RenderTarget& target, int numPoints, Vector2i mouseClickPosition);
	virtual void draw(RenderTarget& target, RenderStates states) const override;
    void update(float dt);
    float getTTL() { return m_ttl; }

    //Functions for unit testing
    bool almostEqual(double a, double b, double eps = 0.0001);
    void unitTests();

private:
    float m_ttl;
    int m_numPoints;
	Vector2f m_centerCoordinate;
    float m_radiansPerSec;
    float m_vx;
    float m_vy;
    View m_cartesianPlane;
    Color m_color1;
    Color m_color2;
    Matrix m_A;

    ///rotate Particle by theta radians counter-clockwise
    ///construct a RotationMatrix R, left mulitply it to m_A
    void rotate(double theta);

    ///Scale the size of the Particle by factor c
    ///construct a ScalingMatrix S, left multiply it to m_A
    void scale(double c);

    ///shift the Particle by (xShift, yShift) coordinates
    ///construct a TranslationMatrix T, add it to m_A
    void translate(double xShift, double yShift);
};
