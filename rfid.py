from tkinter import Tk, Label, LEFT
from PIL import Image, ImageTk
import serial
from threading import Timer
import os
from time import sleep

print('Starting RFID to Image')

path = os.path.dirname(__file__)
start_image = os.path.join(path, 'images/rfid_main.jpg')
ten_minutes = 600

# Setup image map
image_list = os.path.join(path, 'images/image_list.txt')
lines = (line.rstrip('\n') for line in open(image_list))
image_map = {}
for line in lines:
    image_map[line[0]] = line[2:]

# Listen for RFID
sleep(10)
serial.Serial('/dev/ttyACM0', baudrate=9600)

window = Tk()
window.attributes('-fullscreen', True)

# Setup start image
image = Image.open(start_image)
image = image.resize((1920, 1080))
image = ImageTk.PhotoImage(image)
container = Label(window, image=image, command=None)
container.pack(side=LEFT, expand=1)

def update_image(filename):
    new_image = Image.open(filename)
    new_image = new_image.resize((1920, 1080))
    new_image = ImageTk.PhotoImage(new_image)
    container.configure(image=new_image)
    container.image = new_image

def reset_image():
    update_image(start_image)

def handle_keypress(event):
    char = event.char
    print('char ' + char)
    if char == '':
        return
    filename = os.path.join(path, 'images/' + image_map[char])
    print('filename ' + filename)
    update_image(filename)
    timer = Timer(ten_minutes, reset_image)
    timer.start()

window.bind('<KeyPress>', handle_keypress)

window.mainloop()
