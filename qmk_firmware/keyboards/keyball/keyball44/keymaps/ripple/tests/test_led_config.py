import re
import unittest
from pathlib import Path


RGB_MATRIX_SOURCE = Path(__file__).resolve().parents[3] / "rgb_matrix.c"
RGB_MATRIX_CONFIG = Path(__file__).resolve().parents[3] / "config.h"


def _strip_c_comments(source):
    source = re.sub(r"/\*.*?\*/", "", source, flags=re.DOTALL)
    return re.sub(r"//.*", "", source)


def _section(source, start, end):
    return source.split(start, 1)[1].split(end, 1)[0]


class Keyball44RgbMatrixConfigTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.source = RGB_MATRIX_SOURCE.read_text()
        cls.config = RGB_MATRIX_CONFIG.read_text()

    def test_has_sixty_slots_and_split_ranges(self):
        self.assertRegex(self.config, r"#\s*define\s+RGB_MATRIX_LED_COUNT\s+60")
        self.assertRegex(self.config, r"#\s*define\s+RGB_MATRIX_SPLIT\s+\{\s*30\s*,\s*30\s*\}")

    def test_has_fifty_nine_real_leds_and_one_phantom_slot(self):
        points = _strip_c_comments(_section(
            self.source,
            "/* LED index to physical position */",
            "/* LED index to flag */",
        ))
        flags = _strip_c_comments(_section(self.source, "/* LED index to flag */", "};"))

        self.assertEqual(len(re.findall(r"\{\s*\d+\s*,\s*\d+\s*\}", points)), 60)
        self.assertEqual(len(re.findall(r"LED_FLAG_KEYLIGHT|LED_FLAG_UNDERGLOW|LED_FLAG_NONE", flags)), 60)
        self.assertEqual(len(re.findall(r"LED_FLAG_NONE", flags)), 1)

    def test_phantom_slot_is_not_mapped_to_a_key(self):
        matrix = _strip_c_comments(_section(
            self.source,
            "/* Key matrix to LED index */",
            "/* LED index to physical position */",
        ))
        mapped_indices = [int(value) for value in re.findall(r"\b\d+\b", matrix)]

        self.assertNotIn(59, mapped_indices)
        self.assertEqual(set(mapped_indices), set(range(23)) | set(range(30, 51)))


if __name__ == "__main__":
    unittest.main()
