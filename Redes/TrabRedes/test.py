
def format(inp):
	
	formarray = []

	# cheks  #
	if not "getphone" in inp:
		return[]

	# removes the getphone string from the input#
	inp = inp.replace("getphone",'')

	# removes spaces form the begin of the input#
	while ( inp.startswith(' ')):
		inp = inp[1:]

	# removes spaces form the begin of the input#
	while ( inp.endswith(' ')):
		inp = inp[:-1]

	# var extraction #
	while inp != "":

		if inp[0] == '-':
			
			n = ""

			while inp[0] != ' ':
				n += inp[0]
				inp = inp[1:]
				if inp == "":
					break

			formarray.append(n)
			continue

		# add if name #
		if inp[0] == '"':
			
			inp = inp[1:]

			n = ""

			while inp[0] != '"':
				n += inp[0]
				inp = inp[1:]

			inp = inp[1:]

			formarray.append(n)
			continue
		
		# add if contact #
		if inp[0].isdigit():

			n = ""

			while inp[0].isdigit():
				n += inp[0]
				inp = inp[1:]
				if inp == "":
					break
			
			formarray.append(n)
			continue

		# ignore if is space #
		if inp[0] == " ":
			inp = inp[1:]
					
	return formarray


if __name__ == "__main__":
    
    s = input("yaya:")

    print(format(s))