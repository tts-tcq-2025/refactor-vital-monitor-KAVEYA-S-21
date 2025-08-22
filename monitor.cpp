#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>

using std::cout;
using std::flush;
using std::this_thread::sleep_for;
using std::chrono::seconds;

// ---------- Data structures ----------
struct VitalStatus {
    bool ok;
    std::string message;
};

// ---------- Pure functions (testable) ----------
VitalStatus checkTemperature(float temperature) {
    if (temperature < 95 || temperature > 102) {
        return {false, "Temperature is critical!"};
    }
    return {true, ""};
}

VitalStatus checkPulse(float pulseRate) {
    if (pulseRate < 60 || pulseRate > 100) {
        return {false, "Pulse Rate is out of range!"};
    }
    return {true, ""};
}

VitalStatus checkSpo2(float spo2) {
    if (spo2 < 90) {
        return {false, "Oxygen Saturation out of range!"};
    }
    return {true, ""};
}

// ---------- I/O side effects ----------
void blinkWarning(int blinks = 6) {
    for (int i = 0; i < blinks; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
    cout << "\n";
}

// ---------- Coordinator ----------
int vitalsOk(float temperature, float pulseRate, float spo2) {
    std::vector<VitalStatus> results = {
        checkTemperature(temperature),
        checkPulse(pulseRate),
        checkSpo2(spo2)
    };

    auto it = std::find_if(results.begin(), results.end(),
                           [](const VitalStatus& s){ return !s.ok; });

    if (it != results.end()) {
        cout << it->message << "\n";
        blinkWarning();
        return 0;
    }
    return 1;
}
