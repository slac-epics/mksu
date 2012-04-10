#!/afs/slac/g/lcls/package/python/current/bin/python
import sys
import copy
import fileinput
from time import gmtime, strftime, sleep

def printUsage(argv):
    print "Usage: " + argv[0] + " <maplist.map> <output.h> <database.template>"

class Entry:
    RECORD = "record"
    NAME = "name"
    OPERATION = "operation"
    TASK = "task"
    ADDRESS = "address"
    TYPE = "conversion" # 0 for unsigned 1 for signed 16 bit int
    SIZE = "size"
    DESC = "DESC"
    DTYP = "DTYP"
    
    def __init__(self):
        self._fields = {}

    def add(self, name, value):
        self._fields[name] = value

    def show(self):
        for (x,y) in self._fields.items():
            sys.stdout.write(x + ":" + y + " ")
        print ""

    def getName(self):
        if (self._fields.has_key(Entry.NAME)):
            return self._fields[Entry.NAME]
        else:
            return ""
            
    
class InputReader:
    _currentLine = 0
    _recordCount = 0
    _paramCount = 0
    _entries = []

    def __init__(self):
        self._currentLine = 1
        self._recordCount = 0
        self._paramCount = 0
        self._entries = []

    def checkName(self, name, entries):
        for entry in entries:
            if (name == entry.getName()):
                return False
        return True

    def read(self, fileName):
        entry = 0
        try:
            fd = open(fileName)
        except:
            return 0
        _currentLine = 0

        pair = self.nextLine(fd)
        while pair != '':
            _currentLine = _currentLine + 1
            if (pair[0] == Entry.RECORD):
                if (entry != 0):
                    # Assume its unsigned if type is not specified
                    if (not entry._fields.has_key(Entry.TYPE)):
                        entry.add(Entry.TYPE, 0) 
                    entries.append(entry)
                self._recordCount = self._recordCount + 1
                entry = Entry()
                entry.add(pair[0], pair[1])
            else:
                entry.add(pair[0],pair[1])
                if (pair[0] == Entry.NAME):
                    if (not self.checkName(pair[1], entries)):
                        print "Duplicate record name: " + pair[1] + ". Exiting." 
                        exit(-1);
                if (pair[0] == Entry.OPERATION and
                    pair[1] != "record"):
                    self._paramCount = self._paramCount + 1
            pair = self.nextLine(fd)
            
        if (entry != 0):
            # Assume its unsigned if type is not specified
            if (not entry._fields.has_key(Entry.TYPE)):
                entry.add(Entry.TYPE, 0) 
            entries.append(entry);
            fd.close()
        print "Found " + str(self._recordCount) + " record entries"

        return (entries,self._paramCount)

    def nextLine(self,fd):
        line = fd.readline().strip()
        self._currentLine = self._currentLine + 1
        
        while (line.find('#') == 0):
            line = fd.readline().strip()
            self._currentLine = self._currentLine + 1
            
        pair = line.split('\t')
        if (line == ''):
            return ''
        
        if (len(pair) != 2):
            print "Could not read line " + str(self._currentLine) + ". Exiting."
            print "line " + str(self._currentLine) + ": " + line
            return ''
        return pair
                   
class HeaderGenerator:
    def writeEntry(self, fd, entry):
        fd.write("  {");
        fd.write(entry._fields[Entry.TASK] + ", ")
        fd.write(entry._fields[Entry.DTYP].replace("asyn","asynParam") + ", ")
        fd.write(entry._fields[Entry.ADDRESS] + ", ")
        fd.write(str(entry._fields[Entry.TYPE]) + ", ")
        fd.write(entry._fields[Entry.SIZE] + ", ")
        fd.write("\"" + entry._fields[Entry.NAME].split(":").pop() + "\", ")
        fd.write("-1")
        fd.write("},\n")
    
    def generate(self, fileName, entries, paramCount, inputFileName):

        mksuParamFileName = fileName + ".h"
        mksuParamListFileName = fileName + "List.h"

        try:
            fd = open(mksuParamFileName, "w")
        except:
            print "Failed to create header file " + mksuParamFileName
            return ''

        try:
            fdList = open(mksuParamListFileName, "w")
        except:
            fd.close()
            print "Failed to create header file " + mksuParamListFileName
            return ''

        time = strftime('%a, %d %b %Y %H:%M:%S +0000', gmtime())
        fd.write("// Header file generated from " + inputFileName + " on " + time + "\n")
        fd.write("\n");

        fd.write("#ifndef MKSUPARAM_H\n")
        fd.write("#define MKSUPARAM_H\n\n")

        fd.write("// Struct that holds register information. The id field\n")
        fd.write("// is used by asyn to connect with the actual asyn parameter\n")
        fd.write("typedef struct {\n")
        fd.write("  int blockId; // MKSU FPGA Block\n")
        fd.write("  asynParamType type; // Defined in asynPortDriver.h\n")
        fd.write("  long address; // Starting address (offset) within the FPGA block\n")
        fd.write("  int conversion; // 0 for unsigned, 1 for signed int 16 (requires conversion)\n")
        fd.write("  long size; // Number of bytes\n")
        fd.write("  std::string name; // Name given in the INP/OUT asyn record field\n")
        fd.write("  int id; // This is assigned by asynPortDriver::createParam()\n")
        fd.write("} MksuParam;\n\n")
        fd.write("\n#endif\n")
        fd.close()

        fdList.write("// Header file generated from " + inputFileName + " on " + time + "\n")
        fdList.write("\n")
        fdList.write("#include <" + mksuParamFileName + ">")
        fdList.write("\n")

        fdList.write("#ifndef MKSUPARAMLIST_H\n")
        fdList.write("#define MKSUPARAMLIST_H\n\n")

        fdList.write("// Number of records found in the input file\n")
        fdList.write("const int MKSU_NUM_PARAMS = " + str(paramCount) + ";\n\n")

        fdList.write("// Information extracted from the input file\n")
        fdList.write("MksuParam MksuParams[MKSU_NUM_PARAMS] = {\n")
        for entry in entries:
            if (entry._fields[Entry.OPERATION] == "read" or
                entry._fields[Entry.OPERATION] == "write"):
                self.writeEntry(fdList, entry)
        fdList.write("};\n")

        fdList.write("\n#endif\n")
        fdList.close()

        return 0

class DbTemplateGenerator:
    def writeRecord(self, fd, record):
        fd.write("\n")
        fd.write("record(" + record._fields[Entry.RECORD] + ", \"" +
                 record._fields[Entry.NAME] + "\") {\n")

        # First write the DESC field
        fd.write("  field(" + Entry.DESC + ", \"" + record._fields[Entry.DESC] + "\")\n")

        # Second, write the DTYP field
        if (record._fields.has_key(Entry.DTYP)):
            value = record._fields[Entry.DTYP];
            if (record._fields[Entry.OPERATION] == "read"):
                value = value.replace("Array","ArrayIn")
            else:
                value = value.replace("Array","ArrayOut")
            fd.write("  field(" + Entry.DTYP + ", \"" + value + "\")\n")
                
        for (name, value) in record._fields.items():
            if (name != Entry.RECORD and
                name != Entry.NAME and
                name != Entry.OPERATION and
                name != Entry.TASK and
                name != Entry.TYPE and
                name != Entry.DESC and
                name != Entry.DTYP and
                name != Entry.ADDRESS and
                name != Entry.SIZE):
                fd.write("  field(" + name + ", \"" + value + "\")\n")
        fd.write("}\n")
    
    def generate(self, fileName, entries, inputFileName):
        try:
            fd = open(fileName, "w")
        except:
            print "Failed to create database template file " + fileName
            return ''
        
        time = strftime('%a, %d %b %Y %H:%M:%S +0000', gmtime())
        fd.write("# Database template file generated from " + inputFileName + " on " + time + "\n")
        for record in entries:
            self.writeRecord(fd, record)

if (len(sys.argv) != 4):
    printUsage(sys.argv)
    exit(-1)

inputFileName = sys.argv[1]
outputHeaderFileName = sys.argv[2]
outputDbFileName = sys.argv[3]

print "Processing..."
print "Input: " + inputFileName
print "Header file: " + outputHeaderFileName
print "Db file: " + outputDbFileName

reader = InputReader()

try:
    fd = open(inputFileName)
except:
    print "Failed to open file containing list of maps: " + inputFileName + ". Exiting..."
    exit(-1)
    
entries = []
file = fd.readline().strip()
while file != '':
    print "Reading file: " + file
    entries,paramCount = reader.read(file)
    if (entries == 0):
        print "Failed to read input file: " + file
        exit(-1)
    else:
        print file + ": found " + str(paramCount) + " parameters."
        file = fd.readline().strip()

headerGenerator = HeaderGenerator()
if (headerGenerator.generate(outputHeaderFileName, entries, paramCount, inputFileName) == ''):
    exit(-1)

dbTemplateGenerator = DbTemplateGenerator()
if (dbTemplateGenerator.generate(outputDbFileName, entries, inputFileName) == ''):
    exit(-1)

print "Done."
