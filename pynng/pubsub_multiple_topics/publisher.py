# Copyright (C) 2023 twyleg
import asyncio
import pynng
import json

from datetime import datetime

address = "ipc:///tmp/pubsub_multiple_topics.ipc"


class MultiPub0(pynng.Pub0):
    def __init__(self, **kwargs):
        super().__init__(**kwargs)

    @classmethod
    def _assemble_message_with_topic(cls, topic: str, data: str | bytes) -> bytes:
        assembled_data = None
        if isinstance(data, str):
            assembled_data = f"{topic}:{data}".encode()
        elif isinstance(data, bytes):
            assembled_data = f"{topic}:".encode() + data
        return assembled_data

    def send_with_topic(self, topic: str, data: str | bytes, **kwargs) -> None:
        self.send(self._assemble_message_with_topic(topic, data), **kwargs)

    async def asend_with_topic(self, topic: str, data: str | bytes) -> None:
        await self.asend(self._assemble_message_with_topic(topic, data))


async def topic_date_task(pub: MultiPub0):
    while True:
        current_time = datetime.now()

        payload = {
            "date": current_time.strftime("%x"),
        }

        print(f"Publishing date: {payload}")
        await pub.asend_with_topic("date", json.dumps(payload))
        await asyncio.sleep(5.0)


async def topic_time_task(pub: MultiPub0):
    while True:
        current_time = datetime.now()

        payload = {
            "time": current_time.strftime("%X"),
        }

        print(f"Publishing time: {payload}")
        await pub.asend_with_topic("time", json.dumps(payload))
        await asyncio.sleep(1.0)


if __name__ == "__main__":

    with MultiPub0() as pub:
        pub.listen(address)

        loop = asyncio.get_event_loop()
        publish_date_task = loop.create_task(topic_date_task(pub))
        publish_time_task = loop.create_task(topic_time_task(pub))
        loop.run_until_complete(asyncio.wait([publish_time_task, publish_date_task]))

        loop.run_forever()
