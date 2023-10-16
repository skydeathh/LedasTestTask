#include <iostream>
#include <cmath>

#define EPSILON 0.00000000001

class Vector3D
{
public:
    double X;
    double Y;
    double Z;

    Vector3D() 
    { 
        X = 0;
        Y = 0;
        Z = 0;
    }

    Vector3D(double x, double y, double z)
    {
        X = x;
        Y = y;
        Z = z;
    }

    Vector3D operator-(const Vector3D& other) const
    {
        return Vector3D(X - other.X, Y - other.Y, Z - other.Z);
    }

    static Vector3D CrossProduct(const Vector3D& v1, const Vector3D& v2)
    {
        double x = v1.Y * v2.Z - v1.Z * v2.Y;
        double y = v1.Z * v2.X - v1.X * v2.Z;
        double z = v1.X * v2.Y - v1.Y * v2.X;
        return Vector3D(x, y, z);
    }

    static double CrossProductLength(const Vector3D& v)
    {
        return std::sqrt(v.X * v.X + v.Y * v.Y + v.Z * v.Z);
    }
};

class Segment3D
{
public:
    Vector3D start;
    Vector3D end;

    Segment3D(const Vector3D& start, const Vector3D& end)
    {
        this->start = start;
        this->end = end;
    }
};

bool isSamePlane(Vector3D& vector) {
    return abs(vector.X) < EPSILON && abs(vector.Y) < EPSILON && abs(vector.Z) < EPSILON;
}

Vector3D* Intersect(const Segment3D& segment1, const Segment3D& segment2)
{
    Vector3D direction1 = segment1.end - segment1.start;
    Vector3D direction2 = segment2.end - segment2.start;

    Vector3D crossProduct1 = Vector3D::CrossProduct(direction2, segment2.start - segment1.start);
    Vector3D crossProduct2 = Vector3D::CrossProduct(direction1, direction2);

    if (isSamePlane(crossProduct2))
    {
        return nullptr;
    }

    double t = Vector3D::CrossProductLength(crossProduct1) / Vector3D::CrossProductLength(crossProduct2);

    if (t < 0 || t > 1) 
    { 
        return nullptr; 
    }

    Vector3D* intersection = new Vector3D(segment1.start.X + direction1.X * t, segment1.start.Y + direction1.Y * t, segment1.start.Z + direction1.Z * t);

    return intersection;
}

void Output(Vector3D* vector) {
    if (vector == NULL) {
        std::cout << "No intersection found." << std::endl;
    }
    else {
        std::cout << "Intersection point: (" << vector->X << ", " << vector->Y << ", " << vector->Z << ")" << std::endl;
    }
}

int main()
{
    Vector3D* intersection1 = Intersect(Segment3D(Vector3D(1, 2, 3), Vector3D(3, 2, 1)), Segment3D(Vector3D(0, 0, 0), Vector3D(12, -5, -7)));
    Vector3D* intersection2 = Intersect(Segment3D(Vector3D(-5, -4, 9), Vector3D(7, 4, -11)), Segment3D(Vector3D(-4, 6, -2), Vector3D(12, -5, -7)));
    
    Output(intersection1);
    Output(intersection2);
    return 0;
}