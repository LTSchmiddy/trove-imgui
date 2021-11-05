import os

import settings
import db

def init():
    settings.load_settings()
    print("Loading Database...")
    db.init()
    
def shutdown():
    settings.save_settings()
