# from __future__ import __annotations__
import sqlalchemy
from sqlalchemy import *
from sqlalchemy.engine import Engine
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, scoped_session
from sqlalchemy.orm.decl_api import DeclarativeMeta
from sqlalchemy.sql.schema import MetaData

Base: DeclarativeMeta = declarative_base()
metadata: MetaData = Base.metadata

from . import tables
# def init(connection_string: str = None, reset=False):
#     global db_engine    
#     db_engine = create_engine(connection_string, reset)
    
def new_engine(connection_string: str, reset=False):   
    engine = create_engine(connection_string)
    if reset:
        metadata.drop_all(engine)
    metadata.create_all(engine)
    
    return engine

def get_session(engine: Engine = None):
    return scoped_session(sessionmaker(bind=engine))

