#pragma once
#include "Jinclude.h"
#define PI 3.14159

struct vec3d
{
    JFLOAT x, y, z,
        projection = 1.f;
};
struct matrix4x4
{
    JFLOAT mat[4][4] = {0};
};
struct triangle
{
    vec3d p[3];
};
struct mesh
{
    std::vector<triangle> tris;
};

class MeshCube
{
public:
    mesh meshCube;
    matrix4x4 matProjection;

    JFLOAT Theta = 0.f;
    JFLOAT Near = 0.01f;
    JFLOAT Far = 1000.f;
    JFLOAT FOV = 90.f;
    JFLOAT FOVRad = 1.f / tanf(FOV * 0.5f / 180.f * PI);
    JFLOAT AspectRatio;

public:
    void MultiplyMatrixVector(vec3d &in, vec3d &out, matrix4x4 &mat)
    {
        out.x = in.x * mat.mat[0][0] + in.y * mat.mat[1][0] + in.z * mat.mat[2][0] + mat.mat[3][0];
        out.y = in.x * mat.mat[0][1] + in.y * mat.mat[1][1] + in.z * mat.mat[2][1] + mat.mat[3][1];
        out.z = in.x * mat.mat[0][2] + in.y * mat.mat[1][2] + in.z * mat.mat[2][2] + mat.mat[3][2];
        JFLOAT w = in.x * mat.mat[0][3] + in.y * mat.mat[1][3] + in.z * mat.mat[2][3] + mat.mat[3][3];
        if (w != 0.f)
        {
            out.x /= w;
            out.y /= w;
            out.z /= w;
        }
    }

public:
    MeshCube(uint16_t Width, uint16_t Height)
        : AspectRatio((JFLOAT)Height / (JFLOAT)Width)
    {
        meshCube.tris = {
            // SOUTH
            {0.f, 0.f, 0.f, 0.f, 1.f, 0.f, 1.f, 1.f, 0.f},
            {0.f, 0.f, 0.f, 1.f, 1.f, 0.f, 1.f, 0.f, 0.f},
            // EAST
            {1.f, 0.f, 0.f, 1.f, 1.f, 0.f, 1.f, 1.f, 1.f},
            {1.f, 0.f, 0.f, 1.f, 1.f, 1.f, 1.f, 0.f, 1.f},
            // NORTH
            {1.f, 0.f, 1.f, 1.f, 0.f, 0.f, 0.f, 0.f, 1.f},
            {0.f, 0.f, 1.f, 0.f, 1.f, 1.f, 0.f, 0.f, 1.f},
            // WEST
            {0.f, 0.f, 1.f, 0.f, 1.f, 1.f, 0.f, 1.f, 0.f},
            {0.f, 0.f, 1.f, 0.f, 1.f, 0.f, 0.f, 0.f, 0.f},
            // TOP
            {0.f, 1.f, 0.f, 0.f, 1.f, 1.f, 1.f, 1.f, 1.f},
            {0.f, 1.f, 0.f, 1.f, 1.f, 1.f, 1.f, 1.f, 0.f},
            // BOTTOM
            {1.f, 0.f, 1.f, 0.f, 0.f, 1.f, 0.f, 0.f, 0.f},
            {1.f, 0.f, 1.f, 0.f, 0.f, 0.f, 1.f, 0.f, 0.f},
        };

        matProjection.mat[0][0] = AspectRatio * FOVRad;
        matProjection.mat[1][1] = FOVRad;
        matProjection.mat[2][2] = Far / (Far - Near);
        matProjection.mat[3][2] = (-Far * Near) / (Far - Near);
        matProjection.mat[2][3] = 1.f;
        matProjection.mat[3][3] = 0.f;
    }
};
