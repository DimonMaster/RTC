// Для того чтобы настроить время на модуле его нужно вписать в монитор порта 
// Например: 29/01/2024 16:05:00



#include <DS1307RTC.h>

#include <Time.h>

#include <Wire.h>	  


String inSer = "";

boolean strFull = false;

tmElements_t datetime;

	  


void setup() {

	Serial.begin(9600);

}

	  


void loop() {

	// пришли данные по serial


	if (strFull) {

  datetime.Hour=(int(inSer[11])-48)*10+(int(inSer[12])-48);

	datetime.Minute=(int(inSer[14])-48)*10+(int(inSer[15])-48);

	datetime.Second=(int(inSer[17])-48)*10+(int(inSer[18])-48);

	datetime.Day=(int(inSer[0])-48)*10+(int(inSer[1])-48);

	datetime.Month=(int(inSer[3])-48)*10+(int(inSer[4])-48);

	datetime.Year=CalendarYrToTm((int(inSer[6])-48)*1000+(int(inSer[7])-48)*100+(int(inSer[8])-48)*10+(int(inSer[9])-48));


	RTC.write(datetime); // записать данные в DS3231

	// очистить строку

	inSer = "";

	strFull = false;

  }



// получение данных из ds3231

	if (RTC.read(datetime)) {

	print2(datetime.Hour, ":");

	print2(datetime.Minute, ":");

	print2(datetime.Second, " ");

	print2(datetime.Day, "/");

	print2(datetime.Month, "/");

  print2(tmYearToCalendar(datetime.Year) ,"");

	Serial.println();

	}



	else {

	Serial.print("error");

	delay(5000);

	}

	delay(1000);

}



void print2(int nn,String str) {

	(nn >= 0 && nn < 10);

	//{ Serial.print("0");}

	Serial.print(nn);

	Serial.print(str);

}



void serialEvent() {


	while (Serial.available()) {

	// получить очередной байт:

	char c = (char)Serial.read();

	// добавить в строку

	inSer += c;


	// /n - конец передачи


	if (c == '\n')

	  { strFull = true;}

	  }

}

