import re
import unittest
from pathlib import Path


KEYMAP_DIR = Path(__file__).resolve().parents[1]
CONFIG = KEYMAP_DIR / "config.h"
RULES = KEYMAP_DIR / "rules.mk"
ADAPTER = KEYMAP_DIR / "ripple_adapter.c"
EFFECT = KEYMAP_DIR / "rgb_matrix_user.inc"


class RippleIntegrationConfigTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.config = CONFIG.read_text()
        cls.rules = RULES.read_text()
        cls.adapter = ADAPTER.read_text()
        cls.effect = EFFECT.read_text()

    def test_ripple_is_the_firmware_default_effect(self):
        self.assertRegex(self.config, r"#\s*define\s+RGB_MATRIX_DEFAULT_MODE\s+RGB_MATRIX_CUSTOM_RIPPLE\b")
        self.assertIsNotNone(re.search(r"^RGB_MATRIX_CUSTOM_USER\s*=\s*yes\s*$", self.rules, re.MULTILINE))
        self.assertIn("rgb_matrix_mode_noeeprom(RGB_MATRIX_CUSTOM_RIPPLE)", self.adapter)

    def test_split_event_transport_is_declared(self):
        self.assertRegex(self.config, r"#\s*define\s+SPLIT_TRANSACTION_IDS_USER\s+RIPPLE_EVENT_SYNC\b")
        self.assertIn("transaction_register_rpc(RIPPLE_EVENT_SYNC", self.adapter)
        self.assertIn("transaction_rpc_send(RIPPLE_EVENT_SYNC", self.adapter)

    def test_only_key_press_events_start_a_ripple(self):
        self.assertRegex(
            self.adapter,
            r"if\s*\(record->event\.pressed\)\s*\{\s*"
            r"keyball_ripple_trigger_key\(",
        )

    def test_effect_uses_real_led_coordinates_and_dim_background(self):
        self.assertIn("g_led_config.point[i].x", self.effect)
        self.assertIn("g_led_config.point[i].y", self.effect)
        self.assertIn("scale8(background_hsv.v, 32)", self.effect)


if __name__ == "__main__":
    unittest.main()
