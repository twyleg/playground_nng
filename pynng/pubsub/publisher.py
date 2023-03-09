import pynng
import time

from test_image_generator import TestImageGenerator

address = "ipc:///tmp/pubsub.ipc"


if __name__ == '__main__':

    test_image_generator = TestImageGenerator()

    with pynng.Pub0() as pub:
        pub.listen(address)

        i = 0
        while True:

            image = test_image_generator.get_test_image()
            print(f'Publishing image {i}')
            pub.send(image.tobytes())
            time.sleep(1.0/60.0)
