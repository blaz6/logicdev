import json
from os import geteuid, sys
from subprocess import check_call
from shutil import copy2
json_file = "./main.conf.json"

if __name__ == '__main__':
    if geteuid() == 0:
      details = json.load(open(json_file))
      copy2("./target/release/" + details["TARGET_FILENAME"], "/usr/bin")
    else:
        check_call(['sudo', sys.executable] + sys.argv)
