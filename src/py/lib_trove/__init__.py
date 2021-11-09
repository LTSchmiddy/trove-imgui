from pathlib import Path
from typing import Any
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

    def __init__(self, config_file: Path = None):
        self.config = config.load(config_file)

        print(f"{self.config=}")

        self.engine = db.new_engine(self.config["db"]["connection-string"])
        self.scanners = scanning.load_scanners(self.engine, self.config["sources"])

        print("Instance loaded...")

    def scan_all(self, callback):
        for name, scanner in self.scanners.items():
            scanner.run()
            
        callback(f"ok then... {name}")

    def shutdown(self):
        config.save(self.config)
        print("Instance exited...")
