#include <inttypes.h>
#include "SwissSkillsProgrammingBoard.h"

uint8_t prevButtonValues;
uint8_t UltrasonicMeasurementCounter;
SwissSkillsProgrammingBoard *board;

void setup() {
  board = new SwissSkillsProgrammingBoard();
  board->SetLED_PortEnable(0xFF);
  board->lcdDisplay->begin(16, 2);
  board->lcdDisplay->clear();
  Serial.begin(9600);
}

void loop() {
  uint8_t ButtonValues = board->GetButtonStates();
  uint8_t ButtonEdges = ButtonValues & ~prevButtonValues;
  prevButtonValues = ButtonValues;

  board->ToggleLEDs(ButtonEdges);

  if (UltrasonicMeasurementCounter > 50)
  {
    uint16_t distance = board->GetUltrasonicDistance();
    board->lcdDisplay->setCursor(0, 0);
    board->lcdDisplay->print(distance);
    board->lcdDisplay->print("mm   ");
    UltrasonicMeasurementCounter = 0;
  }
  
  float pot0val = BINARY_TO_VOLTAGE(analogRead(A0));
  float pot1val = BINARY_TO_VOLTAGE(analogRead(A1));

  board->lcdDisplay->setCursor(0, 1);
  board->lcdDisplay->print("A0: ");
  board->lcdDisplay->print(pot0val);
  board->lcdDisplay->print("V, A1: ");
  board->lcdDisplay->print(pot1val);
  board->lcdDisplay->print("V    ");
  
  delay(10);
  UltrasonicMeasurementCounter++;
}
