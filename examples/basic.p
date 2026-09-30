include <humanize>;

function main() -> int {
    print(humanize.number(1234567));
    print(humanize.bytes(1572864));
    print(humanize.plural(3, "file", "files"));
    print(humanize.ordinal(21));
    return 0;
}
