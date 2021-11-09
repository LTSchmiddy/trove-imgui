# Scanners locate media files for storage in the library. They don't look up any meta-data for videos.
# They simply find videos, and return a MRL that VLC can play from.
import os, json, threading
from typing import Any
from pathlib import Path

from sqlalchemy.engine import Engine

from ..db.tables import Video

recognized_extensions = json.loads(
    Path(__file__).parent.joinpath("vlc_known_extensions.json").read_text()
)
# print(f"{recognized_extensions=}")


class BaseScanner:
    engine: Engine = None
    thread: threading.Thread = None

    @classmethod
    def get_type_name(cls):
        return "Unnamed Scanner Type"

    @classmethod
    def get_subclass(cls, name: str):
        for i in BaseScanner.__subclasses__():
            if i.__name__ == name:
                return i

        return None

    def __init__(self, engine: Engine, name: str):
        self.engine = engine
        self.name = name

    def get_status_text(self) -> str:
        return "Processing..."

    def run(self):
        print("TRYING TO RUN...")
        self.thread = threading.Thread(None, self.scan, name=self.get_type_name())
        self.thread.start()

    def scan(self):
        pass


class FileScanner(BaseScanner):
    @classmethod
    def get_type_name(cls):
        return "File Scanner"

    def __init__(self, engine: Engine, name: str, root_path=str):
        super().__init__(engine, name)
        self.root = Path(root_path)

    def get_status_text(self) -> str:
        return "Processing..."

    def scan(self):
        session = self.engine.get_session()

        for (
            s_path,
            s_dirs,
            s_files,
        ) in os.walk(self.root):
            path = Path(s_path)
            dirs = [path.joinpath(i) for i in s_dirs]
            files = [path.joinpath(i) for i in s_files]

            for i in files:
                search = session.query(Video).filter(Video.mrl == i.as_uri()).first()
                if search is not None:
                    continue

                nv = Video()
                nv.mrl = i.as_uri()
                nv.fname = i.name
                nv.description = "Found by File Scanner."
                nv.source = self.name

                session.add(nv)

        session.commit()
        session.close()


def load_scanners(engine: Engine, config=None) -> dict[str, BaseScanner]:
    retVal = {}

    for key, value in config.items():
        new_scanner = BaseScanner.get_subclass(value["scanner"])(
            engine, key, **value["scan_config"]
        )
        retVal[key] = new_scanner

    return retVal
