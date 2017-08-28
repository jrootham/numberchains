
def get_max_chains(which, n):
	file_name = which + "/csv/maxfor" + str(n) +".csv"
	file = open(file_name)
	contents = file.read()
	result = []
	for line in contents.split("\n"):
		if 0 < len(line):
			result_line =[]
			for entry in line.split(","):
				result_line.append(int(entry))
			result.append(result_line)

	return result


