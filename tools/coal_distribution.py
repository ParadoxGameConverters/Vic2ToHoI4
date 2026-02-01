import re
from pathlib import Path

HOI4_DIR = Path("")
STATES_DIR = HOI4_DIR / "history/states/"
OUTPUT_FILE = Path("./data/configurables/resources.txt")

coal_re = re.compile(r"\bcoal\s*=\s*([0-9]+(?:\.[0-9]+)?)")
provinces_re = re.compile(r"provinces\s*=\s*\{([^}]*)\}", re.DOTALL)

def extract_coal(text: str) -> int:
    match = coal_re.search(text)
    if not match:
        return 0
    return int(float(match.group(1)))

def extract_provinces(text: str) -> list[int]:
    match = provinces_re.search(text)
    if not match:
        return []
    return [int(p) for p in match.group(1).split() if p.isdigit()]

def distribute(total: int, count: int) -> list[int]:
    base = total // count
    remainder = total % count
    result = [base] * count
    for i in range(remainder):
        result[i] += 1
    return result

OUTPUT_FILE.parent.mkdir(parents=True, exist_ok=True)

with OUTPUT_FILE.open("a", encoding="utf-8") as out:
    out.write("\n### COAL ###\n")

    for state_file in sorted(STATES_DIR.glob("*.txt")):
        text = state_file.read_text(encoding="utf-8", errors="ignore")

        coal = extract_coal(text)
        if coal <= 0:
            continue

        provinces = extract_provinces(text)
        if not provinces:
            continue

        distribution = distribute(coal, len(provinces))

        for province, amount in zip(provinces, distribution):
            if amount <= 0:
                continue
            out.write(
                f"link = {{ province = {province} resources = {{ coal = {amount} }} }}\n"
            )
