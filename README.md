# Sounds of the Surf

When lots of wireless sensors are placed on a body of water, the sensors 
emit buzzer tones of frequencies in harmony of any ripples in that body.

The project was developed on TI CC2650 Sensortags, running the Contiki operating
system. It was a project for Imperial College 3rd Year's Pervasive Computing 
course.

## Running Sounds of the Surf

- Clone this repo and make sure contiki/ is also cloned
- Download UniFlash
- Inside `src/` run `sudo make sounds.bin`
- Connect your TI Sensortag Dev Pack to your computer
- Open UniFlash and select the CC2650 Sensortag
- Load `sounds.bin` onto the board

Inside the `contiki/` folder, run `git submodule update --init` to download the 
contiki-os requirements.

## Debugging Sounds of the Surf

You can listen to the output of the code running on the sensor by first running

`ls /dev/tty.usbmodem*`

And then running the following in the `src/` folder

`make login PORT=/dev/tty.usbmodem<first_result>`

