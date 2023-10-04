# Copyright (C) 2023 twyleg
import json
import pynng
import asyncio
import aiohttp
import aiohttp.client_exceptions


address = "ipc:///tmp/pubsub_time.ipc"


if __name__ == "__main__":

    with pynng.Sub0() as sock:
        sock.subscribe("")
        sock.dial(address)

        i = 0
        while True:
            msg = sock.recv_msg()
            time_date_dict = json.loads(msg.bytes.decode())
            print(f"{i} Received time_date message: {time_date_dict}")
            i += 1
