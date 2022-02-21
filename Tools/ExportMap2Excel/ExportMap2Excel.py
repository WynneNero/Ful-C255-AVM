#coding:utf-8
import os
import string
import xlrd
import xlwt
try:
    import xml.etree.cElementTree as ET
except ImportError:
    import xml.etree.ElementTree as ET


TOTAL_ROM_SIZE = 0
TOTAL_RAM_SIZE = 0
ROM_UPPER_LIMIT = 0x10000000
RAM_LOWER_LIMIT = 0xf0000000

HEAD_STRING = "Module Summary"
SECTION = "Section"
MODULE = "Module"
SIZE = "Size"
ADDR = "Origin"
BASE = ADDR + '+' + SIZE

section_index = 0
base_index = 0
module_index = 0
cur_data_index = 0


def get_next_data(line):
    global cur_data_index
    left_arrow = 0

    if line[cur_data_index] == 0x0d or line[cur_data_index] == 0x0a:
        return ''

    idx = 0
    while line[cur_data_index] == ' ':
        cur_data_index += 1
    idx = cur_data_index
    while line[idx] != ' ' and \
            line[idx] != '\r' and \
            line[idx] != '\n':
        # for specific process start
        if line[idx] == '<':
            left_arrow = 1
        elif line[idx] == '>':
            if left_arrow == 1:
                left_arrow = 0
        # for specific process end
        idx += 1
    # for specific process start
    if (line[idx] == ' ' and line[idx+1] == '-'):
        idx += 4
        while line[idx] != ' ' and \
                line[idx] != '\r' and \
                line[idx] != '\n':
            idx += 1
    elif left_arrow == 1:
        idx += 1
        while line[idx] != '>':
            idx += 1
        idx += 1
        while line[idx] != ' ' and \
                line[idx] != '\r' and \
                line[idx] != '\n':
            idx += 1
    # for specific process end
    data = line[cur_data_index:idx]
    cur_data_index = idx
    #print data

    return data


def find_seg_head(line):
    global section_index
    global base_index
    global module_index
    global cur_data_index
    col_index = 0

    if line.find(SECTION) == -1 or \
            line.find(BASE) == -1 or \
            line.find(MODULE) == -1:
        return 0

    cur_data_index = 0
    while 1:
        data = get_next_data(line)
        if data == '':
            break

        if data == SECTION:
            section_index = col_index
        elif data == BASE:
            base_index = col_index
        elif data == MODULE:
            module_index = col_index

        col_index += 1

    #print section_index, base_index, module_index
    return 1


def parse_obj_info(line):
    global TOTAL_ROM_SIZE
    global TOTAL_RAM_SIZE
    global cur_data_index

    col_index = 0
    rom_line = 0
    ram_line = 0
    cur_data_index = 0
    obj_info = {}

    while 1:
        data = get_next_data(line)
        if data == '':
            break
        if col_index == section_index:
            obj_info['section'] = data
        elif col_index == base_index:
            list = data.split('+')
            addr_str = list[0]
            size_str = list[1]
            addr = string.atoi(addr_str, 16)
            size = string.atoi(size_str, 16)
            obj_info['addr'] = addr_str
            obj_info['size_hex'] = size_str
            obj_info['size_dec'] = string.atoi(size_str, 16)
            #print addr
            if addr <= ROM_UPPER_LIMIT:
                rom_line = 1
            elif addr >= RAM_LOWER_LIMIT:
                ram_line = 1
        elif col_index == module_index:
            obj_info['module'] = data

        col_index += 1

    if rom_line:
        TOTAL_ROM_SIZE += size
    elif ram_line:
        TOTAL_RAM_SIZE += size

    return obj_info

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

def conver_module(module):
    idx1 = module.find('lib')
    idx2 = module.find('.a')
    if (idx1 != -1 and idx2 != -1):
        module_n = module[:idx2 + 2]
    else:
        module_n = module
    return module_n


def cmp_module(module1, module2):
    idx1 = module1.find('lib')
    idx2 = module1.find('.a')
    idx3 = module2.find('lib')
    idx4 = module2.find('.a')

    if (idx1 != -1 and idx2 != -1 and idx3 != -1 and idx4 != -1):
        module1_a = module1[:idx2 + 2]
        module2_a = module2[:idx2 + 2]
        if module1_a == module2_a:
            return 0
        else:
            return 1
    else:
        if module1 == module2:
            return 0
        else:
            return 1


def export2excel():
    global section_index
    global base_index
    global module_index

    find_head = 0
    find_s_head = 0

    mapfile = get_map_file()
    if not mapfile:
        return
    fp = open(mapfile, 'r+')

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

    #create excel head
    workbook = xlwt.Workbook()
    sheet_org = workbook.add_sheet('origin', cell_overwrite_ok=True)
    sheet_parse = workbook.add_sheet('parse', cell_overwrite_ok=True)
    sheet_parse2 = workbook.add_sheet('parse2', cell_overwrite_ok=True)

    sheet_org.panes_frozen = True
    sheet_org.horz_split_pos = 1
    xls_addr_index = base_index
    xls_size_index = base_index + 1
    sheet_org.write(0, xls_addr_index, ADDR)
    sheet_org.write(0, xls_size_index, SIZE)
    if (section_index > base_index):
        xls_section_index = section_index + 1
    else:
        xls_section_index = section_index
    sheet_org.write(0, xls_section_index, SECTION)
    if (module_index > base_index):
        xls_module_index = module_index + 1
    else:
        xls_module_index = module_index
    sheet_org.write(0, xls_module_index, MODULE)

    sheet_parse.panes_frozen = True
    sheet_parse.horz_split_pos = 1
    sheet_parse.col(0).width = 256 * 22
    sheet_parse.write(0, 0, MODULE)
    sheet_parse.write(0, 1, SECTION)
    sheet_parse.write(0, 2, ADDR)
    sheet_parse.write(0, 3, SIZE)

    sheet_parse2.panes_frozen = True
    sheet_parse2.horz_split_pos = 1
    sheet_parse2.vert_split_pos = 1
    sheet_parse2.col(0).width = 256*22
    sheet_parse2.write(0, 0, MODULE)
    sheet_parse2.write(0, 1, 'Total ROM')
    sheet_parse2.write(0, 2, 'Total RAM')
    parse2_data_index = 3

    line = fp.readline()
    row_index = 1
    parse_row_index = 1
    parse2_row_index = 1
    last_module = ""
    rom_size = 0
    ram_size = 0
    sections = []
    section_dict = {}
    section_dict_total = {}
    rom_total = 0
    ram_total= 0

    style = xlwt.XFStyle()
    font = xlwt.Font()
    #font.name = 'Times New Roman'
    font.bold = True
    font.colour_index = 4
    style.font = font
    alignment = xlwt.Alignment()
    alignment.horz = 1
    style.alignment = alignment

    parse2_style = xlwt.XFStyle()
    alignment = xlwt.Alignment()
    alignment.horz = 1
    parse2_style.alignment = alignment

    while line != '\f\n':
        obj_info = parse_obj_info(line)

        #write obj info to excel
        if (obj_info['section'].find('.note') == -1 and
            #obj_info['section'].find('.secinfo') == -1 and
            #obj_info['section'].find('COMMON') == -1 and
            obj_info['section'].find('.debug') == -1):
            sheet_org.write(row_index, xls_addr_index, obj_info['addr'])
            sheet_org.write(row_index, xls_size_index, obj_info['size_hex'])
            sheet_org.write(row_index, xls_section_index, obj_info['section'])
            sheet_org.write(row_index, xls_module_index, obj_info['module'])

            row_index += 1

            addr = string.atoi(obj_info['addr'], 16)
            if (cmp_module(last_module, obj_info['module']) == 0 or
                last_module == ""):
                if addr <= ROM_UPPER_LIMIT:
                    rom_size += obj_info['size_dec']
                elif addr >= RAM_LOWER_LIMIT:
                    ram_size += obj_info['size_dec']

            if (cmp_module(last_module, obj_info['module']) != 0 and
                last_module != ""):
                sheet_parse.write(parse_row_index, 0, conver_module(last_module), style)
                size_str = 'ROM size: ' + str(rom_size) + ', ' + 'RAM size: ' + str(ram_size)
                sheet_parse.write(parse_row_index, 3, size_str, style)
                rom_total += rom_size
                ram_total += ram_size

                sheet_parse2.write(parse2_row_index, 1, rom_size, parse2_style)
                sheet_parse2.write(parse2_row_index, 2, ram_size, parse2_style)
                for key in section_dict.keys():
                    section_dict[key] = 0
                parse2_row_index += 1

                if addr <= ROM_UPPER_LIMIT:
                    rom_size = obj_info['size_dec']
                    ram_size = 0
                elif addr >= RAM_LOWER_LIMIT:
                    ram_size = obj_info['size_dec']
                    rom_size = 0
                parse_row_index += 1

            sheet_parse.write(parse_row_index, 0, obj_info['module'])
            if (obj_info['section'].find('.bss') != -1):
                obj_info['section'] = '.bss'
            sheet_parse.write(parse_row_index, 1, obj_info['section'])
            sheet_parse.write(parse_row_index, 2, obj_info['addr'])
            sheet_parse.write(parse_row_index, 3, obj_info['size_hex'])

            parse_row_index += 1

            sheet_parse2.write(parse2_row_index, 0, conver_module(obj_info['module']))
            if obj_info['section'] in sections:
                sec_idx = sections.index(obj_info['section'])
                section_dict[obj_info['section']] += obj_info['size_dec']
                section_dict_total[obj_info['section']] += obj_info['size_dec']
                sec_idx += 3
            else:
                sheet_parse2.write(0, parse2_data_index, obj_info['section'])
                sec_idx = parse2_data_index
                sections.append(obj_info['section'])
                section_dict[obj_info['section']] = obj_info['size_dec']
                section_dict_total[obj_info['section']] = obj_info['size_dec']
                parse2_data_index += 1
            sheet_parse2.write(parse2_row_index, sec_idx, section_dict[obj_info['section']], parse2_style)

            last_module = obj_info['module']

        line = fp.readline()

    sheet_parse.write(parse_row_index, 0, conver_module(last_module), style)
    size_str = 'ROM size: ' + str(rom_size) + ', ' + 'RAM size: ' + str(ram_size)
    sheet_parse.write(parse_row_index, 3, size_str, style)
    rom_total += rom_size
    ram_total += ram_size

    sheet_parse2.write(parse2_row_index, 1, rom_size, parse2_style)
    sheet_parse2.write(parse2_row_index, 2, ram_size, parse2_style)

    parse2_row_index += 3
    sheet_parse2.write(parse2_row_index, 0, 'All Module', style)
    sheet_parse2.write(parse2_row_index, 1, rom_total, style)
    sheet_parse2.write(parse2_row_index, 2, ram_total, style)
    key_idx = 3
    for key in sections:
        sheet_parse2.write(parse2_row_index, key_idx, section_dict_total[key], style)
        key_idx += 1

    try:
        workbook.save(mapfile + '.xls')
    except Exception, e:
        print e

    fp.close()

export2excel()