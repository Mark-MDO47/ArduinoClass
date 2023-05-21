# Author: Mark Olson 2023-05-20
#
# This bash file invokes the "original" eSpeak program. This produces sounds with a robotic flavor, which I wanted.
#    Kudos to (email)   jonsd at users dot sourceforge.net  for creating eSpeak
#    Kudos to Reece H. Dunn for continuing the good work
# I used eSpeak version 1.48.04
#
#
# After creating text file(s), this is how I processed them:
#    open file in Audacity, set to mono if not already set
#    duplicate the track (select track, then Edit->Duplicate)
#    reverse one of the tracks (select track, then Effect->Special->Reverse)
#    select reversed track and change pitch (Effect->Pitch->ChangePitch, choose -2 semitones)
#    for both tracks one at a time, echo effect (Effect->DelayAndReverb->Echo, choose DelayTime about 0.01 sec and DecayFactor about 0.5)
#    select reversed track and reverse it back to normal order (select track, then Effect->Special->Reverse)
#    select both tracks (ctrl-A) then render (Tracks->Mix->MixAndRender)
#    save as 22050Hz mono, "WAV (microsoft) signed 16-bit PCM"
#
# The following resources are available as shown; they are not included in the RBG repository.
#
# The original eSpeak text to speech code and compiled versions can be found at
#    http://espeak.sourceforge.net/
#        Note that eSpeak project is inactive since disappearance of Jonathan Duddington.
#        Active development and support now happens in eSpeak NG project
#        https://github.com/espeak-ng/espeak-ng maintained by Reece H. Dunn.
#        Mailing list of espeak-ng project is https://groups.io/g/espeak-ng
# A web implementation of eSpeak can be found as below; it is great fun, and just one of many STT engines on the site.
#    https://lingojam.com/RobotVoiceGenerator
#
# Audacity: https://www.audacityteam.org/
#
espeak -g 5 -v en-us -w raw_0001__.wav ". Rainbow."
espeak -g 5 -v en-us -w raw_0002__.wav ". Rainbow With Glitter."
espeak -g 5 -v en-us -w raw_0003__.wav ". Confetti."
espeak -g 5 -v en-us -w raw_0004__.wav ". Sinelon."
espeak -g 5 -v en-us -w raw_0005__.wav ". Juggle."
espeak -g 5 -v en-us -w raw_0006__.wav ". Bee Pee Em."
espeak -g 5 -v en-us -w raw_0007__.wav ". Introducing the Amazing Theremin Sonar Range Detector showing Demo Reel one hundred using Sound."
espeak -g 5 -v en-us -w totString.wav "Ah. Ah. Ah.  Ah. Ah. Ah. Rainbow. Ah. Ah. Ah. Rainbow With Glitter. Ah. Ah. Ah. Confetti. Ah. Ah. Ah. Sinelon. Ah. Ah. Ah. Juggle. Ah. Ah. Ah. Bee Pee Em. Ah. Ah. Ah. Introducing the Amazing Theremin Sonar Range Detector showing Demo Reel one hundred using Sound."


