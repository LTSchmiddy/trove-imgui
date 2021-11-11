import os, json
from pathlib import Path
import imgui_style

style_path = Path("./imgui_style.json")

def save_style_dict(style: dict):
    style_file = open(style_path, 'w')
    json.dump(style, style_file, sort_keys=True, indent=4)
    style_file.close()
    
def load_style_dict() -> dict:
    if not style_path.exists():
        return {}
    
    style_file = open(style_path, 'r')
    retVal = json.load(style_file)
    style_file.close()
    
    return retVal

def save_style():
    save_style_dict(imgui_style.get_style())
    
def load_style():
    imgui_style.set_style(load_style_dict())