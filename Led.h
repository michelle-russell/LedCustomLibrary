#ifndef LED_H
#define LED_H

#include "SoftPWM.h"
#include <arduino.h>

class Led {
  //Constructors
  public:
    Led(uint8_t pinNo = 0) : _pin(pinNo) {}

    void init();
    void on();
    void off();


  protected:
    uint8_t _pin;
};

class LedPwm : public Led {
  public:

    LedPwm(uint8_t pinNo = 0, uint8_t pwmVal = 0) :
      Led(pinNo), _pwmVal(pwmVal) {}

    void init();
    void on();
    void off();
    void setPwmVal(uint8_t pwmVal);
    uint8_t getPwmVal();

  protected:
    uint8_t _pwmVal;
};

class LedBlink : public Led {
  public:

    LedBlink(uint8_t pinNo = 0, uint32_t period_ms = 0) :
      Led(pinNo), _period_ms(period_ms) {}

    void init();
    void on();
    void off();
    void update();
    void setPeriod_ms(uint32_t period_ms);
    uint32_t getPeriod_ms();

  protected:
    uint8_t _onFlg = 0;
    uint32_t _period_ms;
    uint8_t _ledState = LOW;
    uint32_t _previousMillis = 0;
};

class LedFlicker : public LedBlink {
  public:
    //Constructors

    LedFlicker(uint8_t pinNo = 0, uint8_t pwmMin = 0, uint8_t pwmMax = 0,
      uint32_t period_ms = 0) :
      LedBlink(pinNo, period_ms), _pwmMin(pwmMin), _pwmMax(pwmMax) {}

    void init();
    void update();

    void setPwmMin(uint8_t pwmMin);
    uint8_t getPwmMin();
    void setPwmMax(uint8_t pwmMax);
    uint8_t getPwmMax();

  protected:
    uint8_t _pwmMin, _pwmMax;
};

/*
class FireFlicker {

  public:
    //Constructor
    FireFlicker(uint8_t pinNo, uint8_t pwmMin, uint8_t pwmMax, uint32_t period_ms);

    void init();
    void on();
    void off();
    void flickerUpdate();


  private:
    uint8_t pin, pwm_min, pwm_max, onFlg;



};
*/
#endif // LED_H
