/*ºÍÖ÷»úÉèÖÃ²î²»¶à£¬²»¹ý²»ÓÃ¸ø¶¨´Ó»úµÄµØÖ·ºÍ¿ªÆô×Ô¶¯Á¬½Ó¡£ÉèÖÃ·½·¨Í¬Ö÷»ú£¬Òª±£³ÖµçÄÔµÄ´®¿ÚÈí¼þ¹Ø±Õ*/
#define AT 2
#define LED 13
void setup()
{
	pinMode(LED, OUTPUT);
	pinMode(AT, OUTPUT);
	digitalWrite(AT, HIGH); //ATµÄµçÆ½¸ø¸ß£¬ÓÃÓÚÊäÈëATÖ¸Áî
	Serial.begin(9600);//ÕâÀïÓ¦¸ÃºÍÄãµÄÄ£¿éÍ¨ÐÅ²¨ÌØÂÊÒ»ÖÂ
	delay(100);
	Serial.println("AT");
	delay(100);
	Serial.println("AT+NAME=Sinowit_Slave");//ÃüÃûÄ£¿éÃû
	delay(100);
	Serial.println("AT+ROLE=0");//ÉèÖÃÖ÷´ÓÄ£Ê½£º0´Ó»ú£¬1Ö÷»ú
	delay(100);
	Serial.println("AT+PSWD=0000");//ÉèÖÃÅä¶ÔÃÜÂë£¬Èç1234
	delay(100);
	Serial.println("AT+UART=9600,0,0");//ÉèÖÃ²¨ÌØÂÊ9600£¬Í£Ö¹Î»1£¬Ð£ÑéÎ»ÎÞ
	delay(100);
	Serial.println("AT+RMAAD");//Çå¿ÕÅä¶ÔÁÐ±í
}
void loop()
{
	digitalWrite(LED, HIGH);
	delay(500);
	digitalWrite(LED, LOW);
	delay(500);
}
98d3:32:7092df
Serial.println("AT+BIND=0012,08,060146");//Éè¶¨´Ó»úµÄµØÖ·£¬±£³Ö¸ñÊ½Ò»ÖÂ¡£


