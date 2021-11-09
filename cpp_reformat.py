# Used to reformat ALL project C++ code with Clang-Format.
# Python code is formatted via Black.
import os, subprocess
from pathlib import Path

for path_name, dir_names, file_names in os.walk("./src/cpp/"):
    path: Path = Path(path_name)
    dirs: list[Path] = [path.joinpath(i) for i in dir_names]
    files: list[Path] = [path.joinpath(i) for i in file_names]
    
    print(f"{path}")
    
    subprocess.run(
        [
            "clang-format",
            "-i",
            "*.cpp",
            "*.h"
        ],
        cwd=str(path)
    )