from pynput import keyboard


class KeyboardController:
    def __init__(self, communicator):
        self.comms = communicator

        self.keyboard_listener = keyboard.Listener(
            on_press=self.on_key_pressed, on_release=self.on_key_released)

        self.key_pressed_callbacks = {
            keyboard.Key.esc: self.end,
            keyboard.KeyCode.from_char('w'): self.comms.increase_power_limit,
            keyboard.KeyCode.from_char('s'): self.comms.decrease_power_limit,
            keyboard.Key.up: self.comms.drive_forward,
            keyboard.Key.down: self.comms.drive_backward,
            keyboard.Key.left: self.comms.rotate_left,
            keyboard.Key.right: self.comms.rotate_right
        }

        self.key_released_callbacks = {
            keyboard.Key.left: self.comms.stop,
            keyboard.Key.right: self.comms.stop,
            keyboard.Key.up: self.comms.stop,
            keyboard.Key.down: self.comms.stop,
        }

    def end(self) -> bool:
        return False

    def start(self):
        try:
            self.keyboard_listener.start()
            self.keyboard_listener.join()
        except KeyboardInterrupt:
            pass
        print("Exiting...")

    def on_key_pressed(self, key) -> bool:
        if key in self.key_pressed_callbacks:
            return self.key_pressed_callbacks[key]()

        return True

    def on_key_released(self, key) -> bool:
        if key in self.key_released_callbacks:
            return self.key_released_callbacks[key]()

        return True
