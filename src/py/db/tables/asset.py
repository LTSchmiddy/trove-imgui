import enum
from sqlalchemy import *
from sqlalchemy.orm import relationship

import db

# Asset Enums:
class AssetStatus(db.Base):
    __tablename__ = 'asset_status'
    id = Column(Integer, primary_key=True, autoincrement=True)
    name = Column(String, unique=True, nullable=False)

class AssetDepartment(db.Base):
    __tablename__ = 'asset_department'
    id = Column(Integer, primary_key=True, autoincrement=True)
    name = Column(String, unique=True)

# Asset Child Tables:
class AssetBrand(db.Base):
    __tablename__ = 'asset_brand'
    id = Column(Integer, primary_key=True, autoincrement=True)
    name = Column(String, unique=True)
    
class AssetCategory(db.Base):
    __tablename__ = 'asset_category'
    id = Column(Integer, primary_key=True, autoincrement=True)
    name = Column(String, unique=True)
    
    
# Table:
class Asset(db.Base):
    __tablename__ = 'asset'

    id = Column(Integer, primary_key=True, autoincrement=True)
    description = Column(String)
    purchase_date = Column(Date)
    brand_id = Column(Integer, ForeignKey('asset_brand.id'))
    model = Column(String)
    serial_number = Column(String)
    job_site_id = Column(Integer, ForeignKey('job_site.id'))
    category_id = Column(Integer, ForeignKey('asset_category.id'))
    department_id = Column(Integer, ForeignKey('asset_department.id'))
    status_id = Column(Integer, ForeignKey('asset_status.id'), nullable=False, default=1)
    
    assigned_employee_id = Column(Integer, ForeignKey('employee.id'))
    notes = Column(String)

        