import re
import unittest
from pathlib import Path


KEYMAP_CONFIG = Path(__file__).resolve().parents[1] / "config.h"
KEYBALL_SOURCE = Path(__file__).resolve().parents[4] / "lib" / "keyball" / "keyball.c"


class AutoMouseDefaultConfigTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.config = KEYMAP_CONFIG.read_text()
        cls.source = KEYBALL_SOURCE.read_text()

    def test_ripple_opts_into_default_enabled_auto_mouse(self):
        self.assertRegex(
            self.config,
            r"#\s*define\s+KEYBALL_AUTO_MOUSE_DEFAULT_ENABLE\b",
        )

    def test_default_enable_is_only_used_without_saved_keyball_config(self):
        self.assertRegex(
            self.source,
            r"bool\s+has_saved_keyball_config\s*=\s*false\s*;",
        )
        self.assertRegex(
            self.source,
            r"if\s*\(\s*!has_saved_keyball_config\s*\)\s*\{\s*"
            r"set_auto_mouse_enable\(true\)\s*;",
        )


if __name__ == "__main__":
    unittest.main()
