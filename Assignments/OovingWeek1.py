print("OovingWeek1.py - Python")

running = True

'''
@Author Tharald Roland Sørensen
I decided to use a system where you write what section of the,
code you want to run, so that the terminal doesn't get to cluttered,
instructions about the different commands will be written below in,
a function called Menu.
The code runs indefinitely until the user writes command: "Q".
'''

def menu():
    print("Command : ""1"". Checking different types of variables and different types of arithmetic's operations.")
    print("Command : ""2"". Different loops.")
    print("Command : ""3"". Functions.")

    print("Command : ""Q"". Ends Program.")


print(menu())

# while loop that continues to run until, user's stop it.
while running:
    '''
    User input that tells which part of code to run,
    input type str since I want to use letters and since,
    I have no reason to do math on the numbers I can just,
    store them as the data type string.
    '''
    command = input("Enter command: ")

    if command == "1":
        x = 100
        print("Value of x is ",x)
        print("x is of type ", type(x))

        # x is now changed to a float.
        x = 100.0
        print("Value of x is",x)
        print("x is of type ", type(x))

        # Deleting x.
        del(x)

        # Integer division deletes the rest eks:
        print(14//5)  # == 2

        # Modulo divides and prints the rest eks:
        print(14%5)  # == 4

        # Float division eks:
        print(14/5)  # ==2.8

        # Squared:
        print(14**5)  # == 537824

        # Double assignments.
        x,y = 10, 20

        # Swapping.
        x,y = y,x
        print("Value of x",x)
        print("Value of y",y)

        # Deleting x and y.
        del(x,y)

    if command == "2":
        # while loop:
        i = 0
        print("While loop : ")
        while i < 5:
            # "i" starts as 0 and increments all the way up to 4.
            print("i is now : ",i)
            i += 1

        # for loop:
        # if variables such as "i" overlaps changes old one.
        print("for loop ""1"": ")
        for i in range(10):
            # Does not need to increment "i" as in while loop.
            print("i is now : ",i)

        # for loop can also start of "i" as different values:
        print("for loop ""2"" : ")
        for i in range(5,10):
            # Starts at 5 and ends at 9.
            print("i is now : ",i)

        # for loop can also increment in higher numbers than +1
        print("for loop ""3"" : ")
        for i in range(0,10,2):
            # increments +2 starts at 0 and ends at 8.
            print("i is now : ",i)

        x = 0
        # Nested for loops can be seen as squaring two numbers,
        # Eks: two for loops from 0-5 will run = 5^5 times = 3125 times.
        print("Nested for loop : ")
        for i in range(3):
            for j in range(3):
                x += 1
        # Runs 3^3 times = 9

        # Deleting variables.
        del(i,j,x)

    if command == "3":
        # Simple addition function for two numbers.
        def add(x, y):
            return x +y

        print(add(10,20))

        # We can also store the function return in a variable.
        addsum = add(10,20)
        print(addsum)

        del(addsum)

        # Returns input squared.
        def f(x):
            return x**2

        # Prints number squared with the f(x) function.
        print(f(int(input("Enter number x : "))))

        '''
        Lambda functions are 
        '''

    running = False
    if command == "Q":
        running = False
        print("Code ended")