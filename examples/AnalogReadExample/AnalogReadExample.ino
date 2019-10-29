// Arduino libmapper library example

#include "WiFi.h"
#include "mapper.h"

// WiFi ssid and password
const char* ssid = "ssid";
const char* password = "password";

mapper_device dev = 0;
mapper_signal output_signal = 0;

void setup() {
    // Begin WiFi before creating mapper device
    WiFi.begin(ssid, password);
    
    // Initialize mapper device
    dev = mapper_device_new("ESP32", 0, 0);

    int signal_min = 0;
    int signal_max = 1023;

    // Add output signal with type integer and unit "V" (for voltage)
    output_signal = mapper_device_add_output_signal(dev, "sensor_value", 1, 'i', "V", &signal_min, &signal_max);
}

void loop() {
    // Poll device
    mapper_device_poll(dev, 0);

    // Update signal with analog value
    mapper_signal_update_int(output_signal, analogRead(A0));
}