import csv
import re

# Regular expression to capture voltage, current, servo values (assuming comma-separated)
pattern = r"voaltage Value: (\d+\.\d+) current value: (\d+) servo:(\d+ \d+)"

# Function to extract values and create a dictionary
def extract_data(line):
    match = re.search(pattern, line)
    if match:
        voltage, current, servo = match.groups()
        date_time = line.split(",")[-1].strip()  # Extract date and time from the last part
        return {"voltage": voltage, "current": current, "servo": servo, "date_time": date_time}
    else:
        print(f"Warning: Line '{line}' does not match the expected format.")
        return None

# Open the text file for reading
with open("data.csv", "r") as textfile:
    data_lines = textfile.readlines()  # Read all lines into a list

# Open the CSV file for writing
with open("exdata.csv", "w", newline="") as csvfile:
    writer = csv.DictWriter(csvfile, fieldnames=["voltage", "current", "servo", "date_time"])
    writer.writeheader()

    # Process each line in the text file
    for line in data_lines:
        data = extract_data(line)
        if data:  # Write only if data extraction is successful
            writer.writerow(data)

print("Data extraction from TXT and CSV creation complete!")
