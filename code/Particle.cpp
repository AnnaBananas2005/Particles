#include "Engine.h"
#include <SFML/Graphics.hpp>
#include "Particle-2.h"

using namespace sf;
using namespace std;

//Done by Anna :3

/*
Particle(RenderTarget& target, int numPoints, Vector2i mouseClickPosition)
This constructor will be responsible for generating a randomized shape with numPoints vertices,
centered on mouseClickPosition mapped to the Cartesian plane, which is centered at (0,0) instead of (width / 2, height / 2).
    It will also give the particle initial vertical, horizontal, and angular spin velocities
    Each vertex will be stored in the Matrix member variable m_A as a column vector
        Thus, the coordinates (x1, y1), (x2, y2), (x3, y3), ... will be stored as follows:
The Matrix member variable m_A does not have a default constructor and thus must be constructed
in an initialization list before the code for the constructor begins:
    Particle(...) : m_A(2, numPoints)
Initialize m_ttl with the global constant TTL, which gives it a time to live of 5 seconds
Initialize m_numPoints with numPoints
Initialize m_radiansPerSec to a random angular velocity in the range [0:PI]
    You can generate a random fraction between [0:1) by calling (float)rand() / (RAND_MAX)
    Multiply this fraction by PI (this is a constant for pi, declared in Particle.h
m_cartesianPlane will be used to map between monitor pixel coordinates, that are centered at (960, 540)
for a 1080p monitor, to Cartesian coordinates that are centered about the origin (0,0), so our Matrix
algebra will work correctly
    Call setCenter(0,0)
    Call setSize(target.getSize().x, (-1.0) * target.getSize().y)
        This will initialize its width and height to the size of the RenderWindow stored in target and invert the y-axis
Store the location of the center of this particle on the Cartesian plane in m_centerCoordinate
    Use target.mapPixelToCoordsLinks to an external site. with m_cartesianPlane to map mouseClickPosition to
    the Cartesian plane and store it in m_centerCoordinate
        Don't forget to pass m_cartesianPlane in as an argument!
Assign m_vx and m_vy to random pixel velocities
    These will be the initial horizontal and vertical velocities of our particle
    Somewhere between 100 and 500 worked for me, but you can experiment with this
    If you want m_vx to be randomly positive or negative, use rand() % 2 and
    if it is not equal to zero, then multiply m_vx by -1
Assign m_color1 and m_color2 with Colors
    I made m_color1 white and m_color2 random, but you can experiment here
Now we will generate numPoint vertices by sweeping a circular arc with randomized radii.
Please refer to the picture below to visualize each variable:
Particle vertex generation algorithm

The algorithm is as follows:
    Initialize theta to an angle between [0: PI/ 2]
    Initialize dTheta to 2 * PI / (numPoints - 1);
        This is the amount we will rotate per vertex
        We divide by numPoints - 1 because we want the last vertex to overlap with the first so we don't leave an open edge
    Loop from j up to numPoints
        Declare local variables r, dx, and dy
        Assign a random number between [20:80] to r (you can try a different range here)
        dx = r * cos(theta)
        dy = r * sin(theta)
        Assign the Cartesian coordinate of the newly generated vertex to m_A:
            m_A(0, j) = m_centerCoordinate.x + dx;
            m_A(1, j) = m_centerCoordinate.y + dy;
        Increment theta by dTheta to move it to the next location for the next iteration of the loop
*/
Particle::Particle(RenderTarget& target, int numPoints, Vector2i mouseClickPosition) : m_A(2, numPoints) { //initialize m_A
    m_ttl = TTL;
    m_numPoints = numPoints;
    float randomNumber = static_cast<float>(rand()) / (RAND_MAX);       

    m_radiansPerSec = static_cast<float>(randomNumber * M_PI);

    m_cartesianPlane.setCenter(0, 0);
    m_cartesianPlane.setSize(target.getSize().x, -1.0 * target.getSize().y);           
    m_centerCoordinate = target.mapPixelToCoords(mouseClickPosition, m_cartesianPlane);

    m_vx = rand() % 401 + 100; //Can be between whatever number (100-500)
    m_vy = rand() % 401 + 100;

    m_color1 = Color::White;
    m_color2 = Color(rand() % 256, rand() % 256, rand() % 256);

    float theta = static_cast<float>(rand()) / RAND_MAX * (M_PI / 2);
    float dTheta = 2 * M_PI / (numPoints - 1);
    float r, dx, dy;

    for (int j = 0; j < numPoints; j++) {
        r = static_cast<float>(rand() % 21 + 20); //20-40 (61 + 20) for 20-80
        dx = static_cast<float>(r * cos(theta));            //PROBLEM, fixed to static: dx, dy & r is float, cos(theta)/sin(theta) returns double
        dy = static_cast<float>(r * sin(theta));
        m_A(0, j) = m_centerCoordinate.x + dx;      
        m_A(1, j) = m_centerCoordinate.y + dy;
        theta += dTheta;
    }
}

/*
draw(RenderTarget& target, RenderStates states) const
This function overrides the virtual function from sf::Drawable to allow our draw function to polymorph
To draw, we will convert our Cartesian matrix coordinates from m_A to pixel coordinates in a VertexArray of primitive type TriangleFan
    Take a look at the SFML tutorial regarding the TriangleFanLinks to an external site. and refer to the picture below:
    Triangle fan diagram

Construct a VertexArray named lines
    Its arguments are TriangleFan, and the number of points numPoints + 1
    The + 1 is to account for the center as shown above
Declare a local Vector2f named center
    This will be used to store the location on the monitor of the center of our particle
    Assign it with the mapping of m_centerCoordinate from Cartesian to pixel / monitor coordinates
    using target.mapCoordsToPixelLinks to an external site.
        Don't forget to pass m_cartesianPlane in as an argument!
Assign lines[0].position with center
Assign lines[0].color with m_color
      This will assign m_color to the center of our particle.
      If the outer colors are different, the engine will automatically
      create a cool looking smooth color gradient between the two colors
Loop j from 1 up to and including m_numPoints
    Note that the index in lines is 1-off from the index in m_A because
    lines must contain the pixel coordinate for the center as its first element
    Assign lines[j].position with the coordinate from column j - 1 in m_A, mapped from Cartesian to
    pixel coordinates using target.mapCoordsToPixelLinks to an external site.
        Don't forget to pass m_cartesianPlane in as an argument!
    Assign lines[j].color with m_Color2
When the loop is finished, draw the VertexArray:
    target.draw(lines)
*/

void Particle::draw(RenderTarget& target, RenderStates states) const {
    VertexArray lines(TriangleFan, m_numPoints + 1);
 
    Vector2f center(target.mapCoordsToPixel(m_centerCoordinate, m_cartesianPlane));
    lines[0].position = center;
    lines[0].color = m_color1;

    for (int j = 1; j <= m_numPoints; j++) {
        lines[j].position = static_cast<Vector2f>(target.mapCoordsToPixel(Vector2f(m_A(0, j - 1), m_A(1, j - 1)), m_cartesianPlane)); //static_cast

        lines[j].color = m_color2;
    }
    target.draw(lines, states);
}

/*
update(float dt)
Subtract dt from m_ttl
Note:  the functions rotate, scale, and translate will be defined later
Call rotate with an angle of dt * m_radiansPerSec
Call scale using the global constant SCALE from Particle.h
    SCALE will effectively act as the percentage to scale per frame
    0.999 experimentally seemed to shrink the particle at a nice speed that wasn't too fast or too slow (you can change this)
Next we will calculate how far to shift / translate our particle, using distance (dx,dy)
    Declare local float variables dx and dy
    Assign m_vx * dt to dx
    The vertical velocity should change by some gravitational constant G, also experimentally determined and defined in Particle.h
        This will allow the particle to travel up then fall down as if having an
        initial upward velocity and then getting pulled down by gravity
    Subtract G * dt from m_vy
    Assign m_vy * dt to dy
    Call translate using dx,dy as arguments
*/

void Particle::update(float dt) {
    m_ttl -= dt;
    rotate(dt * m_radiansPerSec);
    scale(SCALE);

    float dx, dy;
    dx = m_vx * dt;
    m_vy -= G * dt;
    dy = m_vy * dt;

    translate(dx, dy);
}

/*
translate(double xShift, double yShift)
Construct a TranslationMatrix T with the specified shift values xShift and yShift
Add it to m_A as m_A = T + m_A
Update the particle's center coordinate:
    m_centerCoordinate.x += xShift;
    m_centerCoordinate.y += yShift;
 */

void Particle::translate(double xShift, double yShift) {
    TranslationMatrix T(xShift, yShift, m_A.getCols());
    m_A = m_A + T;
    m_centerCoordinate.x += static_cast<float>(xShift);
    m_centerCoordinate.y += static_cast<float>(yShift);
}

/*
rotate(double theta)
Since the rotation matrix we will use is algebraically derived to rotate coordinates about the origin,
we will temporarily shift our particle to the origin before rotating it
    Store the value of m_centerCoordinate in a Vector2f temp
    Call translate(-m_centerCoordinate.x, -m_centerCoordinate.y);
        This will shift our particle's center, wherever it is, back to the origin
Construct a RotationMatrix R with the specified angle of rotation theta
Multiply it by m_A as m_A = R * m_A
      Note: make sure to left-multiply R, as matrix multiplication is not commutative due to the fact that
      it multiplies the lvalue's rows into the rvalue's columns.
Shift our particle back to its original center:
    translate(temp.x, temp.y);
*/

void Particle::rotate(double theta) {
    Vector2f temp = m_centerCoordinate;
    translate(-temp.x, -temp.y);            
    RotationMatrix R(theta);
    m_A = R * m_A;
    translate(temp.x, temp.y);
}

/*
scale(double c)
Scaling is also derived to scale coordinates relative to their distance from the origin.
So we will also have to temporarily shift back to the origin here before scaling:
    Store the value of m_centerCoordinate in a Vector2f temp
    Call translate(-m_centerCoordinate.x, -m_centerCoordinate.y);
        This will shift our particle's center, wherever it is, back to the origin
Construct a ScalingMatrix S with the specified scaling multiplier c
Multiply it by m_A as m_A = S * m_A
Shift our particle back to its original center:
    translate(temp.x, temp.y);

*/

void Particle::scale(double c) {
    Vector2f temp = m_centerCoordinate;
    translate(-temp.x, -temp.y);
    ScalingMatrix S(c);
    m_A = S * m_A;
    translate(temp.x, temp.y);
}
