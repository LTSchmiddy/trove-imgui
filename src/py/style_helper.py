import os, json

style_path = "./imgui_style.json"

def save_style(style: dict):
    style_file = open(style_path, 'w')
    json.dump(style, style_file, sort_keys=True, indent=4)
    style_file.close()
    
def load_style() -> dict:
    style_file = open(style_path, 'r')
    retVal = json.load(style_file)
    style_file.close()
    
    return retVal