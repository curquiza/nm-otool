# Nm-Otool

Simple version of nm and otool (-t option)

## Usage

```bash
$> make

$> nm/ft_nm
Usage: ./ft_nm [-gjnpruU] binary_file [...]
  -g : display only global (external) symbols
  -j : just display the symbol names (no value or type)
  -n : sort numerically rather than alphabetically
  -p : don't sort; display in symbol-table order
  -r : sort in reverse order
  -u : display only undefined symbols
  -U : don't display undefined symbols
  
$> otool/ft_otool
Usage: ./ft_otool binary_file [...]
```

## Run test

Main tests:
```bash
$> make run_test
```

On other binanries:
```bash
$> bash tests/nm_test.sh [binary-file]
[...]
$> bash tests/otool_test.sh [binary-file]
[...]
```
