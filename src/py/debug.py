try:
    import importlib.machinery
    
    main_suffixes = []
    for i in importlib.machinery.EXTENSION_SUFFIXES:
        if i.startswith("_d"):
            main_suffixes.append(i[2:])

    importlib.machinery.EXTENSION_SUFFIXES += main_suffixes
    print(f"{importlib.machinery.EXTENSION_SUFFIXES=}")


    import ptvsd, os
    port = int(os.environ["TROVE_PY_DEBUG_PORT"])
    print(f"Waiting for Python Debugger attachment on port {port}")

    ptvsd.enable_attach(address=("127.0.0.1", port))
    # ptvsd.wait_for_attach()
    
except Exception as e:
    print(f"ERROR: {e}")
    