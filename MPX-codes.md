# Toyota and Lexus MPX packets descrition #

MPX packets seem to be the same for all Toyota and Lexus cars. However some of them could be different or may be not present in your model. All the information, that is listed bellow, was recognized experimentally and do not pretend to be complete or exact. You may use this information on your own risk. If you have any additions or issues, please contact me: ton (at) specadmin.ru.

<br>

### 0x15 ##

<table>
    <tr>
        <td rowspan=9> byte0 </td>
    </tr>
    <tr> 
        <td> bit7 </td>
        <td> Climate control "AUTO" button pushed </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> Climate control "OFF" button pushed </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> Climate control recycling button pushed  </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> Climate control "FRONT" (windshield) button pushed </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> Climate control back glass heater button pushed </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td> Climate control "A/C" button pushed </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> Climate control "MODE" button pushed </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> Any button pushed on control panel </td> 
    </tr>
</table>

Example: `D2 15 81` -- climate control "AUTO" button pushed

<br>



### 0x17 ##

<table>
    <tr>
        <td rowspan=9> byte0 </td>
    </tr>
    <tr> 
        <td> bit7 </td>
        <td> </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td>  </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
</table>

Example: `46 17 60`

<br>



### 0x1A ###

<table>
    <tr>
        <td rowspan=9> byte0 </td>
    </tr>
    <tr> 
        <td> bit7 </td>
        <td> Climate control "TEMP" encoder rotate direction (1 - CW, 0 - CCW) </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td rowspan=4> The ammount of steps, rotating climate control "TEMP" encoder</td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
    </tr>
    <tr> 
        <td> bit1 </td>  
    </tr>
    <tr> 
        <td> bit0 </td>  
    </tr>
    <tr>
        <td rowspan=9> byte1 </td>
    </tr>  
    <tr> 
        <td> bit7 </td>
        <td> Climate control blower motor speed encoder rotate direction (1 - CW, 0 - CCW) </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td rowspan=4> The ammount of steps, rotating climate control blower motor speed encoder</td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
    </tr>
    <tr> 
        <td> bit1 </td>  
    </tr>
    <tr> 
        <td> bit0 </td>  
    </tr>
</table>

* Works only when ignition is ON

Example: `46 1A 82 00` -- climate control "TEMP" encoder rotated CW

<br>


### 0x1B ##

<table>
    <tr>
        <td rowspan=9> byte0 </td>
    </tr>
    <tr> 
        <td> bit7 </td>
        <td rowspan=3> Climate control blower motor speed level </td> 
    </tr>
    <tr> 
        <td> bit6 </td>          
    </tr>
    <tr> 
        <td> bit5 </td>  
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> Climate control blower motor ON </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
</table>

Example: `45 1B B0` -- climate control blower motor speed level 6

<br>



### 0x20 ###

<table>
    <tr>
        <td> byte0 </td>
        <td rowspan=2> Momentary fuel rate per time (0.01 L/h), big-endian </td>
    </tr>
    <tr>
        <td> byte1 </td>
    </tr>
</table>

Example: `46 20 07 40` -- momentary fuel rate 18.56 L/h

<br>



### 0x24 ##

<table>
    <tr>
        <td> byte0 </td>
        <td colspan=2> Vehicle speed (km/h) </td>        
    </tr>
    <tr>
        <td rowspan=9> byte1 </td>
    </tr>
    <tr> 
        <td> bit7 </td>
        <td> Combination meter power ON </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
</table>

Example: `FE 24 23 80` -- vehicle speed 35 km/h, ignition is ON

<br>



### 0x25 ###

<table>
    <tr>
        <td> byte0 </td>
        <td rowspan=2 colspan=2> Average vehicle speed (see Note for units description), big-endian </td>
    </tr>
    <tr>
        <td> byte1 </td>
    </tr>
    <tr>
        <td rowspan=9> byte2 </td>
    </tr>  
    <tr> 
        <td> bit7 </td>
        <td> 0.1 km/h </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> 0.1 MPH </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td>  </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
</table>

Note: units are defined in byte2 (if it is present) or in [0x6A](#0x6A) packet.

Example: `45 25 02 FC 80` -- average vehicle speed 76.4 km/h

<br>



### 0x26 ###

<table>
    <tr>
        <td> byte0 </td>
        <td rowspan=2> Tachometer value (5.12 RPM), big-endian </td>
    </tr>
    <tr>
        <td> byte1 </td>
    </tr>
</table>

Example: `D2 26 1D 04` -- tachometer value ~ 1450 RPM

<br>




### 0x2C ###

<table>
    <tr>
        <td> byte0 </td>
        <td> Engine temperature (0.5 Celsius degrees) </td>
    </tr>
</table>

Example: `FE 2C A1` -- engine temperature 80.5 Celsius degrees

<br>



### 0x40 ###

<table>
    <tr>
        <td rowspan=9> byte0 </td>
    </tr>
    <tr> 
        <td> bit7 </td>
        <td> P </td> 
        <td rowspan=9> A/T selector position </td>
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> R </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> N </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> D </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> 4 </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td> 3 </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> 2 </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> L </td> 
    </tr>
        <tr>
        <td rowspan=9> byte1 </td>
    </tr>  
    <tr> 
        <td> bit7 </td>
        <td colspan=2> </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td colspan=2> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td colspan=2> </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td colspan=2> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td colspan=2> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td colspan=2> </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td colspan=2> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td colspan=2> </td> 
    </tr>
</table>

Example: `FE 40 10 00` -- A/T selector position "D"

<br>



### 0x6A ###

<table>
    <tr>
        <td> byte0 </td>
        <td colspan=2> Trip computer units <br> 0x00 - distance in km, speed in 0.1 km/h, fuel rate in 0.1 km/L <br> 0x10 - distance in miles, speed in 0.1 MPH, fuel rate in 0.1 MPG <br> 0x11 - distance in km, speed in 0.1 km/h, fuel rate in 0.1 L/100km </td> 
    </tr>
    <tr>
        <td rowspan=9> byte1 </td>
    </tr>  
    <tr> 
        <td> bit7 </td>
        <td> </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
</table>

Example: `40 6A 10 80`

<br>


### 0x76 ###

<table>
    <tr>
        <td> byte0 </td>
        <td rowspan=2 colspan=2> Trip distance from last ignition ON (see Note for units description), big endian </td>
    </tr>
    <tr>
        <td> byte1 </td>
    </tr>
    <tr>
        <td rowspan=9> byte2 </td>
    </tr>  
    <tr> 
        <td> bit7 </td>
        <td> km </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> miles </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td>  </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
</table>

Note: units are defined in byte2 (if it is present) or in [0x6A](#0x6A) packet.

Example: `45 76 01 3B 40` -- trip distance 315 miles (from last ignition on)  


<br>


### 0x8C ###

<table>
    <tr>
        <td rowspan=9> byte0 </td>
    </tr>
    <tr> 
        <td> bit7 </td>
        <td>  </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
    <tr>
        <td rowspan=9> byte1 </td>
    </tr>  
    <tr> 
        <td> bit7 </td>
        <td> </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td>  </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
    <tr>
        <td rowspan=9> byte2 </td>
    </tr>  
    <tr> 
        <td> bit7 </td>
        <td> </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td>  </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
    <tr>
        <td rowspan=9> byte3 </td>
    </tr>  
    <tr> 
        <td> bit7 </td>
        <td> </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td>  </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
</table>

Example: `FE 8C 98 00 18`

<br>



### 0x90 ###

<table>
    <tr>
        <td> byte0 </td>
        <td rowspan=2  colspan=2> Momentary fuel rate per distance (see Note for units description), big-endian </td>
    </tr>
    <tr>
        <td> byte1 </td>
    </tr>
    <tr>
        <td rowspan=9> byte2 </td>
    </tr>  
    <tr> 
        <td> bit7 </td>
        <td> 0.1 km/L </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> 0.1 L/100km </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> 0.1 MPG (USA) </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> 0.1 MPG (English) </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td>  </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
</table>

Note: units are defined in byte2 (if it is present) or in [0x6A](#0x6A) packet.

Example: `45 90 01 08 40` -- momentary fuel rate 26.4 L/100km

<br>



### 0x96 ##

<table>
    <tr>
        <td rowspan=9> byte0 </td>
    </tr>
    <tr> 
        <td> bit7 </td>
        <td> </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td>  </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> Back (5th) door unlocked </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
</table>

Example: `E0 96 10` -- back door unlocked

<br>


### 0xA3 ###

<table>
    <tr>
        <td> byte0 </td>
        <td rowspan=2 colspan=2> Average fuel rate (see Note for units description), big-endian </td>
    </tr>
    <tr>
        <td> byte1 </td>
    </tr>
    <tr>
        <td rowspan=9> byte2 </td>
    </tr>  
    <tr> 
        <td> bit7 </td>
        <td> 0.1 km/L </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> 0.1 L/100km </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> 0.1 MPG (USA) </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> 0.1 MPG (Englsih) </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td>  </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
</table>

Note: units are defined in byte2 (if it is present) or in [0x6A](#0x6A) packet.

Example: `45 A3 00 74 40` -- average fuel rate 11.6 L/100km

<br>



### 0xCA ##

<table>
    <tr>
        <td rowspan=9> byte0 </td>
    </tr>
    <tr> 
        <td> bit7 </td>
        <td> </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td>  </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
</table>

Example: `45 CA 01`

<br>


### 0xCD ###

<table>
    <tr>
        <td> byte0 </td>
        <td> Outside temperature (Celsius degrees + 48) </td>
    </tr>
</table>

Example: `FE CD 4A` -- outside temperature 26 Celsius degrees

<br>



### 0xD0 ###

<table>
    <tr>
        <td rowspan=9> byte0 </td>
    </tr>
    <tr> 
        <td> bit7 </td>
        <td>  </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> Driver's door opened indicator ON (combination meter) </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td> Front passenger's door opened indicator ON (combination meter) </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
    <tr>
        <td rowspan=9> byte1 </td>
    </tr>  
    <tr> 
        <td> bit7 </td>
        <td> </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> Check engine indicator ON (combination meter) </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> ABS warning indicator ON (combination meter) </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> VSC warning indicator ON (combination meter) </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td>  </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
    <tr>
        <td rowspan=9> byte2 </td>
    </tr>  
    <tr> 
        <td> bit7 </td>
        <td> </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> Critical oil pressure indicator ON (combination meter) </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> Battery powered indicator ON (combination meter) </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td>  </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
    <tr>
        <td rowspan=9> byte3 </td>
    </tr>  
    <tr> 
        <td> bit7 </td>
        <td> Combination meter's backlight is dimmed </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td>  </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
</table>

Example: `45 D0 00 00 00 00`

<br>


### 0xD2 ###

<table>
    <tr>
        <td rowspan=9> byte0 </td>
    </tr>
    <tr> 
        <td> bit7 </td>
        <td>  </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> Enables "M" symbol at combination meter's LCD </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> ECT PWR mode</td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> ECT SNOW mode </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> CRUISE ON </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
    <tr>
        <td rowspan=9> byte1 </td>
    </tr>  
    <tr> 
        <td> bit7 </td>
        <td> </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
    <tr>
        <td rowspan=9> byte2 </td>
    </tr>  
    <tr> 
        <td> bit7 </td>
        <td> </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> Critical A/T oil temperature </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
</table>

Example: `45 D2 10 00 00` -- ECT SNOW mode

<br>



### 0xD4 ##

<table>
    <tr>
        <td rowspan=9> byte0 </td>
    </tr>
    <tr> 
        <td> bit7 </td>
        <td> Engine starter is running </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> Battery powered (no charge) </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> Critical engine oil pressure</td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
</table>

Example: `FE D4 10` -- critical engine oil pressure

<br>



### 0xD7 ##

<table>
    <tr>
        <td rowspan=9> byte0 </td>
    </tr>
    <tr> 
        <td> bit7 </td>
        <td> Enable climate blower motor relay </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> Enable compressor's solenoid relay </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> Enable back glass heater relay </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
</table>

Example: `D2 D7 A0` -- blower motor relay enabled, back glass heater relay enabled

<br>


### 0xDA ##

<table>
    <tr>
        <td rowspan=9> byte0 </td>
    </tr>
    <tr> 
        <td> bit7 </td>
        <td> Make a single ding sound </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td>  </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
</table>

Example: `40 DA 80` -- make a single ding sound

<br>


### 0xDB ###

<table>
    <tr>
        <td rowspan=9> byte0 </td>
    </tr>
    <tr> 
        <td> bit7 </td>
        <td> <i>Driver's door warning or status changed (not sure)</i> </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> Driver's door panel button pushed </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> Driver's door opened </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> Driver's door unlocked </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> Driver's door key turned to lock </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> Driver's door key turned to unlock </td> 
    </tr>
    <tr>
        <td rowspan=9> byte1 </td>
    </tr>  
    <tr> 
        <td> bit7 </td>
        <td> </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> Power windows locked by driver's door button </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> Driver's door lock bitton pushed </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td> Driver's door unlock button pushed </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
</table>

Example: `FE DB 30 00` -- driver's door unlocked and opened

<br>



### 0xDC ###

<table>
    <tr>
        <td rowspan=9> byte0 </td>
    </tr>
    <tr> 
        <td> bit7 </td>
        <td> <i>Front passenger's door warning or status changed (not sure)</i> </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> Front passenger's door panel button pushed </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> Front passenger's door opened </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> Front passenger's door unlocked </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> Front passenger's door key turned to lock </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> Front passenger's door key turned to unlock </td> 
    </tr>
    <tr>
        <td rowspan=9> byte1 </td>
    </tr>  
    <tr> 
        <td> bit7 </td>
        <td> </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> Front passenger's door lock bitton pushed </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td> Front passenger's door unlock button pushed </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
</table>

Example: `FE DC 10 00` -- fron paggenger's door unlocked

<br>



### 0xDD ##

<table>
    <tr>
        <td rowspan=9> byte0 </td>
    </tr>
    <tr> 
        <td> bit7 </td>
        <td> </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> Rear right door opened </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> Rear right door unlocked </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
</table>

Example: `FE DD 30 00` -- Rear right door unlocked and opened

<br>



### 0xDE ##

<table>
    <tr>
        <td rowspan=9> byte0 </td>
    </tr>
    <tr> 
        <td> bit7 </td>
        <td> </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> Rear left door opened </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> Rear left door unlocked </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
</table>

Example: `FE DE 30 00` -- Rear left door unlocked and opened

<br>



### 0xDF ###

<table>
    <tr>
        <td rowspan=9> byte0 </td>
    </tr>
    <tr> 
        <td> bit7 </td>
        <td> Parking brake enabled </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> Ignition ON ("ON" key position), from body MCU </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> Body subsystems powered ("ACC" and "ON" key positions) </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> Any door opened </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
    <tr>
        <td rowspan=9> byte1 </td>
    </tr>  
    <tr> 
        <td> bit7 </td>
        <td> </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td>  </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
    <tr>
        <td rowspan=9> byte2 </td>
    </tr>  
    <tr> 
        <td> bit7 </td>
        <td> </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td>  </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
    <tr>
        <td rowspan=9> byte3 </td>
    </tr>  
    <tr> 
        <td> bit7 </td>
        <td> Back (5th) door opened </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td>  </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
    <tr>
        <td rowspan=9> byte4 </td>
    </tr>  
    <tr> 
        <td> bit7 </td>
        <td> </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td>  </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
    <tr>
        <td rowspan=9> byte5 </td>
    </tr>  
    <tr> 
        <td> bit7 </td>
        <td> </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td>  </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
</table>

Example: `FE DF 70 00 00 00 00 00`

<br>


### 0xE0 ###

<table>
    <tr>
        <td rowspan=9> byte0 </td>
    </tr>
    <tr> 
        <td> bit7 </td>
        <td> Open front right power window </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> Close front right power window </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> Open / close front right power window in AUTO mode </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
    <tr>
        <td rowspan=9> byte1 </td>
    </tr>  
    <tr> 
        <td> bit7 </td>
        <td> Open rear right power window </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> Close rear right power window </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> Open / close rear right power window in AUTO mode </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td>  </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
    <tr>
        <td rowspan=9> byte2 </td>
    </tr>  
    <tr> 
        <td> bit7 </td>
        <td> Open rear left power window </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> Close rear left power window </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> Open / close rear left power window in AUTO mode </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td>  </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
    <tr>
        <td rowspan=9> byte3 </td>
    </tr>  
    <tr> 
        <td> bit7 </td>
        <td> Open front left power window </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> Close front left power window </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> Open / close front left power window in AUTO mode </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td>  </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
</table>

Example: `D1 E0 A0 A0 A0 A0` -- open all power windows in AUTO mode

<br>


### 0xE4 ###

<table>
    <tr>
        <td rowspan=9> byte0 </td>
    </tr>
    <tr> 
        <td> bit7 </td>
        <td>  </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> Head light on </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> Tail lights on </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> Rear for light on </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> Ignition key inserted </td> 
    </tr>
    <tr>
        <td rowspan=9> byte1 </td>
    </tr>  
    <tr> 
        <td> bit7 </td>
        <td> Driver's seatbelt is not fastened </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td> Front fog light on </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
</table>

Example: `FE E4 10 80` -- tail lights are on and driver's seatbelt is not fastened

<br>




### 0xE6 ###

<table>
    <tr>
        <td rowspan=9> byte0 </td>
    </tr>
    <tr> 
        <td> bit7 </td>
        <td>  </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
    <tr>
        <td rowspan=9> byte1 </td>
    </tr>  
    <tr> 
        <td> bit7 </td>
        <td> </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td>  </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
    <tr>
        <td rowspan=9> byte2 </td>
    </tr>  
    <tr> 
        <td> bit7 </td>
        <td> </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td>  </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
</table>

Example: `FE E6 21 28 40`

<br>


### 0xFC ###

<table>
    <tr>
        <td rowspan=9> byte0 </td>
    </tr>
    <tr> 
        <td> bit7 </td>
        <td> Climate control AUTO mode </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> Climate control recycling mode </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> Blow direction on windshield only </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> Back glass heater ON </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> Air conditioner ON </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> Blow direction on head and feet </td> 
    </tr>
    <tr>
        <td rowspan=9> byte1 </td>
    </tr>  
    <tr> 
        <td> bit7 </td>
        <td> Blow direction on head only </td> 
    </tr>
    <tr> 
        <td> bit6 </td>  
        <td> Blow direction on windshield and feet </td> 
    </tr>
    <tr> 
        <td> bit5 </td>  
        <td> Blow direction on feet only </td> 
    </tr>
    <tr> 
        <td> bit4 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit3 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit2 </td>  
        <td>  </td> 
    </tr>
    <tr> 
        <td> bit1 </td>  
        <td> </td> 
    </tr>
    <tr> 
        <td> bit0 </td>  
        <td> </td> 
    </tr>
</table>

Example: `45 FC 83 00` -- climate control is in AUTO mode, blow direction on head and feet, air conditioner is ON

<br>



### 0xFD ###

<table>
    <tr>
        <td> byte0 </td>
        <td> Target inside temperature (0.5 Celsius degrees - 16) <br> 0x00 - "Max cold" <br> 0x37 - "Max hot" <br> 0x38 - climate initialization in progress <br> 0x39 - climate control is disabled (switched off) </td>
    </tr>
</table>

Example: `45 FD 13` -- target inside temp 25.5 Celsius degrees

<br>
