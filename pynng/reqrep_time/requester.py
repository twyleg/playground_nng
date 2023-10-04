# Copyright (C) 2023 twyleg
import pynng
import time


address = "ipc:///tmp/reqrep_time.ipc"


if __name__ == '__main__':

    with pynng.Req0(dial=address) as req:

        i = 0
        while True:
            print(f"{i} Requesting time!")
            i += 1
            req.send("time".encode())
            data = req.recv()
            print(f"Received time: {data.decode()}")
            time.sleep(1.0)
