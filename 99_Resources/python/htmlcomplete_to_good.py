# Author: Mark Olson 2023-08-10
#
# This is tuned specifically to the Arduino Class
#    https://github.com/Mark-MDO47/ArduinoClass/tree/master
#
# process the save-as-html-complete of a README.md from github.com
#   and make it an html we can use.
# this code is tuned to the way I organize my repos. You can tune yours a bit
#   by what you put in REPLACE_BODY
#
# The area where we store "save-as-html-complete" and run this tool is not the final
#    stand-alone version of the repository; it will have a lot of other
#    stuff in the subdirectories.
# I use a second build area in which I store the following in these directories
#    Images - all images contained in the repo. Best to copy them all here if
#             you want to view this with no internet access.
#    <other resources> such as KiCad, Fritzing, ArduinoCode, Sounds, etc.
#             same idea as above. Put it in here if you want folks to be
#             able to get it with no internet access.
# I copy the *.html tool outputs to this second area, along with
#    all the *.pdf files, into the root directory. The other areas I fill in
#    with the associated resources.
# The REPLACE_BODY substitutions tie this all together.
#
# When done; all the *.html and *.pdf will be in the root directory.
#
#    All images from the repo should be placed in a subdirectory Images
#
# I use FireFox to do the save-as-html-complete; other browsers probably work
#    on Github (example https://github.com/Mark-MDO47/ArduinoClass)
#       I close all the side windows and click on the README.md; this gives
#       https://github.com/Mark-MDO47/ArduinoClass/blob/master/README.md
#    then I do <menu icon> -> Save Page As... (or CTRL+S) and choose to "Save as type:"
#       "Web Page, complete (*.htm;*.html)" as a *.htm file
#    I save in a unique directory for each README.md, usually named for the
#       directory it comes from.
#       In the case of the root of the repo, I typically name the directory
#       "index" or "_index"
#    I name the *.htm file that it creates the same as the directory it goes in.
#    I repeat this for all README.md files in the repository.
#
# NOTE: the INITIAL_FIND is continually changing as GitHub changes their
#    webpages, so it may be that you will need to change it.
#    There is a comment showing some things I have searched for in the past.
# NOTE that this also means you probably need to save all the webpages at
#    about the same time so the search works for all of them.
# The concept of INITIAL_FIND is to skip most of the GitHub specific controls
#    and etc. and get to the user content of the README.md *.htm.
#
# The next step is to run this program on all the *.htm in the subdirectories
#    and put the output into the root directory
# I use this bash shell script to do that. It generates *.html files from input *.htm files.
    # for d in `ls | grep / | grep -v Images`
    # do
    #   cd $d
    #   f=`ls *.htm`
    #   echo $f
    #   python /d/github-Mark-MDO47/ArduinoClass/99_Resources/python/htmlcomplete_to_good.py ${f} > ../${f}l
    #   cd ..
    # done
#


import sys
# import string
import os
import argparse

INITIAL_FIND = r'<h1 tabindex="-1" id="user-content'
"""
r'<h1 tabindex="-1"' # 

'<h1 tabindex="-1" id="user-content-
' dir="auto">'
"""

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

REPLACE_BODY = [] # will be filled in later


# NOTE: these are (mostly) in order of length; that is important!
# This one for https://github.com/Mark-MDO47/ArduinoClass
REPLACE_BODY_ARD_CLS = [
    ["https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/Images/", "Images/"],
    ['img src="index_files/', 'img src="Images/'],
    ["user-content-", ""],
    ["https://github.com/Mark-MDO47/ArduinoClass/blob/master/03_SonarRangeDetector/03_SonarRangeDetector_ExtraFun.pdf", "03_SonarRangeDetector_ExtraFun.pdf"],
    ["https://github.com/Mark-MDO47/ArduinoClass/blob/master/02_PersistenceOfVision/02_PersistenceOfVision_stick.pdf", "02_PersistenceOfVision_stick.pdf"],
    ["https://github.com/Mark-MDO47/ArduinoClass/blob/master/04_TheFinale/04_TheFinale_DemoReelVoiceCommand_I2C.pdf", "04_TheFinale_DemoReelVoiceCommand_I2C.pdf"],
    ["https://github.com/Mark-MDO47/ArduinoClass/blob/master/ArduinoCode/SawtoothRevisited/SawtoothRevisited.ino", "ArduinoCode/SawtoothRevisited/SawtoothRevisited.ino"],
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
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/SawtoothRevisited/README.md", "ArduinoCode_SawtoothRevisited.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/VoiceCommands_I2C/README.md", "ArduinoCode_VoiceCommands_I2C.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/blob/master/ArduinoCode/HelloWorld/HelloWorld.ino", "ArduinoCode/HelloWorld/HelloWorld.ino"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/AllThePatterns/README.md", "ArduinoCode_AllThePatterns.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/ThereminSound/README.md", "ArduinoCode_ThereminSound.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/FastLEDBlink/README.md", "ArduinoCode_FastLEDBlink.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/VC_DemoReel/README.md", "ArduinoCode_VC_DemoReel.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/HelloWorld/README.md", "ArduinoCode_HelloWorld.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/DemoReel/README.md", "ArduinoCode_DemoReel.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/MDO_AllThePatterns", "ArduinoCode_MDO_AllThePatterns.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/Sawtooth/README.md", "ArduinoCode_Sawtooth.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/Theremin/README.md", "ArduinoCode_Theremin.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/VoiceCommands_UART", "ArduinoCode/VoiceCommands_UART"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/02_PersistenceOfVision/Part_A", "02_PersistenceOfVision_Part_A.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/02_PersistenceOfVision/Part_B", "02_PersistenceOfVision_Part_B.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/02_PersistenceOfVision/Part_C", "02_PersistenceOfVision_Part_C.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/02_PersistenceOfVision/Part_D", "02_PersistenceOfVision_Part_D.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/SawtoothRevisited", "ArduinoCode/SawtoothRevisited"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/VoiceCommands_I2C", "ArduinoCode/VoiceCommands_I2C"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/Blink/README.md", "ArduinoCode_Blink.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/AllThePatterns", "ArduinoCode/AllThePatterns"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/Oval/README.md", "ArduinoCode_Oval.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/blob/master/ArduinoCode/Oval/Oval.ino", "ArduinoCode/Oval/Oval.ino"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/ThereminSound", "ArduinoCode/ThereminSound"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/FastLEDBlink", "ArduinoCode/FastLEDBlink"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/MDO_DemoReel", "ArduinoCode_MDO_DemoReel.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/MDO_Theremin", "ArduinoCode_MDO_Theremin.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/VC_DemoReel", "ArduinoCode/VC_DemoReel"],
    ["https://github.com/Mark-MDO47/ArduinoClass/blob/master/99_Resources/README.md", "99_Resources.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/02_PersistenceOfVision", "02_PersistenceOfVision.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/HelloWorld", "ArduinoCode/HelloWorld"],
    ["https://github.com/Mark-MDO47/ArduinoClass/blob/master/04_TheFinale/README.md", "04_TheFinale.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/03_SonarRangeDetector", "03_SonarRangeDetector.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/README.md", "ArduinoCode.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/00_InstallArduinoIDE", "00_InstallArduinoIDE.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/DemoReel", "ArduinoCode/DemoReel"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/Sawtooth", "ArduinoCode/Sawtooth"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/Theremin", "ArduinoCode/Theremin"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/99_Resources/Sounds", "99_Resources_Sounds.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/99_Resources/KiCad", "99_Resources_KiCad.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/Blink", "ArduinoCode/Blink"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode/Oval", "ArduinoCode/Oval"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/05_ThatIsNotAll", "05_ThatIsNotAll.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/01_BlinkingLED", "01_BlinkingLED.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/04_TheFinale", "04_TheFinale.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/99_Resources", "99_Resources.html"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master/ArduinoCode", "ArduinoCode"],
    ["https://github.com/Mark-MDO47/ArduinoClass/tree/master", "_index.html"],
    ["https://youtube.com/shorts/qGxECSMQtAQ", "YouTube/01_blink_button_2023-04-20.mp4"],
    ["https://youtu.be/c5UH3J40uWE", "YouTube/01_blink_extLED_setup_2023-04-28.mp4"],
    ["https://youtu.be/cnjk-xBvyEo", "YouTube/02A_fastled_blink_2023-04-28.mp4"],
    ["https://youtu.be/UdA5ehl802k", "YouTube/02B_sawtooth_2023-04-20.mp4"],
    ["https://youtu.be/I-3vgafNRE8", "YouTube/02C_oval_button_2023-04-29.mp4"],
    ["https://youtu.be/sXV3qn8dh8o", "YouTube/02D_sinelon_2023-04-29.mp4"],
    ["https://youtu.be/0KehSIJmKcs", "YouTube/03_Theremin_final_2023-04-29.mp4"],
    ["https://youtu.be/G7ARC0xHXRg", "YouTube/04_ThereminSound_final_2023-04-29.mp4"],
    ["https://youtu.be/M8Xc4aVh5Hc", "YouTube/04_VoiceCommands_and_VC_DemoReel_02.mp4"]
] # end REPLACE_BODY_ARD_CLS[]

# NOTE: these are (mostly) in order of length; that is important!
# This one for https://github.com/Mark-MDO47/CforArduinoClass
#
# to start on this list, save to *.htm files using FireFox -> SavePageAs -> WebPageComplete(*.htm,*.html)
#      save as *.htm
# grep CforArduinoClass */*.htm | sed "s?^.*http?http?" | sed "s?[\"\&< ].*??" | sort | uniq | grep http
#
REPLACE_BODY_C4CLS = [
    ["https://github.com/Mark-MDO47/CforArduinoClass/blob/master/99_Resources/Images/", "Images/"],
    ['img src="index_files/', 'img src="Images/'],
    ["user-content-", ""],
    ["https://github.com/Mark-MDO47/CforArduinoClass/blob/master/99_Resources/Images/Arduino-Nano-Pinout_from_circuitstoday.com.png", "Images/Arduino-Nano-Pinout_from_circuitstoday.com.png"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/blob/master/02_LetsGetTalking/README.md#ascii-characters-and-strings", "02_LetsGetTalking.html#ascii-characters-and-strings"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/blob/master/99_Resources/Images/Config_USB_SerialMonitor_screen.png", "Images/Config_USB_SerialMonitor_screen.png"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/blob/master/99_Resources/Images/03_SerMon_DO_DEBUG_INPUT_run.png", "Images/03_SerMon_DO_DEBUG_INPUT_run.png"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/blob/master/99_Resources/Images/01_BlinkingLED_part_A_setup.png", "Images/01_BlinkingLED_part_A_setup.png"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/blob/master/ArduinoCode/02_LetsGetTalking/02_LetsGetTalking.ino", "ArduinoCode/02_LetsGetTalking/02_LetsGetTalking.ino"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/blob/master/99_Resources/Images/Config_USB_SerialMonitor.png", "Images/Config_USB_SerialMonitor.png"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/blob/master/99_Resources/Images/03_SerMon_DO_DEBUG_run.png", "Images/03_SerMon_DO_DEBUG_run.png"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/blob/master/99_Resources/Images/02_SerMon_setup_only.png", "Images/02_SerMon_setup_only.png"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/blob/master/99_Resources/Images/IDE_CompileAndRun.png", "Images/IDE_CompileAndRun.png"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/blob/master/ArduinoCode/03_YakityYak/03_YakityYak.ino", "ArduinoCode/03_YakityYak/03_YakityYak.ino"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/blob/master/ArduinoCode/02_LetsGetTalking/README.md", "ArduinoCode_02_LetsGetTalking.html"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/raw/master/ArduinoCode/02_LetsGetTalking/README.md", "ArduinoCode_02_LetsGetTalking.html"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/blob/master/99_Resources/Images/02_SerMon_run.png", "Images/02_SerMon_run.png"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/blob/master/99_Resources/Images/03_SerMon_run.png", "Images/03_SerMon_run.png"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/blob/master/99_Resources/Images/IDE_LoadBlink.png", "Images/IDE_LoadBlink.png"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/blob/master/README.md#some-resources-on-the-web", "README.md#some-resources-on-the-web"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/blob/master/ArduinoCode/03_YakityYak/README.md", "ArduinoCode_03_YakityYak.html"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/blob/master/99_Resources/Images/ConfigUSB.png", "Images/ConfigUSB.png"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/blob/master/99_Resources/Images/IDE_Blink.png", "Images/IDE_Blink.png"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/raw/master/ArduinoCode/03_YakityYak/README.md", "ArduinoCode_03_YakityYak.html"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/blob/master/ArduinoCode/01_Blink/01_Blink.ino", "ArduinoCode/01_Blink/01_Blink.ino"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/blob/master/ArduinoCode/01_Blink/README.md", "ArduinoCode_01_Blink.html"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/raw/master/00_InstallArduinoIDE/README.md", "00_InstallArduinoIDE.html"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/raw/master/ArduinoCode/01_Blink/README.md", "ArduinoCode_01_Blink.html"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/raw/master/02_LetsGetTalking/README.md", "02_LetsGetTalking.html"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/raw/master/01_BlinkingLED/README.md", "01_BlinkingLED.html"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/raw/master/03_YakityYak/README.md", "03_YakityYak.html"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/raw/master/ArduinoCode/README.md", "ArduinoCode.html"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/tree/master/00_InstallArduinoIDE", "00_InstallArduinoIDE.html"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/tree/master/02_LetsGetTalking", "02_LetsGetTalking.html"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/tree/master/01_BlinkingLED", "01_BlinkingLED.html"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/tree/master/03_YakityYak", "03_YakityYak.html"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/tree/master/ArduinoCode", "ArduinoCode.html"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/blob/master/README.md", "_index.html"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/raw/master/README.md", "_index.html"],
    ["https://github.com/Mark-MDO47/CforArduinoClass/tree/master", "_index.html"],
    ["https://github.com/Mark-MDO47/CforArduinoClass", "_index.html"],
] # end REPLACE_BODY_C4CLS[]

###################################################################################
# apply_body_replaces
#
# Does the replacements from REPLACE_BODY
g_line_num = 0
def apply_body_replaces(a_line):
    for pair in REPLACE_BODY:
        a_line = a_line.replace(pair[0], pair[1])

    return a_line
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
#
# This is accomplished by the following shell script:
"""
for d in `ls | grep / | grep -v Images`
do
  cd $d
  f=`ls *.htm`
  echo $f
  python /d/github-Mark-MDO47/ArduinoClass/99_Resources/python/htmlcomplete_to_good.py ${f} > ../${f}l
  cd ..
done
mv index.html _index.html
cp -p *.html /d/github-Mark-MDO47/_html_fix/
"""

def do_htmlcomplete_to_good(fname, fptr_out):
    global REPLACE_BODY # we will add entries
    global g_line_num # so can print out meaningful error messages

    fptr_in = open(fname, 'rt')

    my_fname = os.path.abspath(fname)
    dot = os.path.split(my_fname)
    my_files = os.listdir(dot[0])
    my_dirs = []
    my_fns = []
    for a_file in my_files:
        if os.path.isfile(os.path.join(dot[0],a_file)):
            my_fns.append(a_file)
        if os.path.isdir(os.path.join(dot[0],a_file)):
            my_dirs.append(a_file)
    if 1 != len(my_dirs):
        sys.stderr.write("ERROR - directory containing file %s has %d subdirectories, expected 1\n" % (dot[1], len(my_dirs)))
    if 1 != len(my_fns):
        sys.stderr.write("ERROR - directory containing file %s has %d files, expected 1\n" % (dot[1], len(my_fns)))
    REPLACE_BODY.append(['"'+my_dirs[0]+"/", '"Images/'])
    # print("my_dirs[0]=%s" % my_dirs[0])
    # thing = ['"'+my_dirs[0]+"/", '"Images/']
    # print("REPLACE_BODY.append(%s)" % thing)

    # process to the initial find/replace
    a_line = fptr_in.readline()
    while 0 != len(a_line):
        g_line_num += 1
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
        g_line_num += 1
        a_line = apply_body_replaces(a_line)
        if -1 != a_line.find(FINAL_FIND):
            fptr_out.write(FINAL_REPLACE)
            break
        fptr_out.write(a_line)
        # read the next line
        try:
            a_line = fptr_in.readline()
        except:
            sys.stderr.write("ERROR - problem input line %d %s\n" % (g_line_num, fname))
            break

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
    # print("here in __main__")
    my_parser = argparse.ArgumentParser(prog='htmlcomplete_to_good',
        formatter_class=argparse.RawTextHelpFormatter,
        description="stdout receives standalone version of fname",
        epilog="""Example:
python htmlcomplete_to_good.py --arduino_class save-as-html-complete-README.htm > standalone_ard_cls.html
python htmlcomplete_to_good.py --c_for_arduino_class save-as-html-complete-README.htm > standalone_c4ard_cls.html
""",
        usage='%(prog)s listFname prevRatingsFname')
    my_parser.add_argument('fname',type=str,help='path to fname *.htm, save-as-html-complete of a README.md from github.com')

    me_group1 = my_parser.add_mutually_exclusive_group(required=False)
    me_group1.add_argument('-a',
                           '--arduino_class',
                           action='store_true',
                           help='process ArduinoClass files (default)')
    me_group1.add_argument('-c',
                           '--c_for_arduino_class',
                           action='store_true',
                           help='process CforArduinoClass files')

    args = my_parser.parse_args()

    # print("filename: %s" % args.fname)

    if args.c_for_arduino_class:
        REPLACE_BODY = REPLACE_BODY_C4CLS
    else:
        REPLACE_BODY = REPLACE_BODY_ARD_CLS

    # all the real work is done here
    do_htmlcomplete_to_good(args.fname, sys.stdout)
    #  do_htmlcomplete_to_good(r"C:\Users\mdo\Downloads\html_fix\index\index.htm", sys.stdout)

    # end of "__main__"
