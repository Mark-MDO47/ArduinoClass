# Author: Mark Olson 2023-08-10
#
# process the save-as-html-complete of a README.md from github.com
#   and make it an html we can use
#

import sys
# import string
import os
import argparse

INITIAL_FIND = r'<h1 tabindex="-1" dir="auto">'
INITIAL_REPLACE = """
<!DOCTYPE html>
<html>
<head>
<style>
table, th, td {
  border: 1px solid black;
  border-collapse: collapse;
}
table {
  width:        80%;
}

th, td {
  padding: 15px;
}
</style>
</head>
<body>


"""


FINAL_FIND = r'</footer>'
FINAL_REPLACE = """
</footer>
</body></html>
"""


REPLACE_BODY = {r'https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/': r'Images/',
                "user-content-": ""}






###################################################################################
# do_htmlcomplete_to_good
#
# We expect a directory structure something like this (fix_html is arbitrary):
#
# .../fix_html/
# .../fix_html/first/
# .../fix_html/first/first.htm
# .../fix_html/first/first_files/*
# .../fix_html/second/second.htm
# .../fix_html/second/second_files/*
# etc.
#
# We expect there will be a directory with all the images we are to use;
#       these files are placed there separately
# .../fix_html/images/*
#
# We will create files as follows that use the files in the images directory
# .../fix_html/first.html
# .../fix_html/second.html

def do_htmlcomplete_to_good(fname, fptr_out):
    global REPLACE_BODY # we will add entries

    fptr_in = open(fname, 'rt')
    my_fname = os.path.abspath(fname)
    dot = os.path.split(my_fname)
    dotdot = os.path.split(dot[0])
    my_files = os.listdir(dot[0])
    my_dirs = []
    for a_file in my_files:
        if os.path.isdir(os.path.join(dot[0],a_file)):
            my_dirs.append(a_file)
    if 1 != len(my_dirs):
        sys.stderr.write("ERROR - directory containing file has %d subdirectories, expected 1\n" % len(my_dirs))
    REPLACE_BODY[my_dirs[0]+"/"] = "Images/"

    # process to the initial find/replace
    a_line = fptr_in.readline()
    while 0 != len(a_line):
        tmp = a_line.find(INITIAL_FIND)
        if -1 != tmp:
            fptr_out.write(INITIAL_REPLACE)
            fptr_out.write(a_line[tmp:])
            break
        # read the next line
        a_line = fptr_in.readline()

    # copy to the end of useful info, doing replaces for the body of the page
    a_line = fptr_in.readline()
    while 0 != len(a_line):
        for find in REPLACE_BODY.keys():
            a_line = a_line.replace(find, REPLACE_BODY[find])
        if -1 != a_line.find(FINAL_FIND):
            fptr_out.write(FINAL_REPLACE)
            break
        fptr_out.write(a_line)
        # read the next line
        a_line = fptr_in.readline()

    fptr_in.close()
    fptr_out.close()

    # end do_htmlcomplete_to_good()


###################################################################################
# "__main__" processing for htmlcomplete_to_good
#
# use argparse to process command line arguments
# python htmlcomplete_to_good.py -h to see what the arguments are
#
if __name__ == "__main__":
#     my_parser = argparse.ArgumentParser(prog='htmlcomplete_to_good',
#         formatter_class=argparse.RawTextHelpFormatter,
#         description="stdout receives standalone version of fname",
#         epilog="""Example:
# python htmlcomplete_to_good.py save-as-html-complete-README.htm > standalone.html
# """,
#         usage='%(prog)s listFname prevRatingsFname')
#     my_parser.add_argument('fname',type=str,help='path to fname *.htm, save-as-html-complete of a README.md from github.com')
#     args = my_parser.parse_args()


    # all the real work is done here
    # do_htmlcomplete_to_good(args.fname, sys.stdout)
    do_htmlcomplete_to_good(r"C:\Users\mdo\Downloads\html_fix\index\index.htm", sys.stdout)

    # end of "__main__"
