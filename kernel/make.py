import config
from build.compile import *
import subprocess

compileDir(f"boot/{config.BOOTLOADER}")
compileDir(f"kernel")

subprocess.run(f"{config.LD} {config.LDFLAGS} bin/*.o -o viz", shell=True, check=True)