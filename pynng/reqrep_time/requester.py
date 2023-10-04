# Copyright (C) 2023 twyleg
import asyncio
import pynng


address = "ipc:///tmp/reqrep_time_date.ipc"


async def request_time() -> None:
    with pynng.Req0(dial=address) as req:

        while True:
            print("Requesting time!")
            req.send("time".encode())
            response = req.recv_msg()
            print(f"Received time: {response.bytes.decode()}")
            await asyncio.sleep(1.0)


async def request_date() -> None:
    with pynng.Req0(dial=address) as req:

        while True:
            print("Requesting date!")
            req.send("date".encode())
            response = req.recv_msg()
            print(f"Received date: {response.bytes.decode()}")
            await asyncio.sleep(5.0)


if __name__ == '__main__':

    loop = asyncio.get_event_loop()
    request_time_task = loop.create_task(request_time())
    request_date_task = loop.create_task(request_date())
    loop.run_until_complete(asyncio.wait([request_time_task, request_date_task]))

    loop.run_forever()
