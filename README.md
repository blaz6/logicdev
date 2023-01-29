# A new project to learn the basics of c++

## Installation
### ==> Linux
#### Requirements:
You will need ninja and cmake(version 3.24+) installed.

Arch Linux
```shell
$ sudo pacman -Sy cmake ninja
```

#### Steps:
1. Clone this repository to a folder of your choice
```shell
$ git clone https://github.com/LogicApples/cpp-helloworld
```
2. cd into the new directory
```shell
$ cd <cpp-helloworld>
```
3. Run build.sh (Debug or Release) to create an executable binary
```shell
$ ./build.sh Debug|Release
```
4. This will create an executable binary which can be used in this directory only. If you wish to install it globally, run install.sh
```shell
$ ./install.sh
```

## Updating
To update the program go to the cloned directory and enter the following commands:
```shell
$ git pull
$ ./build.sh
$ ./install.sh
```

## Uninstall
If you haven't ran the install script you can just delete the directory you cloned into when installing.
If you ran the install script then you can uninstall the program globally with this command:
```shell
$ <ProgramBinary> self-uninstall
```