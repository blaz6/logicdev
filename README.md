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
$ git clone https://github.com/LogicApples/logicdev
```
2. cd into the new directory
```shell
$ cd <logicdev>
```
3. Run build.sh to create an executable binary
```shell
$ ./build.sh Debug|Release (Default: Release)
```

## Updating
To update the program go to the cloned directory and enter the following commands:
```shell
$ git pull
$ ./build.sh
```

## Uninstall
You can uninstall the program globally with this command:
```shell
$ <ProgramBinary> self-uninstall
```