from sqlalchemy import *
from sqlalchemy.orm import relationship

from ... import db


class Video(db.Base):
    __tablename__ = "video"

    # Item Common
    mrl = Column(String, primary_key=True)
    fname = Column(String)
    description = Column(String)

    source = Column(String)

    # Internal info
    # source_id = Column(Integer, ForeignKey('video_source.id'))
    # source = relationship("VideoSource", back_populates="videos")
