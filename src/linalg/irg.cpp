//
// Created by m43 on 02. 05. 2020..
//

#include "irg.h"
#include "matrix.h"
#include "vector.h"

shared_ptr<IMatrix> IRG::translate3D(double dx, double dy, double dz) {
    auto m = Matrix::identityMatrix(4);
    m->set(3, 0, dx);
    m->set(3, 1, dy);
    m->set(3, 2, dz);
    return m;
}

shared_ptr<IMatrix> IRG::scale3D(double sx, double sy, double sz) {
    auto m = Matrix::identityMatrix(4);
    m->set(0, 0, sx);
    m->set(1, 1, sy);
    m->set(2, 2, sz);
    return m;
}

shared_ptr<IMatrix> IRG::lookAtMatrix(IVector &eye, IVector &center, IVector &viewUp) {
    if (eye.getDimension() != 3) {
        throw invalid_argument("eye must be a three dimensional vector");
    }
    if (center.getDimension() != 3) {
        throw invalid_argument("center must be a three dimensional vector");
    }
    if (viewUp.getDimension() != 3) {
        throw invalid_argument("viewUp must be a three dimensional vector");
    }

    // rotation
    auto forward = make_unique<Vector>(vector<double>{
            center.get(0) - eye.get(0),
            center.get(1) - eye.get(1),
            center.get(2) - eye.get(2)
    });
    if (forward->get(0) == 0 && forward->get(1) == 0 && forward->get(2) == 0) {
        throw invalid_argument("eye cannot be the same as the center");
    }
    forward->normalize();
    viewUp.normalize();
    if ((forward->get(0) == viewUp.get(0) && forward->get(1) == viewUp.get(1) && forward->get(2) == viewUp.get(2)) ||
        (forward->get(0) == -viewUp.get(0) && forward->get(1) == -viewUp.get(1) && forward->get(2) == -viewUp.get(2))) {
        // TODO refactor - add equals to vector class
        throw invalid_argument("viewUp vector cannot be parallel with z axis of view coordinate system.");
    }

    auto side = forward->nCrossProduct3D(viewUp);
    side->normalize();

    auto up = side->nCrossProduct3D(*forward);
//    up->normalize();

    auto r = Matrix::identityMatrix(4);
    r->set(0, 0, side->get(0));
    r->set(0, 1, side->get(1));
    r->set(0, 2, side->get(2));
    r->set(1, 0, up->get(0));
    r->set(1, 1, up->get(1));
    r->set(1, 2, up->get(2));
    r->set(2, 0, -forward->get(0));
    r->set(2, 1, -forward->get(1));
    r->set(2, 2, -forward->get(2));
    auto rTransposed = r->nTranspose();

    // translation
    auto t = IRG::translate3D(-eye.get(0), -eye.get(1), -eye.get(2));

    return t->nMultiply(*rTransposed);
}

shared_ptr<IMatrix> IRG::buildFrustumMatrix(double l, double r, double b, double t, int n, int f) {
    auto m = make_shared<Matrix>(Matrix(4, 4));

    m->set(0, 0, 2 * n / (r - l));
    m->set(0, 1, 0);
    m->set(0, 2, 0);
    m->set(0, 3, 0);

    m->set(1, 0, 0);
    m->set(1, 1, 2 * n / (t - b));
    m->set(1, 2, 0);
    m->set(1, 3, 0);

    m->set(2, 0, (r + l) / (r - l));
    m->set(2, 1, (t + b) / (t - b));
    m->set(2, 2, -(f + n) / (f - n));
    m->set(2, 3, -1);

    m->set(3, 0, 0);
    m->set(3, 1, 0);
    m->set(3, 2, -2 * f * n / (f - n));
    m->set(3, 3, 0);

    return m;
}
