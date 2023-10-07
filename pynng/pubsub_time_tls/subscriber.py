# Copyright (C) 2023 twyleg
import json
import pynng
from pathlib import Path


FILE_DIR = Path(__file__).parent
address = "tls+tcp://localhost:5556"


if __name__ == "__main__":

    with pynng.Sub0() as sub:

        tls_config = pynng.TLSConfig(pynng.TLSConfig.MODE_CLIENT,
                                         ca_files=[str(FILE_DIR / "certs/ca.crt")])
        sub.tls_config = tls_config

        sub.subscribe("")
        sub.dial(address)

        i = 0
        while True:
            msg = sub.recv_msg()
            time_date_dict = json.loads(msg.bytes.decode())
            print(f"{i} Received time_date message: {time_date_dict}")
            i += 1
