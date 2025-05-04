#include "Particle.h"


bool Particle::almostEqual(double a, double b, double eps)
{
	return fabs(a - b) < eps;
}

void Particle::unitTests()
{
    int score = 0;

    cout << "Testing RotationMatrix constructor...";
    double theta = M_PI / 4.0;
    RotationMatrix r(M_PI / 4);
    if (r.getRows() == 2 && r.getCols() == 2 && almostEqual(r(0, 0), cos(theta))
        && almostEqual(r(0, 1), -sin(theta))
        && almostEqual(r(1, 0), sin(theta))
        && almostEqual(r(1, 1), cos(theta)))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Testing ScalingMatrix constructor...";
    ScalingMatrix s(1.5);
    if (s.getRows() == 2 && s.getCols() == 2
        && almostEqual(s(0, 0), 1.5)
        && almostEqual(s(0, 1), 0)
        && almostEqual(s(1, 0), 0)
        && almostEqual(s(1, 1), 1.5))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Testing TranslationMatrix constructor...";
    TranslationMatrix t(5, -5, 3);
    if (t.getRows() == 2 && t.getCols() == 3
        && almostEqual(t(0, 0), 5)
        && almostEqual(t(1, 0), -5)
        && almostEqual(t(0, 1), 5)
        && almostEqual(t(1, 1), -5)
        && almostEqual(t(0, 2), 5)
        && almostEqual(t(1, 2), -5))
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    
    cout << "Testing Particles..." << endl;
    cout << "Testing Particle mapping to Cartesian origin..." << endl;
    if (m_centerCoordinate.x != 0 || m_centerCoordinate.y != 0)
    {
        cout << "Failed.  Expected (0,0).  Received: (" << m_centerCoordinate.x << "," << m_centerCoordinate.y << ")" << endl;
    }
    else
    {
        cout << "Passed.  +1" << endl;
        score++;
    }

    cout << "Applying one rotation of 90 degrees about the origin..." << endl;
    Matrix initialCoords = m_A;
    rotate(M_PI / 2.0);
    bool rotationPassed = true;
    for (int j = 0; j < initialCoords.getCols(); j++)
    {
        if (!almostEqual(m_A(0, j), -initialCoords(1, j)) || !almostEqual(m_A(1, j), initialCoords(0, j)))
        {
            cout << "Failed mapping: ";
            cout << "(" << initialCoords(0, j) << ", " << initialCoords(1, j) << ") ==> (" << m_A(0, j) << ", " << m_A(1, j) << ")" << endl;
            rotationPassed = false;
        }
    }
    if (rotationPassed)
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Applying a scale of 0.5..." << endl;
    initialCoords = m_A;
    scale(0.5);
    bool scalePassed = true;
    for (int j = 0; j < initialCoords.getCols(); j++)
    {
        if (!almostEqual(m_A(0, j), 0.5 * initialCoords(0,j)) || !almostEqual(m_A(1, j), 0.5 * initialCoords(1, j)))
        {
            cout << "Failed mapping: ";
            cout << "(" << initialCoords(0, j) << ", " << initialCoords(1, j) << ") ==> (" << m_A(0, j) << ", " << m_A(1, j) << ")" << endl;
            scalePassed = false;
        }
    }
    if (scalePassed)
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Applying a translation of (10, 5)..." << endl;
    initialCoords = m_A;
    translate(10, 5);
    bool translatePassed = true;
    for (int j = 0; j < initialCoords.getCols(); j++)
    {
        if (!almostEqual(m_A(0, j), 10 + initialCoords(0, j)) || !almostEqual(m_A(1, j), 5 + initialCoords(1, j)))
        {
            cout << "Failed mapping: ";
            cout << "(" << initialCoords(0, j) << ", " << initialCoords(1, j) << ") ==> (" << m_A(0, j) << ", " << m_A(1, j) << ")" << endl;
            translatePassed = false;
        }
    }
    if (translatePassed)
    {
        cout << "Passed.  +1" << endl;
        score++;
    }
    else
    {
        cout << "Failed." << endl;
    }

    cout << "Score: " << score << " / 7" << endl;
}