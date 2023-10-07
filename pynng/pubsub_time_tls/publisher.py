# Copyright (C) 2023 twyleg
import pynng
import time
import json

from datetime import datetime
from pathlib import Path


FILE_DIR = Path(__file__).parent
address = "tls+tcp://localhost:5556"


def get_json_time_date_string_as_bytes() -> bytes:
    current_time = datetime.now()

    time_date = {
        "time": current_time.strftime("%X"),
        "date": current_time.strftime("%x"),
    }

    return json.dumps(time_date).encode()


if __name__ == '__main__':

    with pynng.Pub0() as pub:

        tls_config = pynng.TLSConfig(pynng.TLSConfig.MODE_SERVER,
                             cert_key_file=str(FILE_DIR / "certs/key_pair_file.pem"))
        pub.tls_config = tls_config
        pub.listen(address)

        i = 0
        while True:

            time_date = get_json_time_date_string_as_bytes()

            print(f"{i}: Publishing time_date {time_date}")
            pub.send(time_date)
            i += 1
            time.sleep(1.0)
