This is an Arduino script to set the PIDv values of the S42C motor designed by Big Tree Tech. The requirements are an Arduino Uno, a usb to serial wire (for Arduino Uno), an S42C motor, and three male to female jumper wires. UART communication is set up between the Arduino Uno and the S42C motor to set specific PIDv values.

UART communication involves communication between devices by having a receive (RX) and transmit (TX) pin for all devices. The S42C motor board uses an STMicroelectronics chip that has pins set aside for RX and TX. The manual for the chip is found: https://www.st.com/en/microcontrollers-microprocessors/stm32g031g8.html. On the manual, you can find that PA2 supports USART_TX and PA3 supports USART_RX. The physical location of the pins can be found on the motor diagram in the user manual for S42C motor found here: https://github.com/bigtreetech/BIGTREETECH-Stepper-Motor-Driver/blob/master/BIGTREETECH%20S42C%20V1.0/BIGTREETECH%20S42C%20user%20manual.pdf.

On the Arduino Uno, pin 0 and pin 1 are set aside for UART communication. However, if you establish a serial connection with a computer, the pins become inaccessible. This can be circumvented by using the SoftwareSerial package and using pin 2 and 3 on the Arduino to set up RX and TX communication.

In my case, I connected PA2 to pin 2, PA3 to pin 3, and ground to ground on both systems. Power to the S42C motor board was provided through an SKR V1.4 turbo as it is the easiest set up I have available. Providing approximately 24 volts to the VM connection on S42C motor board is sufficient to turn on the board.

In the code, pin 2 is set up as RX and pin 3 is set up as TX. 
