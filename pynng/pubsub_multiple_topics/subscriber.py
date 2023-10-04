# Copyright (C) 2023 twyleg
import pynng
from typing import List, Tuple


address = "ipc:///tmp/pubsub_multiple_topics.ipc"


class MultiSub0(pynng.Sub0):

    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self._topics: List[str] = []

    def subscribe(self, topic: str) -> None:
        self._topics.append(topic)
        super().subscribe(topic)

    def _split_message(self, msg: bytes) -> Tuple[str, bytes]:
        for topic in self._topics:
            if msg.bytes.startswith(topic.encode()):
                return topic, msg.bytes[len(topic):].decode()

    def recv_msg(self, **kwargs) -> Tuple[str, bytes]:
        msg = super().recv_msg(**kwargs)
        return self._split_message(msg)

    async def arecv_msg(self) -> Tuple[str, bytes]:
        msg = await super().arecv_msg()
        return self._split_message(msg)


if __name__ == "__main__":

    with MultiSub0() as sock:
        sock.subscribe("time:")
        sock.subscribe("date:")

        sock.dial(address)

        while True:
            topic, data = sock.recv_msg()
            print(f"Received topic='{topic}', data='{data}'")
