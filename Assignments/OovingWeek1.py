import random, math, sympy

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
    print("Command : ""2"". Different types of loops.")
    print("Command : ""3"". Functions.")
    print("Command : ""4"". Sympy library.")
    print("Command : ""5"". Creating list with 10000 number's no range, dictionaries and tuples.")
    print("Command : ""M"". Writes menu.")
    print("Command : ""Q"". Ends Program.")

menu()

# while loop that continues to run until, user's stop it.
while running:
    '''
    User input that tells which part of code to run,
    input type str since I want to use letters furthermore,
    I have no reason to do math on the numbers that gets inputted,
    so i can just store them as a string, or use eval() ;) if i,
    really want to do some math with the inputs.
    '''
    command = input("Enter command: ").upper()

    if command == "1":
        x = 100
        print("Value of x is ", x)
        print("x is of type ", type(x))

        # x is now changed to a float.
        x = 100.0
        print("Value of x is", x)
        print("x is of type ", type(x))

        # Deleting x.
        del x

        # Integer division deletes the rest eks:
        print(14//5)  # = 2

        # Modulo divides and prints the rest eks:
        print(14%5)  # = 4

        # Float division eks:
        print(14/5)  # = 2.8

        # Squared:
        print(14**5)  # = 537824

        # Double assignments.
        x, y = 10, 20

        # Swapping.
        x, y = y, x
        print("Value of x", x)
        print("Value of y", y)

        # Deleting x and y.
        del x, y

    if command == "2":
        # while loop:
        i, j = 0, 0
        print("While loop : ")
        while i < 5:
            # "i" starts as 0 and increments all the way up to 4.
            print("i is now : ", i)
            i += 1

        # While loops can also take in multiple arguments:
        # Argument number 1 will never be fulfilled but argument 2 will.
        while i < 10 and j < 10:
            i = 5
            print("j is now : ", j)
            print("i is still : ", i)
            j += 1

        # for loop:
        # if variables such as variable : "i" overlaps changes old "i" into new "i".
        print("for loop ""1"": ")
        for i in range(10):
            # Does not need to increment "i" as in while loop.
            print("i is now : ", i)

        # for loop can also start of "i" as different values:
        print("for loop ""2"" : ")
        for i in range(5,10):
            # Starts at 5 and ends at 9.
            print("i is now : ", i)

        # for loop can also increment in higher numbers than +1
        print("for loop ""3"" : ")
        for i in range(0,10,2):
            # increments +2 starts at 0 and ends at 8.
            print("i is now : ", i)

        x = 0
        # Nested for loops can be seen as squaring two numbers,
        # Eks: two for loops from 0-5 will run = 5^2 times = 25 times.
        for i in range(3):
            for j in range(3):
                x += 1
        # Runs 3^2 times = 9, x should be = 9.
        print("x is now : ", x)

        # Deleting variables.
        del i, j, x

    if command == "3":
        # Simple addition function for two numbers.
        def add(x, y):
            return x+y

        print(add(10,20))

        # We can also store the function return in a variable.
        addsum = add(10,20)
        print(addsum)

        del addsum

        # Returns input squared.
        def squared(x):
            return x**2

        # Prints number squared with the f(x) function.
        # functions can take inputs as variable.
        print(squared(int(input("Enter number x : "))))

        '''
        Lambda functions are anonymous functions which means they are not necessarily bound to a variable.
        lambda functions can only have single line expressions, it assumes that the first line
        of code is whats being returned.
        '''
        # lambda example of previous function add(x,y):
        print((lambda x,y: x+y)(10,20))

        '''
        lambda functions are often used in conjunction with higher tier functions and are sent in as
        a variable. in this higher tier function "cube" i send inn a list and a lambda function that
        cubes a variable x.
        '''
        list = [1,2,3,4,5,6,7,8,9,10]

        def cube(func, arr):
            result = []
            for num in arr:
                result.append(func(num))
            return result

        print(cube((lambda x: x**3), list))

        del list

    if command == "4":
        '''
        resources used: 
        https://www.youtube.com/playlist?list=PLSE7WKf_qqo1T5VV1nqXTj2iNiSpFk72T
        
        Sympy is symbolic, which means that it uses symbols instead of numerical values.
        Eks: sqrt(2)^2 numerically is = 2.000...004 whilst sqrt(2)^2 = 2, symbolically.
        '''
        print("Numerical : ", math.sqrt(2)**2)
        print("Symbolical : ", sympy.sqrt(2)**2)

        # Sympy can create symbols and do math with these symbols:
        x, y = sympy.Symbol('x'), sympy.Symbol('y')
        print(2*x-x+7+4*x-2) # = 5x+5

        # Sympy has some limitations, Eks: even though cos^2(x) + sin^2(x) is an identity,
        # sympy will not understand.
        print(sympy.cos(x)**2+sympy.sin(x)**2) # Should be = 1, but sympy doesn't understand.

        # Sympy can also substitute symbols in expressions:
        expr = 5*x+5
        print(expr.subs('x',2)) # = 15

        # Substituting symbols does not change the initial variable:
        print(expr)

        # Even though sympy is symbolic, it can also be used numerical:
        # with the sympy.N = Numerical.
        print(sympy.N(expr.subs('x',sympy.pi))) # = 20.7079.....

        # With sympy you can calculate equations, normally on paper one would write:
        # x+2 = 5 but in Python the "=" is reserved for variable assignment.
        # In sympy we create an equation with sympy.Eq(expr, equates).
        eq = sympy.Eq(expr,15)
        print(eq)

        # Equations in sympy have different types:
        print(type(eq))

        del eq, expr

        # Some equations have a finite amount of solutions:
        # x**2 = 2 has two solutions: sqrt(2), -sqrt(2),
        # to solve these equations we use sympy.solveset(eq, variable).
        eq = sympy.Eq(x**2,2)
        print(sympy.solveset(eq,x))

        # These equations with finite solutions have a type: finite.
        print(type(sympy.solveset(eq,x)))

        # For finite equations we can put the results straight into a list.
        sympyList = [sympy.solveset(eq,x)]
        print(sympyList)

        del eq, sympyList

        # Sympy can solve trigonometric equations:
        # Pretty hard to understand if you don't have a pretty printer,
        # installed like "Unicode pretty printer".
        eq = sympy.Eq(-sympy.sin(x) + sympy.cos(x),0)
        print(sympy.solveset(eq,x))

        # This trigonometric equation has infinite solutions therefore,
        # it's type is "Union"
        print(type(sympy.solveset(eq,x)))

        del eq

        # Sympy can also solve sets of equations.
        # we can solve these equations using sympy.linsolve([equations], variables)
        eq1 = sympy.Eq(5*x+5*y-3, 4)
        eq2 = sympy.Eq(x-7*y-1, 2)

        print(sympy.linsolve([eq1, eq2], x, y))

        del eq1, eq2

        # polynomials can be factorized in sympy using sympy.factor(poly)
        poly = x**2+5*x+6
        print(poly.factor())

        del poly

    if command == "5":
        '''
        Creating a list with 10000 index's.
        We are not looking for whats inside the index's but just that the list is n long.
        '''

        # Multiply index function:
        # We create the first index then multiply by how many index's we want "n".
        def mulList(n):
            arr = [0] * n
            return arr

        myList = mulList(10000)

        print(myList)
        print("Length of myList : ", len(myList))

        del myList

        '''
        Combining dictionaries with items can be done in multiple ways,
        one way is with the union = "|" operator.
        The union operator checks whether there are variables that are the same,
        then updates them with the values of the new dictionary.
        '''

        sword = {
            'name': 'Sword',
            'length': 3,
            'weight': 4,
            'type': 'short sword',
            'enchantment': 'N/A',
            'state': 'broken'
        }

        newSword = {
            'name': 'newSword',
            'length': 6,
            'weight': 9,
            'type': 'long sword',
            'enchantment': 'Sharpness'
        }

        print(sword)

        # Unifies sword and newSword.
        sword |= newSword

        print(sword)

        del newSword

        # Using for loop to print all items in dictionary.
        def printSword(obj):
            for item1, item2 in obj.items():
                print(item1, " : ", "'", item2, "'")

        printSword(sword)

        # Or just easy and simple way:
        print(sword)

        # ----------------------------------------------------------------------------
        # DOES NOT WORK :(

        # Changing the positions of an item.
        # Dictionaries are unordered so moving an item wouldn't really change anything,
        # Therefore
        # first we need user input to see what item we want to move:
        obj, index, arr = input('What item do you want to change : '), None, []

        # Fills arr array with sword's variable names, to find if input is in
        # array, then index of variable.
        for item in sword:
            arr.append(item)

        print(arr)

        for item in arr:
            if obj == item:
                index = arr.index(item)
                print(index)

        if index is not None:
            print("Moving item : ", obj)

        # User input for item to switch with former user inputted item.
        changeObj = input('Enter item to change its position : ')

        while True:
            if changeObj in arr:
                index2 = arr.index(changeObj)

                print("Item : ", arr[index], "Switched place's with : ", arr[index2])
                break
            print("Item : ", changeObj, " is not in the dictionary")

        for item1, item2 in sword.items():
            item1 = item1.upper()

        print(sword)

        del obj, changeObj, arr, index, index2
        # ----------------------------------------------------------------------------

        # Turning a list into a tuple and vise versa.

        myList = [1,5,1,2,3,6,8,1,2,4,7,9,2,1,4,7,3,1,1,2,3,5,7,4,3,1,1,1,2,3,5,7,4,3,1,1,1,2,3,5,7]

        # One can easily turn a tuple into a list with the tuple() command:

        myList = tuple(myList)
        print("List is now tuple : ", myList)

        myList = list(myList)

        print("List is now list : ", myList)

    if command == "M":
        menu()

    running = False
    if command == "Q":
        running = False
        print("Code ended")