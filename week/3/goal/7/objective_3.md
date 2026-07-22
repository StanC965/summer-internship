# Week: 3 - Goal : 7


## Objective 3: Implement driver and test application

---

### Task Checklist & Results

| Task ID   | Type       | Status
| :---      | :---       | :--- 
| **[731]** | `CORE`     | [x] Completed

---

#### Task 731
> **Question/Prompt:** Implement a new software driver for your peripheral: start simple (send a single byte, receiving a single byte), then you can complicate things more (like sending/receiving a couple of bytes which could represent a string). Be attentive to the separation of concerns (what a driver is supposed to do, and what an application is supposed to do) and give appropriate names for the files, functions, variables.

> **Answer/Explanation:**

**`uart.c`**
```c
void uart_init(void)
{
    UBRR2H = (uint8_t)(UART_UBRR_VALUE >> 8);
    UBRR2L = (uint8_t)(UART_UBRR_VALUE);

    UCSR2A |= (1 << U2X2);

    UCSR2B = (1 << TXEN2) | (1 << RXEN2);

    UCSR2C = (1 << UCSZ21) | (1 << UCSZ20);   
}

void uart_send_byte(uint8_t data)
{
    while (!(UCSR2A & (1 << UDRE2)))          
    {
    }
    UDR2 = data;
}

uint8_t uart_receive_byte(void)
{
    while (!(UCSR2A & (1 << RXC2)))          
    {
    }
    return UDR2;
}

void uart_send_string(const char *str)
{
    while (*str != '\0')
    {
        uart_send_byte((uint8_t)*str);
        str++;
    }
}

void uart_receive_string(char *buffer, uint8_t max_length)
{
    uint8_t index = 0;
    char received_byte;

    do
    {
        received_byte = (char)uart_receive_byte();

        if (index < (max_length - 1U))
        {
            buffer[index] = received_byte;
            index++;
        }
    } while (received_byte != '\n');

    buffer[index] = '\0';
}
```

---
