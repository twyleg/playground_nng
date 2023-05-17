""""
Copyright (C) 2022 twyleg
"""
from enum import IntEnum
from PySide6.QtCore import QObject, Signal, Property


class State(IntEnum):
    RESET = 0
    RUNNING = 1
    PAUSED = 2


class Model(QObject):
    def __init__(self, millis: int, seconds: int, minutes: int, hours: int) -> None:
        QObject.__init__(self)
        self._state = State.RESET
        self._millis = millis
        self._seconds = seconds
        self._minutes = minutes
        self._hours = hours

    def set_timestamp(self, timestamp_ns: int) -> None:
        timestamp_ms = timestamp_ns // (1000 * 1000)

        millis = timestamp_ms % 1000
        seconds = (timestamp_ms // 1000) % 60
        minutes = (timestamp_ms // (1000 * 60)) % 60
        hours = (timestamp_ms // (1000 * 60 * 60))

        self.set_millis(millis)
        self.set_seconds(seconds)
        self.set_minutes(minutes)
        self.set_hours(hours)

    def get_state(self) -> State:
        return self._state

    def get_millis(self) -> int:
        return self._millis

    def get_seconds(self) -> int:
        return self._seconds

    def get_minutes(self) -> int:
        return self._minutes

    def get_hours(self) -> int:
        return self._hours

    def set_state(self, state: int) -> None:
        self._state = state
        self.state_changed.emit()

    def set_millis(self, millis: int) -> None:
        self._millis = millis
        self.millis_changed.emit()

    def set_seconds(self, seconds: int) -> None:
        self._seconds = seconds
        self.seconds_changed.emit()

    def set_minutes(self, minutes: int) -> None:
        self._minutes = minutes
        self.minutes_changed.emit()

    def set_hours(self, hours: int) -> None:
        self._hours = hours
        self.hours_changed.emit()

    @Signal
    def state_changed(self) -> None:
        pass

    @Signal
    def millis_changed(self) -> None:
        pass

    @Signal
    def seconds_changed(self) -> None:
        pass

    @Signal
    def minutes_changed(self) -> None:
        pass

    @Signal
    def hours_changed(self) -> None:
        pass

    @Signal
    def start_stop_button_clicked(self) -> None:
        pass

    @Signal
    def reset_button_clicked(self) -> None:
        pass

    state = Property(int, get_state, set_state, notify=state_changed)

    millis = Property(int, get_millis, set_millis, notify=millis_changed)
    seconds = Property(int, get_seconds, set_seconds, notify=seconds_changed)
    minutes = Property(int, get_minutes, set_minutes, notify=minutes_changed)
    hours = Property(int, get_hours, set_hours, notify=hours_changed)
