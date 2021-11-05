import enum
from sqlalchemy import *
from sqlalchemy.orm import relationship

import db

# Child DBs:
class Employee(db.Base):
    __tablename__ = 'employee'
    id = Column(Integer, primary_key=True, autoincrement=True)
    first = Column(String, nullable=False)
    middle = Column(String(1), nullable=True)
    last = Column(String, nullable=False)
