import os
from pathlib import Path

for path_name, dir_names, file_names in os.walk("./build/x64-windows-DEBUG"):
    path: Path = Path(path_name)
    dirs: list[Path] = [path.joinpath(i) for i in dir_names]
    files: list[Path] = [path.joinpath(i) for i in file_names]
    
    for i in files:
        if i.suffix == ".pyd":
            new_name = i.with_stem(i.stem + "_d")
            i.rename(new_name)
