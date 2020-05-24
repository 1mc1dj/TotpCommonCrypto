from random import seed
from random import randint
import random, string, base64

print("create data set")
numOfTest = 500

def randomname(n):
   randlst = [random.choice(string.ascii_letters + string.digits) for i in range(n)]
   return ''.join(randlst)

base = """struct {
    const char *inputBase32;
    const char *outputBase32;
    int len;
} testData[] = {
   %s
};
"""
body = ""

for i in range(numOfTest):
    value = randint(4, 32)
    text = randomname(value)
    b = text.encode("UTF-8")
    e = base64.b32encode(b)
    s1 = e.decode("UTF-8")
    body += "{ \"%s\", \"%s\", %d }, //test_decode_%02d  \n" % (s1, text, value, i)

last = ""
last += base % body

last += "\n"
for i in range(numOfTest):
    last += "TEST_BUF_BASE32_DECODETEST(test_decode_%02d, %d)\n" % (i,i)
last += "\n"

with open("Base32randomStr.inc", "w+") as f:
   f.write(last)
