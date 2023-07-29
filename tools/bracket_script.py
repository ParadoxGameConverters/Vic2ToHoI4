import glob
import sys


def remove_comments(line, sep):
    for s in sep:
        i = line.find(s)
        if i >= 0:
            line = line[:i]
    return line.strip()


# root_dir needs a trailing slash (i.e. /root/dir/)
root_dir = './data/'

errors_found = False
for filename in glob.iglob(root_dir + '**/*.txt', recursive=True):
    opening_bracket_count = 0
    closing_bracket_count = 0

    file_encoding = 'utf_8'
    if filename == './data/blank_mod/common/ai_strategy/default.txt' or \
    filename == './data/blank_mod/common/country_leader/00_traits.txt' or \
    filename == './data/configurables/converterFocuses.txt contains' or \
    filename == './data/configurables/Divergences of Darkness_province_mappings.txt' or \
    filename == './data/configurables/Greater Flavor Mod_province_mappings.txt' or \
    filename == './data/configurables/Historical Flavour Mod v1.27I_province_mappings.txt' or \
    filename == './data/configurables/Historical Project Mod 0.4.6_province_mappings.txt' or \
    filename == './data/configurables/province_mappings.txt' or \
    filename == './data/configurables/TGC - The Grand Combination_province_mappings.txt' or \
    filename == './data/configurables/The Concert of Europe_province_mappings.txt' or \
    filename == './data/test_files/Technology/BaseGameTech2.txt':
        file_encoding = 'cp1252'

    try:
        with open(filename, 'r', encoding=file_encoding) as file:
            for line in file:
                cleaned_line = remove_comments(line, '#')
                opening_bracket_count += cleaned_line.count('{')
                closing_bracket_count += cleaned_line.count('}')
    except Exception as e:
        print(filename, e)

    if opening_bracket_count != closing_bracket_count:
        errors_found = True
        print(filename, 'contains', opening_bracket_count, 'opening ({) vs', closing_bracket_count, 'closing (}) braces')

if errors_found:
    sys.exit(1)
