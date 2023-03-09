import json
from colorama import Fore, Style, init
import os
import shutil
init()

details = json.load(open("./logicdev.conf.json"))
for name, value in Fore.__dict__.items():
    if not name.startswith("__") and not callable(value):
        globals()[name] = value
BRIGHT = Style.BRIGHT

def build_binaries(OS: str):
  match OS:
    case "LINUX":
      print(f"{YELLOW}:: {RESET}{BRIGHT}Building linux binaries{RESET}")
      print(f"{MAGENTA}   ->{RESET}{BRIGHT} Generating build files{RESET}")
      os.system("cmake -G 'Ninja' -B" + details['LINUX_BUILD_DIR'] + " -DCMAKE_BUILD_TYPE=" + details['MODE'] + "> /dev/null 2>&1")
      print(f"{MAGENTA}   ->{RESET}{BRIGHT} Building project{RESET}")
      os.system("cd " + details['LINUX_BUILD_DIR'] + " && ninja")# + "> /dev/null 2>&1")
    case "WINDOWS":
      print(f"{YELLOW}:: {RESET}{BRIGHT}Building windows binaries{RESET}")
      print(f"{MAGENTA}   ->{RESET}{BRIGHT} Generating build files{RESET}")
      os.system("cmake -G 'Ninja' -B" + details['WINDOWS_BUILD_DIR'] + " -DCMAKE_BUILD_TYPE=" + details['MODE'] + " -DCMAKE_TOOLCHAIN_FILE=../../toolchains/mingw-w64-x86_64.cmake" + "> /dev/null 2>&1")
      print(f"{MAGENTA}   ->{RESET}{BRIGHT} Building project{RESET}")
      os.system("cd " + details['WINDOWS_BUILD_DIR'] + " && ninja")# + "> /dev/null 2>&1")
    case _:
        print(f"{RED}Not a valid Operating System");

print(f"{BRIGHT}{YELLOW}:: {RESET}{BRIGHT}Using {details['MODE']} Mode!{RESET}")

if not os.path.isdir(details['BUILD_DIR']):
  os.mkdir(details['BUILD_DIR'])
  os.mkdir(details['BINARIES_DIR'])
  os.mkdir(details['LINUX_BUILD_DIR'])
  os.mkdir(details['WINDOWS_BUILD_DIR'])

build_binaries("LINUX")
build_binaries("WINDOWS")

print(f"{YELLOW}:: {RESET}{BRIGHT}Distributing binaries in ./{details['BINARIES_DIR']}{RESET}")
if os.path.exists(details['LINUX_BUILD_DIR'] + "/logicdev"):
  shutil.copy2(details['LINUX_BUILD_DIR'] + "/logicdev", details['BINARIES_DIR'])
if os.path.exists(details['LINUX_BUILD_DIR'] + "/logicdev.exe"):
  shutil.copy2(details['WINDOWS_BUILD_DIR'] + "/logicdev.exe", details['BINARIES_DIR'])

print(f"{GREEN}:: {RESET}{BRIGHT}Done{RESET}")