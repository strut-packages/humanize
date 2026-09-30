function humanize_internal_decimal(int_64 value) -> string {
    string[] digits := ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"];
    if (value == 0) {
        return "0";
    }
    result := "";
    while (value > 0) {
        int_64 digit := value % 10;
        result = digits[digit] + result;
        value = value / 10;
    }
    return result;
}

function humanize_integer(int_64 value) -> string {
    if (value == 0) {
        return "0";
    }
    bool negative := value < 0;
    if (negative) {
        value = -value;
    }

    string[] digits := ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"];
    result := "";
    int group := 0;
    while (value > 0) {
        if (group == 3) {
            result = "," + result;
            group = 0;
        }
        int_64 digit := value % 10;
        result = digits[digit] + result;
        value = value / 10;
        group++;
    }
    if (negative) {
        result = "-" + result;
    }
    return result;
}

function humanize_internal_tenths(int_64 remainder, int_64 divisor) -> int_64 {
    int_64 base := divisor / 10;
    int_64 extra := divisor % 10;
    int_64 digit := 9;
    while (digit > 0) {
        int_64 threshold := base * digit + (extra * digit + 9) / 10;
        if (remainder >= threshold) {
            return digit;
        }
        digit--;
    }
    return 0;
}

function humanize_bytes(int_64 value) -> string {
    bool negative := value < 0;
    if (negative) {
        value = -value;
    }

    string[] units := ["B", "KiB", "MiB", "GiB", "TiB", "PiB", "EiB"];
    int unit := 0;
    int_64 divisor := 1;
    while (value / divisor >= 1024 && unit < 6) {
        divisor = divisor * 1024;
        unit++;
    }
    int_64 whole := value / divisor;
    int_64 remainder := value % divisor;

    result := "";
    if (negative) {
        result = "-";
    }
    result = result + humanize_internal_decimal(whole);
    if (unit > 0) {
        int_64 tenths := humanize_internal_tenths(remainder, divisor);
        if (tenths > 0) {
            result = result + "." + humanize_internal_decimal(tenths);
        }
    }
    return result + " " + units[unit];
}

function humanize_plural(int_64 count, string singular, string plural) -> string {
    if (count == 1 || count == -1) {
        return humanize_integer(count) + " " + singular;
    }
    return humanize_integer(count) + " " + plural;
}

function humanize_ordinal(int_64 value) -> string {
    int_64 absolute := value;
    if (absolute < 0) {
        absolute = -absolute;
    }
    int_64 last_two := absolute % 100;
    suffix := "th";
    if (last_two < 11 || last_two > 13) {
        int_64 last := absolute % 10;
        if (last == 1) {
            suffix = "st";
        } else if (last == 2) {
            suffix = "nd";
        } else if (last == 3) {
            suffix = "rd";
        }
    }
    return humanize_integer(value) + suffix;
}
