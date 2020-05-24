from random import seed
from random import randint
import random, string, base64

print("create data set")
numOfTest = 500

def randomname(n):
   randlst = [random.choice(string.ascii_letters + string.digits) for i in range(n)]
   return ''.join(randlst)

body = ""
last = ""
for i in range(numOfTest):
    value = randint(4, 32)
    text = randomname(value)
    b = text.encode("UTF-8")
    e = base64.b32encode(b)
    s1 = e.decode("UTF-8")
    body += "TEST_BUF_BASE32_DECODEEXTRA(test_decode_%02d, \"%s\", \"%s\", %d) \n" % (i, s1, text, value)
last += body

with open("Base32randomStr.inc", "w+") as f:
   f.write(last)
