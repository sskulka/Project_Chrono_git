// =============================================================================
// PROJECT CHRONO - http://projectchrono.org
//
// Copyright (c) 2014 projectchrono.org
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file at the top level of the distribution and at
// http://projectchrono.org/license-chrono.txt.
//
// =============================================================================

#include <cstdio>
#include <cstring>

#include "chrono/collision/edgetempest/ChCMatVec.h"
#include "chrono/collision/edgetempest/ChCGetTime.h"
#include "chrono/collision/edgetempest/ChCCollisionTree.h"
#include "chrono/physics/ChBody.h"

namespace chrono {
namespace collision {

ChCollisionTree::ChCollisionTree() {
    // no bounding volume tree yet
    num_geometries = 0;

    last_geometry = NULL;

    build_state = ChC_BUILD_STATE_MODIFIED;

    m_body = NULL;
}

ChCollisionTree::~ChCollisionTree() {
    ResetModel();
}

int ChCollisionTree::ResetModel() {
    // delete previously added geometries
    std::vector<geometry::ChGeometry*>::iterator nit = geometries.begin();
    for (; nit != geometries.end(); ++nit) {
        if (*nit)
            delete (*nit);
        *nit = NULL;
    }
    geometries.clear();
    num_geometries = 0;

    build_state = ChC_BUILD_STATE_MODIFIED;

    return ChC_OK;
}

int ChCollisionTree::BuildModel(double envelope) {
    if (build_state == ChC_BUILD_STATE_PROCESSED) {
        // fprintf(stderr,"Warning! Called EndModel() on ChCollisionTree \n"
        //               "object that was already ended. EndModel() was\n"
        //               "ignored.  Must do a BeginModel() to clear the\n"
        //               "model for addition of new triangles\n");
        return ChC_OK;
    }

    if (num_geometries)
        last_geometry = *geometries.begin();
    else
        last_geometry = NULL;

    return ChC_OK;
}

int ChCollisionTree::AddGeometry(geometry::ChGeometry* mgeo) {
    this->geometries.push_back(mgeo);

    num_geometries += 1;

    build_state = ChC_BUILD_STATE_MODIFIED;

    return ChC_OK;
}

void ChCollisionTree::GetBoundingBox(ChVector<>& cmin, ChVector<>& cmax, const ChMatrix33<>& rot) {
    cmin = ChVector<>(+std::numeric_limits<double>::max());
    cmax = ChVector<>(-std::numeric_limits<double>::max());

    std::vector<geometry::ChGeometry*>::iterator nit = geometries.begin();
    for (; nit != geometries.end(); ++nit) {
        if ((*nit)) {
            (*nit)->InflateBoundingBox(cmin, cmax, rot);
        }
    }
}

void ChCollisionTree::UpdateAbsoluteAABB(double envelope) {
    assert(m_body);

    m_absoluteAABB.init(this);

    static ChMatrix33<> at = m_body->GetA().transpose();
    ChVector<> cmin;
    ChVector<> cmax;
    GetBoundingBox(cmin, cmax, at);

    m_absoluteAABB.m_beginX.m_value = cmin.x() - envelope + m_body->GetPos().x();
    m_absoluteAABB.m_endX.m_value = cmax.x() + envelope + m_body->GetPos().x();
    m_absoluteAABB.m_beginY.m_value = cmin.y() - envelope + m_body->GetPos().y();
    m_absoluteAABB.m_endY.m_value = cmax.y() + envelope + m_body->GetPos().y();
    m_absoluteAABB.m_beginZ.m_value = cmin.z() - envelope + m_body->GetPos().z();
    m_absoluteAABB.m_endZ.m_value = cmax.z() + envelope + m_body->GetPos().z();
}

}  // end namespace collision
}  // end namespace chrono
