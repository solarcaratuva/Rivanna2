# Modular EV Battery Management System
UVA ECE Fall 2020 Capstone Project design for a modular battery management system (BMS) for use in electric vehicles. This repository contains the embedded systems code for the Main Node and Cell Node boards.


## Hardware
* The PCB layouts and associated schematics for the Main Node and Cell Node boards can be found on the [associated repository on CADLAB.io](https://cadlab.io/project/23337/master/files).
* The Main Node uses the [STM32G473 MCU](https://www.mouser.com/datasheet/2/389/stm32f042c4-1851049.pdf).
* The Cell Node uses the [STM32F042 MCU](https://www.mouser.com/datasheet/2/389/stm32f042c4-1851049.pdf).
* The Cell Node board is designed to attach using nickel strips to a pair of standard 18650 battery cells connected together using the [Vruzend V2.1 battery connector kit](https://vruzend.com/product/vruzend-battery-kit-v2-0/).
* Photos demonstrating the attachment of the Cell Node board to the battery cells can be found [here](https://imgur.com/a/J0ZLfna).
* Both the Main Node and Cell Node were designed to run off an external 12V supply, such as a lead-acid battery, rather than directly off the battery pack.
* This choice was made to avoid the potential complexity created by the addition of a buck-boost converter for a design without an external supply.


## Software
* Both the Main and Cell Nodes run Mbed OS v6.
* The Cell Node's STM32F042 MCU has an extremely limited amount of flash memory. As a result, a large number of features must be removed from the build.
* Macros built into the code allow for the enabling and disabling of features (such as `printf`) as needed.


## Software Environment
* The instructions on the [UVA Solar Car Team Website](https://solarcaratuva.github.io/stm32-mbed-info) were used to help set up this project.
* The [PlatformIO Core](https://docs.platformio.org/en/latest/core/installation.html), which includes the PlatformIO CLI, must first be installed.
* The [PlatformIO IDE](https://docs.platformio.org/en/latest/integration/ide/pioide.html) can be optionally installed as either a Visual Studio Code or Atom extension.
* On Windows, the driver for the ST-Link debugger will be needed to upload programs. This driver can be found [here](https://os.mbed.com/teams/ST/wiki/ST-Link-Driver).


## Directory Structure
* The `include` and `src` directories are split into `CellNode`, `MainNode`, and `Shared` subdirectories.
* The `CellNode` subdirectories will only include .cpp and .h files specific to the Cell Node, while the `MainNode` subdirectories will only include .cpp and .h files specific to the Main Node.
* The `Shared` subdirectories will include .cpp and .h files that are common between the two boards.
* All testing code that can be run on both boards will be located in `src/Shared/test_main.cpp`.


## Authors
* William Zhang
* Dipesh Manandhar
* Nripesh Manandhar
* Nikilesh Subramaniam
* Phillip Phan


## Acknowledgements
We would like to thank Dr. Harry Powell and Prof. Adam Barnes for their valuable help and support throughout the development of this project.
