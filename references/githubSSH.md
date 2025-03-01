# How to set up github on Odin with keys that will not need to be rotated: Using SSH instead of HTTPS

### Step 1: Sign into Odin
### Step 2: Run: 

    vim ~/.ssh/config

### Step 3: Inside of .ssh/config input the following:

    Host github.com
        User git
        Hostname github.com
        IdentityFile ~/.ssh/id_rsa

### Step 4: Create Public - Private key pair using ssh-keygen
Run:

    ssh-keygen -t rsa -b 4096

Don't set up a passphrase. 
So press enter twice to make the passphrase empty.

### Step 5: The command will prompt for an output file. Just hit enter to select the default ~/.ssh/id_rsa

### Step 6: get the public key
Run:

    ssh-keygen -y -t rsa -b 4096

### Step 7: The command will output a public key of the form 

    ssh-rsa AAA1498234032...==  Username@odin

Copy everything starting from      ssh      and ending before the first space. Don't copy the username. Do copy both equals signs.

### Step 8: Go to Github -> Settings -> SSH and GPG keys -> New SSH Key

Name the key something like Odin in the title box
Paste the public key into the Key box
Key type should be authentication key

-> Add SSH Key

If Github tells you that it's not a valid key, you probably copied it wrong from the terminal. 

### Step 9: Go to your Odin:../pizza_delivery..  directory

### Step 10: Run:

    git remote set-url origin git@github.com:SystemCo/pizza_delivery_simulator.git

### Step 11:
Profit. Your pushes and pulls should work now. 
