
import sys, csv




def main(argv):
	if len(argv) == 0:
		print('please specify input file')
		return

	races = {}
	#create dictionary of races with horses and their matched bets against them
	with open(argv[0], 'r') as csvfile:
		reader = csv.reader(csvfile)
		for row in reader:
			if row[0] != str(7) or row[17] != 'PE':
				continue
			if row[1] in races:
				if row[10] in races[row[1]]:
					try:
						races[row[1]][row[10]].append([int(row[11]), float(row[13])])
					except:
						pass
				else:
					try:
						races[row[1]][row[10]] = [int(row[16]), [float(row[11]), float(row[13])]]
					except:
						pass
			else:
				try:
					races[row[1]] = {row[10]: [int(row[16]), [int(row[11]), float(row[13])]]}
				except:
					pass

	#some of the events are not what we want for learning
	to_remove = []

	for key in races:
		if len(races[key]) < 5:
			to_remove.append(key)



	for key in to_remove:
		del races[key]


	to_remove = []	

	for key in races:

		winners = 0

		for horse in races[key]:

			winners = winners + races[key][horse][0]
			odds = races[key][horse][1:]

			fx = 0
			sx = 0

			for pair in odds:
				fx = fx + pair[0] * pair[1]
				sx = sx + pair[1]

			average_odd = fx / sx

			races[key][horse] = [races[key][horse][0], average_odd] 

		if winners != 1:
			to_remove.append(key)
		
	for key in to_remove:

		del races[key]

	out = "output.csv"

	if len(argv) > 1:
		out = argv[1]

	max_length = 0

	f = open(out, 'w+')
	for key in races:
		line = ""
		for horse in races[key]:
			line = line + str(races[key][horse][0]) + ' '
		for horse in races[key]:
			line = line + str(races[key][horse][1]) + ' '
		f.write(line + "\n")
			
	f.close()


if __name__ == '__main__':
	main(sys.argv[1:])