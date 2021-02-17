# 8mulator

A small [CHIP-8](https://en.wikipedia.org/wiki/CHIP-8) emulator.

![Screenshot](/doc/screenshot.png)

# How to build
* Copy the repository to your computer
* Navigate into the projects root folder
* Create new folder named build
* Navigate into the build folder
* Run the cmake command (cmake ..)
* Run the make command (make). In case some of the required libraries are missing, install them and try again.

# How to use
Once the program has been built, it can be launched by using the following command.
```
./8mulator <chip8_program_file>
```
The program can be killed by hitting the esc key. The original key layout has been swapped to the following:

<pre>
Keypad                   Keyboard
+-+-+-+-+                +-+-+-+-+
|1|2|3|C|                |1|2|3|4|
+-+-+-+-+                +-+-+-+-+
|4|5|6|D|                |Q|W|E|R|
+-+-+-+-+       =>       +-+-+-+-+
|7|8|9|E|                |A|S|D|F|
+-+-+-+-+                +-+-+-+-+
|A|0|B|F|                |Z|X|C|V|
+-+-+-+-+                +-+-+-+-+
</pre>
