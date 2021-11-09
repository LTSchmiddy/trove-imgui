import os, subprocess
from pathlib import Path

# start_path = Path(__file__).joinpath("")
# print(f"{start_path}")

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