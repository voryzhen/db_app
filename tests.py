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

    # print(output)
    # print(errors)

    return output, errors

def run_test ( name, input, expected ):

    output, errors = execute_programm(inp1)
    
    if output == exp1: print ( name + " ok" )
    else:
        print ( "expected output:\n" )
        print ( "[" + expected + "]" )
        print ( "\n" )
        print ( "real output\n" )
        print ( "[" + output + "]" )
        print ( "\n" )
    

inp1 = "insert 1 user user@main.com\nselect\n.exit\n"
inp2 = "insert 2 usasdasder user@main.com\nselect\n.exit\n"

exp1 = "db > Executed.\ndb > (1, user, user@main.com)\nExecuted.\ndb > Executed.\n"
exp2 = "db > Executed.\ndb > (1, usasdasder, user@main.com)\nExecuted.\ndb > Executed.\n"

run_test ( "first test", inp1, exp1 )