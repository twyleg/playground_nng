# Copyright (C) 2023 twyleg
import pynng
import time
import json

from datetime import datetime


address = "ipc:///tmp/pubsub_time_asyncio.ipc"


if __name__ == '__main__':

    with pynng.Pub0() as pub:
        pub.listen(address)

        i = 0

        while True:

            current_time = datetime.now()

            payload = {
                "time": current_time.strftime("%X"),
                "date": current_time.strftime("%x"),
            }

            print(f"{i}: Publishing date and time {payload}")
            pub.send(json.dumps(payload).encode())
            i += 1
            time.sleep(1.0)
