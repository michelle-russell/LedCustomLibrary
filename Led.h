#ifndef LED_H
#define LED_H

#include "SoftPWM.h"
#include <arduino.h>

class Led {
  //Constructors
  public:
    Led();
    Led(uint8_t pinNo);

    void init();
    void on();
    void off();


  protected:
    uint8_t _pin;
};

class LedPwm : Led {
  public:
    LedPwm():Led(){
      _pwmVal = 0;
    };
    LedPwm(uint8_t pinNo, uint8_t pwmVal):Led(pinNo){
      _pwmVal = pwmVal;
    };

    void init();
    void on();
    void off();
    void setPwmVal(uint8_t pwmVal);
    uint8_t getPwmVal();

  protected:
    uint8_t _pwmVal;
};

class LedBlink : Led {
  public:
    LedBlink():Led(){
      _period_ms = 0;
    };
    LedBlink(uint8_t pinNo, uint32_t period_ms):Led(pinNo){
      _period_ms = period_ms;
    };

    void init();
    void on();
    void off();
    void update();
    void setPeriod_ms(uint32_t period_ms);
    uint32_t getPeriod_ms();

  protected:
    uint8_t _pin;
    uint8_t _onFlg = 0;
    uint32_t _period_ms;
    uint8_t _ledState = LOW;
    uint32_t _previousMillis = 0;
};

class LedFlicker : LedBlink {
  public:
    //Constructors
    LedFlicker():LedBlink(){
      _pwmMin = 0;
      _pwmMax = 0;
    };
    LedFlicker(uint8_t pinNo, uint8_t pwmMin, uint8_t pwmMax, uint32_t period_ms):LedBlink(pinNo, period_ms){
      _pwmMin = pwmMin;
      _pwmMax = pwmMax;
    };

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
