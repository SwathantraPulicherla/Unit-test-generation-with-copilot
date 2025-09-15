
import os
import re
import requests

HF_TOKEN = os.getenv("HF_TOKEN")
MODEL = "bigcode/starcoder"  # open-source code LLM

headers = {"Authorization": f"Bearer {HF_TOKEN}"}
API_URL = f"https://api-inference.huggingface.co/models/{MODEL}"

def call_hf(prompt: str) -> str:
    response = requests.post(API_URL, headers=headers, json={"inputs": prompt})
    response.raise_for_status()
    return response.json()[0]["generated_text"]

def extract_functions(code: str):
    """Find C function signatures using regex."""
    # This regex matches function definitions (not declarations)
    return re.findall(r"\b[A-Za-z_][A-Za-z0-9_]*\s+\**[A-Za-z_][A-Za-z0-9_]*\s*\([^)]*\)\s*{", code)

def ensure_test_file(fname: str, functions: list):
    test_file = f"test_{fname}.c"

    existing = ""
    if os.path.exists(test_file):
        with open(test_file) as f:
            existing = f.read()

    for func in functions:
        func_name = func.split("(")[0].split()[-1]
        if func_name not in existing:
            print(f"[+] Generating test for {func}")
            prompt = f"Write a C unit test using Unity framework for function:\n{func}\n"
            test_code = call_hf(prompt)
            with open(test_file, "a") as f:
                f.write("\n" + test_code + "\n")

def main():
    for src_file in os.listdir("."):
        if src_file.endswith(".c") and not src_file.startswith("test_") and src_file != "unity.c":
            with open(src_file) as f:
                code = f.read()
            functions = extract_functions(code)
            if functions:
                fname = os.path.splitext(src_file)[0]
                ensure_test_file(fname, functions)

if __name__ == "__main__":
    main()
