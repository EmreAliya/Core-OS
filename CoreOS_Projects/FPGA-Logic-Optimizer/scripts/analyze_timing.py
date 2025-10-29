import re, sys

def analyze_report(path):
    with open(path) as f:
        text = f.read()
    delay = re.findall(r"Critical path:\s+([\d\.]+) ns", text)
    if delay:
        print(f"[+] Critical path delay: {delay[0]} ns")
    else:
        print("[-] No critical path found.")

if __name__ == "__main__":
    report = sys.argv[1] if len(sys.argv) > 1 else "timing.rpt"
    analyze_report(report)
