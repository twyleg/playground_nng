# Copyright (C) 2023 twyleg
import pynng
import time
import json

from datetime import datetime


address = "ipc:///tmp/pubsub_time.ipc"


def get_json_time_date_string_as_bytes() -> bytes:
    current_time = datetime.now()

    time_date = {
        "time": current_time.strftime("%X"),
        "date": current_time.strftime("%x"),
    }

    return json.dumps(time_date).encode()


if __name__ == '__main__':

    with pynng.Pub0() as pub:
        pub.listen(address)

        i = 0
        while True:

            time_date = get_json_time_date_string_as_bytes()

            print(f"{i}: Publishing time_date {time_date}")
            pub.send(time_date)
            i += 1
            time.sleep(1.0)
