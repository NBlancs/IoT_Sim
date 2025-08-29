from machine import Pin
from time import sleep

# Segment pin assignments (matching your GPIOs)
SEG_A = Pin(13, Pin.OUT)
SEG_B = Pin(12, Pin.OUT)
SEG_C = Pin(14, Pin.OUT)
SEG_D = Pin(27, Pin.OUT)
SEG_E = Pin(26, Pin.OUT)
SEG_F = Pin(25, Pin.OUT)
SEG_G = Pin(33, Pin.OUT)

# List of segment pins in order A-G
segments = [SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G]

# Digit patterns: [A, B, C, D, E, F, G]
digits = [
    [1,1,1,1,1,1,0], # 0
    [0,1,1,0,0,0,0], # 1
    [1,1,0,1,1,0,1], # 2
    [1,1,1,1,0,0,1], # 3
    [0,1,1,0,0,1,1], # 4
    [1,0,1,1,0,1,1], # 5
    [1,0,1,1,1,1,1], # 6
    [1,1,1,0,0,0,0], # 7
    [1,1,1,1,1,1,1], # 8
    [1,1,1,1,0,1,1]  # 9
]

# Show a single digit on the display
def show_number(num):
    for i in range(7):
        segments[i].value(digits[num][i])

# Main loop
while True:
    for i in range(10):
        show_number(i)
        sleep(1)  # Wait 1 second
