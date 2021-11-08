import subprocess, pathlib, sys, os
from subprocess import Popen
from pathlib import Path
import uuid

from python_telnet_vlc import *

# This might be a terrible idea. Too bad:
class VLCProcess(Popen):
    path: Path
    host: str
    port: int
    password: uuid.UUID
    
    connection: VLCTelnet
    
    def __init__ (self, *args, **kwargs):
        self.path = Path(sys.executable).parent.joinpath("vlc.exe" if os.name == "nt" else "vlc")
        self.host = "localhost"
        self.port = 4212
        self.password = str(uuid.uuid4()).replace('-', "_")
        
        super().__init__(
            [
                self.path,
                # f"--intf telnet",
                # f"-I telnet",
                f"--extraintf=telnet",
                f"--telnet-host={self.host}",
                f"--telnet-port={self.port}",
                f"--telnet-password={self.password}"
            ]
        )

        self.connection = self.create_telnet_control()
        
    
    def create_telnet_control(self) -> VLCTelnet:
        return VLCTelnet(
            host=self.host,
            port=self.port,
            password=str(self.password)
        )