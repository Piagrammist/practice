from colorama import Back, Fore, init

bit_count = 8
a = 63
b = 34
SEP = "—"


def col(text: str, *colors) -> str:
    return f"{''.join(colors)}{text}{Back.RESET}{Fore.RESET}"


def fmt_bin(num: int) -> str:
    return f"{num:0{bit_count}b}"


def twos_comp(num: int) -> int:
    return ~num + (1 << bit_count) + 1


def to_binary(num: int | str) -> str:
    if type(num) is int:
        num = bin(num)
    return num.replace("0b", "")


def parse_bits(num: int | str) -> list:
    binary = int(to_binary(num))
    result = []
    allowed = [0, 1]
    while binary > 0:
        bit = binary % 10
        if bit not in allowed:
            raise ValueError("Invalid bit")
        result.append(bit)
        binary //= 10
    if len(result) < bit_count:
        for _ in range(bit_count - len(result)):
            result.append(0)
    return result


def show_binary_expansion(binary: int | str):
    if len(binary) >= bit_count:
        binary = binary[len(binary) - bit_count :]
    bits = parse_bits(binary)
    count = len(bits)
    last_index = count - 1
    last_set_field = count - binary.find("1") - 1
    assert count == len(binary)

    print("= ", end="")
    for i in range(count):
        if bits[i]:
            power = f"2^{i}"
            if i == last_index:
                power = f"-1 * {power}"
            print(power, end="\t+ " if i < last_index and i < last_set_field else "")
    print()
    print("= ", end="")
    powers = []
    for i in range(count):
        if bits[i]:
            power = pow(2, i)
            if i == last_index:
                power *= -1
            powers.append(power)
            print(power, end="\t+ " if i < last_index and i < last_set_field else "")
    print()
    print(f"= {sum(powers)}")


def show_twos_comp(num: int, c: list = [Fore.WHITE, Fore.WHITE]):
    print(SEP * 34)
    print(" {0}  \t\t\t= {1}".format(col(num, c[0]), col(fmt_bin(num), c[0])))
    print("\t    ~{0}\t\t= {1}".format(num, fmt_bin(~num + (1 << bit_count))))
    print(
        "{0}\t  = ~{1} + 1\t= {2}".format(
            col(f"-{num}", c[1]),
            num,
            col(fmt_bin(twos_comp(num)), c[1]),
        )
    )


def show_comps_sum(x: int, y: int, c: list = [Fore.WHITE, Fore.WHITE]):
    comp = twos_comp(y)
    res = fmt_bin(x + comp)
    if len(res) > bit_count:
        res = (
            col(res[0 : len(res) - bit_count], Back.MAGENTA, Fore.BLACK)
            + res[len(res) - bit_count :]
        )
    print(SEP * 57)
    print(
        " {0} + {1} = {2: >3}\t\t= {3} + {4} = {5: >{6}}".format(
            col(x, c[0]),
            col(f"-{y}", c[1]),
            x - y,
            col(fmt_bin(x), c[0]),
            col(fmt_bin(comp), c[1]),
            res,
            bit_count + 1,
        )
    )
    if len(res) > bit_count:
        res = res[len(res) - bit_count :]
    print()
    show_binary_expansion(res)


def main():
    show_twos_comp(a, [Fore.RED, Fore.YELLOW])
    show_twos_comp(b, [Fore.CYAN, Fore.GREEN])

    show_comps_sum(a, b, [Fore.RED, Fore.GREEN])
    show_comps_sum(b, a, [Fore.CYAN, Fore.YELLOW])


if __name__ == "__main__":
    init()
    main()
