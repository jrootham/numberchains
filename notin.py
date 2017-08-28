import chains
import sys

def order(stuff):
	return sorted([i for i in stuff])

def main():
	if len(sys.argv) != 4:
		print ("Usage: [search|hotrod] low high")
		exit(1)

	which = sys.argv[1]
	low = int(sys.argv[2])
	high = int(sys.argv[3])

	for n in range(low, high + 1):
		data = chains.get_max_chains(which, n)

		total = {i for i in range(1, n + 1)}
		in_all = set(total)
		in_any = set()

		for instance in data:
			members = set(instance)
			others = total - members
			in_all = in_all & others
			in_any = in_any | others

		print("N=", n, " length=", len(data[0]), " solutions=", len(data))
		print("Not in any", order(in_all))
		print("Not in some", order(in_any - in_all))

if __name__ == "__main__":
    main()
