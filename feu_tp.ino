const int VERT_1 = 2; 
const int JAUNE_1 = 3;
const int ROUGE_1 = 4;

const int VERT_2 = 5; 
const int JAUNE_2=6;
const int ROUGE_2 = 7;  

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(VERT_1, OUTPUT); pinMode(JAUNE_1, OUTPUT); pinMode(ROUGE_1, OUTPUT);   
  pinMode(VERT_2, OUTPUT); pinMode(JAUNE_2, OUTPUT); pinMode(ROUGE_2, OUTPUT); 
   
}

int stateFeu1 = 0; 
int stateFeu2 = 2; 
// 0: vert
// 1: jaune
// 2: rouge
const int delayVert = 7000;
const int delayOrange = 3000;
long currentMillis = millis();

void loop() {
  // put your main code here, to run repeatedly:
  long now = millis(); 
  if(stateFeu1==0){
    if(now-currentMillis>=delayVert){
      stateFeu1 = 1;
      stateFeu2 = 0;
      currentMillis = now;
    }
  }else if(stateFeu1==1){
    if(now-currentMillis>=delayOrange){
      stateFeu1 = 2;
      stateFeu2 = 0;
      currentMillis = now;
    }
  }else{
    if(stateFeu2==0){
      if(now-currentMillis>=delayVert){
            stateFeu1 = 2;
            stateFeu2 = 1;
            currentMillis = now;
      }
    }else {
        if(now-currentMillis>=delayOrange){
          stateFeu1 = 0;
          stateFeu2 = 2;
          currentMillis = now;
        }
    } 
  } 
  Serial.println("restart ");
  Serial.println(stateFeu2);
  setState();  

} 

void setState(){
  if(stateFeu1==0){
    //mettre feu 2 au rouge || orange;  
    
    switchOn(VERT_1);
    switchOn(ROUGE_2);
    
    switchOff(JAUNE_1);
    switchOff(ROUGE_1); 
    switchOff(VERT_2);  
    switchOff(JAUNE_2); 
  }else if(stateFeu1==1){
    //mettre feu 2 au rouge;  
    switchOn(JAUNE_1);
    switchOn(ROUGE_2);
    
    switchOff(VERT_1);
    switchOff(ROUGE_1); 
    switchOff(JAUNE_2); 
    switchOff(VERT_2); 
  }else if(stateFeu1==2){
    //mettre feu 2 au vert;
    
    if(stateFeu2==0){
      switchOn(VERT_2);
      switchOff(JAUNE_2); 
    }else{
      switchOn(JAUNE_2);
      switchOff(VERT_2); 
    }
    switchOn(ROUGE_1);
    
    switchOff(VERT_1);
    switchOff(JAUNE_1); 
    switchOff(ROUGE_2);  
     
  } 
}

void switchOff(int led){ 
    digitalWrite(led, HIGH);
}


void switchOn(int led){ 
    digitalWrite(led, LOW);
}

