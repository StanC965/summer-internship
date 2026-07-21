# Week: 3 - Goal : 6


## Objective 4: HYUNDAI Imaginary Use Case

---

### Task Checklist & Results

| Task ID   | Type       | Status
| :---      | :---       | :--- 
| **[641]** | `CORE`     | [] Completed

---

#### Task 631
> **Question/Prompt:** HYUNDAI is an important asian customer for Marquardt. It plans a new Elantra carline to be unveiled next year. Today they are in prototyping phase. A Request For Bid (RFB) has been sent to Marquardt Rietheim Headquarters for a rapid prototype on Elantra's dashboard background illumination control. Therefore the management of Marquardt set up a mixed german-romanian team to make a prototype and go to Seoul, South Koreea next week. You are part of this team. If presentation to the customer is good then your team wins the project! Heavy responsability on you!
>
> There are a just few requirements received from Hyundai. Lack of details force you to take some engineering decisions to go on. The requirements are referring to a day illumination design (that means the way LEDs are behaving during the day light intensity) and a night illumination design (that means the way LEDs are behaving during night light intensity). Both designs are based on the measured ambient light intensity within the driver's cockpit. The measurements are based on TEMT6000 light sensor which outputs an analog signal (high light intensity = low voltage, and low light intensity = high voltage). To make a good impression to the presentation in Seoul, you have chosen to use 10bit ADC resolution which assures a fine grain reading of the light intensity. On the main board (ATmega324PB Xplained PRO) you choose SW0 switch to enable the headlights, therefore also the interior light intensity measurements are started in parallel. You need these initial measurements to detect if your prototype should behave in day or night mode.
>
> Once again, Hyundai detailed only the entry phase in the illumination design (when driver switches on the headlights!) and not the complete behavior (e.g. what happens after entry phase when ambient light is changing continously, how reactive the prototype should be or the illumination curve response after entry phase). The latter are up to you, to propose a certain design so that you please the customer. You can also counter-propose to Hyundai a different approach to the entry phase, but this only after you presented his request :) e.g. maybe you observed the requested illumination pattern to be too agressive for the human eye because of the PWM entry levels or too faint and not observable.
> 
> Remember: in prototyping it is room for negociation, the final objective is to please the customer within realistic technological possibilities and win the project.
> 
> Additionally with OLED1 board you implement the visual feedback to the driver/passenger in the car. Use two LEDs, LED1 and LED2 for background illumination in Day mode and Night Mode. Each time SW0 is pressed then the driver scenario turning on the headlights is repeated. Take care that Hyundai has a preference over the entry phase in Day/Night design (see Table 741.1 and Table 741.2).

> Table 741.1

| Eye Perceived Light Levels	| PWM % duty-cycle ABSOLUTE entry level	    | Design/Mode
| :---                          | :---                                      | :--- 
| 0  - 20	                    | 15%	                                    | Night
| 21 - 40	                    | 20%	                                    | Night
| 41 - 50	                    | 42%	                                    | Day
| 51 - 70	                    | 80%	                                    | Day
| 71 - 100	                    | 90%	                                    | Day

> Table 741.2

| Time [sec]	| Entry phase Night mode RELATIVE steps	| Entry phase Day mode RELATIVE steps
| :---          | :---                                  | :--- 
| 0	            | 0	                                    | 0
| 0.2	        | 1	                                    | 4
| 0.4	        | 1	                                    | 7
| 0.6	        | 3	                                    | 16
| 0.8	        | 7	                                    | 44
| 1	            | 16	                                | 59
| 1.2	        | 16	                                | 59
| 1.4	        | 14	                                | 55
| 1.6	        | 12	                                | 50
| 1.8	        | 10	                                | 45
| 2	            | 8	                                    | 40

> **Answer/Explanation:**
> 

---