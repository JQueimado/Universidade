import random
import string
f= open("guru99.txt","w+")
def randomString(stringLength=4):
    """Generate a random string of fixed length """
    letters = string.ascii_uppercase
    return ''.join(random.choice(letters) for i in range(stringLength))
for i in range(200000):
    f.write("AI " + randomString() + '\n')

f.close() 
