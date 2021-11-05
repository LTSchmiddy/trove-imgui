from sqlalchemy import *
from sqlalchemy.orm import relationship

import db

class EquipmentCategory(db.Base):
    __tablename__ = 'equipment_category'
    id = Column(Integer, primary_key=True, autoincrement=True)
    name = Column(String, unique=True)
    
    # Internal info
    equipment_ref = relationship("Equipment")
    

class Equipment(db.Base):
    __tablename__ = 'equipment'

    # Item Common
    id = Column(String, primary_key=True)
    description = Column(String)
    category_id = Column(Integer, ForeignKey('equipment_category.id'))
    make_model = Column(String)
    serial_number = Column(String)
    current_location_id = Column(Integer, ForeignKey('job_site.id'))
    assigned_location_id = Column(Integer, ForeignKey('job_site.id'))
    
    # Internal info
    category_ref = relationship("EquipmentCategory", back_populates="equipment_ref")
    # current_location_ref = relationship("Location")
    # assigned_location_ref = relationship("Location")
    