# from __future__ import __annotations__
import sqlalchemy
from sqlalchemy import *
from sqlalchemy.engine import Engine
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker, scoped_session

import settings

# Base: sqlalchemy.ext.declarative.api.DeclarativeMeta = declarative_base()
Base = declarative_base()
metadata: MetaData = Base.metadata
db_engine: Engine = None

from . import tables

def init(reset=False):
    global Session, db_engine
    db_engine = create_engine(settings.current["db"]["connection-string"])
    if reset:
        metadata.drop_all(db_engine)
    metadata.create_all(db_engine)

def get_session():
    return scoped_session(sessionmaker(bind=db_engine))

