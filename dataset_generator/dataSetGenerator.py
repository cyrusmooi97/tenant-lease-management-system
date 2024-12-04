import random
import string

# Function to generate random strings (for names, lease start and end dates)
def random_string(length):
    return ''.join(random.choices(string.ascii_letters + string.digits, k=length))

# Function to generate a random date in the format YYYY-MM-DD
def random_date():
    year = random.randint(2000, 2024)
    month = random.randint(1, 12)
    day = random.randint(1, 28)  # To avoid invalid dates
    return f"{year}-{month:02d}-{day:02d}"

# Create the dataset
tenant_ids = set()  # To store unique tenant IDs
dataset = []
for _ in range(1, 100001):
    tenant_id = random.randint(1, 100000)
    while tenant_id in tenant_ids:  # Ensure unique tenant_id
        tenant_id = random.randint(1, 100000)
    tenant_ids.add(tenant_id)
    
    name = random_string(15)  # Random name of 10 characters
    lease_id = random.randint(100000, 999999)
    lease_start = random_date()
    lease_end = random_date()
    
    dataset.append(f"{tenant_id},{name},{lease_id},{lease_start},{lease_end}")

# Write to a .dat file
with open("tenant_data.dat", "w") as file:
    file.write("\n".join(dataset))

print("Dataset generated and saved to 'tenant_data.dat'")