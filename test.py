import chains
import sys

def main():
    if len(sys.argv) != 3:
        print("Usage: low high")
        exit(1)

    low = int(sys.argv[1])
    high = int(sys.argv[2])

    for n in range(low, high + 1):
        search_list = chains.get_max_chains("search", n)
        hotrod_list = chains.get_max_chains("hotrod", n)

        member = lambda chain: chain in hotrod_list or list(reversed(chain)) in hotrod_list

        print(list(filter(lambda chain: not member(chain), search_list)))

        result = " passed "
        if len(search_list[0]) != len(hotrod_list[0]):
            result = " failed "

        if all(list(map(member, search_list))):
            print(n, result, " complete")
        else:
            print(n, result, " missing")


if __name__ == "__main__":
    main()
