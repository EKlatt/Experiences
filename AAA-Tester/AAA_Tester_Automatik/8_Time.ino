// function for evaluating RTC
String echo_time(){
  DateTime now = rtc.now();
  String date_stamp = String(now.day(),DEC) + '.';
  date_stamp += String(now.month(),DEC) + '.';
  date_stamp += String(now.year(),DEC);
  
  String time_stamp = String(now.hour(),DEC) + ':';
  time_stamp += String(now.minute(),DEC)  + ':';
  time_stamp += String(now.second(),DEC);   
  Serial.println(date_stamp + "; "+ time_stamp); 
  lcd.clear();
  lcd.print(date_stamp);
  lcd.setCursor(0,1);lcd.print(time_stamp);
  delay(1000); 
  return date_stamp + ";" + time_stamp;
}
