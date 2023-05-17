import pynng
import time

from test_image_generator import TestImageGenerator

address = "ipc:///tmp/publisher1.ipc"


def send_lap_start(pub: pynng.Pub0):

    payload = '''
    {
      "sector_1_best_time": "<TIME>",
      "sector_2_best_time": "<TIME>",
      "sector_3_best_time": "<TIME>".
      "lap_best_time": "<TIME>"
    } '''

    msg = f"lap_start: {payload}"
    print(f"Publishing lap_start: {msg}")
    pub.send(msg.encode())

def send_section_finished(pub: pynng.Pub0):
    payload = '''
    {
      "sector_number": 1/2/3
      "sector_time": "<TIME>"
      "sector_valid": "true/false"
      "type": yellow/green/purple
    } '''

    msg = f"section_finished: {payload}"
    print(f"Publishing section_finished: {msg}")
    pub.send(msg.encode())


if __name__ == '__main__':

    test_image_generator = TestImageGenerator()

    with pynng.Pub0() as pub:
        pub.listen(address)

        i = 0
        while True:

            send_lap_start(pub)
            send_section_finished(pub)

            time.sleep(5.0)

            # image = test_image_generator.get_test_image()
            # print(f'Publishing image {i}')
            # pub.send(image.tobytes())
            # time.sleep(1.0/60.0)
