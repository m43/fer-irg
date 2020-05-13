//
// Created by m43 on 02. 05. 2020..
//

#ifndef FER_IRG_IRG_H
#define FER_IRG_IRG_H

#include "i_matrix.h"

class IRG {
public:
    static shared_ptr<IMatrix> translate3D(double dx, double dy, double dz);

    static shared_ptr<IMatrix> scale3D(double sx, double sy, double sz);

    static shared_ptr<IMatrix> lookAtMatrix(IVector &eye, IVector &center, IVector &viewUp);

    static shared_ptr<IMatrix>
    buildFrustumMatrix(double left, double right, double bottom, double top, int near, int far);
};


#endif //FER_IRG_IRG_H
