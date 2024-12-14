#pragma once
#ifndef MATRIX4_H
#define MATRIX4_H

class Vector3; // Forward declaration for use in Matrix4

class Matrix4 {
public:
    double m[4][4]; // 4x4 matrix

    // Constructor
    Matrix4();

    // Matrix multiplication
    Matrix4 operator*(const Matrix4& other) const;

    // Vector transformation
    Vector3 transform(const Vector3& v) const;

    // Static methods for creating transformation matrices
    static Matrix4 translate(double dx, double dy, double dz);
    static Matrix4 scale(double sx, double sy, double sz);
    static Matrix4 rotateX(double angle);
    static Matrix4 rotateY(double angle);
    static Matrix4 rotateZ(double angle);

    // Projection matrices
    static Matrix4 orthographic(double left, double right, double bottom, double top, double near, double far);
    static Matrix4 perspective(double fov, double aspect, double near, double far, double d);

    // Modify perspective parameter 'd'
    void setPerspectiveD(double d);

    // Inverse of the matrix
    Matrix4 inverse() const; // Placeholder for matrix inversion

    // Print the matrix (for debugging)
    void print() const;
};

#endif // MATRIX4_H
