 //******************************  
 // Potenciometro com memoria  
 // http://www.pakequis.com.br  
 //******************************  
 #include <AFMotor.h>  
   
 const int Min_Value = 5;   //Valor minimo da leitura do potenciometro  
 const int Max_Value = 65000; //Valor maximo da leitura do potenciometro  
   
 AF_DCMotor motor(1);  //Define motor para a saida 1 do shield  
 int KeyStatus = 0;      //Valor da tecla  
 unsigned int Mem_Value = 0; //Valor memorizado do potenciometro  
   
 void setup(){  
  motor.setSpeed(200); //Velocidade maxima  
  motor.run(RELEASE);  //Desativa o motor  
 }  
   
 void loop(){  
  KeyStatus = analogRead(A4);  //Verifica a tecla de memoria  
   
  if (KeyStatus > 950){    //Tecla pressionada?  
   Mem_Value = AvgMeasure();  //Memoriza o valor do potenciometro  
   if(Mem_Value > Max_Value){  //Verifica se ultrapassou os limites  
    Mem_Value = Max_Value;   //Limite maximo atingido  
   }  
   if(Mem_Value < Min_Value){  
    Mem_Value = Min_Value;   //Limite minimo atingido  
   }  
   KeyStatus = 0;        //volta ao estado de tecla nao pressionada  
  }  
   
  KeyStatus = analogRead(A2);      //Verifica tecla de recuperar memoria  
  if (KeyStatus > 950){         //Tecla pressionada?  
   if (Mem_Value > AvgMeasure()){    //  
    while(Mem_Value >= AvgMeasure()){ //Ateh chegar na posicao correta  
     //Serial.println(analogRead(A0));  
     motor.run(FORWARD);       //aciona o motor  
    }    
    motor.run(RELEASE);        //Desliga o motor  
    delay(250);            //250ms de atraso  
   }else{  
    while(Mem_Value <= AvgMeasure()){ //Ateh chegar na posicao correta  
     motor.run(BACKWARD);       //Aciona o motor  
    }  
    motor.run(RELEASE);        //Desliga o motor  
    delay(250);            //250ms de atraso  
   }  
   KeyStatus = 0;        //volta ao estado de tecla nao pressionada  
  }  
 }  
   
 //Calcula a media de 64 amostras da entrada A0  
 //(de 10 bits para 16 bits)  
 unsigned int AvgMeasure(){  
  int i;  
  unsigned int Temp = 0;  
  for (i=0;i<64;i++){  
   Temp += analogRead(A0); //Soma 64 amostras do A0  
  }  
  return Temp; //Retorna valor da media  
 }  