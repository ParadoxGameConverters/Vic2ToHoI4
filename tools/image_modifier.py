from PIL import Image
import os
from pathlib import Path
import re

options = {
    "hoi4_path": Path(),
}

config_file = Path("data/configurables/cultureGroupToGraphics.txt")
mod_gfx_dir = Path("data/blank_mod/gfx")
mod_interface_dir = Path("data/blank_mod/interface")
gfx_extensions = {'.dds', '.png', '.tga'}


def extract_sprite_textures(interface_dirs):
    sprite_textures = {}
    sprite_name_pattern = re.compile(r'name\s*=\s*"?(GFX[^"\s]+)"?')
    texture_pattern = re.compile(r'texturefile\s*=\s*"?([^"]+)"?')

    current_sprite = None
    for interface_dir in interface_dirs:
        for file in interface_dir.glob("*.gfx"):
            with file.open(encoding="utf-8", errors="ignore") as f:
                for line in f:
                    name_match = sprite_name_pattern.search(line)
                    if name_match:
                        current_sprite = name_match.group(1)
                    elif current_sprite:
                        texture_match = texture_pattern.search(line)
                        if texture_match:
                            sprite_textures[current_sprite] = texture_match.group(1)
                            current_sprite = None  # reset until next name
    return sprite_textures

# === Extract portrait references from the config file ===
def extract_portrait_references(file_path):
    references = []
    seen = set()
    portrait_pattern = re.compile(r'\s+"?(GFX[^"\n]+|gfx[^"\n]+)"?')

    with open(file_path, encoding="utf-8") as f:
        for line in f:
            line = line.split('#', 1)[0]  # strip comments
            matches = portrait_pattern.findall(line)
            for ref in matches:
                cleaned = ref.strip().strip('"')
                if cleaned and cleaned not in seen:
                    seen.add(cleaned)
                    references.append(cleaned)

    return references

# === Load all image files from gfx directories ===
def load_existing_files(*gfx_dirs):
    existing = {}
    for gfx_dir in gfx_dirs:
        for path in gfx_dir.rglob("*"):
            if path.is_file() and path.suffix.lower() in gfx_extensions:
                rel_path = path.relative_to(gfx_dir.parent)
                key = str(rel_path).replace("\\", "/").lower()
                existing[key] = str(path)
    return existing

def DetermineSmallFilename(big_filename):
    small_filename = "data/blank_mod/gfx/interface/ideas/idea_" + os.path.basename(big_filename).replace("Portrait_", "").replace("portrait_", "")
    small_filename = small_filename.replace("portrait_", "idea_")
    return small_filename

def GetScalingFactor(width):
    return 34.0 / width;

def GetDefinition(filename):
    definition = "\tspriteType = {\n"
    definition += "\t\tname = GFX_" + os.path.basename(filename).replace("Portrait_", "").replace("portrait_", "").replace(".tga","").replace(".dds","").replace(" ", "_") + "\n"
    definition += "\t\ttexturefile = \"" + filename.replace("data/blank_mod/", "").replace("\\","/") + "\"\n"
    definition += "\t}\n"
    definition += "\n"
    definition += "\tspriteType = {\n"
    definition += "\t\tname = GFX_" + os.path.basename(filename).replace("Portrait_", "").replace("portrait_", "").replace(".tga","").replace(".dds","").replace(" ", "_") + "_small\n"
    definition += "\t\ttexturefile = \"" + DetermineSmallFilename(filename).replace("data/blank_mod/", "").replace("\\","/") + "\"\n"
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

def UpdateMappings(filename):
    replacement = "GFX_" + os.path.basename(filename).replace("Portrait_", "").replace("portrait_", "").replace(".tga","").replace(".dds","")
    mappings_file = open("data/configurables/cultureGroupToGraphics.txt", "r")
    mappings_lines = mappings_file.read()
    mappings_file.close()
    new_mappings_file = open("data/configurables/cultureGroupToGraphics.txt", "w")
    replacement_lines = mappings_lines.replace(filename, replacement)
    new_mappings_file.write(replacement_lines)
    new_mappings_file.close()


hoi4_path = options["hoi4_path"]
hoi4_exe = hoi4_path / "hoi4.exe"
if not hoi4_exe.exists():
    raise ("Enter a valid HoI4 path!")

interface_dirs = [hoi4_path / "interface", mod_interface_dir]
gfx_dirs = [hoi4_path / "gfx", mod_gfx_dir]

portrait_refs = extract_portrait_references(config_file)
existing_files = load_existing_files(*gfx_dirs)
sprite_textures = extract_sprite_textures(interface_dirs)

log = open("tools/portraits.log", "w")
gfx_file = open("data/blank_mod/interface/_leader_portraits_mod_generated.gfx", "w")
gfx_file.write("spriteTypes = {\n")

for ref in portrait_refs:
    normalized_ref = ref.strip('"')
    ref_lower = normalized_ref.lower()
    is_sprite = not ref_lower.endswith(tuple(gfx_extensions))
    
    if is_sprite:
        if normalized_ref in sprite_textures:
            texture = sprite_textures[normalized_ref]
            normalized_path = texture.lower().lstrip("/")
            if normalized_path in existing_files:
                image_file = existing_files[normalized_path]
                CreateSmallVersion(image_file)
                gfx_file.write(GetDefinition(texture))
            else:
                log.write(f"Missing texture file for {ref}: {texture}\n")
        else:
            log.write(f"Missing sprite: {ref}\n")
    else:
        normalized_path = ref_lower.lstrip("/")
        if normalized_path in existing_files:
            image_file = existing_files[normalized_path]
            CreateSmallVersion(image_file)
            gfx_file.write(GetDefinition(ref))
            UpdateMappings(ref)
        else:
            log.write(f"Missing file: {ref}\n")

gfx_file.write("}")
gfx_file.close()
