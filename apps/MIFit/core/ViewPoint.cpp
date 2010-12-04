#include "ViewPoint.h"

#include <cmath>
#include <cstdio>
#include <chemlib/chemlib.h>
#include <chemlib/Monomer.h>
#include <chemlib/MIMoleculeBase.h>
#include <math/mathlib.h>
#include <math/Quaternion.h>
#include <math/Vector3.h>
#include <opengl/QuatUtil.h>

#include "Cfiles.h"

using namespace chemlib;
using namespace mi::math;
using namespace mi::opengl;

ViewPoint::ViewPoint()
    : width_(200), height_(100),
      perspective_(0),
      scale_(20),
      frontClip_(5.0), backClip_(-5.0)

{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (i == j)
            {
                viewmat[i][j] = 1.0;
            }
            else
            {
                viewmat[i][j] = 0;
            }
        }
    }
    center[0] = center[1] = center[2] = 0;
    zangle = sin(perspective_ * M_PI/180.0);
}

void ViewPoint::UnDo()
{
    if (UndoList.size() > 0)
    {
        for (int i = 0; i < 3; i++)
        {
            center[i] = UndoList.back().center[i];
            for (int j = 0; j < 3; j++)
            {
                viewmat[i][j] = UndoList.back().viewmat[i][j];
            }
        }
        scale_ = UndoList.back().scale;
        frontClip_ = UndoList.back().frontClip;
        backClip_ = UndoList.back().backClip;
        //undoable = false;
        UndoList.pop_back();
    }
}

void ViewPoint::Do()
{
    ViewSave last;
    for (int i = 0; i < 3; i++)
    {
        last.center[i] = center[i];
        for (int j = 0; j < 3; j++)
        {
            last.viewmat[i][j] = viewmat[i][j];
        }
    }
    last.scale = scale_;
    last.frontClip = frontClip_;
    last.backClip = backClip_;
    UndoList.push_back(last);
}

void ViewPoint::setmatrix(float mat[3][3])
{
    viewmat[0][0] = mat[0][0];
    viewmat[0][1] = mat[0][1];
    viewmat[0][2] = mat[0][2];
    viewmat[1][0] = mat[1][0];
    viewmat[1][1] = mat[1][1];
    viewmat[1][2] = mat[1][2];
    viewmat[2][0] = mat[2][0];
    viewmat[2][1] = mat[2][1];
    viewmat[2][2] = mat[2][2];
    orthomatrix(viewmat, viewmat);
}

void ViewPoint::copymatrix(float mat[3][3])
{
    //float msf = MSF;
    mat[0][0] = viewmat[0][0];
    mat[0][1] = viewmat[0][1];
    mat[0][2] = viewmat[0][2];
    mat[1][0] = viewmat[1][0];
    mat[1][1] = viewmat[1][1];
    mat[1][2] = viewmat[1][2];
    mat[2][0] = viewmat[2][0];
    mat[2][1] = viewmat[2][1];
    mat[2][2] = viewmat[2][2];
}

void ViewPoint::setSize(int width, int height)
{
    width_ = width;
    height_ = height;
}

void ViewPoint::rotate(float rx, float ry, float rz)
{
    incmatrix(rx, ry, rz, viewmat, viewmat);
    orthomatrix(viewmat, viewmat);
}

void ViewPoint::moveto(float x, float y, float z)
{
    center[0] = x;
    center[1] = y;
    center[2] = z;
}

void ViewPoint::moveBy(const mi::math::Vector3<float> &delta)
{
    center[0] += delta.x;
    center[1] += delta.y;
    center[2] += delta.z;
}


float ViewPoint::perspective() const
{
    return perspective_;
}

void ViewPoint::setPerspective(float p)
{
    perspective_ = std::max(0.0f, p);
    zangle = sin(perspective_*M_PI/180.0);
}

void ViewPoint::zoom(float ds)
{
    scale_ *= ds;
}

void ViewPoint::changeSlab(float delta)
{
    frontClip_ += delta/2.0;
    backClip_ -= delta/2.0;
    if (frontClip_ < backClip_)
    {
        frontClip_ = backClip_ + 1;
    }
}

void ViewPoint::setSlab(float frontClip, float backClip)
{
    frontClip_ = frontClip;
    backClip_ = backClip;
    if (frontClip_ < backClip_)
        std::swap(frontClip_, backClip_);
}

void ViewPoint::setScale(qreal s)
{
    scale_ = s;
    if (scale_ < 1.1)
    {
        scale_ = 1.1;
    }
}

qreal ViewPoint::scale() const
{
    return scale_;
}

qreal ViewPoint::frontClip() const
{
    return frontClip_;
}

qreal ViewPoint::backClip() const
{
    return backClip_;
}

void ViewPoint::setFrontClip(qreal f)
{
    frontClip_ = f;
}

void ViewPoint::setBackClip(qreal b)
{
    backClip_ = b;
}

float ViewPoint::getcenter(int i) const
{
    if (i >= 0 && i < 3)
        return center[i];
    else
        return 0.0;
}

int ViewPoint::width() const
{
    return width_;
}

int ViewPoint::height() const
{
    return height_;
}


float ViewPoint::getwidth() const
{
    return width_ / scale_;
}

float ViewPoint::getheight() const
{
    return height_ / scale_;
}

bool ViewPoint::UnDoable() const
{
    return UndoList.size() > 0;
}
