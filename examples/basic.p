include <humanize>;

function main() -> int {
    print(humanize_integer(1234567));
    print(humanize_bytes(1572864));
    print(humanize_plural(3, "file", "files"));
    print(humanize_ordinal(21));
    return 0;
}
