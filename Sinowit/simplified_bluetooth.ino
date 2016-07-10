
int serialflag=0;
int numOrange=0;
int numGreen=0;


//void setup() {
//  // put your setup code here, to run once:
//Serial.begin(9600);
//Serial1.begin(9600);
//Serial1.setTimeout(100);
//}
 void writeblue(String writein)
 {
    Serial1.print(writein);
	Serial1.flush();
    Serial.println(writein);
	Serial.flush();
	delay(1000);
  }
 void readblue() 
 {
	 if (Serial1.available() > 0)
	 {
		 Serial.println("bt");
		 readin = Serial1.readStringUntil('#');
		 
	 //readin.&at(0);
		 Serial.println(readin);
	     
		 Serial.flush();
	// serialflag++;      
     }
//        if (readin[0]!='X'){
//        Serial.print(readin[0]);
//        Serial.println(readin[1]);}
        //Car2 choices
   //     if(readin[0]=='B'){    //begin
   //       startwork = 1;
   //     }else if (readin[0]=='G'){
   //       numGreen=int(readin[1]);
   //       Serial.print("we have green");
   //       Serial.println(readin[1]);
   //     }else if (readin[0]=='O'){
   //       numOrange=int(readin[1]);
   //       Serial.print("we have orange");
   //       Serial.println(readin[1]);
   //     }else if (readin[0]=='R'){//rotation
   //     //延时10s合上中间板
			//continuework = 1;
   //     }
   //     //Car1 choices
   //     if(readin[0]=='A'){    //car2 arrived
   //       car2arr = 1;
   //     }else if (readin[0]=='C'){    //Copy
   //       //go on send another.
   //     }
        //readin[0]='X';
        //readin[1]='X';
        //serialflag=0;
 }
//void test()
//{
//
//    writeblue("A#");
//    delay(1000);
//    writeblue("G");
//    writeblue("3");
//    writeblue("#");
//    delay(1000);
//    writeblue("O5#");
////writeblue('5');
//    delay(1000);
////writeblue('B');
//    delay(1000);
//}
//void loop() {
//  // put your main code here, to run repeatedly:
//  readblue();
////test();
//
//}
