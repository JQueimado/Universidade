import random
import string
f= open("guru99.txt","w+")
def randomString(stringLength=4):
    """Generate a random string of fixed length """
    letters = string.ascii_uppercase
    return ''.join(random.choice(letters) for i in range(stringLength))
for i in range(200000):
    f.write("AI " + randomString() + '\n')
for i in range(150000):
    f.write("FI " + randomString() + " " + randomString() + " " + str(random.randrange(10,23)) + ":" + str(random.randrange(10,23)) + " " + str(random.randrange(30,999)) + '\n')

f.close() 
