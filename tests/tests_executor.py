import subprocess

def execute_programm( input ):

    useless_cat_call = subprocess.Popen(
    
        ["../db"],
        
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

    if output == expected: print ( "Test: " + name + ";\nStatus: ok;\n" )
    else:
        print ( "Test: " + name + ";\nStatus: error:\n" )
        print ( "expected output:" )
        print ( "[" + expected + "]" )
        print ( "" )
        print ( "real output:" )
        print ( "[" + output + "]\n" )

import tests_data

for [ name, input, output ] in tests_data.tests_data:
    run_test ( name, input, output )
