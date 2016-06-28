// LED Flicker library file
#include "Led.h"

////////////////////////////////////////////////////////////////////////////////////
// Led class
////////////////////////////////////////////////////////////////////////////////////

// init()
// Purpose:
//    -Initializes Led object. Sets pin mode to output. Must be called in setup()
void Led::init(){
  pinMode(_pin, OUTPUT);
}

// on()
// Purpose:
//    -Sets Led pin to HIGH
void Led::on(){
  digitalWrite(_pin, HIGH);
}

// off()
// Purpose:
//    -Sets Led pin to LOW
void Led::off(){
  digitalWrite(_pin, LOW);
}

////////////////////////////////////////////////////////////////////////////////////
// LedPwm class
////////////////////////////////////////////////////////////////////////////////////

// init()
// Purpose:
//    -Initializes LedPwm object. Sets pin mode to output,
//     initializes SoftPWM to 0. Must be called in setup()
void LedPwm::init(){
  pinMode(_pin, OUTPUT);
  // Set soft PWM pins to zero
  SoftPWMBegin();
  SoftPWMSet(_pin, 0);
}


// on()
// Purpose:
//    -Sets Led pin to predetermined pwm value
void LedPwm::on(){
  SoftPWMSet(_pin, _pwmVal);
}

// off()
// Purpose:
//    -Sets Led pin to pwm value 0
void LedPwm::off(){
  SoftPWMSet(_pin, 0);
}

// setPwmVal()
// Purpose:
//    -Sets pwmVal variable to new value
// Inputs:
//    -pwmVal: PWM value to assign to Led
void LedPwm::setPwmVal(uint8_t pwmVal){
  _pwmVal = pwmVal;
}

// getPwmVal()
// Purpose:
//    -Gets pwmVal
// Outputs:
//    -pwmVal: returns PWM value currently assigned to Led
uint8_t LedPwm::getPwmVal(){
  return _pwmVal;
}

////////////////////////////////////////////////////////////////////////////////////
// LedBlink class
////////////////////////////////////////////////////////////////////////////////////

// init()
// Purpose:
//    -Initializes LedBlink object. Sets pin mode to output.
//     Must be called in setup()
void LedBlink::init(){
  _onFlg = 0;
  pinMode(_pin, OUTPUT);
}


// on()
// Purpose:
//    -Sets on flag. update() must be called in loop for Led to blink
void LedBlink::on(){
  _onFlg = 1;
}

// off()
// Purpose:
//    -Clears on flag. update() must be called in loop for Led to turn off
void LedBlink::off(){
  _onFlg = 0;
}

// update()
// Purpose:
//    -Updates state of Led based on previously set period_ms
void LedBlink::update(){

  uint32_t _currentMillis = millis();

  if (_onFlg == 1 && (_currentMillis - _previousMillis >= _period_ms/2)) {
    // blink Led
    _previousMillis = _currentMillis;
    _ledState = !_ledState;
    digitalWrite(_pin, _ledState);

  } else if (_onFlg == 0) {
    if (_ledState != LOW){
      // led is not already LOW
      _ledState = LOW;
      digitalWrite(_pin, _ledState);
    }
  }
}

// setPeriod_ms()
// Purpose:
//    -Sets period_ms variable to new value
// Inputs:
//    -period_ms: time (in ms) to assign as period for Led to blink
void LedBlink::setPeriod_ms(uint32_t period_ms){
  _period_ms = period_ms;
}

// getPeriod_ms()
// Purpose:
//    -Gets period_ms
// Outputs:
//    -period_ms: returns time (in ms) currently assigned to Led period
uint32_t LedBlink::getPeriod_ms(){
  return _period_ms;
}


////////////////////////////////////////////////////////////////////////////////////
// LedFlicker class
////////////////////////////////////////////////////////////////////////////////////

// init()
// Purpose:
//    -Initializes LedFlicker object. Sets pin mode to output,
//     initializes SoftPWM to 0. Must be called in setup()
void LedFlicker::init(){
  _ledState = 0;
  pinMode(_pin, OUTPUT);
  // Set soft PWM pins to zero
  SoftPWMBegin();
  SoftPWMSet(_pin, 0);
}

// update()
// Purpose:
//    -Updates state of Led based on previously set period_ms
void LedFlicker::update(){
  uint32_t _currentMillis = millis();

  if (_onFlg == 1 && (_currentMillis - _previousMillis >= _period_ms/2)) {
    // Draw random value for the brightness of the LEDs. Inputs are (minimum value, maximum value).
    // Random returns a random value between the minimum and maximum given.
    _ledState = random(_pwmMin, _pwmMax + 1);

    // set pwm value
    SoftPWMSet(_pin, _ledState);

  } else if (_onFlg == 0) {
    if (_ledState != LOW){
      // led is not already LOW
      _ledState = 0;
      SoftPWMSet(_pin, _ledState);
    }
  }
}

// setPwmMin()
// Purpose:
//    -Sets pwmMin variable to new value
// Inputs:
//    -pwmMin: min for PWM acceptable range
void LedFlicker::setPwmMin(uint8_t pwmMin){
  _pwmMin = pwmMin;
}

// getPwmMin()
// Purpose:
//    -Gets pwmMin
// Outputs:
//    -pwmMin: returns min for PWM acceptable range
uint8_t LedFlicker::getPwmMin(){
  return _pwmMin;
}

// setPwmMax()
// Purpose:
//    -Sets pwmMax variable to new value
// Inputs:
//    -pwmMax: max for PWM acceptable range
void LedFlicker::setPwmMax(uint8_t pwmMax){
  _pwmMax = pwmMax;
}

// getPwmMax()
// Purpose:
//    -Gets pwmMax
// Outputs:
//    -pwmMax: returns max for PWM acceptable range
uint8_t LedFlicker::getPwmMax(){
  return _pwmMax;
}

/*


////////////////////////////////////////////////////////////////////////////////////
// Constructor
// Purpose:
//    -Constructs object of the FireFlicker class
//
// Inputs:
//    -pinNo: pin number
//    -pwmMin: min for PWM acceptable range
//    -pwmMax: max for PWM acceptable range
///////////////////////////////////////////////////////////////////////////////////////
FireFlicker::FireFlicker(uint8_t pinNo, uint8_t pwmMin, uint8_t pwmMax, uint32_t period_ms){
    pin = pinNo;
    pwm_min = pwmMin;
    pwm_max = pwmMax;
}

////////////////////////////////////////////////////////////////////////////////////
// init()
// Purpose:
//    -Initializes FireFlicker object. Sets On flag to 0, sets pin mode to output,
//     initializes SoftPWM to 0.
///////////////////////////////////////////////////////////////////////////////////////
void FireFlicker::init(){
  onFlg = 0;
  pinMode(pin, OUTPUT);
  // Set soft PWM pins to zero
  SoftPWMBegin();
  SoftPWMSet(pin, 0);
}

////////////////////////////////////////////////////////////////////////////////////
// on()
// Purpose:
//    -Sets On flag to 1
///////////////////////////////////////////////////////////////////////////////////////
void FireFlicker::on(){
  onFlg = 1;
}

////////////////////////////////////////////////////////////////////////////////////
// off()
// Purpose:
//    -Sets On flag to 0
///////////////////////////////////////////////////////////////////////////////////////
void FireFlicker::off(){
  onFlg = 0;
}

////////////////////////////////////////////////////////////////////////////////////
// flickerUpdate()
// Purpose:
//    -If On flag is set to 0, sets output PWM to 0. If On flag is set to 1,
//     calculates random value between pwm_min and pwm_max to set PWM output to.
// Inputs:
//    - flickerFlg: this is a flag passed in that should be set in an interrupt
///////////////////////////////////////////////////////////////////////////////////////
void FireFlicker::flickerUpdate(){
  // initialize variables.  This value is the brightness of the fire LED.
  uint8_t val = 0;

  // Draw random value for the brightness of the LEDs. Inputs are (minimum value, maximum value).
  // Random returns a random value between the minimum and maximum given.
  val = random(pwm_min, pwm_max + 1);

  // If the On flag is not 1, send a PWM of 0 to the output.
  if(onFlg == 0){
    val = 0;
  }

  // set pwm value
  SoftPWMSet(pin, val);


}
*/
