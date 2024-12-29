/**
* @file 01-BasicUsage.ino
* @brief Example of how to use the ESPRIC to analyse the cause of the reset.
* 
* This example shows how to use the ESPRIC to define reset conditions
* and register callback functions to process the corresponding conditions.
* The results are output via the serial interface.
*/

#include <ESPRIC.h>

/**
* @brief Defines the ESPRIC conditions and their associated callback functions.
* 
* This function creates a list of conditions for the analyser to check.
* Each condition consists of two lambda functions:
* - The first function returns a boolean value that indicates whether the condition is met.
* - The second function defines what should happen if the condition is met.
* 
* @return std::vector<ESPRIC::ESPRIC_Condition> 
*         List of defined ESPRIC conditions.
*/
std::vector<ESPRIC::ESPRIC_Condition> getMyESPRIC_Conditions() {
  return {
    // Unknown reset reason, e.g. after uploading a new sketch
    {[]() { return esp_reset_reason() == ESP_RST_UNKNOWN; }, 
     []() { Serial.println("ESPRIC: Reset reason could not be determined."); }},

    // Power-on reset, e.g. after pressing the RST button
    {[]() { return esp_reset_reason() == ESP_RST_POWERON; }, 
     []() { Serial.println("ESPRIC: Power-on event detected."); }},
  };
}

/**
* @brief Setup function that is called once when the ESP32 starts.
* 
* Initialises the serial interface, outputs a start message and starts
* the ESPRIC with the defined conditions.
*/
void setup() {
  // Initialise serial interface
  Serial.begin(115200);
  while (!Serial) {};  // Wait until serial connection is ready (ESP32C3...)
  Serial.println("Firmware started: ESPRIC - BasicUsage");

  // Start the analyser with defined conditions
  ESPRIC analyzer(getMyESPRIC_Conditions());

  Serial.println("Start Analyzer...");
  analyzer.analyze();  // Analyse conditions and execute corresponding callbacks
  Serial.println("Ready!");
}

/**
* @brief Main program loop that runs continuously.
* 
* In this example, the loop remains empty because the analysis of the conditions
* takes place exclusively in the `setup()` part.
*/
void loop() {
  // Main logic
}