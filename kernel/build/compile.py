import subprocess
import config
import os

def compile(filePath: str) -> None:
    filetype = filePath.split(".")[-1]
    binpath = f"bin/{filePath.split('.')[0].replace('/', '_')}.o"
    if filetype == "c":
        print(f"{filePath}")
        subprocess.run(f"{config.CC} {config.CCFLAGS} -c {filePath} -o {binpath}", shell=True, check=True)

def compileDir(folderPath: str) -> None:
    for item in os.listdir(folderPath):
        if os.path.isfile(f"{folderPath}/{item}"): compile(f"{folderPath}/{item}")
        elif os.path.isdir(f"{folderPath}/{item}"): compileDir(f"{folderPath}/{item}")