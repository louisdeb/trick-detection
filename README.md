# Skateboard Trick Detection

By attaching two sensors to the bottom of your skateboard, this project detects the trick you have performed and reports it on the basestation (currently a third sensor attached to a computer).

The project was developed on TI CC2650 Sensortags, running the Contiki operating
system. It was a project for Imperial College 3rd Year's Pervasive Computing 
course.

The project uses detection algorithms designed by the developers. It could be improved by the use of machine learning. Given the time restriction of the project we chose to not follow this route.

## Running the project

- Clone this repo and make sure contiki/ is also cloned
- Download UniFlash
- Inside `src/` run `sudo make sounds.bin`
- Connect your TI Sensortag Dev Pack to your computer
- Open UniFlash and select the CC2650 Sensortag
- Load `sounds.bin` onto the board

Inside the `contiki/` folder, run `git submodule update --init` to download the 
contiki-os requirements.

## Debugging the project

You can listen to the output of the code running on the sensor by first running

`ls /dev/tty.usbmodem*`

And then running the following in the `src/` folder

`make login PORT=/dev/tty.usbmodem<first_result>`

