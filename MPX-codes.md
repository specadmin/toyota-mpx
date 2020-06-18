# MPX Codes #

MPX codes seem to be the same for all Toyota and Lexus cars. However some of them could be different or not be present in your model.

----

## Vehicle ##


* Body subsystems powered ("ACC" and "ON" key positions)
    `FE DF 20 00 00 00 00 00`

* Ignition ON  ("ON" key position)
    `FE DF 40 00 00 00 00 00` (from body MCU)



* Parking brake on  
    `FE DF 80 00 00 00 00 00`

* Brake pedal pushed  
    `FE E4 04 00`

* Tail light is on  
    `FE E4 10 00`

* Head light is on  
    `FE E4 20 00`

* Front fog light is on  
    `FE E4 00 04`

* Rear fog light is on  
    `FE E4 08 00`

* Driver's seatbelt is not fastened  
    `FE E4 00 80`

* VSC warning indicator ON (combination meter)
    `45 D0 00 08 00 00`

* ABS warning indicator ON (combination meter)
    `45 D0 00 10 00 00`

* Check engine indicator ON (combination meter)
    `45 D0 00 20 00 00`



## Engine ##

* Engine temperature (temp = data / 2, degrees Celsium)  
    `FE 2C B5`

* Low oil pressure  
    `FE D4 10`

* Battery powered  
    `FE D4 20`

* Tachometer value (RPM = data / 512 * 100)  
    `D2 26 13 B0`

* Momentary fuel rate (fuel rate = data / 100, L/h)  
    `46 20 01 85`

* Momentary fuel rate (fuel rate = data / 10, L/100km)  
    `45 90 01 36`

* Average fuel rate (fuel rate = data / 10, L/100km)  
    `45 A3 00 76`




## Transmission ##

### A/T selector's position ###

* A/T selector "L"  
    `FE 40 01 00`

* A/T selector "2"  
    `FE 40 02 00`

* A/T selector "D"  
    `FE 40 10 00`

* A/T selector "N"  
    `FE 40 20 00`

* A/T selector "R"  
    `FE 40 40 00`

* A/T selector "P"  
    `FE 40 80 00`


### A/T options ###

* "ECT SNOW" mode on  
    `46 D2 10 00 00`

* "ECT PWR" mode on (if present)  
    `46 D2 20 00 00`



## Doors Status ##

### Driver's Door Status ###

* Driver's door unlocked  
    `FE DB 10 00`

* Driver's door opened  
    `FE DB 20 00`

* Driver's door unlock button pushed  
    `FE DB 40 40`

* Driver's door lock button pushed  
    `FE DB 40 80`

* Driver's door warning or status changed (not sure)  
    `FE DB 80 00`

* Driver's door key turned to unlock  
    `FE DB 01 00`

* Driver's door key turned to lock  
    `FE DB 02 00`

* Power windows locked by driver's door button  
    `FE DB 00 20`



### Front Passenger's Door Status ###

* Front passenger's door unlocked  
    `FE DC 10 00`

* Front passenger's door opened  
    `FE DC 20 00`

* Front passenger's door unlock button pushed  
    `FE DC 40 40`

* Front passenger's door lock button pushed  
    `FE DC 40 80`

* Front passenger's door warning or status changed (not sure)  
    `FE DC 80 00`

* Front passenger's door key turned to unlock  
    `FE DC 01 00`

* Front passenger's door key turned to lock  
    `FE DC 02 00`



### Rear Right Door Status ###

* Rear right door unlocked  
    `FE DD 10`

* Rear right door opened  
    `FE DD 20`




### Rear Left Door Status ###

* Rear left door unlocked  
    `FE DE 10`

* Rear left door opened  
    `FE DE 20`



### Back (5-th) Door Status ###

* Back door unlocked
    `E0 96 10`

* Back door opened (not sure)  
    `FE DF 10 00 00 80 00 00`



## Doors control ##

* Driver's door unlock button pushed  
    `FE DB 40 40`

* Driver's door lock button pushed  
    `FE DB 40 80`

* Driver's door key turned to unlock  
    `FE DB 01 00`

* Driver's door key turned to lock  
    `FE DB 02 00`

* Front passenger's door unlock button pushed  
    `FE DC 40 40`

* Front passenger's door lock button pushed  
    `FE DC 40 80`

* Front passenger's door key turned to unlock  
    `FE DC 01 00`

* Front passenger's door key turned to lock  
    `FE DC 02 00`




## Power windows control ##

All power windows are controlled by the one command (see bellow). The following data bytes order is used: front right, rear right, rear left, front left.

* Close all windows (repeat the command until it is required)  
    `D1 E0 40 40 40 40`

* Close all windows in auto mode  
    `D1 E0 60 60 60 60`

* Open all windows (repeat the command until it is required)  
    `D1 E0 80 80 80 80`

* Open all windows in auto mode  
    `D1 E0 A0 A0 A0 A0`



## Climate Satus ##

* Outside temperature (temp = data - 48, degrees Celsium)  
    `FE CD 41`

* Target inside temperature (temp = 16 + data / 2, degrees Celsium)  
    `45 FD 21`

* "Max cold" target inside temperature  
    `45 FD 00`

* "Max hot" target inside temperature  
    `45 FD 37`

* Target inside temperature initialization  
    `45 FD 38`

* Climate control is switched off  
    `45 FD 39`

* Blow direction on windshield and feet  
    `45 FC 00 40`

* Blow direction on feet only  
    `45 FC 00 20`

* Blow direction on head only  
    `45 FC 00 80`

* Blow direction on head and feet  
    `45 FC 01 00`

* Air conditioner on  
    `45 FC 02 00`

* Blow direction on windshield only  
    `45 FC 10 00`

* Recycling mode  
    `45 FC 20 00`

* AUTO mode  
    `45 FC 80 00`

* Blower motor speed level (bits 5...7, 0xB0 = level 6)  
    `45 1B B0`

* Back glass heater on  
    `D2 D7 20`



## Climate Control Actions (Control Panel) ##

* No buttons pushed  
    `D2 15 00`

* Any button pushed  
    `D2 15 01`

* "OFF" button pushed  
    `D2 15 41`

* "FRONT" glass heater button pushed  
    `D2 15 11`

* Back glass heater button pushed  
    `D2 15 09`

* Recycling button pushed  
    `D2 15 21`

* "A/C" button pushed  
    `D2 15 05`

* "AUTO" button pushed  
    `D2 15 81`

* Temp encoder turn CW (1...3 -- the ammount of steps, works only when ignition is on)  
    `46 1A 81`  
    `46 1A 82`  
    `46 1A 83`  

* Temp encoder turn CCW (1...3 -- the ammount of steps, works only when ignition is on)  
    `46 1A 01`  
    `46 1A 02`  
    `46 1A 03`  

* Blower motor speed encoder turn CW (1...3 -- the ammount of steps, works only when ignition is on)  
    `46 1A 00 81`  
    `46 1A 00 82`  
    `46 1A 00 83`  

* Blower motor speed encoder turn CCW (1...3 -- the ammount of steps, works only when ignition is on)  
    `46 1A 00 01`  
    `46 1A 00 02`  
    `46 1A 00 03`  
