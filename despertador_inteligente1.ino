#include<LiquidCrystal.h>
#define PIN_RS 2
#define PIN_E 3


//Direccion al Circuito
//https://www.tinkercad.com/things/8Fo2gibJ8e7-despertador-inteligente/editel
//



LiquidCrystal lcd(PIN_RS, PIN_E, 4 ,5, 6, 7);
int contadorHoras=18;
int contadorMinutos=30;
int contadorSegundos =00;// Hora de cursar XD
int pulsador;
int pulsadorMas;
int pulsadorMenos;
float temperatura =0;
float temperaturaF=0;
int pulsadorTemp = A0;
unsigned long millisAntes=0;
unsigned long millisAhora=0;
int estadoTemp=0;
int estadoSalida=0;
int contador=0;
int control =0;
int controlF=0;
int contadorF = 0;
int controlH=0;
int controlS=0;
int contadorS=0;
int contadorH=0;
int controlM=0;
int contadorM=0;
int flagZ = 0;
int estadoSet=0;
int alarmaSet=0;
int flagAlarma=0;
int contadorAlarma=0;
int flagBloqueoBoton=0;
int flagSetTime=0;
int contadorSeteoReloj=0;
int flagAl=0;
int flagHr=0;

void setup()
{
Serial.begin(9600);
pinMode(A0,INPUT);
lcd.begin(16,2);
lcd.setCursor(6,0);
lcd.print(":");
lcd.setCursor(9,0);
lcd.print(":");
pinMode(13, OUTPUT); 
pinMode(A2, INPUT);
pinMode (A3, INPUT);
pinMode (A4, INPUT);
}

  
void loop()
{
  delay(20);
  temperatura = map(analogRead(A1),0,1023,-5000,45000);
  temperatura = temperatura/100.00;
  temperaturaF = temperatura *1.8 + 32;
  estadoTemp = analogRead(pulsadorTemp);

   
   //TEMPERATURA
  
   temperaturaLeds();
   celciusFahrenheitSwitch();
   celciusFahrenheitDisplay();
   celciusFahrenheitRefresh();
  
   //TEMPERATURA
  
  
   //MILLIS
  
   millisAhora = millis();
   if(millisAhora - millisAntes >1000)
   {        
    
    millisReloj();
    millisSegundos();
    millisMinutos();
    millisHoras();
    contadorSegundos++;
    contadorAlarma++;
    millisAntes = millisAhora;
     
    }
  
  	//MILLIS
  

    //ALARMA

    horasAlarma();           
    minutosAlarma();
    setAlarma();
    alarma();

    //ALARMA

       
}//LOOP



//// Alarma / Sonido  On/Off
  void alarma()
  {
    if(contadorHoras == contadorH && contadorMinutos == contadorM && estadoSet==1 && flagSetTime==0)
  	{
      	
 	  if(flagAlarma)
      {
        lcd.setCursor(0,1);
 		lcd.print("                ");
        flagAlarma=0;
        flagBloqueoBoton=1;
        contadorAlarma=0;
      }
       
         lcd.setCursor(5,1);
  		 lcd.print("ALARMA");

	   if(contadorSegundos %2 == 0 )
       {
         digitalWrite(13, LOW);
       }
       else
       {
         digitalWrite(13, HIGH);    
       }
  	   if(contadorAlarma==30)
       {
         digitalWrite(13, LOW);
         alarmaSet=1;
         estadoSet=2;
         flagBloqueoBoton=0;
       }
    }
   if(alarmaSet==1)
   {
      lcd.setCursor(5,1);
  	  lcd.print("                ");    
      digitalWrite(13, LOW);
      alarmaSet=0;
      flagBloqueoBoton=0;   
   }
}



//Seteo de la alarma
void setAlarma()
{ 
   if(estadoTemp > 485 && estadoTemp < 536 && controlS != estadoTemp ){
  
      flagZ=1; 
     
      contadorSeteoReloj++;
     
      if(contadorSeteoReloj==1 || flagAl==0)
      {
       lcd.setCursor(0,1);
       lcd.print("                ");
       lcd.setCursor(0,1);
       lcd.print("Set:         AL");
       flagAl = 1;
       flagHr = 1;
       flagSetTime = 0;
      }
      else
      {
        if(flagHr==1)
        {
          lcd.setCursor(0,1);
          lcd.print("                ");
          lcd.setCursor(0,1);
          lcd.print("Set:         Hr");
          flagHr = 0;
          flagAl = 0;
          flagSetTime = 1;
        }
      }
     
      contador++;
      estadoSet=0;
     
     
 	if(contador %2 == 0)
    {
       lcd.setCursor(0,1);
       lcd.print("                 ");
       estadoSalida = 0;
       alarmaSet=1;
            
     }
     else
     {
        estadoSet=1;
        flagAlarma=1;
     }
          
   }
  controlS = estadoTemp;
}


//Ajustar Minutos Alarma  /  Reloj
void minutosAlarma()
{
    if(estadoTemp > 694 && estadoTemp < 767 && controlM != estadoTemp && flagZ==1 && estadoSet==1 && flagBloqueoBoton==0)
    { 
      
      contadorM++;
      if(flagSetTime==1)
      {
        contadorMinutos=contadorM;
      }
       
      if(contadorM ==60)
      {
       contadorM=0;
      }
      if(contadorM<10)
   		 {
           lcd.setCursor(8,1);
           lcd.print(contadorM);
           lcd.setCursor(7,1);
      	   lcd.print(0);
         }
         else
           {
           lcd.setCursor(7,1);
           lcd.print(contadorM);  
           }
      lcd.setCursor(6,1);
      lcd.print(":");
      }
  
  controlM = estadoTemp;
  
}


//Ajustar Horas Alarma  /  Reloj
void horasAlarma()
{
   if(estadoTemp > 583 && estadoTemp < 644 && controlH != estadoTemp && estadoSet==1 && flagBloqueoBoton==0)
     {
       contadorH++;
     
       if(flagSetTime==1)
       {
        contadorHoras=contadorH;
       }
     
       if(contadorH ==24)
       {
       contadorH=0;
       }
       if(contadorH<10)
   		 {
           lcd.setCursor(5,1);
           lcd.print(contadorH);
           lcd.setCursor(4,1);
      	   lcd.print(0);
         }
         else
           {
           lcd.setCursor(4,1);
           lcd.print(contadorH);  
           }
        lcd.setCursor(6,1);
        lcd.print(":");

         if(contadorH >=0 && contadorH <12)
         {
           lcd.setCursor(9,1);
           lcd.print(".am");
         }
         else
         {
           lcd.setCursor(9,1);
           lcd.print(".pm");
         }
      }
  controlH = estadoTemp;
}


//Display de horas en el reloj
void millisHoras()
{
     if(contadorHoras<10)
     { 
        lcd.setCursor(5,0);
        lcd.print(contadorHoras);
        lcd.setCursor(4,0);
      	lcd.print(0);
      }
      else
      {
        lcd.setCursor(4,0);
        lcd.print(contadorHoras);  
      }
}


//Display de minutos en el reloj
void millisMinutos()
{
        
  	if(contadorMinutos<10)
  	  {
    
       lcd.setCursor(8,0);
       lcd.print(contadorMinutos);
       lcd.setCursor(7,0);
  	   lcd.print(0);
      }
       else
       {
       lcd.setCursor(7,0);
       lcd.print(contadorMinutos);  
       }
 }



//Display de segundos en el reloj
void millisSegundos()
{
         
      if(contadorSegundos<10)
 	  {
        lcd.setCursor(11,0);
        lcd.print(contadorSegundos);
        lcd.setCursor(10,0);
        lcd.print(0);	
 	   }
       else
       {
         lcd.setCursor(10,0);
         lcd.print(contadorSegundos);   
       }
 }



//Conteo de horas/minutos/segundos en el reloj
void millisReloj()
{
     if(contadorSegundos >59)
     {
        contadorSegundos=0;
        contadorMinutos++;

        if(contadorMinutos ==60)
        {
           contadorHoras++;
           contadorMinutos=0;
        }
        if(contadorHoras==24)
        {
            contadorHoras=0;
        }
      }
 }


//Mantiene el refresh para mostrar cambios de temperatura en vivo
void celciusFahrenheitRefresh()
{
     if(estadoSalida == 1 && estadoTemp > 1000)
  	 {
      	if(contadorF %2 ==0)
     	{
         lcd.setCursor(2,1);
         lcd.print("Temp:");
         lcd.setCursor(7,1);
         lcd.print(temperaturaF);
         lcd.setCursor(13,1);
         lcd.print("F");  
     	 }
         else
         {
           lcd.setCursor(2,1);
           lcd.print("Temp:");
           lcd.setCursor(7,1);
           lcd.print(temperatura);
           lcd.setCursor(13,1);
           lcd.print("C");
         }  
  	  }
 }


//Display de temperatura en C o F
void celciusFahrenheitDisplay()
{
      if(estadoTemp>795 && estadoTemp<878 && control != estadoTemp && flagBloqueoBoton==0)
      {
           flagZ=2;
           lcd.setCursor(0,1);
           lcd.print("                ");
         if(contadorF %2 ==0)
         {
              lcd.setCursor(2,1);
              lcd.print("Temp:");
              lcd.setCursor(7,1);
              lcd.print(temperaturaF);
              lcd.setCursor(13,1);
              lcd.print("F");  
          }
          else
          {
              lcd.setCursor(2,1);
              lcd.print("Temp:");
              lcd.setCursor(7,1);
              lcd.print(temperatura);
              lcd.setCursor(13,1);
              lcd.print("C");
           }
        
               contador++;
    
            if(flagSetTime>=0)
            {
              contadorM = 0;
              contadorH = 0;
            }
               estadoSalida = 1;  

            if(contador %2 == 0)
            {
               lcd.setCursor(0,1);
               lcd.print("                 ");
               estadoSalida = 0;      
            } 
         }
         control = estadoTemp;
}


//Switch entre modalidades de temperatura
void celciusFahrenheitSwitch()
{
       if(estadoTemp>694 && estadoTemp<767 && controlF != estadoTemp && flagZ ==2)
       {
         contadorF++;   
       }
  		controlF = estadoTemp;  
 }



//Seteo de leds para desplegar color segun rangos termicos
void temperaturaLeds()
{
      	  
       if(temperatura<20)
       {
         digitalWrite(A2, HIGH);
         digitalWrite(A3, LOW);
         digitalWrite(A4, LOW);
       }
       else if(temperatura>19 && temperatura <26)
       {
          digitalWrite(A3, HIGH);
          digitalWrite(A2, LOW);
          digitalWrite(A4, LOW);
       }
       else if(temperatura>25)
       {
           digitalWrite(A4, HIGH);
           digitalWrite(A2, LOW);
           digitalWrite(A3, LOW);
       }
  }