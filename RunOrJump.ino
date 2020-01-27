#include <MaxMatrix.h>

const int clk=12;
const int cs=11;
const int din=10;
const int matrixNum=2;
int btn=7;

int btnST =  HIGH;
int ST = 0;

int humanJump_Duration=0;

int RUNSPEED=300;

int barrierLoc=0;

bool GAMEOVER=false;

MaxMatrix m(din,cs,clk,matrixNum); 


void setup(){
  pinMode(btn,INPUT);
  m.init();
  m.setIntensity(1);

//  Serial.begin(9600); 
  
}

void loop(){

GAMEOVER=false;
 for(int i=15; i>= -3; i--){

    barrierLoc=i;
    
    //print barrier
    barrier(i,1);

    //check button
//    readSerialInput();
    if (digitalRead(btn) == LOW) ST = 1;
    
    //human activities choose
  if(ST == 1){

Serial.println("jumping");

    jumping_Human(1);
    delay(300);
    jumping_Human(0);

    humanJump_Duration++;

  }else {
Serial.println("running");   
    //reset this
    humanJump_Duration=0;
    
    running_Human(1);
    delay(150);
    running_Human(0);
    delay(150);
    
//GAME OVER
    if(barrierLoc == 4){
      gameOver();
      Serial.println("RUNcalled");
    }
  }


if(GAMEOVER){
  return;
}
  //delete barrier
  barrier(i,0);  
  }
  
 
}


void running_Human(int st){

  humanJump_Duration=0;

  if(st==1){
    //body
    m.setDot(2,4,1);
    m.setDot(2,5,1);
    m.setDot(2,6,1);
  
    //hand
    m.setDot(1,5,1);
    m.setDot(3,5,1);

    //leg
    m.setDot(1,7,1);
    m.setDot(3,7,1);
  
    //deleting last step (leg)
    m.setDot(2,7,0);
  }else 
  if(st==0){
  
    //leg
    m.setDot(2,7,1);
  
    //deleting last step (hand)
    m.setDot(1,5,0);
    m.setDot(3,5,0);

    //deleting last step (leg)
    m.setDot(1,7,0);
    m.setDot(3,7,0);
  }
}



void barrier(int col,int st){
  m.setDot(col,5,st);

  m.setDot(col+1,5,st);
  m.setDot(col+1,6,st);
  m.setDot(col+1,7,st);

  m.setDot(col+2,5,st);
}


void jumping_Human(int st){

  switch(humanJump_Duration){
    case 0:
      //body
    m.setDot(2,4,st);
    m.setDot(2,5,st);
    m.setDot(2,6,st);
  
    //hand
    m.setDot(3,5,st);

    //leg
    m.setDot(2,7,st);
      break;
      
    case 1:
    //body
    m.setDot(3,4,st);
    m.setDot(3,3,st);
    m.setDot(4,3,st);
    m.setDot(5,3,st);

    //hand

    //leg
    m.setDot(2,4,st);
      break;
      
    case 2:
      //body
    m.setDot(3,4,st);
    m.setDot(4,3,st);
    m.setDot(4,2,st);
    m.setDot(3,2,st);
  
    //hand

    //leg
    m.setDot(3,1,st);
      break;
      
    case 3:
      //body
    m.setDot(3,2,st);
    m.setDot(4,3,st);
    m.setDot(5,3,st);
    m.setDot(5,2,st);
  
    //hand

    //leg
    m.setDot(6,2,st);
      break;
      
    case 4:
      //body
      m.setDot(2,2,st);
      m.setDot(3,3,st);
      m.setDot(4,4,st);
  
      //hand
      m.setDot(3,2,st);

      //leg
      m.setDot(4,5,st);
//GAME OVER
      if(barrierLoc >= 2 && barrierLoc <= 5 && st == 1){
        gameOver();
        ST=0;
        Serial.println("5called");
      }
      break;
      
    case 5:
      //body
    m.setDot(3,4,st);
    m.setDot(3,5,st);
    m.setDot(3,6,st);
  
    //hand
    m.setDot(4,5,st);

    //leg
    m.setDot(3,7,st);

ST=0;
    break;
  }
}
void gameOver(){
  GAMEOVER=true;
//  Serial.println("called");
    for (int i=0; i<8; i++){
      m.setColumn(i,1);
      m.setColumn(15-i,1);
      delay(100);
    }
    for (int i=0; i<8; i++){
      m.setColumn(7-i,0);
      m.setColumn(8+i,0);
      delay(100);
    }
  }

