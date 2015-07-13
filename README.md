#RFID to Image

This project allows a radio frequency identification (RFID) module connected to an Arduino Leonardo to communicate with a Python program. The Python program runs on a separate computer and will respond to scanned RFID tags by displaying images to the computer's screen.

To add new images you must place them in the images folder, add entries associating RFID tag numbers to characters to the Arduino code, and modify image_list.txt to associate the characters with an image name.

This project was created by Keith Hamm for the [University of Oregon Museum of Natural and Cultural History](natural-history.uoregon.edu). As of this writing it is currently used by guests in the museum's natural history exhibit hall.
