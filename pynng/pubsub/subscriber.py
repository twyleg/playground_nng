import select

import pynng
import cv2
import numpy as np
import os
import sys

from pathlib import Path

from PySide6.QtGui import QGuiApplication
from PySide6.QtQml import QQmlApplicationEngine
from PySide6.QtCore import QTimer

from stopwatch_model import Model, State


address_publisher1 = "ipc:///tmp/publisher1.ipc"
address_publisher2 = "ipc:///tmp/publisher2.ipc"


class Gui:

    def __init__(self, sock: pynng.sub0) -> None: 
        self.diff = 0
        self.stopwatch_model = Model(0, 0, 0, 0)

        self.app = QGuiApplication(sys.argv)
        self.engine = QQmlApplicationEngine()

        self.engine.rootContext().setContextProperty("stopwatch_model", self.stopwatch_model)
        self.engine.load(os.fspath(Path(__file__).resolve().parent / "../frontend/qml/main.qml"))
        
        self.sock = sock
        self._notifier = QSocketNotifier(self.sock.recv_fd, QSocketNotifier.Read)
        self._notifier.activated.connect(self.test)
        
    def test(self):
        msg1 = self.sock.recv_msg()
        print(str(msg1.bytes))

    def run(self) -> None:
        if not self.engine.rootObjects():
            sys.exit(-1)
        sys.exit(self.app.exec())


if __name__ == "__main__":

    with pynng.Sub0() as subscriber1,\
            pynng.Sub0() as subscriber2:
        subscriber1.subscribe("lap_start")
        subscriber1.dial(address_publisher1)

        subscriber2.subscribe("section_finished")
        subscriber2.dial(address_publisher2)

        inputs = [subscriber1.recv_fd, subscriber2.recv_fd]

        sock_fd_dict = {
            subscriber1.recv_fd: subscriber1,
            subscriber2.recv_fd: subscriber2
        }

        gui = Gui(subscriber1)
        gui.run()



    # with pynng.Sub0() as subscriber1,\
    #         pynng.Sub0() as subscriber2:
    #     subscriber1.subscribe("lap_start")
    #     subscriber1.dial(address_publisher1)
    #
    #     subscriber2.subscribe("section_finished")
    #     subscriber2.dial(address_publisher2)
    #
    #     inputs = [subscriber1.recv_fd, subscriber2.recv_fd]
    #
    #     sock_fd_dict = {
    #         subscriber1.recv_fd: subscriber1,
    #         subscriber2.recv_fd: subscriber2
    #     }
    #
    #     while True:
    #
    #         readable_fds, _, _ = select.select(inputs, [], [])
    #
    #         for readable_fd in readable_fds:
    #             subscriber = sock_fd_dict[readable_fd]
    #             msg = subscriber.recv_msg()
    #             print(str(msg.bytes))


            # msg1 = sock1.recv_msg()
            # print(str(msg1.bytes))
            #
            # msg2 = sock2.recv_msg()
            # print(str(msg2.bytes))

            # image = np.frombuffer(msg.bytes, np.uint8).reshape(720, 1280, 3)
            #
            # cv2.imshow('image', image)
            # key = cv2.waitKey(1)
