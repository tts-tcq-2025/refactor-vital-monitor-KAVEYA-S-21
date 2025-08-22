#pragma once


bool isTemperatureInRange(float temperature);
bool isPulseRateInRange(float pulseRate);
bool isSpoInRange(float spo2);
bool vitalsInRange(float temperature, float pulseRate, float spo2);
void alert(const char* message);
