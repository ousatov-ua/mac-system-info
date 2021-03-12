# C++ project for getting System Info for MacOSX

## Open project

Use CLion or any other IDE to open it, `CMakeLists.txt` should be used for that.

## SMC

Information about temperatures and fan is fetched from SMC

## Build

You'll need `nlomann_json` to build it:
`brew tap nlohmann/json` and `brew install nlohmann_json`

You'll need `ncurses`:
`brew install ncurses`

# The output

Example of output `SystemInfo::to_string()`:

```json
{
  "system_info": {
    "cpu": {
      "freq": 3100000000,
      "logical_cores": 12,
      "name": "Intel(R) Core(TM) i5-10500 CPU @ 3.10GHz",
      "phys_cores": 6,
      "temperature": 40.187500,
      "type": 7
    },
    "memory": {
      "memory": 34359738368
    },
    "fans": [
      {
        "actual_speed": 1200.1839599609375,
        "id": 0,
        "maximum_speed": 2700.0,
        "minimal_speed": 1200.0,
        "name": "[Empty]",
        "safe_speed": 0.0,
        "target_speed": 1200.0
      }
    ],
    "gpu": {
      "temperature": 40.125000
    }
  }
}
```

