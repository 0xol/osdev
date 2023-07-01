import config
from build.compile import *
import subprocess

if (os.path.isdir("bin")): subprocess.run("rm -rf bin", shell=True)
os.mkdir("bin")

compileDir(f"boot/{config.BOOTLOADER}")
compileDir(f"kernel")
compileDir(f"klibc")

subprocess.run(f"{config.LD} {config.LDFLAGS} bin/*.o -o viz", shell=True, check=True)