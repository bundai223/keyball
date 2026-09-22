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
        self.assertEqual(set(mapped_indices), set(range(20)) | set(range(27, 30)) | set(range(30, 51)))

    def test_right_key_matrix_columns_follow_physical_left_to_right_order(self):
        matrix = _strip_c_comments(_section(
            self.source,
            "/* Key matrix to LED index */",
            "/* LED index to physical position */",
        ))
        rows = [
            ["NO_LED" if value == "NO_LED" else int(value) for value in re.findall(r"NO_LED|\d+", row)]
            for row in re.findall(r"\{([^{}]*)\}", matrix)
        ]

        # LAYOUT_* expands the right-hand arguments as R00..R05 in the
        # matrix, while the physical LED coordinates are ordered R05..R00
        # from the centre toward the outside edge.
        self.assertEqual(rows[4], [35, 34, 33, 32, 31, 30])
        self.assertEqual(rows[5], [41, 40, 39, 38, 37, 36])
        self.assertEqual(rows[6], [47, 46, 45, 44, 43, 42])

    def test_left_matrix_matches_serial_led_chain(self):
        matrix = _strip_c_comments(_section(
            self.source,
            "/* Key matrix to LED index */",
            "/* LED index to physical position */",
        ))
        rows = [
            ["NO_LED" if value == "NO_LED" else int(value) for value in re.findall(r"NO_LED|\d+", row)]
            for row in re.findall(r"\{([^{}]*)\}", matrix)
        ]

        # The left PCB's WS2812 chain runs column-by-column.  The matrix
        # columns must therefore point into the serial order, not row-major
        # LED numbers.
        self.assertEqual(rows[0], [17, 14, 10, 6, 3, 0])
        self.assertEqual(rows[1], [18, 15, 11, 7, 4, 1])
        self.assertEqual(rows[2], [19, 16, 12, 8, 5, 2])
        self.assertEqual(rows[3], ["NO_LED", 13, 9, 27, 28, 29])

    def test_left_keylight_points_and_flags_follow_serial_led_chain(self):
        points = _strip_c_comments(_section(
            self.source,
            "/* LED index to physical position */",
            "/* LED index to flag */",
        ))
        coordinates = [
            tuple(int(value) for value in pair)
            for pair in re.findall(r"\{\s*(\d+)\s*,\s*(\d+)\s*\}", points)
        ]
        flags = re.findall(
            r"LED_FLAG_KEYLIGHT|LED_FLAG_UNDERGLOW|LED_FLAG_NONE",
            _strip_c_comments(_section(self.source, "/* LED index to flag */", "};")),
        )

        self.assertEqual(coordinates[0:20], [
            (100, 0), (100, 21), (100, 42),
            (80, 0), (80, 21), (80, 42),
            (60, 0), (60, 21), (60, 42),
            (60, 63),
            (40, 0), (40, 21), (40, 42),
            (40, 63),
            (20, 0), (20, 21), (20, 42),
            (0, 0), (0, 21), (0, 42),
        ])
        self.assertEqual(coordinates[27:30], [(80, 63), (100, 63), (120, 63)])
        self.assertEqual(flags[0:20], ["LED_FLAG_KEYLIGHT"] * 20)
        self.assertEqual(flags[20:27], ["LED_FLAG_UNDERGLOW"] * 7)
        self.assertEqual(flags[27:30], ["LED_FLAG_KEYLIGHT"] * 3)


if __name__ == "__main__":
    unittest.main()
