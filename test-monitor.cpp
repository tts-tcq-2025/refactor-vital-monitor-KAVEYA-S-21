#include "monitor.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// --- Mocking printVisualEffect ---
class MonitorMock {
public:
    MOCK_METHOD(void, printVisualEffect, (const std::string&), ());
};

static MonitorMock* g_mock = nullptr;

// Override the real function with mock delegation
void printVisualEffect(const std::string& message) {
    if (g_mock) {
        g_mock->printVisualEffect(message);
    }
}

// --- Test Suite ---
class TestMonitorVitalOk : public ::testing::Test {
protected:
    void SetUp() override {
        g_mock = new MonitorMock();
    }
    void TearDown() override {
        delete g_mock;
        g_mock = nullptr;
    }
};

// Test when all vitals are in the normal range; no alert should be triggered
TEST_F(TestMonitorVitalOk, AllVitalsNormal) {
    EXPECT_CALL(*g_mock, printVisualEffect(::testing::_)).Times(0);
    EXPECT_TRUE(vitalOk(98, 80, 95));
}

// Test when temperature is critically high
TEST_F(TestMonitorVitalOk, TemperatureCriticalHigh) {
    EXPECT_CALL(*g_mock, printVisualEffect("Temperature critical!")).Times(1);
    EXPECT_FALSE(vitalOk(103, 80, 95));
}

// Test when temperature is critically low
TEST_F(TestMonitorVitalOk, TemperatureCriticalLow) {
    EXPECT_CALL(*g_mock, printVisualEffect("Temperature critical!")).Times(1);
    EXPECT_FALSE(vitalOk(94, 80, 95));
}

// Test when pulse rate is critically high
TEST_F(TestMonitorVitalOk, PulseRateCriticalHigh) {
    EXPECT_CALL(*g_mock, printVisualEffect("Pulse Rate is out of range!")).Times(1);
    EXPECT_FALSE(vitalOk(98, 103, 95));
}

// Test when pulse rate is critically low
TEST_F(TestMonitorVitalOk, PulseRateCriticalLow) {
    EXPECT_CALL(*g_mock, printVisualEffect("Pulse Rate is out of range!")).Times(1);
    EXPECT_FALSE(vitalOk(98, 59, 95));
}

// Test when SpO2 is critically low
TEST_F(TestMonitorVitalOk, Spo2CriticalLow) {
    EXPECT_CALL(*g_mock, printVisualEffect("Oxygen Saturation out of range!")).Times(1);
    EXPECT_FALSE(vitalOk(98, 80, 89));
}

// Test when multiple vitals are critical
TEST_F(TestMonitorVitalOk, MultipleCritical) {
    EXPECT_CALL(*g_mock, printVisualEffect("Temperature critical!")).Times(1);
    EXPECT_CALL(*g_mock, printVisualEffect("Pulse Rate is out of range!")).Times(1);
    EXPECT_CALL(*g_mock, printVisualEffect("Oxygen Saturation out of range!")).Times(1);

    EXPECT_FALSE(vitalOk(103, 103, 89));
}

// --- Main for running tests ---
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
