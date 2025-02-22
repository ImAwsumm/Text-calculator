import time
print("Text Calculator! Operators: \"+, -, *, /\"")
equation = input("Enter Here: ")

start = time.time()
pemdas = ["*", "/", "+", "-"]

math_phrase = []
n = []

# Adding the mathematical equation
for j in equation:
    if j in pemdas:
        o = "".join(n)
        math_phrase.append(float(o))
        math_phrase.append(j)
        n = []
    elif j == " ":
        continue
    else:
        n.append(j)
# Adding the last number
if len(n) > 0:
    o = "".join(n) 
    math_phrase.append(float(o))
    n = []

print(math_phrase)

########### MULTIPLY AND DIVIDE ################

muldiv_lst = math_phrase
addsub_lst = []
n = muldiv_lst[0]
i = 1
while i < len(muldiv_lst):
    if muldiv_lst[i] == "*":
        print("*")
        n *= muldiv_lst[i+1]
        print(n)
    elif muldiv_lst[i] == "/":
        print("/")
        n /= muldiv_lst[i+1]
        print(n)
    else:
        print("Append")
        addsub_lst.append(n)
        addsub_lst.append(muldiv_lst[i])
        n = muldiv_lst[i+1]
    i += 2
# Add the last number depending on the last operator sign
if muldiv_lst[i - 2] == "*" or muldiv_lst[i - 2] == "/":
    addsub_lst.append(n)
    n = 0
else:
    addsub_lst.append(muldiv_lst[len(muldiv_lst)-1])
    n = 0

print(addsub_lst)

############### ADDITION AND SUBSTRACTION ####################

n = addsub_lst[0]
i = 1
while i < len(addsub_lst):
    if addsub_lst[i] == "+":
        print("+")
        n += addsub_lst[i+1]
        print(n)
    elif addsub_lst[i] == "-":
        print("-")
        n -= addsub_lst[i+1]
        print(n)
    i += 2

if int(n) == n:
    result = int(n)
else:
    result = n
print("Result: "+str(result))

end = time.time()
t = end - start
print(f"Time: {t} seconds")
