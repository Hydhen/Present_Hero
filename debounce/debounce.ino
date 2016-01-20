#include <Bounce2.h>
#include <SoftwareSerial.h>

////////////////////
//      BUTTON    //
////////////////////

struct Button {
  const int     pin;
  const int     mask;
  unsigned long last_bounce;
  Bounce        bouncer;
  const char*   str;
};

Button select   = {2,   0b1,          0,  Bounce(), "SELECT"};
Button start    = {3,   0b10,         0,  Bounce(), "START"};

Button orange   = {4,   0b100,        0,  Bounce(), "ORANGE"};
Button blue     = {5,   0b1000,       0,  Bounce(), "BLUE"};
Button yellow   = {6,   0b10000,      0,  Bounce(), "YELLOW"};
Button red      = {7,   0b100000,     0,  Bounce(), "RED"};
Button green    = {8,   0b1000000,    0,  Bounce(), "GREEN"};

Button up       = {9,   0b10000000,   0,  Bounce(), "UP"};
Button down     = {10,  0b100000000,  0,  Bounce(), "DOWN"};

Button buttons[9] = {select, start, orange, blue, yellow, red, green, up, down};

int button_updated = 0;
int button_pressed = 0;

////////////////////
//      LED       //
////////////////////

const int witness = 13;

////////////////////
//    BLUETOOTH   //
////////////////////

const int rx = 12;
const int tx = 11;
SoftwareSerial bluetoothSerial(rx, tx);

////////////////////
//      TIMER     //
////////////////////

unsigned long clk = 0;
unsigned long last_clk = 0;
const int debounce_timer = 300;
const int debounce_interval = 200;

////////////////////
//      ARDUINO   //
////////////////////

const bool debugging = false;

void setup()
{
  // Setup witness LED
  pinMode(witness, OUTPUT);
  // Setup Serial
  Serial.begin(9600);
  bluetoothSerial.begin(9600);
  
  // Setup buttons
  for (int i = 0; i <= 8; i++) pinMode(buttons[i].pin, INPUT);
  
  // After setting up the button, setup the object
  for (int i = 0; i <= 8; i++)
  {
    buttons[i].bouncer.attach(buttons[i].pin);
    buttons[i].bouncer.interval(5);
  }
}

int button_update()
{
  button_updated = 0;
  for (int i = 0; i <= 8; i++)
    if (buttons[i].bouncer.update()) button_updated |= buttons[i].mask;
  return button_updated;
}

void button_reader()
{
  for (int i = 0; i <= 8; i++)
  {
    if (button_updated & buttons[i].mask)
    {
      if (buttons[i].bouncer.read())
      {
        buttons[i].last_bounce = millis();
        button_pressed |= buttons[i].mask;
        if (debugging)    
        {
          Serial.print("## ENVOI");
          Serial.println(buttons[i].str);
        }
      }
      else
      {
        buttons[i].last_bounce = 0;
        if (debugging)
        {
          Serial.print(buttons[i].str);
          Serial.println(" BOUNCE 0");
        }
      }
    }
  }
  button_updated = 0;
}

void last_bounce_update()
{
  for (int i = 0; i <= 8; i++)
  {
    if (buttons[i].last_bounce)
    {
      if (millis() - buttons[i].last_bounce >= debounce_timer)
      {
        buttons[i].last_bounce += debounce_interval;
        button_pressed |= buttons[i].mask;
        if (debugging)
        {
          Serial.print("RENVOI");
          Serial.println(buttons[i].str);
        }
      }
    }
  }
}

void loop()
{
  // Lights up withness
  digitalWrite(witness, HIGH);

  clk = millis();
  if ((clk - last_clk) >= 10)
  {
    button_pressed = 0;
    last_clk = clk;
    if (button_update()) button_reader();
    last_bounce_update();
    for(int i = 0; i < 9 - String(button_pressed, BIN).length(); ++i)
    {
      Serial.print("0");
      bluetoothSerial.print("0");
    }
    Serial.println(button_pressed, BIN);
    bluetoothSerial.println(button_pressed, BIN);
  }
}
