# vpr-midas
This project aims to provide a tool for the modification of the  
date-time information of a file.

## Docker Environment
```
# Download repo
git clone https://github.com/0xvpr/vpr-midas
cd vpr-midas

# Create docker image
chmod +x docker-build.sh && ./docker-build.sh
chmod +x docker-start.sh && ./docker-start.sh
```

## Build instructions
```bash
git clone https://github.com/0xvpr/vpr-midas
cd vpr-midas
make
# sudo make install # if you want it available globally (only recommended for WSL/MSYS environments)
```

## Example Usage
```bash
vpr-midas path/to/file [ -c | --custom | -s | --silent ]
```

## Testing (Needs improvement)
```bash
chmod +x ./run-test.sh && ./run-test.sh
```
