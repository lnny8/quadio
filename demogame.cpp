//very simple memory game code, will be changed when the board is assembled

#include <Adafruit_NeoPixel.h>

// C++

Adafruit_NeoPixel pixels(4, 9, NEO_GRB + NEO_KHZ800);

void setup()
{
  setupPins();
  startGame();
}

const int maxCount = 10;
int stepSize = 2;
int arr[maxCount] = {0,3,1,3,2,4,3,1,2,0};
int onTime = 300;
int betweenTime = 400;

int rgbForIndex[4][3] = {
  {255, 0, 0},    // rot
  {0, 0, 255},    // blau
  {0, 255, 0},    // grün
  {255, 255, 0}   // gelb
};

void loadArray() {
  for(int i=0;i<maxCount-1;i++){
  	arr[i] = random(0,4);
  }
}

void startGame() {
  //loadArray();
  allBlink(0,255,255);
  delay(500);
  for(int count=stepSize; count<=maxCount; count+=stepSize) {
  	blinkTillIndex(count);
    int inputArr[count];
    for(int j=0;j<count;j++) {
      inputArr[j] = waitUserInput();
      if(!validateUserInput(inputArr, arr, j)) {
        allBlink(255, 0, 0);
        delay(500);
        startGame();
        return;
      }
      delay(500);
     }

  }
  allBlink(255, 255, 255);
}

boolean validateUserInput(int userInput[], int real[], int index) {
  boolean validInput = true;
  if(userInput[index] != real[index]) validInput = false;
  return validInput;
}

void loop() {
  delay(10); // delay for performance
}

int waitUserInput() {
  int buttonPressed = 0;
  while(buttonPressed == 0) {
    if(digitalRead(5) == LOW) buttonPressed = 0;
    if(digitalRead(6) == LOW) buttonPressed = 1;
    if(digitalRead(7) == LOW) buttonPressed = 2;
    if(digitalRead(8) == LOW) buttonPressed = 3;
  }
  //wait till released
  while(digitalRead(buttonPressed+4)==LOW){}
  return buttonPressed;
}

void blinkTillIndex(int endIndex) {
  for(int i=0;i<endIndex;i++) {
    int r = rgbForIndex[i][0];
    int g = rgbForIndex[i][1];
    int b = rgbForIndex[i][2];
    blinkLamp(arr[i], r, g, b);
  }
}

void blinkLamp(int index, int r, int g, int b) {
  	pixels.setPixelColor(index, pixels.Color(r,g,b));
  	pixels.show();
  	delay(onTime);
    pixels.setPixelColor(index, pixels.Color(0,0,0));
    pixels.show();	
    delay(betweenTime);
}

void allBlink(int r, int g, int b){
  	pixels.setPixelColor(0, pixels.Color(r,g,b));
    pixels.setPixelColor(1, pixels.Color(r,g,b));
    pixels.setPixelColor(2, pixels.Color(r,g,b));
    pixels.setPixelColor(3, pixels.Color(r,g,b));
    pixels.show();
  	delay(onTime);
    pixels.setPixelColor(0, pixels.Color(0,0,0));
    pixels.setPixelColor(1, pixels.Color(0,0,0));
    pixels.setPixelColor(2, pixels.Color(0,0,0));
    pixels.setPixelColor(3, pixels.Color(0,0,0));
    pixels.show();
    delay(betweenTime);
}

void setupPins() {
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, OUTPUT);
}

void test() {
  for (int i=0;i<=3;i++) {
    if (digitalRead(i+5) == LOW) {
      int r = rgbForIndex[i][0];
      int g = rgbForIndex[i][1];
      int b = rgbForIndex[i][2];
      pixels.setPixelColor(i, pixels.Color(r,g,b));
    }
  	else pixels.setPixelColor(i, pixels.Color(0,0,0));
    pixels.show();
  }
}
