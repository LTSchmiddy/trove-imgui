import sys
import os
import io
import typing
import types
import string
from typing import List

class CustomStdout:
    stream: str
    appended_stream: str
    substreams: List[io.TextIOWrapper]

    def __init__(self, old_stdout = None, output_log = None):
        self.old_stdout = old_stdout
        self.substreams = []

        if self.old_stdout is not None:
            self.substreams.append(old_stdout)
        if output_log is not None:
            self.substreams.append(open(output_log, 'w'))

        self.stream = ""
        self.appended_stream = ""

    def write(self, data):
        self.stream += data
        self.appended_stream += data
        
        for i in self.substreams:
            i.write(data)

    def get_appended_stream(self):
        retVal = self.appended_stream
        self.appended_stream = ""
        return retVal

    def flush(self):
        for i in self.substreams:
            i.flush()
    
    def close(self):
        for i in self.substreams:
            i.close()

custom_stdout = CustomStdout(sys.stdout, "out.log")
custom_stderr = CustomStdout(sys.stderr, "err.log")
def init():
    sys.stdout = custom_stdout
    sys.stderr = custom_stderr