# -c \"import os, shutil\; print(os.getcwd())\; # shutil.copytree('src/py', '${CMAKE_CURRENT_BINARY_DIR}/bin/py', ignore=shutil.ignore_patterns('**/__pycache__')) \"

import sys, os, shutil
from pathlib import Path

bin_directory = Path(sys.argv[1])

print("Running Py Builder...")
shutil.copytree(
    f"{Path(__file__).parent}/src/py",
    f"{bin_directory}/bin/py",
    ignore=shutil.ignore_patterns("**.pyc"),
    dirs_exist_ok=True,
)

print("Copying of .py files complete.")
