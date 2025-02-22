#include "Matrix4.h"
#include "Vector4.h"
#include <cmath>
#include <iostream>
#include <stdexcept>
#define PI 3.14159265359

// Constructor: Initializes to identity matrix
Matrix4::Matrix4() {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            m[i][j] = (i == j) ? 1.0 : 0.0;
}



//construction from vectors
Matrix4::Matrix4(Vector4& a, Vector4& b, Vector4& c, Vector4& d)
{
    m[0][0] = a.x;
    m[0][1] = a.y;
    m[0][2] = a.z;
    m[0][3] = a.w;

    m[1][0] = b.x;
    m[1][1] = b.y;
    m[1][2] = b.z;
    m[1][3] = b.w;

    m[2][0] = c.x;
    m[2][1] = c.y;
    m[2][2] = c.z;
    m[2][3] = c.w;

    m[3][0] = d.x;
    m[3][1] = d.y;
    m[3][2] = d.z;
    m[3][3] = d.w;
}


// Matrix multiplication
Matrix4 Matrix4::operator*(const Matrix4& other) const {
    Matrix4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = 0;
            for (int k = 0; k < 4; ++k) {
                result.m[i][j] += m[i][k] * other.m[k][j];
            }
        }
    }
    return result;
}

// Transform a Vector4
Vector4 Matrix4::transform(const Vector4& v) const {
    float newX = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
    float newY = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w;
    float newZ = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w;
    float newW = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;

    // If w is not 1, normalize the result
    if (newW != 1.0 && newW != 0.0) {
        newX /= newW;
        newY /= newW;
        newZ /= newW;
        newW = 1.0; // Normalize w to 1 for homogeneous coordinates

    }
    else if (newW == 0.0) {
        newW = 1.0;
    // Handle the case where w = 0. Avoid division by zero.
    //throw std::runtime_error("Invalid transformation: w = 0");
    }
    return Vector4(newX, newY, newZ, newW);
}




// Translation matrix
Matrix4 Matrix4::translate(float dx, float dy, float dz) {
    Matrix4 mat;
    mat.m[0][3] = dx;
    mat.m[1][3] = dy;
    mat.m[2][3] = dz;
    return mat;
}

// Scaling matrix
Matrix4 Matrix4::scale(float sx, float sy, float sz) {
    Matrix4 mat;
    mat.m[0][0] = sx;
    mat.m[1][1] = sy;
    mat.m[2][2] = sz;
    mat.m[3][3] = 1.0; // Preserve homogeneous coordinate
    return mat;
}

inline float ToRadians(float degrees) {
    return degrees * (PI / 180.0);
}

// Rotation matrix around X-axis
Matrix4 Matrix4::rotateX(float angle) {
    Matrix4 mat;
    float radians = ToRadians(angle); // Convert degrees to radians
    float cosA = cos(radians), sinA = sin(radians);
    mat.m[1][1] = cosA;
    mat.m[1][2] = -sinA;
    mat.m[2][1] = sinA;
    mat.m[2][2] = cosA;
    return mat;
}

// Rotation matrix around Y-axis
Matrix4 Matrix4::rotateY(float angle) {
    Matrix4 mat;
    float radians = ToRadians(angle); // Convert degrees to radians
    float cosA = cos(radians), sinA = sin(radians);
    mat.m[0][0] = cosA;
    mat.m[0][2] = sinA;
    mat.m[2][0] = -sinA;
    mat.m[2][2] = cosA;
    return mat;
}

// Rotation matrix around Z-axis
Matrix4 Matrix4::rotateZ(float angle) {
    Matrix4 mat;
    float radians = ToRadians(angle); // Convert degrees to radians
    float cosA = cos(radians), sinA = sin(radians);
    mat.m[0][0] = cosA;
    mat.m[0][1] = -sinA;
    mat.m[1][0] = sinA;
    mat.m[1][1] = cosA;
    return mat;
}

// Orthographic projection matrix
Matrix4 Matrix4::orthographic(float left, float right, float bottom, float top, float near, float far) {
    Matrix4 mat;
    mat.m[0][0] = 2.0 / (right - left);
    mat.m[1][1] = 2.0 / (top - bottom);
    mat.m[2][2] = -2.0 / (far - near);
    mat.m[0][3] = -(right + left) / (right - left);
    mat.m[1][3] = -(top + bottom) / (top - bottom);
    mat.m[2][3] = -(far + near) / (far - near);
    return mat;
}



Matrix4 Matrix4::withoutTranslation() const {
    Matrix4 result = *this; // Start with a copy of the current matrix

    // Zero out the translation components in the 4th column
    result.m[0][3] = 0.0;
    result.m[1][3] = 0.0;
    result.m[2][3] = 0.0;

    return result;
}

// Perspective projection matrix
Matrix4 Matrix4::PerspectiveMatrix(double fovy, double aspectRatio, double nearPlane, double farPlane,double d) {
    Matrix4 tmp;
    double fovy_rad = tmp.DegsToRad(fovy);
    double half_fovy = tan(fovy_rad / 2.0);
    double f = 1.0 / tan(fovy_rad / 2.0);
    Matrix4 matrix;
    matrix.m[0][0] = 1.0f / (aspectRatio * half_fovy);
    matrix.m[1][1] = f;
    matrix.m[2][2] = (farPlane + nearPlane) / (nearPlane - farPlane);
    matrix.m[2][3] = (2.0 * farPlane * nearPlane) / (nearPlane - farPlane);
    matrix.m[3][2] = -1.0;
    matrix.m[3][3] = d;
    return matrix;
}

// Modify perspective parameter 'd'
void Matrix4::setPerspectiveD(float d) {
    m[3][3] = d;
}


// Print the matrix (for debugging)
void Matrix4::print() const {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << m[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Transpose the matrix
Matrix4 Matrix4::transpose() const {
    Matrix4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = m[j][i];
        }
    }
    return result;
}


Matrix4 Matrix4::inverse() const {
    Eigen::Matrix4f eigenMat;

    // Convert Matrix4 to Eigen::Matrix4f
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            eigenMat(i, j) = m[i][j];
        }
    }

    // Compute the inverse using Eigen
    if (eigenMat.determinant() == 0) {
        throw std::runtime_error("Matrix is singular and cannot be inverted.");
    }

    Eigen::Matrix4f eigenInverse = eigenMat.inverse();

    // Convert Eigen::Matrix4f back to Matrix4
    Matrix4 result;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = eigenInverse(i, j);
        }
    }

    return result;
}
double Matrix4::DegsToRad(double angle)
{
    return angle * (PI / 180);
}

Vector4 Matrix4::MultiplyMatrixVector(const Vector4& vec)
{
    Vector4 result;
    result.x = m[0][0] * vec.x + m[1][0] * vec.y + m[2][0] * vec.z + m[3][0] * vec.w;
    result.y = m[0][1] * vec.x + m[1][1] * vec.y + m[2][1] * vec.z + m[3][1] * vec.w;
    result.z = m[0][2] * vec.x + m[1][2] * vec.y + m[2][2] * vec.z + m[3][2] * vec.w;
    result.w = m[0][3] * vec.x + m[1][3] * vec.y + m[2][3] * vec.z + m[3][3] * vec.w;
    return result;
}