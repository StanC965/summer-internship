# Week: 2 - Goal : 4


## Objective 1: Getting to know TC0 timer

---

### Task Checklist & Results

| Task ID   | Type   | Status
| :---      | :---   | :--- |
| **[411]** | `CORE` | [ ] Completed


#### Task 411
> **Question/Prompt:** Go at the top menu bar: Atmel-ICE -> Fuse Handler -> Low Fuse -> check the box: Divide clock by 8 internally, check the box: Clock output on PORTB1. Select from the drop-down list the Internal RC oscillator 8MHz as shown (the New Value for Low Fuse is 0x22) -> Program Fuses -> Close.
> 
> What you have set here is the source for system clock signal. The heartbeat of the system. Internal RC oscillator @ 8MHz frequency, but divided by 8, so resulting in 1MHz system clock frequency which will be distributed to all peripherals including CPU. Lowering the system clock frequency is a great way to reduce power consumption in embedded systems. TC0 is an 8bit timer/counter which also receives clock signal from this source. This TC0 we will study further.

> **Answer/Explanation:**
> 

