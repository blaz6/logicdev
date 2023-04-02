import json
from colorama import Fore, Style, init
from os import system, mkdir, path
from shutil import copy2
init()

details = json.load(open("./logicdev.conf.json"))
for name, value in Fore.__dict__.items():
    if not name.startswith("__") and not callable(value):
        globals()[name] = value

def println(COLOR: str, arrow: bool, string: str):
  if(arrow == None): print(f"{COLOR}" + string);
  elif(not arrow): print(f"{COLOR}:: {RESET}{Style.BRIGHT}" + string + f"{RESET}")
  elif(arrow): print(f"{COLOR}   ->{RESET}{Style.BRIGHT} " + string + f"{RESET}")

def build_binaries(OS: str):
  match OS:
    case "LINUX":
      println(YELLOW, False, "Building linux binaries")
      println(MAGENTA, True, "Generating build files")
      system("cmake -G 'Ninja' -B" + details['LINUX_BUILD_DIR'] + " -DCMAKE_BUILD_TYPE=" + details['MODE'] + "> /dev/null 2>&1")
      println(MAGENTA, True, "Building project")
      system("cd " + details['LINUX_BUILD_DIR'] + " && ninja" + "> /dev/null 2>&1")
    case "WINDOWS":
      println(YELLOW, False, "Building windows binaries")
      println(MAGENTA, True, "Generating build files")
      system("cmake -G 'Ninja' -B" + details['WINDOWS_BUILD_DIR'] + " -DCMAKE_BUILD_TYPE=" + details['MODE'] + " -DCMAKE_TOOLCHAIN_FILE=../../toolchains/mingw-w64-x86_64.cmake" + "> /dev/null 2>&1")
      println(MAGENTA, True, "Building project")
      system("cd " + details['WINDOWS_BUILD_DIR'] + " && ninja" + "> /dev/null 2>&1")
    case _:
      println(RED, None, "Not a valid Operating System: " + f"{details['TARGETS']}");
      println(GREEN, True, "Valid operating systems: " + "['LINUX', 'WINDOWS']")
      raise SystemExit(1)

println(YELLOW, None, f"Using {details['MODE']} Mode!")
println(BLUE, True, f'Selected targets: {details["TARGETS"]}')

if not path.isdir(details['BUILD_DIR']):
  mkdir(details['BUILD_DIR'])
  mkdir(details['BINARIES_DIR'])
  for target in details["TARGETS"]:
    mkdir(details[target + "_BUILD_DIR"])

for target in details["TARGETS"]:
  build_binaries(target)

println(YELLOW, False, f"Distributing binaries in ./{details['BINARIES_DIR']}")
for target in details["TARGETS"]:
  if path.exists(details[target + "_BUILD_DIR"] + "/" + details["TARGET_FILENAME"]):
    copy2(details[target + '_BUILD_DIR'] + "/" + details["TARGET_FILENAME"], details['BINARIES_DIR'])

println(GREEN, None, "Done")