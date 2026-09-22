import subprocess
import tempfile
import unittest
from pathlib import Path


RIPPLE_DIR = Path(__file__).resolve().parents[1]
HARNESS = Path(__file__).with_name("ripple_host_test.c")


class RipplePublicInterfaceTest(unittest.TestCase):
    def test_host_behavior(self):
        with tempfile.TemporaryDirectory() as temp_dir:
            executable = Path(temp_dir) / "ripple_host_test"
            compile_result = subprocess.run(
                [
                    "cc",
                    "-std=c99",
                    "-Wall",
                    "-Wextra",
                    "-Werror",
                    "-I",
                    str(RIPPLE_DIR),
                    str(RIPPLE_DIR / "ripple.c"),
                    str(HARNESS),
                    "-o",
                    str(executable),
                ],
                capture_output=True,
                text=True,
            )
            self.assertEqual(
                compile_result.returncode,
                0,
                compile_result.stderr,
            )

            run_result = subprocess.run(
                [str(executable)],
                capture_output=True,
                text=True,
            )
            self.assertEqual(run_result.returncode, 0, run_result.stderr)


if __name__ == "__main__":
    unittest.main()
