Tachometer Sensor Model {#tachometer_sensor}
=================================

\tableofcontents

In Chrono::Sensor::ChTachometerSensor, the synthetic data is generated by querying the angular velocity of the parent body.

### Creating a Tachometer
~~~{.cpp}
auto tachometer = chrono_types::make_shared<ChTachometerSensor>(
                        parent_body,        // body sensor is attached to
                        update_rate,        // measurement rate in Hz
                        offset_pose,        // offset pose of sensor
                        axis,               // axis of rotation to take measurements
)

tachometer->SetName("Tachometer Sensor");
tachometer->SetLag(lag);
tachometer->SetCollectionWindow(collection_time); 
~~~
<br>

### Tachometer Filter Graph
~~~{.cpp}
// Access tachometer data in raw format (angular velocity)
tachometer->PushFilter(chrono_types::make_shared<ChFitlerTachometerAccess>());

// Add sensor to manager
manager->AddSensor(tachometer);
~~~

### Tachometer Data Access
~~~{.cpp}
UserTachometerBufferPtr data_ptr;
while(){
    data_ptr = tachometer->GetMostRecentBuffer<UserTachometerBufferPtr>();
    if (data_ptr->Buffer){
        // Retrieve and print the angular velocity
        angular_vel = data_ptr->Buffer[0];
        std::cout<<"Angular  velocity: <<angular_vel<<std::endl;
    }
}
~~~
