# Formats the text file provided according to data/How-to-use.txt

import os

maximumWidth = 128
letterWidth = 5
testfile = "data/Demo.txt"
newLinesFinal = []

filename = ""
if testfile == "":
    print(f"Current working directory: {os.getcwd()}")
    filename = input("Enter filename WITHIN C.W.D: ")
else:
    filename = testfile

with open(filename, "r+") as file:
    contents = file.readlines()
    for lines in contents:
        newLineList = []
        newLine = ""
        uneditedList = lines.split()
        for word in uneditedList:
            word.replace("\n", "")
            if len(newLine) * letterWidth < maximumWidth and len(newLine) * letterWidth + len(word) * letterWidth < maximumWidth:
                newLine += word + " "
            else:
                res = newLine.strip()
                newLineList.append(res)
                newLine = word + " "
        
        newLineList.append(newLine)
        newLinesFinal.append(newLineList)

    file.seek(0)
    file.truncate(0)
    for arr in newLinesFinal:
        for i in arr:
            file.write(i + "\n")

                