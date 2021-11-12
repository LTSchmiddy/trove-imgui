import std_handler
std_handler.init()

import os, json
from sqlalchemy.orm.scoping import scoped_session
import lib_trove 
from lib_trove import TroveInstance


lib_trove_instance: TroveInstance = None

style_path = "./imgui_style.json"

def init():
    global lib_trove_instance
    lib_trove_instance = TroveInstance()
    return lib_trove_instance


def shutdown():
    global lib_trove_instance
    lib_trove_instance.shutdown()

def get_videos(session: scoped_session):
    return session.query(lib_trove.db.tables.Video).all()