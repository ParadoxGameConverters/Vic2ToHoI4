import os
import sys
from PIL import Image

original_stdout = sys.stdout
output_file = open('image_sizes.txt', 'w')
sys.stdout = output_file

path = '../../Vic2ToHoI4/Data_Files/blankMod/output/gfx/leaders'
print('Path is ' + path)

print('Gathering files')
files = []
# r=root, d=directories, f = files
for r, d, f in os.walk(path):
    for file in f:
        if '.tga' in file:
            files.append(os.path.join(r, file))
        if '.dds' in file:
            files.append(os.path.join(r, file))
        if '.png' in file:
            files.append(os.path.join(r, file))

print('Found ' + str(len(files)) + ' files')
for f in files:
    if '.dds' in f:
        file = open(f,"rb")
        file_bytes = list(file.read(20))
        width = file_bytes[16] + 256 * file_bytes[17]
        height = file_bytes[12] + 256 * file_bytes[13]
        print(f + ' - ' + str(width) + ' x ' + str(height))
    else:
        image = Image.open(f)
        width, height = image.size
        print(f + ' - ' + str(width) + ' x ' + str(height))
        
sys.stdout = original_stdout