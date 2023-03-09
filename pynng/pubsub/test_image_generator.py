""""
Copyright (C) 2022 twyleg
"""
import cv2
import time
import numpy as np


class TestImageGenerator:

    IMAGE_WIDTH = 1280
    IMAGE_HEIGHT = 720
    IMAGE_DEPTH = 3

    def __init__(self) -> None:
        self.x = self.IMAGE_WIDTH // 2
        self.y = self.IMAGE_HEIGHT // 2

        self.plusX = 1
        self.plusY = 1

    def draw_rectangle(self, image, center_x, center_y):
        cv2.rectangle(image, (center_x - 100, center_y - 100), (center_x + 100, center_y + 100), (0, 0, 0), -1)

    def draw_time_string(self, image, x, y):
        font = cv2.FONT_HERSHEY_SIMPLEX
        org = (x, y)
        font_scale = 1
        color = (255, 255, 255)
        thickness = 2
        time_string = time.strftime("%H:%M:%S", time.gmtime())
        image = cv2.putText(image, time_string, org, font, font_scale, color, thickness, cv2.LINE_AA)

    def get_test_image(self):

        image = np.full((self.IMAGE_HEIGHT, self.IMAGE_WIDTH), 255, dtype=np.uint8)
        self.draw_rectangle(image, self.x, self.y)
        self.draw_time_string(image, self.x - 75, self.y)

        self.x = self.x + self.plusX
        if self.x + 100 > self.IMAGE_WIDTH or self.x < 100:
            self.plusX = -self.plusX

        self.y = self.y + self.plusY
        if self.y + 100 > self.IMAGE_HEIGHT or self.y < 100:
            self.plusY = -self.plusY

        return cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
