import pynng
import cv2
import numpy as np

address = "ipc:///tmp/pubsub.ipc"


if __name__ == "__main__":
    with pynng.Sub0() as sock:
        sock.subscribe("")
        sock.dial(address)

        while True:
            msg = sock.recv_msg()

            image = np.frombuffer(msg.bytes, np.uint8).reshape(720, 1280, 3)

            cv2.imshow('image', image)
            key = cv2.waitKey(1)
