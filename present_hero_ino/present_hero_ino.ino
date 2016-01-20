const long debounce_delay     = 50;

const int SELECT_pin          = 2;
const int START_pin           = 3;
const int ORANGE_pin          = 4;
const int BLUE_pin            = 5;
const int YELLOW_pin          = 6;
const int RED_pin             = 7;
const int GREEN_pin           = 8;
const int UP_pin              = 9;
const int DOWN_pin            = 10;

const int WITNESS_pin         = 12;
const int BOARD_pin           = 13;


const int SELECT              = 0b1;
const int START               = 0b10;
const int ORANGE              = 0b100;
const int BLUE                = 0b1000;
const int YELLOW              = 0b10000;
const int RED                 = 0b100000;
const int GREEN               = 0b1000000;
const int UP                  = 0b10000000;
const int DOWN                = 0b100000000;

struct {
  int color;
  int updown;
  int stsel;
} data = {0, 0, 0};

int input = 0;

// Variables will change:
boolean debugging             = false;
int ledState                  = HIGH;
int last_START_state          = LOW;
int last_SELECT_state         = LOW;
int last_ORANGE_state         = LOW;
int last_BLUE_state           = LOW;
int last_YELLOW_state         = LOW;
int last_RED_state            = LOW;
int last_GREEN_state          = LOW;
int last_UP_state             = LOW;
int last_DOWN_state           = LOW;
long lastDebounceTime         = 0;

void setup() 
{
  pinMode(START_pin,          INPUT);
  pinMode(SELECT_pin,         INPUT);
  pinMode(ORANGE_pin,         INPUT);
  pinMode(BLUE_pin,           INPUT);
  pinMode(YELLOW_pin,         INPUT);
  pinMode(RED_pin,            INPUT);
  pinMode(GREEN_pin,          INPUT);
  pinMode(UP_pin,             INPUT);
  pinMode(DOWN_pin,           INPUT);
  pinMode(BOARD_pin,          OUTPUT);
  pinMode(WITNESS_pin,        OUTPUT);

  digitalWrite(BOARD_pin, ledState);
  Serial.begin(9600);
}

void loop() 
{
  int START_state   = digitalRead(START_pin);
  int SELECT_state  = digitalRead(SELECT_pin);
  int ORANGE_state  = digitalRead(ORANGE_pin);
  int BLUE_state    = digitalRead(BLUE_pin);
  int YELLOW_state  = digitalRead(YELLOW_pin);
  int RED_state     = digitalRead(RED_pin);
  int GREEN_state   = digitalRead(GREEN_pin);
  int UP_state      = digitalRead(UP_pin);
  int DOWN_state    = digitalRead(DOWN_pin);

  if (UP_state      != last_UP_state
  ||  DOWN_state    != last_DOWN_state
  ||  ORANGE_state  != last_ORANGE_state
  ||  BLUE_state    != last_BLUE_state
  ||  YELLOW_state  != last_YELLOW_state
  ||  RED_state     != last_RED_state
  ||  GREEN_state   != last_GREEN_state
  ||  START_state   != last_START_state
  ||  SELECT_state  != last_SELECT_state)
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounce_delay) 
  {
    ledState    = LOW;
    input       = 0;
    data.color  = 0;
    data.stsel  = 0;
    data.updown = 0;
  }
  else
  {
    ledState = HIGH;
    if (UP_state      == HIGH)
    {
      if (debugging) Serial.print("<UP>");
      data.updown |= UP;
      input |= UP;
    }
    if (DOWN_state    == HIGH)
    {
      if (debugging) Serial.print("<DOWN>");
      data.updown |= DOWN;
      input |= DOWN;
    }
    if (ORANGE_state  == HIGH)
    {
      if (debugging) Serial.print("<ORANGE>");
      data.color |= ORANGE;
      input |= ORANGE;
    }
    if (BLUE_state    == HIGH)
    {
      if (debugging) Serial.print("<BLUE>");
      data.color |= BLUE;
      input |= BLUE;
    }
    if (YELLOW_state  == HIGH)
    {
      if (debugging) Serial.print("<YELLOW>");
      data.color |= YELLOW;
      input |= YELLOW;
    }
    if (RED_state     == HIGH)
    {
      if (debugging) Serial.print("<RED>");
      data.color |= RED;
      input |= RED;
    }
    if (GREEN_state   == HIGH)
    {
      if (debugging) Serial.print("<GREEN>");
      data.color |= GREEN;
      input |= GREEN;
    }
    if (START_state   == HIGH)
    {
      if (debugging) Serial.print("<START>");
      data.stsel |= START;
      input |= START;
    }
    if (SELECT_state  == HIGH)
    {
      if (debugging) Serial.print("<SELECT>");
      data.stsel |= SELECT;
      input |= SELECT;
    }
    
    if (UP_state      == LOW)
    {
      if (debugging) Serial.print("</UP>");
      if (data.stsel & UP) data.stsel -= UP;
      if (input & UP) input -= UP;
    }
    if (DOWN_state    == LOW)
    {
      if (debugging) Serial.print("</DOWN>");
      if (data.stsel & DOWN) data.stsel -= DOWN;
      if (input & DOWN) input -= DOWN;
    }
    if (ORANGE_state  == LOW)
    {
      if (debugging) Serial.print("</ORANGE>");
      if (data.color & ORANGE) data.color -= ORANGE;
      if (input & ORANGE) input -= ORANGE;
    }
    if (BLUE_state    == LOW)
    {
      if (debugging) Serial.print("</BLUE>");
      if (data.color & BLUE) data.color -= BLUE;
      if (input & BLUE) input -= BLUE;
    }
    if (YELLOW_state  == LOW)
    {
      if (debugging) Serial.print("</YELLOW>");
      if (data.color & YELLOW) data.color -= YELLOW;
      if (input & YELLOW) input -= YELLOW;
    }
    if (RED_state     == LOW)
    {
      if (debugging) Serial.print("</RED>");
      if (data.color & RED) data.color -= RED;
      if (input & RED) input -= RED;
    }
    if (GREEN_state   == LOW)
    {
      if (debugging) Serial.print("</GREEN>");
      if (data.color & GREEN) data.color -= GREEN;
      if (input & GREEN) input -= GREEN;
    }
    if (START_state   == LOW)
    {
      if (debugging) Serial.print("</START>");
      if (data.stsel & START) data.stsel -= START;
      if (input & START) input -= START;
    }
    if (SELECT_state  == LOW)
    {
      if (debugging) Serial.print("</SELECT>");
      if (data.stsel & SELECT) data.stsel -= SELECT;
      if (input & SELECT) input -= SELECT;
    }
    if (debugging) Serial.println();
    for(int i = 0; i < 9 - String(input, BIN).length(); ++i)
      Serial.print("0");
    Serial.println(input, BIN);
  }
  digitalWrite(BOARD_pin,     ledState);
  digitalWrite(WITNESS_pin,   ledState);
  delay(50);
}
