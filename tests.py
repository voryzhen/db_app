import subprocess

def execute_programm( input ):

    useless_cat_call = subprocess.Popen(
    
        ["./db"],
        
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    
    )

    output, errors = useless_cat_call.communicate ( input = input )

    useless_cat_call.wait()

    return output, errors

def run_test ( name, input, expected ):

    output, errors = execute_programm(input)

    if errors:
        print ( name, "errors:" )
        print ( errors )

    if output == expected: print ( name + " ok" )
    else:
        print ( "expected output:" )
        print ( "[" + expected + "]" )
        print ( "" )
        print ( "real output:" )
        print ( "[" + output + "]" )
        print ( "\n" )

## tests below

inp1 = "insert 1 user user@main.com\nselect\n.exit\n"
exp1 = "db > Executed.\ndb > (1, user, user@main.com)\nExecuted.\ndb > Executed.\n"

run_test ( "1 test", inp1, exp1 )

inp2 = "insert 1 useruseruseruseruseruseruseruser12 user@main.com\nselect\n.exit\n"
exp2 = "db > Executed.\ndb > (1, useruseruseruseruseruseruseruser12, user@main.com)\nExecuted.\ndb > Executed.\n"

run_test ( "2 test", inp2, exp2 )
