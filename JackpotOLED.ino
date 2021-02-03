#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define butt 7 //Your start button

const int locat[4] = {15,55,95,14}; // Varible to set image location on screen. x of the first image, x of the second image, x of the third image and y of all images 

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
//Here it is the code that represents the pictures
//---------------------------------------------------------------------------------------------------
const unsigned char apple [] = {
  0x03, 0xc0, 0x00, 0x00, 0x40, 0x00, 0x00, 0xf0, 0x00, 0x07, 0x9c, 0x00, 0x1c, 0x07, 0x00, 0x30, 
  0x01, 0x80, 0x60, 0x00, 0x60, 0xc0, 0x00, 0x20, 0x80, 0x00, 0x10, 0xc0, 0x00, 0x10, 0x60, 0x00, 
  0x30, 0x30, 0x00, 0xe0, 0x0c, 0x01, 0x80, 0x07, 0x87, 0x00, 0x00, 0xfc, 0x00
};
const unsigned char banana [] = {
  0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0x10, 0x80, 0x00, 0x10, 0xe0, 0x00, 0x30, 0xb8, 
  0x00, 0x70, 0x8f, 0x83, 0xd0, 0xc0, 0xfc, 0x10, 0x40, 0x00, 0x30, 0x60, 0x00, 0x20, 0x30, 0x00, 
  0x60, 0x1c, 0x01, 0xc0, 0x07, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
const unsigned char fruit [] = {
  0x03, 0xfe, 0x00, 0x03, 0x1c, 0x00, 0x01, 0xb0, 0x00, 0x00, 0xa0, 0x00, 0x00, 0xe0, 0x00, 0x7f, 
  0xff, 0xf0, 0x40, 0x40, 0x10, 0x55, 0x55, 0x30, 0x60, 0x20, 0x60, 0x34, 0x8a, 0xc0, 0x1a, 0x21, 
  0x80, 0x08, 0x8b, 0x00, 0x0e, 0x26, 0x00, 0x03, 0x3c, 0x00, 0x01, 0xe0, 0x00
};
//---------------------------------------------------------------------------------------------------


void setup()   { 
  Serial.begin(9600);
  pinMode(butt, INPUT_PULLUP);
  digitalWrite(butt, HIGH);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Here set adress of your I2C screen 0x3C or 0x3D
  display.clearDisplay();
  // Display logo with sample images
  logo();
  display.drawBitmap(locat[0],locat[3], apple, 20,15, WHITE);
  display.drawBitmap(locat[1],locat[3], banana, 20,15, WHITE);
  display.drawBitmap(locat[2],locat[3], fruit, 20,15, WHITE);
  display.display();
}

void loop() {
  // Button checking to start the draw
  if(digitalRead(butt) == LOW){
    draw();
  }
}
void logo(){
  display.drawLine(0, 12, 128, 12, SSD1306_WHITE); // Draw line form x,y to x,y on the screen and color of the line
  display.drawLine(0, 30, 128, 30, SSD1306_WHITE);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(34, 0);
  display.println("$ JACKPOT $");
  display.display(); 
}
void draw(){
  byte randomNumber = 0; // Single drawn number
  int RandomNumbers[3]; // array of drawn numbers
  int win1[3] = {1,1,1}, win2[3] = {2,2,2}, win3[3] = {3,3,3}; // Define your win combinations where: apple -> 1, banana -> 2, fruit -> 3 
 
  display.clearDisplay();

  logo(); // Draw logo on the screen
  Serial.println();
  
// Here is our draw algorithm
//---------------------------------------------------------------------------
  for(int i=0; i<=2; i++){
    randomSeed(analogRead(A0)); // Use seed in a random function for better randomness
    randomNumber = byte(random(1,4));
    RandomNumbers[i]=randomNumber;
    
    Serial.print(RandomNumbers[i]); // Here you can see our numbers 
    
    // swap the drawn number to image on the screen
    switch(RandomNumbers[i]){
      case 1:
        display.drawBitmap(locat[i],locat[3], apple, 20,15, WHITE);
      break;
      case 2:
        display.drawBitmap(locat[i],locat[3], banana, 20,15, WHITE);
      break;
      case 3:
        display.drawBitmap(locat[i],locat[3], fruit, 20,15, WHITE);
      break;
    }    
   display.display(); 
  }


//Here is the part of the code that checks our drawn numbers
//--------------------------------------------------------------------------- 
  int s1=0, s2=0, s3=0;
  for(int i=0; i<=2 ; i++){
    if(RandomNumbers[i] == win1[i]){
      s1++;
      if(s1==3){
        while(digitalRead(butt)== HIGH){
          display.clearDisplay();
          display.setTextColor(WHITE);
          display.setTextSize(3);
          display.setCursor(40, 0);
          display.println("WIN");
          display.setTextSize(1);
          display.setCursor(12, 24);
          display.println("HOLD TO TRY AGAIN");
          display.display();
          delay(300);
          display.clearDisplay();
          logo();
          display.drawBitmap(locat[0],locat[3], apple, 20,15, WHITE);
          display.drawBitmap(locat[1],locat[3], apple, 20,15, WHITE);
          display.drawBitmap(locat[2],locat[3], apple, 20,15, WHITE);
          display.display();
          delay(300);
        }  
      }
    }
    else if(RandomNumbers[i] == win2[i]){
      s2++;
        if(s2==3){
          while(digitalRead(butt)== HIGH){
            display.clearDisplay();
            display.setTextColor(WHITE);
            display.setTextSize(3);
            display.setCursor(40, 0);
            display.println("WIN");
            display.setTextSize(1);
            display.setCursor(12, 24);
            display.println("HOLD TO TRY AGAIN");
            display.display();
            delay(300);
            display.clearDisplay();
            logo();
            display.drawBitmap(locat[0],locat[3], banana, 20,15, WHITE);
            display.drawBitmap(locat[1],locat[3], banana, 20,15, WHITE);
            display.drawBitmap(locat[2],locat[3], banana, 20,15, WHITE);
            display.display();
            delay(300);
          }
          
        } 
      }
    else if(RandomNumbers[i] == win3[i]){
      s3++;
        if(s3==3){
          while(digitalRead(butt)== HIGH){
            display.clearDisplay();
            display.setTextColor(WHITE);
            display.setTextSize(3);
            display.setCursor(40, 0);
            display.println("WIN");
            display.setTextSize(1);
            display.setCursor(12, 24);
            display.println("HOLD TO TRY AGAIN");
            display.display();
            delay(300);
            display.clearDisplay();
            logo();
            display.drawBitmap(locat[0],locat[3], fruit, 20,15, WHITE);
            display.drawBitmap(locat[1],locat[3], fruit, 20,15, WHITE);
            display.drawBitmap(locat[2],locat[3], fruit, 20,15, WHITE);
            display.display();
            delay(300);
          }
        } 
      }  
    }
}



