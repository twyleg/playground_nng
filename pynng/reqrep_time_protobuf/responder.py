# Copyright (C) 2023 twyleg
import time_pb2
import pynng
import json
from datetime import datetime


address = "ipc:///tmp/reqrep_time_date_protobuf.ipc"


def get_time_string() -> str:
    current_time = datetime.now()

    time_date = {
        "time": current_time.strftime("%X"),
    }

    return json.dumps(time_date)


def get_date_string() -> str:
    current_time = datetime.now()

    time_date = {
        "date": current_time.strftime("%x"),
    }

    return json.dumps(time_date)


if __name__ == '__main__':

    with pynng.Rep0(listen=address) as rep:

        while True:

            request_msg = rep.recv_msg()

            request = time_pb2.Request()
            request.ParseFromString(request_msg.bytes)

            print(f"Received request: {request}")
            match request.request_type:
                case time_pb2.Request.RequestType.REQUEST_TYPE_TIME:
                    time = time_pb2.Time()
                    time.time = get_time_string()
                    rep.send(time.SerializeToString())
                    print(f"Responded with time: {time}")
                case time_pb2.Request.RequestType.REQUEST_TYPE_DATE:
                    date = time_pb2.Date()
                    date.date = get_date_string()
                    rep.send(date.SerializeToString())
                    print(f"Responded with date: {date}")
