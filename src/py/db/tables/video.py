from sqlalchemy import *
from sqlalchemy.orm import relationship

import db

class Video(db.Base):
    __tablename__ = 'videos'

    # Item Common
    id = Column(Integer, primary_key=True, autoincrement=True)
    fname = Column(String)
    description = Column(String)
    mrl = Column(String, unique=True)
    
    
    # Internal info
    # current_equipment = relationship("Equipment", back_populates="current_location_ref")
    # assigned_equipment = relationship("Equipment", back_populates="assigned_location_ref")