import chains
import sys

def main():
	if len(sys.argv) != 4:
		print ("Usage: [search|hotrod] low high")
		exit(1)

	which = sys.argv[1]
	low = int(sys.argv[2])
	high = int(sys.argv[3])

	for n in range(low, high + 1):
		data = chains.get_max_chains(which, n)
		temp = []

		for element in data:
			temp.append(sorted(element))

		check = sorted(temp)

		previous = check[0]
		permutations = [1]

		for i in range(1, len(temp)):
			if previous == check[i]:
				permutations[len(permutations) - 1] += 1
			else:
				permutations.append(1)
				previous = check[i]

		print ("N=", n, " max length=", len(data[0]), " permutations=", len(permutations))
		print (permutations)

if __name__ == "__main__":
    main()
