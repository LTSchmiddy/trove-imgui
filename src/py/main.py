import os

from sqlalchemy.orm.scoping import scoped_session

from lib_trove import TroveInstance
from py import lib_trove

lib_trove_instance: TroveInstance = None


def init():
    global lib_trove_instance
    lib_trove_instance = TroveInstance()
    return lib_trove_instance


def shutdown():
    global lib_trove_instance
    lib_trove_instance.shutdown()

def get_videos(session: scoped_session):
    return session.query(lib_trove.db.tables.Video).all()