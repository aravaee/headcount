# Headcount

A program for tracking people entering and exiting a building that additionally provides useful functionality such as setting a maximum store capacity (i.e. for enforcing COVID-19 safety measures) and sending notifications to involved parties.

## Table of Contents

- [Headcount](#headcount)
  - [Table of Contents](#table-of-contents)
  - [Preface](#preface)
  - [Requirements](#requirements)
  - [Compilation](#compilation)
  - [Testing](#testing)

## Requirements

- CMake (version 3.1.0 or later)
  - On linux, you can run `sudo apt install -y cmake`.
- Qt5
  - On linux, you can run `sudo apt-get install qt5-default`.
  - More information available [here](https://wiki.qt.io/Install_Qt_5_on_Ubuntu).
- OpenCV4
  - Follow the OpenCV linux installation tutorial found [here](https://docs.opencv.org/master/d7/d9f/tutorial_linux_install.html).
  - However, for this program, OpenCV needs to be compiled with the flag `WITH_QT=ON`.
  - You can use the `cmake` command found [here](https://stackoverflow.com/questions/28776053/opencv-gtk2-x-error) for the `cmake` portion of the installation process.
  - Additional instructions are provided in the `opencv_installation.txt` file.
- SimpleMail2Qt5

## Compilation

To compile this program, run the following commands from the root of the project:

```sh
cmake .
make
```

## Testing

To test the program, run it from the command line using the following command:

```sh
./headcount
```
