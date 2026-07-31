import os
import sys
import time
import subprocess
import requests
import re
import datetime

# ==========================================
# DUAL LOGGING SETUP (Display + File)
# ==========================================
LOG_DIR = "/storage/emulated/0/VMoutput/Magisk/my_repo"
try:
    os.makedirs(LOG_DIR, exist_ok=True)
except Exception:
    pass

LOG_FILE = os.path.join(LOG_DIR, "script_history.txt")

class TeeLogger:
    def __init__(self, filename):
        self.terminal = sys.stdout
        self.log_file_path = filename
        try:
            self.log = open(filename, "a", encoding="utf-8")
        except Exception:
            self.log = None

    def write(self, message):
        self.terminal.write(message)
        self.terminal.flush()
        if self.log:
            try:
                self.log.write(message)
                self.log.flush()
            except Exception:
                pass

    def flush(self):
        self.terminal.flush()
        if self.log:
            try:
                self.log.flush()
            except Exception:
                pass

sys.stdout = TeeLogger(LOG_FILE)
sys.stderr = sys.stdout

print(f"[*] Logging initialized. Saving session history to: {LOG_FILE}")

# ==========================================
# AUTO-DETECT GITHUB REPOSITORY FROM LOCAL GIT
# ==========================================
def auto_detect_git_repo():
    try:
        remote_url = subprocess.check_output(
            ["git", "config", "--get", "remote.origin.url"],
            stderr=subprocess.DEVNULL,
            text=True
        ).strip()
        match = re.search(r"github\.com[:/]([^/]+)/([^/.]+)(?:\.git)?$", remote_url)
        if match:
            return match.group(1), match.group(2)
    except Exception:
        pass
    return None, None

auto_owner, auto_repo = auto_detect_git_repo()

# ==========================================
# VENICE API KEY & MODEL CONFIG
# ==========================================
chosen_arg = sys.argv[1].strip() if len(sys.argv) > 1 else ""
env_key = os.environ.get("VENICE_API_KEY", os.environ.get("VENICE_KEY_1", os.environ.get("OPENROUTER_API_KEY", "")))

if len(chosen_arg) > 10:
    API_KEY = chosen_arg
    print("[*] Using CLI-provided Venice API Key")
elif env_key:
    API_KEY = env_key
    print(f"[*] Venice API Key loaded successfully from environment (Hint: ...{API_KEY[-4:]})")
else:
    API_KEY = ""
    print("[!] Critical Error: VENICE_API_KEY not found!")

MODEL_NAME = "qwen3-5-35b-a3b"
if os.path.exists("borcher"):
    try:
        with open("borcher", "r", encoding="utf-8") as bf:
            val = bf.read().strip()
            if val:
                MODEL_NAME = val
    except Exception:
        pass

print(f"[*] Target Venice AI Model set to: {MODEL_NAME}")

# ==========================================
# REPOSITORY SELECTION
# ==========================================
print("\n==================================================")
print(" Full-Auto Venice Private Zygisk Builder & Touch Fixer")
print("==================================================")

default_owner = auto_owner if auto_owner else "jason8105"
default_repo = auto_repo if auto_repo else "Reveny-Android-ImGui-Mod-Menu"

_owner = input(f"Enter GitHub Username/Owner (Press Enter for '{default_owner}'): ").strip()
REPO_OWNER = _owner if _owner else default_owner

_repo = input(f"Enter Repository Name (Press Enter for '{default_repo}'): ").strip()
REPO_NAME = _repo if _repo else default_repo

print(f"\n[*] Target Repository set to: {REPO_OWNER}/{REPO_NAME}")
print("==================================================\n")

# ==========================================
# GITHUB ACTIONS FUNCTIONS
# ==========================================
GITHUB_TOKEN = os.environ.get("GITHUB_TOKEN", "")

HEADERS_GH = {
    "Authorization": f"Bearer {GITHUB_TOKEN}",
    "Accept": "vnd.github+json"
} if GITHUB_TOKEN else {}

def run_cmd(cmd):
    result = subprocess.run(cmd, shell=True, capture_output=True, text=True)
    return result.stdout + result.stderr

def trigger_workflow_dispatch():
    # Attempt to fetch dynamic workflows first
    url_workflows = f"https://api.github.com/repos/{REPO_OWNER}/{REPO_NAME}/actions/workflows"
    try:
        res = requests.get(url_workflows, headers=HEADERS_GH, timeout=10)
        if res.status_code == 200:
            workflows = res.json().get("workflows", [])
            if workflows:
                wf_id = workflows[0]["id"]
                dispatch_url = f"https://api.github.com/repos/{REPO_OWNER}/{REPO_NAME}/actions/workflows/{wf_id}/dispatches"
                requests.post(dispatch_url, headers=HEADERS_GH, json={"ref": "main"}, timeout=10)
                return
    except Exception:
        pass

    # Fallback to standard build workflow filenames
    for wf in ["build.yml", "main.yml", "build_zygisk.yml"]:
        url = f"https://api.github.com/repos/{REPO_OWNER}/{REPO_NAME}/actions/workflows/{wf}/dispatches"
        try:
            res = requests.post(url, headers=HEADERS_GH, json={"ref": "main"}, timeout=10)
            if res.status_code in [204, 200]:
                break
        except Exception:
            pass

def get_latest_workflow_run():
    url = f"https://api.github.com/repos/{REPO_OWNER}/{REPO_NAME}/actions/runs?per_page=1"
    try:
        res = requests.get(url, headers=HEADERS_GH, timeout=15)
        if res.status_code == 200:
            data = res.json()
            runs = data.get("workflow_runs", [])
            if not runs:
                return None, None
            return runs[0]["id"], runs[0]["status"]
    except Exception as e:
        print(f"[!] Error fetching latest run: {e}")
    return None, None

def check_artifact_size(run_id):
    url = f"https://api.github.com/repos/{REPO_OWNER}/{REPO_NAME}/actions/runs/{run_id}/artifacts"
    try:
        res = requests.get(url, headers=HEADERS_GH, timeout=15)
        if res.status_code == 200:
            artifacts = res.json().get("artifacts", [])
            if not artifacts:
                print("[!] Warning: No build artifacts found in this run!")
                return False
                
            for art in artifacts:
                size = art.get("size_in_bytes", 0)
                name = art.get("name", "unknown")
                print(f"[*] Found Artifact: '{name}' | Size: {size} bytes")
                if size < 5000:
                    print(f"[!] Critical: Artifact size is too small ({size} bytes). Missing compiled binaries (.so files)!")
                    return False
            return True
    except Exception as e:
        print(f"[!] Error verifying artifact size: {e}")
    return True

def get_workflow_logs(run_id, max_retries=5):
    print("[*] Fetching failed job details to get direct text logs via GitHub API...")
    jobs_url = f"https://api.github.com/repos/{REPO_OWNER}/{REPO_NAME}/actions/runs/{run_id}/jobs"

    for attempt in range(max_retries):
        try:
            res = requests.get(jobs_url, headers=HEADERS_GH, timeout=30)
            if res.status_code != 200:
                print(f"[!] Failed to get jobs. Status {res.status_code}. Retrying...")
                time.sleep(5)
                continue

            jobs = res.json().get("jobs", [])
            failed_logs = ""

            for job in jobs:
                if job.get("conclusion") == "failure":
                    job_id = job["id"]
                    print(f"[*] Downloading text log for failed job: {job['name']}...")
                    log_url = f"https://api.github.com/repos/{REPO_OWNER}/{REPO_NAME}/actions/jobs/{job_id}/logs"

                    log_res = requests.get(log_url, headers=HEADERS_GH, allow_redirects=True, timeout=150)
                    if log_res.status_code == 200:
                        failed_logs += f"\n=== Job: {job['name']} ===\n" + log_res.text
                        print(f"[*] Log downloaded successfully for {job['name']}")
                    else:
                        print(f"[!] Failed to get log text. Status {log_res.status_code}")

            if failed_logs:
                lines = failed_logs.splitlines()
                clean_lines = []
                
                for line in lines:
                    if "[" in line and "%" in line:
                        continue
                    if any(noise in line for noise in ["Downloading", "Unzipping", "Loading local repository", "Accept? (y/N)", "Terms and Conditions", "License Agreement"]):
                        continue
                    clean_lines.append(line)
                    
                final_error_block = "\n".join(clean_lines[-400:])
                
                try:
                    with open("clean_errors.txt", "w", encoding="utf-8") as lf:
                        lf.write(final_error_block)
                except Exception:
                    pass
                return final_error_block
            else:
                return "Empty logs or no failure found."

        except Exception as e:
            print(f"[!] Network error fetching job logs: {e}. Retrying ({attempt+1}/{max_retries})...")
            time.sleep(10)

    return "Log fetch error: Network timeout."

# ==========================================
# VENICE AI LOGIC (ZYGISK + IMGUI + TOUCH FIX)
# ==========================================
def ask_venice_api(error_logs):
    prompt = f"""
You are an elite Android NDK, C++, Gradle, and Zygisk module build engineer specializing in native game mod menus, ImGui overlays, and touch injection hooks.
Your mission is to fix build, compilation, and packaging errors for this Magisk Zygisk ImGui + Touch Fix module repository.

CRITICAL ARCHITECTURAL REQUIREMENTS:
1. PRESERVE & FIX EXISTING HOOKS: The repository contains native touch interception and ImGui rendering logic. Fix any C++ compilation errors (such as missing namespace members like `HookEngine::PltHookAllModules`, incorrect `ImGui::SetNextWindowPos`/`SetNextWindowSize` syntax, or `TouchHook` scope resolutions) without breaking the core overlay loop.
2. IMGUI & GRAPHICS HOOK: Ensure the ImGui context is correctly initialized and rendered inside the graphics hook (e.g., `eglSwapBuffers` or Vulkan swapchain hook). Keep rendering calls compatible with the target C++17 standard.
3. TOUCH INTERCEPTION: Maintain the touch hook logic (e.g., hooking `AInputQueue_getEvent` or similar input queues) so the ImGui menu receives touch events properly while letting gameplay touches pass through when the menu is closed.
4. ZYGISK & MAGISK PACKAGING: Ensure the compiled native library (`.so`) is properly exported, built for `arm64-v8a`, and packaged correctly into the final Magisk module structure (`zygisk/arm64-v8a.so` or standard module folders) so the generated zip is clean and valid.

STRICT OUTPUT INSTRUCTIONS:
- DO NOT ask clarifying questions. DO NOT output conversational text, explanations, or markdown prose outside the blocks.
- You MUST output the exact file modifications using the strict file block formats specified below.

You MUST provide a short git commit message summary using this exact format:
=== COMMIT: [Your descriptive commit message here] ===

Use these exact block formats for files:
=== FILE: path/to/file ===
[File content here]
=== END FILE ===

To delete an obsolete file:
=== DELETE: path/to/file ===
=== END DELETE ===

ERROR LOGS / STATUS CONTEXT:
{error_logs}
"""
    
    if not API_KEY:
        print("[!] Error: Venice API_KEY is missing.")
        return "API Error: API_KEY missing."

    chat_url = "https://api.venice.ai/api/v1/chat/completions"
    headers = {
        "Authorization": f"Bearer {API_KEY}",
        "Content-Type": "application/json"
    }
    
    payload = {
        "model": MODEL_NAME,
        "messages": [{"role": "user", "content": prompt}],
        "max_tokens": 4096,
        "venice_parameters": {
            "enable_web_search": "auto",
            "enable_web_scraping": True,
            "include_venice_system_prompt": True
        }
    }

    print(f"\n[*] Sending request to Venice AI Model: {MODEL_NAME} with ImGui/Touch context...")

    try:
        response = requests.post(chat_url, headers=headers, json=payload, timeout=120)
        res_json = response.json()
        
        ai_message = res_json.get('choices', [{}])[0].get('message', {}).get('content', '')
        
        if ai_message and ai_message.strip():
            print(f"[+] Success getting response from Venice Model: {MODEL_NAME}")
            return ai_message
        else:
            error_msg = res_json.get('error', {}).get('message', 'Unknown Error or Empty Response')
            print(f"[!] Venice API Error: {error_msg}")
            return f"API Error: {error_msg}"
    except Exception as e:
        print(f"[!] Network error/timeout calling Venice API: {str(e)}")
        return f"API Error: {str(e)}"

def apply_ai_patches(ai_response):
    changes_made = []

    if not ai_response or "API Error" in ai_response:
        print(f"[!] API Error encountered: {ai_response}")
        return [], "fix: api error fallback"

    # Clean markdown code fences safely
    ai_response = re.sub(r"^```[a-zA-Z]*\n", "", ai_response, flags=re.MULTILINE)
    ai_response = re.sub(r"\n```\s*$", "", ai_response)

    commit_match = re.search(r"=== COMMIT:\s*([^\n]+)\s*===", ai_response)
    commit_message = commit_match.group(1).strip() if commit_match else "fix: resolve build and compilation errors"

    # Robust regex to extract FILE blocks
    pattern_explicit = r"=== FILE:\s*([^\n]+)===\s*\n(.*?)\s*=== END FILE ==="
    matches_file = re.findall(pattern_explicit, ai_response, re.DOTALL)
    
    # Fallback pattern if explicit END tags are missing
    if not matches_file:
        pattern_fallback = r"=== FILE:\s*([^\n]+)===\s*\n(.*?)(?==== FILE:|=== DELETE:|\Z)"
        matches_file = re.findall(pattern_fallback, ai_response, re.DOTALL)

    for file_path, content in matches_file:
        file_path = file_path.strip().replace("\r", "").strip("`").strip()
        content = content.strip().replace("=== END FILE ===", "").strip()
        
        # Double safe markdown stripping
        content = re.sub(r"^```[a-zA-Z]*\n", "", content)
        content = re.sub(r"\n```\s*$", "", content)
        content = content.strip()

        if not file_path or len(file_path) > 200:
            continue
            
        dir_name = os.path.dirname(file_path)
        if dir_name and not os.path.exists(dir_name):
            os.makedirs(dir_name, exist_ok=True)
            
        with open(file_path, "w", encoding="utf-8") as f:
            f.write(content + "\n")
        changes_made.append(f"Updated/Created: {file_path}")

    pattern_del = r"=== DELETE:\s*([^\n]+)===\s*(?:=== END DELETE ===)?"
    matches_del = re.findall(pattern_del, ai_response, re.DOTALL)
    for file_path in matches_del:
        file_path = file_path.strip().replace("\r", "").strip("`").strip()
        if file_path.endswith("/") or file_path.endswith("*"):
            try:
                subprocess.run(f"rm -rf {file_path.strip('*')}", shell=True)
                changes_made.append(f"Deleted Directory: {file_path}")
            except:
                pass
        elif os.path.exists(file_path):
            os.remove(file_path)
            changes_made.append(f"Deleted: {file_path}")

    if not changes_made:
        print("[!] Warning: Response received from model but could not parse patch blocks. Saving to ai_fix_suggestion.txt")
        with open("ai_fix_suggestion.txt", "w", encoding="utf-8") as f:
            f.write(ai_response)
        return [], commit_message

    return changes_made, commit_message

# ==========================================
# MASTER CONTROL LOOP
# ==========================================
def master_loop():
    print("==================================================")
    print(" Starting Full-Auto Venice Private Zygisk Builder & Touch Fixer")
    print("==================================================")

    last_processed_run_id = None

    while True:
        try:
            try:
                subprocess.run("termux-wake-lock", shell=True, capture_output=True)
            except Exception:
                pass

            print(f"[*] Checking GitHub ({REPO_OWNER}/{REPO_NAME}) for active workflow run...")
            run_id, status = get_latest_workflow_run()

            if not run_id:
                time.sleep(15)
                continue

            if run_id == last_processed_run_id:
                time.sleep(10)
                continue

            print(f"[*] Monitoring Workflow Run ID: {run_id} | Status: {status}")

            while status in ["queued", "in_progress"] or status is None:
                time.sleep(15)
                _, status = get_latest_workflow_run()
                if status is None:
                    print("[!] Internet disconnected. Waiting for network...")
                else:
                    print(f"[*] Build is {status}... waiting for it to finish...")

            url = f"https://api.github.com/repos/{REPO_OWNER}/{REPO_NAME}/actions/runs/{run_id}"

            try:
                run_details = requests.get(url, headers=HEADERS_GH, timeout=15).json()
                conclusion = run_details.get("conclusion")
                print(f"[*] Build completed. Conclusion: {conclusion}")
            except Exception as e:
                print(f"[!] Network error checking build conclusion: {e}. Retrying...")
                time.sleep(15)
                continue

            if conclusion == "success":
                print("[*] GitHub Actions reports build success. Checking artifact contents & size...")
                if check_artifact_size(run_id):
                    print("\n==================================================")
                    print(" SUCCESS! Valid Zygisk Module Zip compiled cleanly!")
                    print("==================================================")
                    last_processed_run_id = run_id
                    print("[*] Waiting for new builds...\n")
                    continue
                else:
                    print("[!] Artifact validation failed (empty zip size). Forcing Auto-Heal...")
                    conclusion = "failure"

            if conclusion in ["failure", "cancelled", "timed_out"] or conclusion != "success":
                print(f"[!] Build failed or status invalid (conclusion: {conclusion}). Initiating Auto-Heal...")

                logs = get_workflow_logs(run_id)
                if "Log fetch error" in logs:
                    logs = "Build artifact was empty/invalid. Gradle/CMake failed to build or package binaries."

                print("[*] Analyzing clean error logs with Venice AI...")
                ai_fix = ask_venice_api(logs)

                print("[*] Automatically applying AI patches to local files...")
                applied_changes, commit_message = apply_ai_patches(ai_fix)

                if applied_changes:
                    print(f"[+] CHANGES APPLIED: {', '.join(applied_changes)}")
                    print(f"[+] AI COMMIT MESSAGE: {commit_message}")
                    run_cmd("git add .")
                    safe_msg = commit_message.replace('"', '\\"')
                    run_cmd(f'git commit -m "{safe_msg}"')
                    run_cmd("git push origin main --force")
                    print("[+] Pushed code updates to GitHub!")

                    print("[+] Triggering a new workflow build to test the fixes...")
                    trigger_workflow_dispatch()
                    last_processed_run_id = run_id
                    time.sleep(20)
                else:
                    print("[!] No patch blocks applied.")
                    last_processed_run_id = run_id
                    time.sleep(15)

        except Exception as e:
            print(f"\n[CRITICAL ERROR] Script encountered an issue: {e}")
            print("[*] Don't worry, restarting loop in 15 seconds...\n")
            time.sleep(15)

if __name__ == "__main__":
    master_loop()
