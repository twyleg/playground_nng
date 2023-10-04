# Copyright (C) 2023 twyleg
import json
from datetime import datetime

import pynng
import time


address = "ipc:///tmp/reqrep_time.ipc"


if __name__ == '__main__':

    with pynng.Rep0(listen=address) as rep:

        i = 0
        while True:

            response = rep.recv()

            current_time = datetime.now()

            payload = {
                "time": current_time.strftime("%X"),
            }

            print(f"Responding with time: {payload}")
            rep.send(json.dumps(payload).encode())

