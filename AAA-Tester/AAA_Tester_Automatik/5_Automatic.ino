// main function for automatic operation
// position 1: loading position of AA-battery
//             move 512 steps
// position 2: measuring position
//             check if battery present or not, if not stop automatic
//             measure voltage the first time (voltageStart)
//             if voltageStart equals 0.0 batterie connect reverse, stop automatic
//             if voltageStart below compareVoltage jump badBattery
//             activate stress circuit for referenceStressTime
//             measure voltage the second time (voltageEnd)
//             deactivate stress circuit
//             if voltageEnd below compareVoltage jump badBattery
//             close trap (goog battery)
//             set badBattery to false
// badBattery: check if badBattery is true/false
//             if true open trap
//             write to SD-card
//             move 512 steps
// position 3: trap positon
//             unload battery
//             move 1024 steps in opposite direction
//start over with positon 1

void automatic(){
  boolean stopAuto = false;       // battery or no battery present 
  boolean badBattery = false;     // if true we have a bad battery
  double voltageStart;
  double voltageEnd; 
  
  while (true){     
    stepper_move(stepsLoadTest, "--> Testposition"); // move from load to test
    servo_move(trapClosed);                          // start position of trap
    stopAuto = battery_present();                    // check battery in measuring position?    
    if (stopAuto == true) {                          // there is no battery
      Serial.println(F("Automatik stopp"));
      lcd.clear(); lcd.print("Automatik");    
      lcd.setCursor(0,1);lcd.print("   Stopp!");
      delay(2000);         
      help(); 
      break;                                          // leave automatic operation     
    } 
    voltageStart = check_voltage();                   // get open-circuit-voltage
    if (voltageStart == 0.0) {                        //checking voltage and decide to test
      Serial.println(F("Batterie verpolt"));
      lcd.clear(); lcd.print("Batterie");    
      lcd.setCursor(0,1);lcd.print("   verpolt!");
      delay(2000);
      Serial.println(F("Automatik stopp"));
      lcd.clear(); lcd.print("Automatik");    
      lcd.setCursor(0,1);lcd.print("   Stopp!");
      delay(2000);       
      help(); 
      break;                                          // leave automatic operation         
    }
    if (voltageStart >= compareVoltage) {
      echo_voltage(voltageStart);      
      Serial.println(F("Teste Batterie"));
      lcd.clear(); lcd.print(F("Teste Batterie"));
      delay(1000); 
      stress_circuit();                             // start stress on battery
      delay(referenceStressTime*1000);      
      voltageEnd = check_voltage();                 // get stress-voltage 
      echo_voltage(voltageEnd);
      stress_circuit();                             // end stress on battery            
      if (voltageEnd >= compareVoltage) {
        servo_move(trapClosed);                     // trap postion good battery
        badBattery = false;          
        } else badBattery = true;          
      } else badBattery = true;               
    
    if (badBattery == true){
      Serial.println(F("Batterie leer"));
      lcd.clear(); lcd.print(F("Batterie leer"));
      delay(2000);                     
      servo_move(trapOpen);                        // trap postion bad battery      
    } else {
      Serial.println(F("Batterie gut"));
      lcd.clear(); lcd.print(F("Batterie gut"));
      delay(2000);        
      servo_move(trapClosed);                       // trap postion good battery   
    }

    // write file
    write_file(echo_time(), String(voltageStart), String(voltageEnd), String(!badBattery));

    // position 3
    delay(1000);                              // waiting for moving trap
    stepper_move(stepsTestTrap, "--> Falle"); // stepper move to trap
    delay(1000);                              // unloading AA-battery
                                              // back to loading position    
    stepper_move(-(stepsLoadTest+stepsTestTrap), "--> Ladepunkt");     
    delay(2000); 
  }           
}
