from PIL import Image
import os

def DetermineSmallFilename(big_filename):
    small_filename = "data/blank_mod/gfx/interface/ideas/" + os.path.basename(big_filename).replace("Portrait", "idea")
    return small_filename

def GetScalingFactor(width):
    return 34.0 / width;

def GetDefinition(filename):
    definition = "\tspriteType = {\n"
    definition += "\t\tname = GFX" + os.path.basename(filename).replace("Portrait", "").replace(".tga","").replace(".dds","") + "\n"
    definition += "\t\ttexturefile = \"" + filename + "\"\n"
    definition += "\t}\n"
    definition += "\n"
    definition += "\tspriteType = {\n"
    definition += "\t\tname = GFX" + os.path.basename(filename).replace("Portrait", "").replace(".tga","").replace(".dds","") + "_small\n"
    definition += "\t\ttexturefile = \"" + DetermineSmallFilename(filename) + "\"\n"
    definition += "\t}\n"
    definition += "\n"
    return definition

def CreateSmallVersion(filename):
    small_filename = DetermineSmallFilename(filename)
    big_image = Image.open(filename)
    resized = big_image.resize((34, int(GetScalingFactor(big_image.size[0]) * big_image.size[1])))
    new = Image.new("RGBA", (65, 67))
    new.paste(resized, (15,int((67-resized.size[1])/2)))
    rotated = new.rotate(5)
    on_canvas = Image.open("data/resources/images/nat_ideas_template_canvas.png")
    on_canvas.paste(rotated,(-6,-4),rotated)
    frame = Image.open("data/resources/images/nat_ideas_template_frame.png")
    on_canvas.paste(frame, (0,0), frame)
    on_canvas.save(small_filename)

    
gfx_file = open("data/blank_mod/interface/_leader_portraits_mod.gfx", "w")
gfx_file.write("spriteTypes = {\n")


image_fileme in glob.iglob('data/blank_mod/gfx/leaders/**/*.txt', recursive=True):
    CreateSmallVersion(image_file)
    gfx_file.write(GetDefinition(image_file))

gfx_file.write("}")
