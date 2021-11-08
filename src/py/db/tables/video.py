from sqlalchemy import *
from sqlalchemy.orm import relationship

import db

class Video(db.Base):
    __tablename__ = 'job_site'

    # Item Common
    id = Column(Integer, primary_key=True, autoincrement=True)
    description = Column(String)
    
    
    # Internal info
    # current_equipment = relationship("Equipment", back_populates="current_location_ref")
    # assigned_equipment = relationship("Equipment", back_populates="assigned_location_ref")