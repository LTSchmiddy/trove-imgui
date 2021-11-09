import sys, os, debugpy
from pathlib import Path


port = int(os.environ["TROVE_PY_DEBUG_PORT"])
print(f"Waiting for Python Debugger attachment on port {port}")

# ptvsd.enable_attach(address=("127.0.0.1", port))
# ptvsd.wait_for_attach()

# this is cursed, but debugpy needs the path to the REAL python executable:
old_exec = sys.executable
sys.executable = str(
    Path(old_exec).parent.joinpath("python.exe" if os.name == "nt" else "python")
)
debugpy.listen(port)
debugpy.wait_for_client()
sys.executable = old_exec
