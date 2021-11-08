import os

from lib_trove import settings
from lib_trove import db
from lib_trove import scanning

def init():
    settings.load_settings()
    print("Loading Database...")
    db.init(True)
    
    
def shutdown():
    settings.save_settings()

def test_scan():
    scanners = scanning.load_scanners()
    for name, scanner in scanners.items():
        scanner.run()
        
def test_module(unknown):
    print("Testing...")
    print(unknown.test_function())