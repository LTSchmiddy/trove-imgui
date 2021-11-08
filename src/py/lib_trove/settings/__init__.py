import sys
import os
import json
from colors import color
from pathlib import Path


exec_dir, exec_file = os.path.split(os.path.abspath(sys.argv[0]))

exec_dir = exec_dir.replace("\\", "/")

# determine if application is a script file or frozen exe
if getattr(sys, 'frozen', False):
    exec_dir = os.path.dirname(sys.executable)
# elif __file__:
    # exec_dir = os.path.dirname(__file__)

# If we're executing as the source version, the main .py file  is actually found in the `src` subdirectory
# of the project, and `exec_dir` is changed to reflect that. We'll create `exec_file_dir` in case we actually need the
# unmodified path to that script. Obviously, in build mode, these two values will be the same.
exec_file_dir = exec_dir

def is_build_version():
    return exec_file.endswith(".exe")


def is_source_version():
    return exec_file.endswith(".py")


if is_source_version():
    path_arr = exec_dir.split("/")
    exec_dir = "/".join(path_arr[: len(path_arr) - 1]).replace("/", "\\")

# print(f"Is Source: {is_source_version()}")
# print(f"Is Build: {is_build_version()}")
# print(f"Exec Dir: {exec_dir}")

settings_file_name = "settings.json"

global_settings_path = Path(sys.executable).parent.joinpath(settings_file_name)


def default_settings():
    return {
        "db": {
            "connection-string": "sqlite:///library.db"
        },
        "sources": {
            "local": {
                "scanner": "FileScanner",
                "scan_config": {
                    "root_path": "F:/Videos"
                }
            }
        }
    }

current = default_settings()


def load_settings(path: str = global_settings_path, settings_dict: dict = current):

    def recursive_load_list(main: list, loaded: list):
        for i in range(0, max(len(main), len(loaded))):
            # Found in both:
            if i < len(main) and i < len(loaded):
                if isinstance(loaded[i], dict):
                    recursive_load_dict(main[i], loaded[i])
                elif isinstance(loaded[i], list):
                    recursive_load_list(main[i], loaded[i])
                else:
                    main[i] = loaded[i]
            # Found in main only:
            elif i < len(loaded):
                main.append(loaded[i])


    def recursive_load_dict(main: dict, loaded: dict):
        new_update_dict = {}
        for key, value in main.items():
            if not (key in loaded):
                continue
            if isinstance(value, dict):
                recursive_load_dict(value, loaded[key])
            elif isinstance(value, list):
                recursive_load_list(value, loaded[key])
            else:
                new_update_dict[key] = loaded[key]
        
        # Load settings added to file:
        for key, value in loaded.items():
            if not (key in main):
                new_update_dict[key] = loaded[key]

        main.update(new_update_dict)

    # load preexistent settings file
    if os.path.exists(path) and os.path.isfile(path):
        try:
            imported_settings = json.loads(Path(path).read_text())
            # current.update(imported_settings)
            recursive_load_dict(settings_dict, imported_settings)
        except json.decoder.JSONDecodeError as e:
            print (color(f"CRITICAL ERROR IN LOADING SETTINGS: {e}", fg='red'))
            print (color("Using default settings...", fg='yellow'))
        
        
    # settings file not found
    else:
        save_settings(path, settings_dict)

def save_settings(path: str = global_settings_path, settings_dict: dict = current):
    outfile = open(path, "w")
    json.dump(settings_dict, outfile, indent=4)
    outfile.close()


