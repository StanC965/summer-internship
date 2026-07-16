# Week: 2 - Goal : 3


## Objective 4: Light sensor

---

### Task Checklist & Results

| Task ID   | Type      | Status 
| :---      | :---      | :---                    
| **[341]** | `CORE`    | [x] Completed 
| **[342]** | `CORE`    | [x] Completed 

--- 

#### Task 341
> **Question/Prompt:** Our next big move will be to integrate the light sensor within our project and writing code for handling the analog to digital conversion. On short we want to do: connect light sensor to pin, receiving analog signal based on ambient light, convert this signal to a digital value, light up LED. A preview of how the setup will look like is here: TEMT6000 Ambient Light Sensor with Arduino - YouTube.

> **Answer/Explanation:**
> 

--- 

#### Task 342
> **Question/Prompt:** Connect the I/O board with light sensor to EXT4. Read from the User Guide about sensor type, its datasheet and most important: connection to microcontroller's pins. Observe in the electronic schematic also the connections to GND and VCC (without them the sensor would not work, right?).

> **Answer/Explanation:**
> - The light sensor uses pin 3 to read the signal, and this corresponds to pin PA4 on the ATmega324PB board.
> - VCC is connected to pin 20 of the EXT4 header.
> - GND is connected to pin 2 of the EXT4 header.
> - The sensor type is a phototransistor.
> - The signal type is analog voltage output: increased ambient light increases the output voltage on the signal pin.

## References & Resources
* I/O1 Xplained Pro user guide