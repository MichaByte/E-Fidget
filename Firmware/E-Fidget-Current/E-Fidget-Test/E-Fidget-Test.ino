#include "Vars.h"

void setup() {
  pinMode(M1_PIN, OUTPUT);
  pinMode(M2_PIN, OUTPUT);
  pinMode(M3_PIN, OUTPUT);

  pinMode(B1_PIN, INPUT_PULLUP);
  pinMode(B2_PIN, INPUT_PULLUP);

  digitalWrite(M1_PIN, LOW);
  digitalWrite(M2_PIN, LOW);
  digitalWrite(M3_PIN, LOW);


}

int b1down = 0;
int curmotor = 0;
int delaymode = 0;
unsigned long event_time = 0;
unsigned long spin_count = 0;

#define MOTOR_RUN_TIME 5000
#define DELAY_MULTIPLIER 950

//int debounce = 0;

void restart_motors()
{
    spin_count = 0;
    if (curmotor == 0)
    {
        curmotor = M1_PIN;
        digitalWrite(curmotor, HIGH);
    }
    delaymode = 0;
    event_time = micros() + MOTOR_RUN_TIME;
}

void next_motor(unsigned long curtime)
{
    digitalWrite(curmotor, LOW);
    delaymode = 1;
    event_time = curtime + (spin_count * 3 + curmotor) * DELAY_MULTIPLIER;
    if (curmotor == M1_PIN)
    {
        curmotor = M2_PIN;
    }
    else if (curmotor == M2_PIN)
    {
        curmotor = M3_PIN;
    }
    else
    {
        // curmotor == M3_PIN
        ++spin_count;
        if (spin_count >= 12)
        {
            curmotor = 0;
        }
        else
        {
            curmotor = M1_PIN;
        }
    }
}

void next_event(unsigned long curtime)
{
    if (delaymode == 0)
    {
        next_motor(curtime);
    }
    else
    {
        digitalWrite(curmotor, HIGH);
        event_time = curtime + MOTOR_RUN_TIME;
        delaymode = 0;
    }
}

void loop()
{
    if (curmotor > 0)
    {
        unsigned long curtime = micros();

        if (curtime > event_time)
        {
            next_event(curtime);
        }
    }

    if (digitalRead(B1_PIN) == BTN_ON)
    {
        b1down = 1;
    }
    else if (b1down)
    {
        restart_motors();
        b1down = 0;
    }
}

