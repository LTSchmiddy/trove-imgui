from sqlalchemy import *
from sqlalchemy.orm import relationship

import db

class JobSite(db.Base):
    __tablename__ = 'job_site'

    # Item Common
    id = Column(Integer, primary_key=True, autoincrement=True)
    description = Column(String)
    project = Column(String)
    street_address = Column(String)
    city = Column(String)
    state = Column(String(2))
    zip_code = Column(Integer)
    
    # Internal info
    # current_equipment = relationship("Equipment", back_populates="current_location_ref")
    # assigned_equipment = relationship("Equipment", back_populates="assigned_location_ref")