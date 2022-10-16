# Rivanna2

Embedded system code for Rivanna 2

## Development
The recommended approach for development is to use the [rivanna2-env](https://github.com/orgs/solarcaratuva/packages/container/package/rivanna2-env) container. It contains all of the necessary tools to build the firmware for each board. 

### Prerequisites
- OCI-compliant container runtime (e.g. [`docker`](https://docs.docker.com/engine/install/), [`podman`](https://podman.io/getting-started/installation))
- ST-LINK driver ([open-source](https://github.com/stlink-org/stlink) (recommended) or [official](https://www.st.com/en/development-tools/stsw-link009.html))
- [PlatformIO](https://platformio.org/install/cli) or any other software that can connect to a serial console

### Running the development container
- To open an interactive session:
  - With Docker: `docker run -it -v $(pwd)/:/root/Rivanna2:Z ghcr.io/solarcaratuva/rivanna2-env`
  - With Podman: `podman run -it -v .:/root/Rivanna2:Z ghcr.io/solarcaratuva/rivanna2-env` 
- Alternatively, you can connect to the container in VSCode, which will allow you to open new shells inside of the container to easily run commands. This will also provide features like code autocomplete and IDE compilation errors. 
  1. Install the [Remote - Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) extension.
  2. Open the Rivanna2 repository.
  3. Type `Ctrl+Shift+P` and run the `Remote-Containers: Open Folder in Container` command. This will open the current folder (Rivanna2) inside of the container.
  4. From there, opening a new terminal will open a shell inside of the container.

### Compiling
`./compile.sh` - This script will run `mbed-tools compile` with the correct environment and toolchain arguments. This will compile the firmware for all boards. Before running this the first time, run `mbed-tools deploy`, which will download the version of Mbed OS specified in `mbed-os.lib`.

### Uploading
`./upload_{ecu, motor, power_aux, solar}.sh` - This script will check that the correct board is connected and upload the corresponding firmware to the board. (Since the container does not have access to the ST-LINK USB device, this command will have to be run outside of the container.)

### Monitoring
`./monitor.sh` - This script will run `pio device monitor` with the correct baud rate. (Since the container does not have access to the ST-LINK USB device, this command will have to be run outside of the container.)

## Hardware
* The PCB layouts and associated schematics for all boards can be found on the [associated repositories on CADLAB.io](https://cadlab.io/solar-car-uva).
* All boards use the [STM32G473CCT3 MCU](https://www.st.com/resource/en/datasheet/stm32g473ce.pdf).

## Software environment
* The instructions on the [UVA Solar Car Team Website](https://solarcaratuva.github.io/software/stm32-mbed-info.html) were used to help set up this project.

## For Apple Silicon -> Building the docker container locally
Using the exisiting docker container rivanna2-env can result in slow compilation times since the container was made for x86 not arm. 

First, we want to built a docker image from the existing docker file. The following command makes a docker image with name "arm-rivanna2":
`docker build -t arm-rivanna2 .`

Next, we want to create and run a container with the image we created above. Run the following command: `docker run -it --name rivanna2arm -v $(pwd)/:/root/Rivanna2:Z arm-rivanna2`.

The prior command will create a docker container with name `rivanna2arm`. Use this container going forward. 

Refer to [the notion page](https://peppered-song-568.notion.site/Docker-Help-Desk-711ef6f7045e4865a3dd7e7e5ba39755) for more docker help and commands! :)
