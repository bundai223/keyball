import re
import unittest
from pathlib import Path


KEYMAP_CONFIG = Path(__file__).resolve().parents[1] / "config.h"
KEYBALL_SOURCE = Path(__file__).resolve().parents[4] / "lib" / "keyball" / "keyball.c"


class AutoMouseForceEnableConfigTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.config = KEYMAP_CONFIG.read_text()
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

    def test_force_enable_overrides_saved_auto_mouse_state(self):
        self.assertRegex(
            self.source,
            r"#\s*ifdef\s+KEYBALL_AUTO_MOUSE_FORCE_ENABLE"
            r"(?s:.*?)"
            r"set_auto_mouse_enable\(true\)\s*;",
        )


if __name__ == "__main__":
    unittest.main()
