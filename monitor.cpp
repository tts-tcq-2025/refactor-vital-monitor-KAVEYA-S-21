#include <iostream>
#include <thread>
#include <chrono>
#include <string>

using std::cout;
using std::endl;
using std::flush;
using std::this_thread::sleep_for;
using std::chrono::seconds;

// ---------- Visual Effect ----------
void printVisualEffect(const std::string& message) {
    cout << message << endl;
    for (int i = 0; i < 6; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
    cout << endl;
}

// ---------- Vital checks ----------
bool vitalRangeCheck(float vitalValue, float lowThreshold, float highThreshold,
                     const std::string& message) {
    if (vitalValue < lowThreshold || vitalValue > highThreshold) {
        printVisualEffect(message);
        return false;
    }
    return true;
}

bool vitalLowThresholdCheck(float vitalValue, float lowThreshold,
                            const std::string& message) {
    if (vitalValue < lowThreshold) {
        printVisualEffect(message);
        return false;
    }
    return true;
}

// ---------- Coordinator ----------
bool vitalOk(float temperature, float pulseRate, float spo2) {
    bool tempOk  = vitalRangeCheck(temperature, 95, 102, "Temperature critical!");
    bool pulseOk = vitalRangeCheck(pulseRate, 60, 100, "Pulse Rate is out of range!");
    bool spo2Ok  = vitalLowThresholdCheck(spo2, 90, "Oxygen Saturation out of range!");

    return tempOk && pulseOk && spo2Ok;
}
