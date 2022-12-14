// =============================================================================
// PROJECT CHRONO - http://projectchrono.org
//
// Copyright (c) 2019 projectchrono.org
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be found
// in the LICENSE file at the top level of the distribution and at
// http://projectchrono.org/license-chrono.txt.
//
// =============================================================================
// Authors: Asher Elmquist
// =============================================================================
//
// Class for managing the all sensor updates
//
// =============================================================================

#ifndef CHDYNAMICSMANAGER_H
#define CHDYNAMICSMANAGER_H

// API include
#include "chrono_sensor/ChApiSensor.h"

#include "chrono/physics/ChSystem.h"

#include "chrono_sensor/sensors/ChGPSSensor.h"
#include "chrono_sensor/sensors/ChIMUSensor.h"

#include <fstream>
#include <sstream>

namespace chrono {
namespace sensor {

/// @addtogroup sensor_sensors
/// @{

/// class for managing dynamic sensors. This class is not built for mutlithreading as it is lockstep with the
/// Chrono system. Will hold and update all sensors that don't need access to rendering or the environmnet. That
/// currently includes GPS and IMU
class CH_SENSOR_API ChDynamicsManager {
  public:
    /// Constructor for the dynamic sensor manager.
    /// @param chrono_system The Chrono system that is associated with the dynamic sensor manager. Used for time keeping
    /// purposes.
    ChDynamicsManager(ChSystem* chrono_system);

    /// Class destructor
    ~ChDynamicsManager();

    /// Function for updating the sensors for which the dynamic sensor manager is responsible
    void UpdateSensors();

    /// Add sensor to this manager. Must be sensor the class can handle. Currently only GPS or IMU
    /// @param sensor A shared pointer to a sensor that should be assigned to this manager.
    void AssignSensor(std::shared_ptr<ChSensor> sensor);

  private:
    ChSystem* m_system;  ///< system in which the manager lives

    std::vector<std::shared_ptr<ChDynamicSensor>> m_sensor_list;  ///< list of dynamic sensors
};

/// @} sensor_sensors

}  // namespace sensor
}  // namespace chrono

#endif
