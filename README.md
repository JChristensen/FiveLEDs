# Five LEDs Puzzle
https://github.com/JChristensen/FiveLEDs  
README file  
Jack Christensen  
Jan-2021

## License
![](https://licensebuttons.net/l/by/4.0/88x31.png)  
Five LEDs Puzzle by Jack Christensen and the original project by David Johnson-Davies are both licensed under under a [Creative Commons Attribution 4.0 International License](http://creativecommons.org/licenses/by/4.0/).

See the original project at:  
https://github.com/technoblogy/five-leds-puzzle  
http://www.technoblogy.com/show?3EL5

## Introduction
This is just my spin on David Johnson-Davies' Five LEDs Puzzle. The [circuit](https://raw.githubusercontent.com/JChristensen/FiveLEDs/master/extras/schematic.png) is modified slightly, to use an ATtiny84A microcontroller, and the [PC board design](https://raw.githubusercontent.com/JChristensen/FiveLEDs/master/extras/board.png) is new, to accommodate SMT components and an AA battery holder.

## Instructions
The object of the puzzle is to get all the LEDs to remain lit. Each LED lights up briefly when the corresponding button below it is pressed, but an LED only stays lit under certain conditions; to solve the puzzle you need to work out what the rule is.

The puzzle can be solved by pressing one button at a time; there is no benefit in pressing combinations. To return the puzzle to the start, with all LEDs off, press the RESET button.

If no button is pressed for 30 seconds, the puzzle will automatically turn itself off. Press any button to turn it back on. The LEDs will then be in the same state as when it turned off.

## Circuit design
A bill of materials is available at [Mouser Electronics](https://www.mouser.com/ProjectManager/ProjectDetail.aspx?AccessID=cfd9324946) and also in [this repo](https://github.com/JChristensen/FiveLEDs/blob/master/extras/bom.csv).  

![](https://raw.githubusercontent.com/JChristensen/FiveLEDs/master/extras/boards.jpg)
