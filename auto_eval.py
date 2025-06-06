import os
import sys
import subprocess
import time
from datetime import datetime
import psutil

ALGORITHMS = [
    "mst_based",
    "held_karp",
    "nearest_neighbor",
    "randomized_nearest_neighbor",
    "greedy",
    "jam"
]

DATASETS = [
    "jam20",
    "a280",
    "xql662",
    "kz9976",
    "mona-lisa100K"
]

EVAL_EXECUTABLE = "./eval"

results = []


def run_evaluation(algorithm: str, dataset: str) -> dict:
    """
    Launches the eval executable with the given algorithm and dataset,
    tracks peak memory usage, captures stdout/stderr, and returns a summary dict:
        {
            "dataset": str,
            "algorithm": str,
            "length": int or None,
            "duration_s": float or None,
            "peak_memory_kb": int,
            "status": str,
            "stderr": str
        }
    """
    cmd = [EVAL_EXECUTABLE, algorithm, dataset]

    try:
        proc = subprocess.Popen(
            cmd,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True
        )
    except FileNotFoundError:
        raise RuntimeError(f"Executable '{EVAL_EXECUTABLE}' not found or not executable.")

    # Create a psutil.Process object for memory monitoring
    try:
        ps_proc = psutil.Process(proc.pid)
    except psutil.NoSuchProcess:
        ps_proc = None

    max_rss = 0  # Peak Resident Set Size in bytes
    exit_code = None
    stdout_text = ""
    stderr_text = ""

    # While the subprocess is still running, update max_rss every 0.1 seconds
    while True:
        exit_code = proc.poll()
        if ps_proc is not None:
            try:
                mem_info = ps_proc.memory_info()
                if mem_info.rss > max_rss:
                    max_rss = mem_info.rss
            except psutil.NoSuchProcess:
                # The process has exited before we polled; break out
                break

        if exit_code is not None:
            # The subprocess has finished
            break

        time.sleep(0.1)

    # After termination, collect any remaining stdout/stderr
    stdout_text, stderr_text = proc.communicate()

    # Determine if it was killed by a signal (exit_code < 0)
    if exit_code is not None and exit_code < 0:
        signal_num = -exit_code
        status = f"Killed by signal {signal_num}"
    else:
        if exit_code == 0:
            status = "Success"
        else:
            status = f"Error (exit code {exit_code})"

    # Parse Length and Duration from the output (stdout_text)
    length_value = None
    duration_value = None
    for line in stdout_text.splitlines():
        line = line.strip()
        if line.startswith("Length:"):
            # Example format: "Length: 12345.67"
            parts = line.split(":", 1)
            if len(parts) == 2:
                try:
                    length_value = int(parts[1].strip())
                except ValueError:
                    length_value = None
        elif line.startswith("Duration (s):"):
            # Example format: "Duration (s): 0.023456"
            parts = line.split(":", 1)
            if len(parts) == 2:
                try:
                    duration_value = float(parts[1].strip())
                except ValueError:
                    duration_value = None

    # Convert max_rss from bytes to kilobytes
    peak_memory_kb = max_rss // 1024

    return {
        "dataset": dataset,
        "algorithm": algorithm,
        "length": length_value,
        "duration_s": duration_value,
        "peak_memory_kb": peak_memory_kb,
        "status": status,
        "stderr": stderr_text.strip()
    }


def main():
    # Verify that the eval executable exists and is runnable
    if not os.path.isfile(EVAL_EXECUTABLE) or not os.access(EVAL_EXECUTABLE, os.X_OK):
        print(f"[Error] Executable '{EVAL_EXECUTABLE}' not found or not executable.")
        sys.exit(1)

    print("=== Starting Auto Evaluation ===")
    print(f"Executable: {EVAL_EXECUTABLE}")
    print(f"Algorithms: {ALGORITHMS}")
    print(f"Datasets  : {DATASETS}")
    print()

    # Iterate through every dataset–algorithm combination
    for dataset in DATASETS:
        for algorithm in ALGORITHMS:
            timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            print(f"[{timestamp}] Running: algorithm='{algorithm}', dataset='{dataset}' ...", end=" ", flush=True)

            try:
                result = run_evaluation(algorithm, dataset)
            except RuntimeError as e:
                print("Failed")
                print(f"  Reason: {e}")
                print()
                continue

            if result["status"] == "Success":
                print("Done")
            else:
                print("Failed")
            print(f"  Length      : {result['length']}")
            print(f"  Duration    : {result['duration_s']} (s)")
            print(f"  Peak Memory : {result['peak_memory_kb']} (KB)")
            print(f"  Status      : {result['status']}")
            if result["stderr"]:
                print(f"  stderr      : {result['stderr']}")
            print()

            results.append(result)

    # Final summary: write CSV file
    summary_filename = "auto_eval_result.csv"
    try:
        with open(summary_filename, "w") as csv_file:
            # Write header
            csv_file.write("dataset,algorithm,length,duration_s,peak_memory_kb,status\n")
            # Write each result row
            for r in results:
                ds = r["dataset"]
                alg = r["algorithm"]
                length = r["length"] if r["length"] is not None else ""
                dur = r["duration_s"] if r["duration_s"] is not None else ""
                mem = r["peak_memory_kb"]
                st = r["status"]
                csv_file.write(f"{ds},{alg},{length},{dur},{mem},{st}\n")
        print(f"[Info] Summary written to '{summary_filename}'")
    except IOError as e:
        print(f"[Error] Could not write to '{summary_filename}': {e}")

    # # Final summary in CSV format
    # print("=== All Evaluations Completed ===")
    # print("dataset,algorithm,length,duration_s,peak_memory_kb,status")
    # for r in results:
    #     ds = r["dataset"]
    #     alg = r["algorithm"]
    #     length = r["length"] if r["length"] is not None else ""
    #     dur = r["duration_s"] if r["duration_s"] is not None else ""
    #     mem = r["peak_memory_kb"]
    #     st = r["status"]
    #     print(f"{ds},{alg},{length},{dur},{mem},{st}")


if __name__ == "__main__":
    main()
