import os

from lib_trove import TroveInstance
lib_trove_instance: TroveInstance = None

def init():
    global lib_trove_instance
    lib_trove_instance = TroveInstance()
    return lib_trove_instance
    
def shutdown():
    global lib_trove_instance
    lib_trove_instance.shutdown()
