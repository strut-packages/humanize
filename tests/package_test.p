include <humanize>;

function main() -> int {
    print(humanize.number(0));
    print(humanize.number(1234567890));
    print(humanize.number(-1234));
    print(humanize.bytes(0));
    print(humanize.bytes(1536));
    print(humanize.bytes(1572864));
    print(humanize.bytes(1154047));
    print(humanize.bytes(-1024));
    print(humanize.plural(1, "file", "files"));
    print(humanize.plural(2, "file", "files"));
    print(humanize.plural(-1, "file", "files"));
    print(humanize.ordinal(1));
    print(humanize.ordinal(2));
    print(humanize.ordinal(3));
    print(humanize.ordinal(4));
    print(humanize.ordinal(11));
    print(humanize.ordinal(12));
    print(humanize.ordinal(13));
    print(humanize.ordinal(21));
    print(humanize.ordinal(-22));
    return 0;
}
