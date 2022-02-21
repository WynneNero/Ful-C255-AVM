#coding:utf-8
import os
import string
import glob
try:
    import xml.etree.cElementTree as ET
except ImportError:
    import xml.etree.ElementTree as ET


TOTAL_ROM_SIZE = 0
TOTAL_RAM_SIZE = 0
ROM_UPPER_LIMIT = 0x10000000
RAM_LOWER_LIMIT = 0xf0000000
ROM_END_STRING = ".top_of_ROM_BOOT"
RAM_END_STRING = ".top_of_RAM_R"

MAP_FILE = "vicp.map"
HEAD_STRING = "Image Summary"
SECTION = "Section"
BASE = "Base"
SIZE_HEX = "Size(hex)"
SIZE_DEC = "Size(dec)"

rom_end = 0
ram_end = 0
section_index = 0
base_index = 0
size_hex_index = 0
cur_data_index = 0


def get_next_data(line):
    global cur_data_index

    if line[cur_data_index] == 0x0d or line[cur_data_index] == 0x0a:
        return ''

    idx = 0
    while line[cur_data_index] == ' ':
        cur_data_index += 1
    idx = cur_data_index
    while line[idx] != ' ' and \
            line[idx] != '\r' and \
            line[idx] != '\n':
        idx += 1
    data = line[cur_data_index:idx]
    cur_data_index = idx
    #print data

    return data


def find_seg_head(line):
    global section_index
    global base_index
    global size_hex_index
    global cur_data_index
    col_index = 0

    if line.find(SECTION) == -1 or \
            line.find(BASE) == -1 or \
            line.find(SIZE_HEX) == -1:
        return 0

    cur_data_index = 0
    while 1:
        data = get_next_data(line)
        if data == '':
            break

        if data == SECTION:
            section_index = col_index
        if data == BASE:
            base_index = col_index
        elif data == SIZE_HEX:
            size_hex_index = col_index

        col_index += 1

    #print section_index, base_index, size_hex_index
    return 1


def parse_mem_size(line):
    global TOTAL_ROM_SIZE
    global TOTAL_RAM_SIZE
    global rom_end, ram_end
    global cur_data_index
    col_index = 0
    rom_line = 0
    ram_line = 0
    cur_data_index = 0
    while 1:
        data = get_next_data(line)
        if data == '':
            break
        if col_index == section_index:
            if data == ROM_END_STRING:
                rom_end = 1
            elif data == RAM_END_STRING:
                ram_end = 1
        elif col_index == base_index:
            addr = string.atoi(data, 16)
            #print addr
            if not rom_end:
                if addr <= ROM_UPPER_LIMIT:
                    rom_line = 1
            elif not ram_end:
                if addr >= RAM_LOWER_LIMIT:
                    ram_line = 1
        elif col_index == size_hex_index:
            size = string.atoi(data, 16)
            #print size

        col_index += 1

    if rom_line:
        TOTAL_ROM_SIZE += size
    elif ram_line:
        TOTAL_RAM_SIZE += size


def get_map_file():
    try:
        tree = ET.ElementTree(file='setting.xml')
        root = tree.getroot()
        for mapfile in root.findall('mapfile'):
            path = mapfile.get('path')
            print path
    except Exception, e:
        print "Error:cannot parse file:setting.xml."
        return ""

    if not os.path.isfile(path):
        print "Can't find %s" %path
        return ""

    return path


def calc_total_mem():
    find_head = 0
    find_s_head = 0

    #for mapfile in glob.glob("*.map"):
    #    print mapfile
    mapfile = get_map_file()
    if not mapfile:
        return
    fp = open(mapfile, 'r+')

    fp.seek(-200,2)
    buf = fp.read()
    if buf.find('Total RAM Size') != -1:
        fp.close()
        return

    fp.seek(0)

    line = fp.readline()
    while line:
        #print line
        idx = line.find(HEAD_STRING)
        if idx != -1:
            find_head = 1
            break
        line = fp.readline()

    if find_head == 0:
        print 'cannot find %s in map file' %HEAD_STRING
        fp.close()
        return

    insert_index = idx + len(HEAD_STRING) + 1
    line = fp.readline()
    while line:
        #print line
        if find_seg_head(line):
            find_s_head = 1
            break
        line = fp.readline()

    if find_s_head == 0:
        print 'cannot find segment head in map file'
        fp.close()
        return

    line = fp.readline()
    while line != '\f\n':
        parse_mem_size(line)
        line = fp.readline()

    #add rom/ram size to map file
    fp.seek(0,2)
    str = '''
==========================================================
Total ROM Size                    %10d ( %6.2f kB )
Total RAM Size                    %10d ( %6.2f kB )
==========================================================
    ''' %(TOTAL_ROM_SIZE, TOTAL_ROM_SIZE/1024, TOTAL_RAM_SIZE, TOTAL_RAM_SIZE/1024)
    try:
        fp.write(str)
    except Exception, e:
        print e
    fp.close()

    print 'total rom size: %d, total ram size: %d' %(TOTAL_ROM_SIZE, TOTAL_RAM_SIZE)


calc_total_mem()