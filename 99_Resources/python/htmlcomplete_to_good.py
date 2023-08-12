# Author: Mark Olson 2023-08-10
#
# This is tuned specifically to the Arduino Class
#    https://github.com/Mark-MDO47/ArduinoClass/tree/master
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

h1 {
    border-bottom:1px solid #CCC;
    padding-bottom:3px;
}
h2 {
    border-bottom:1px solid #CCC;
    padding-bottom:3px;
}
h3 {
    border-bottom:1px solid #CCC;
    padding-bottom:3px;
}
h4 {
    border-bottom:1px solid #CCC;
    padding-bottom:3px;
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

# NOTE: these are (mostly) in order of length; that is important!
REPLACE_BODY = [
    ["https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/", "Images/"],
    ["user-content-", ""],
    ["https://github.com/Mark-MDO47/ArduinoClass/blob/master/03_SonarRangeDetector/03_SonarRangeDetector_ExtraFun.pdf", "03_SonarRangeDetector_ExtraFun.pdf"],
    ["https://github.com/Mark-MDO47/ArduinoClass/blob/master/02_PersistenceOfVision/02_PersistenceOfVision_stick.pdf", "02_PersistenceOfVision_stick.pdf"],
    ["https://github.com/Mark-MDO47/ArduinoClass/blob/master/04_TheFinale/04_TheFinale_DemoReelVoiceCommand_I2C.pdf", "04_TheFinale_DemoReelVoiceCommand_I2C.pdf"],
    ["https://github.com/Mark-MDO47/ArduinoClass/blob/master/01_BlinkingLED/01_Blinking_LED_part_A_Schematic.pdf", "01_Blinking_LED_part_A_Schematic.pdf"],
    ["https://github.com/Mark-MDO47/ArduinoClass/blob/master/01_BlinkingLED/01_Blinking_LED_part_B_Schematic.pdf", "01_Blinking_LED_part_B_Schematic.pdf"],
    ["https://github.com/Mark-MDO47/ArduinoClass/blob/master/02_PersistenceOfVision/02_PersistenceOfVision.pdf", "02_PersistenceOfVision.pdf"],
    ["https://github.com/Mark-MDO47/ArduinoClass/blob/master/03_SonarRangeDetector/03_SonarRangeDetector.pdf", "03_SonarRangeDetector.pdf"],
    ["https://github.com/Mark-MDO47/ArduinoClass/blob/master/04_TheFinale/04_TheFinale_ThereminSound.pdf", "04_TheFinale_ThereminSound.pdf"],
    ["https://github.com/Mark-MDO47/ArduinoClass/blob/master/02_PersistenceOfVision/Pattern_Calcs.xlsx", "Pattern_Calcs.xlsx"],
    ["https://github.com/Mark-MDO47/ArduinoClass/blob/master/02_PersistenceOfVision/Part_A/README.md", "02_PersistenceOfVision_Part_A.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/blob/master/02_PersistenceOfVision/Part_B/README.md", "02_PersistenceOfVision_Part_B.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/blob/master/02_PersistenceOfVision/Part_C/README.md", "02_PersistenceOfVision_Part_C.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/blob/master/02_PersistenceOfVision/Part_D/README.md", "02_PersistenceOfVision_Part_D.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/MDO_AllThePatterns", "ArduinoCode_MDO_AllThePatterns.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/VoiceCommands_UART", "ArduinoCode_VoiceCommands_UART.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/02_PersistenceOfVision/Part_A", "02_PersistenceOfVision_Part_A.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/02_PersistenceOfVision/Part_B", "02_PersistenceOfVision_Part_B.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/02_PersistenceOfVision/Part_C", "02_PersistenceOfVision_Part_C.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/02_PersistenceOfVision/Part_D", "02_PersistenceOfVision_Part_D.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/SawtoothRevisited", "ArduinoCode_SawtoothRevisited.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/VoiceCommands_I2C", "ArduinoCode_VoiceCommands_I2C.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/AllThePatterns", "ArduinoCode_AllThePatterns.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/ThereminSound", "ArduinoCode_ThereminSound.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/FastLEDBlink", "ArduinoCode_FastLEDBlink.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/MDO_DemoReel", "ArduinoCode_MDO_DemoReel.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/MDO_Theremin", "ArduinoCode_MDO_Theremin.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/VC_DemoReel", "ArduinoCode_VC_DemoReel.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/README.md", "99_Resources.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/02_PersistenceOfVision", "02_PersistenceOfVision.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/HelloWorld", "ArduinoCode_HelloWorld.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/03_SonarRangeDetector", "03_SonarRangeDetector.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/00_InstallArduinoIDE", "00_InstallArduinoIDE.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/DemoReel", "ArduinoCode_DemoReel.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/Sawtooth", "ArduinoCode_Sawtooth.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/Theremin", "ArduinoCode_Theremin.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/99_Resources/Sounds", "99_Resources_Sounds.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/99_Resources/KiCad", "99_Resources_KiCad.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/Blink", "ArduinoCode_Blink.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/Oval", "ArduinoCode_Oval.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/05_ThatIsNotAll", "05_ThatIsNotAll.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/01_BlinkingLED", "01_BlinkingLED.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/04_TheFinale", "04_TheFinale.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/99_Resources", "99_Resources.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode", "ArduinoCode.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master", "_index.html"],
]



###################################################################################
# apply_body_replaces
#
# Does the replacements from REPLACE_BODY
def apply_body_replaces(a_line):
    for pair in REPLACE_BODY:
        a_line = a_line.replace(pair[0], pair[1])
    return(a_line)
    # end apply_body_replaces()

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
    REPLACE_BODY.append([my_dirs[0]+"/", "Images/"])

    # process to the initial find/replace
    a_line = fptr_in.readline()
    while 0 != len(a_line):
        tmp = a_line.find(INITIAL_FIND)
        if -1 != tmp:
            fptr_out.write(INITIAL_REPLACE)
            fptr_out.write(apply_body_replaces(a_line[tmp:]))
            break
        # read the next line
        a_line = fptr_in.readline()

    # copy to the end of useful info, doing replaces for the body of the page
    a_line = fptr_in.readline()
    while 0 != len(a_line):
        a_line = apply_body_replaces(a_line)
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
    my_parser = argparse.ArgumentParser(prog='htmlcomplete_to_good',
        formatter_class=argparse.RawTextHelpFormatter,
        description="stdout receives standalone version of fname",
        epilog="""Example:
python htmlcomplete_to_good.py save-as-html-complete-README.htm > standalone.html
""",
        usage='%(prog)s listFname prevRatingsFname')
    my_parser.add_argument('fname',type=str,help='path to fname *.htm, save-as-html-complete of a README.md from github.com')
    args = my_parser.parse_args()


    # all the real work is done here
    do_htmlcomplete_to_good(args.fname, sys.stdout)
    #  do_htmlcomplete_to_good(r"C:\Users\mdo\Downloads\html_fix\index\index.htm", sys.stdout)

    # end of "__main__"
