# Copyright (C) 2023 twyleg
import time_pb2
import asyncio
import pynng


address = "ipc:///tmp/reqrep_time_date_protobuf.ipc"


async def request_time() -> None:
    with pynng.Req0(dial=address) as req:

        while True:
            print("Requesting time!")
            request = time_pb2.Request()
            request.request_type = time_pb2.Request.RequestType.REQUEST_TYPE_TIME
            req.send(request.SerializeToString())

            response = req.recv_msg()
            time = time_pb2.Time()
            time.ParseFromString(response.bytes)

            print(f"Received time: {time}")
            await asyncio.sleep(1.0)


async def request_date() -> None:
    with pynng.Req0(dial=address) as req:

        while True:
            print("Requesting date!")
            request = time_pb2.Request()
            request.request_type = time_pb2.Request.RequestType.REQUEST_TYPE_DATE

            req.send(request.SerializeToString())

            response = req.recv_msg()
            date = time_pb2.Time()
            date.ParseFromString(response.bytes)
            print(f"Received date: {date}")
            await asyncio.sleep(5.0)


if __name__ == '__main__':

    loop = asyncio.get_event_loop()
    request_time_task = loop.create_task(request_time())
    request_date_task = loop.create_task(request_date())
    loop.run_until_complete(asyncio.wait([request_time_task, request_date_task]))

    loop.run_forever()
