# humanize

Official English integer and IEC byte-size formatting for Strut.

## Install

```sh
strut install humanize
```

For a local checkout:

```sh
strut add /path/to/humanize
```

## Usage

```strut
include <humanize>;

function main() -> int {
    print(humanize_integer(1234567));             // 1,234,567
    print(humanize_bytes(1572864));               // 1.5 MiB
    print(humanize_plural(3, "file", "files")); // 3 files
    print(humanize_ordinal(21));                   // 21st
    return 0;
}
```

Formatting is deterministic, ASCII, English-specific, and integer-based. Byte sizes use IEC units and at most one truncated decimal place. Locale rules, floating-point formatting, relative dates, and automatic word inflection are intentionally outside the package contract.

The minimum `int_64` value cannot be negated and is outside the formatting contract.

## Test

```sh
python3 tests/run.py --strut /path/to/strut
```
