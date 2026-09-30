#!/usr/bin/env python3
import argparse
import json
import os
import subprocess
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SOURCE = (ROOT / "tests" / "package_test.p").read_text()
EXPECTED = (
    "0\n1,234,567,890\n-1,234\n0 B\n1.5 KiB\n1.5 MiB\n1.1 MiB\n-1 KiB\n"
    "1 file\n2 files\n-1 file\n1st\n2nd\n3rd\n4th\n11th\n12th\n13th\n21st\n-22nd\n"
)


def run(command, cwd, env):
    return subprocess.run(command, cwd=cwd, env=env, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--strut", default=os.environ.get("STRUT_BIN", "strut"))
    args = parser.parse_args()
    compiler = str(Path(args.strut).resolve()) if Path(args.strut).exists() else args.strut

    with tempfile.TemporaryDirectory(prefix="strut-humanize-test-") as temporary:
        root = Path(temporary)
        app = root / "app"
        app.mkdir()
        (app / "main.p").write_text(SOURCE)
        (app / "strut.json").write_text(json.dumps({
            "name": "humanize-package-test",
            "version": "0.1.0",
            "entry": "main.p",
            "dependencies": {},
        }) + "\n")
        env = os.environ.copy()
        env["STRUT_HOME"] = str(root / "strut-home")

        for command in (
            [compiler, "init"],
            [compiler, "add", str(ROOT)],
            [compiler, "install", "--offline"],
            [compiler, "packages", "--json"],
        ):
            result = run(command, app, env)
            if result.returncode:
                print(result.stdout, end="")
                print(result.stderr, end="", file=os.sys.stderr)
                return result.returncode

        output = app / ("humanize-test.exe" if os.name == "nt" else "humanize-test")
        result = run([compiler, "main.p", "-o", str(output)], app, env)
        if result.returncode:
            print(result.stdout, end="")
            print(result.stderr, end="", file=os.sys.stderr)
            return result.returncode
        result = run([str(output)], app, env)
        if result.returncode or result.stdout != EXPECTED:
            print("unexpected result", file=os.sys.stderr)
            print("stdout:", repr(result.stdout), file=os.sys.stderr)
            print("stderr:", repr(result.stderr), file=os.sys.stderr)
            return 1

    print("humanize package test: PASS")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
