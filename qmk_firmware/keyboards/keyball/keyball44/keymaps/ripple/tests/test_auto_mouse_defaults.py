import re
import unittest
from pathlib import Path


KEYMAP_CONFIG = Path(__file__).resolve().parents[1] / "config.h"
KEYMAP_SOURCE = Path(__file__).resolve().parents[1] / "keymap.c"
KEYBALL_SOURCE = Path(__file__).resolve().parents[4] / "lib" / "keyball" / "keyball.c"


class AutoMouseForceEnableConfigTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.config = KEYMAP_CONFIG.read_text()
        cls.keymap = KEYMAP_SOURCE.read_text()
        cls.source = KEYBALL_SOURCE.read_text()

    def test_ripple_opts_into_force_enabled_auto_mouse(self):
        self.assertRegex(
            self.config,
            r"#\s*define\s+KEYBALL_AUTO_MOUSE_FORCE_ENABLE\b",
        )

    def test_ripple_targets_personal_mouse_layer(self):
        self.assertRegex(
            self.config,
            r"#\s*define\s+AUTO_MOUSE_DEFAULT_LAYER\s+3\b",
        )

    def test_personal_mouse_layer_contains_remap_controls(self):
        for keycode in ("KC_BTN1", "KC_BTN2", "KC_BTN3", "MO(4)"):
            with self.subTest(keycode=keycode):
                self.assertIn(keycode, self.keymap)

    def test_personal_mouse_layer_does_not_enable_scroll_mode(self):
        self.assertNotRegex(self.keymap, r"get_highest_layer\(state\)\s*==\s*3")

    def test_force_enable_overrides_saved_auto_mouse_state(self):
        self.assertRegex(
            self.source,
            r"#\s*ifdef\s+KEYBALL_AUTO_MOUSE_FORCE_ENABLE"
            r"(?s:.*?)"
            r"set_auto_mouse_enable\(true\)\s*;",
        )


if __name__ == "__main__":
    unittest.main()
