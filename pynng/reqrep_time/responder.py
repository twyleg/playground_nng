# Copyright (C) 2023 twyleg
import json
from datetime import datetime

import pynng


address = "ipc:///tmp/reqrep_time_date.ipc"


def get_json_time_string_as_bytes() -> bytes:
    current_time = datetime.now()

    time_date = {
        "time": current_time.strftime("%X"),
    }

    return json.dumps(time_date).encode()


def get_json_date_string_as_bytes() -> bytes:
    current_time = datetime.now()

    time_date = {
        "date": current_time.strftime("%x"),
    }

    return json.dumps(time_date).encode()


if __name__ == '__main__':

    with pynng.Rep0(listen=address) as rep:

        while True:

            request_msg = rep.recv_msg()
            request = request_msg.bytes.decode()

            print(f"Received request: {request}")
            match request:
                case "time":
                    time = get_json_time_string_as_bytes()
                    rep.send(time)
                    print(f"Responded with time: {time.decode()}")
                case "date":
                    date = get_json_date_string_as_bytes()
                    rep.send(date)
                    print(f"Responded with date: {date.decode()}")
