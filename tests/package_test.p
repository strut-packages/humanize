include <humanize>;

function main() -> int {
    print(humanize_integer(0));
    print(humanize_integer(1234567890));
    print(humanize_integer(-1234));
    print(humanize_bytes(0));
    print(humanize_bytes(1536));
    print(humanize_bytes(1572864));
    print(humanize_bytes(1154047));
    print(humanize_bytes(-1024));
    print(humanize_plural(1, "file", "files"));
    print(humanize_plural(2, "file", "files"));
    print(humanize_plural(-1, "file", "files"));
    print(humanize_ordinal(1));
    print(humanize_ordinal(2));
    print(humanize_ordinal(3));
    print(humanize_ordinal(4));
    print(humanize_ordinal(11));
    print(humanize_ordinal(12));
    print(humanize_ordinal(13));
    print(humanize_ordinal(21));
    print(humanize_ordinal(-22));
    return 0;
}
