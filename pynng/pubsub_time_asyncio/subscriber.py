# Copyright (C) 2023 twyleg
import json
import pynng
import asyncio
import aiohttp
import aiohttp.client_exceptions


address = "ipc:///tmp/pubsub_time_asyncio.ipc"


async def receive_nng_messages(queue: asyncio.Queue):
    with pynng.Sub0() as sock:
        sock.subscribe("")
        sock.dial(address)

        i = 0

        while True:
            msg = await sock.arecv_msg()
            time_date_dict = json.loads(msg.bytes.decode())
            print(f"{i} Received time_date message: {time_date_dict}")
            i += 1
            await queue.put(time_date_dict)


async def publish_messages(queue: asyncio.Queue):
    timeout = aiohttp.ClientTimeout(total=2, connect=None)
    i = 0
    while True:
        time_date_dict = await queue.get()

        async with aiohttp.ClientSession(timeout=timeout) as session:
            try:
                async with session.post("http://localhost:5000/feedme", json=time_date_dict, timeout=timeout) as resp:
                    await resp.text()
                    if resp.ok:
                        print(f"{i} Message forwarded successfully to HTTP endpoint!")
                    else:
                        print(f"{i} Unable to forward Message to HTTP endpoint, status={resp.status}!")
            except aiohttp.client_exceptions.ClientConnectorError as e:
                print(f"{i} Unable to connect to HTTP endpoint!")
            i += 1


if __name__ == "__main__":

    queue = asyncio.Queue()

    loop = asyncio.get_event_loop()
    receive_nng_messages_task = loop.create_task(receive_nng_messages(queue))
    publish_messages_task = loop.create_task(publish_messages(queue))
    loop.run_until_complete(asyncio.wait([receive_nng_messages_task, publish_messages_task]))

    loop.run_forever()
