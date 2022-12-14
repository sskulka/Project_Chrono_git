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
// =============================================================================

#ifndef CHFILTERONNX_H
#define CHFILTERONNX_H

#include "chrono_sensor/filters/ChFilter.h"
#include "NvInfer.h"
#include "NvOnnxParser.h"
#include <NvUtils.h>
#include <cuda_runtime_api.h>
#include "chrono_sensor/tensorrt/ChTRTUtils.h"

#include <iostream>

namespace chrono {
namespace sensor {

/// @addtogroup sensor_tensorrt
/// @{

/// A filter that processes data through a pre-trained neural network, based on ONNX format
class CH_SENSOR_API ChFilterONNX : public ChFilter {
  public:
    /// Class constructor
    ChFilterONNX(std::string name = "ChFilterONNX");

    /// Apply function runs data through neural network
    virtual void Apply();

    /// Initialize function for generating any information or structures needed once
    /// @param pSensor The sensor used for processing
    /// @param bufferInOut A shared pointer for passing data between filters
    virtual void Initialize(std::shared_ptr<ChSensor> pSensor, std::shared_ptr<SensorBuffer>& bufferInOut);

  private:
    std::unique_ptr<nvinfer1::ICudaEngine, TRTDestroyer> m_inference_engine;  ///< object used for inference
    std::unique_ptr<nvinfer1::IExecutionContext, TRTDestroyer>
        m_inference_context;  ///< executing context for inference

    std::shared_ptr<float> m_input;        ///< input buffers for processing
    std::shared_ptr<float> m_output;       ///< output buffers for processing
    std::vector<void*> m_process_buffers;  ///< vector for pointers which inlcude input and output buffers

    std::shared_ptr<SensorDeviceRGBA8Buffer> m_buffer_in;
};

/// @} sensor_tensorrt

}  // namespace sensor
}  // namespace chrono

#endif
