from pathlib import Path
from typing import Any
from threading import Thread

from sqlalchemy.engine import Engine

from . import db
from . import scanning
from . import scrapers
from . import config
from . import vlc_telnet


class TroveInstance:
    config_file: Path
    config: dict[str, Any]

    engine: Engine
    scanners: dict[str, scanning.BaseScanner]
    
    scan_thread: Thread

    def __init__(self, config_file: Path = None):
        self.config = config.load(config_file)

        print(f"{self.config=}")

        self.engine = db.new_engine(self.config["db"]["connection-string"])
        self.scanners = scanning.load_scanners(self.engine, self.config["sources"])
        
        self.scan_thread = None
        
        print("Instance loaded...")

    def scan_async(self, callback):
        if self.scan_thread is not None and self.scan_thread.is_alive():
            print("Already running a scan...")
            
        
        self.scan_thread = Thread(None, self.scan, "Scanner Thread", args=(callback,))
        self.scan_thread.start()

    def scan(self, callback):
        for name, scanner in self.scanners.items():
            scanner.scan()
        
        callback()
    
    def get_session(self):
        return db.get_session(self.engine)
    
    def shutdown(self):
        config.save(self.config)
        print("Instance exited...")
