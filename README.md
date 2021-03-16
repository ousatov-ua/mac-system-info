# System Info for MacOSX

## Screenshot of UI (ncurses)

![alt text](screen.jpg?raw=true)

## Run program

`./system_info` or `./system_info --help` - show possible arguments

`./system_info --console`                 - output json (one time without refresh)

`./system_info --ui`                      - ncurses view (from screenshot) with auto refresh

## Open project

Use CLion or any other IDE to open it, `CMakeLists.txt` should be used for that.

## SMC

Information about temperatures and fan is fetched from SMC.

## Build

Can be built by running `build.sh` (you'll need `brew` installed).

# The output

Example of output `SystemInfo::toString()`:

```json
{
  "system_info": {
    "cpu": {
      "freq": 2600000000,
      "logical_cores": 8,
      "name": "Intel(R) Core(TM) i7-6700HQ CPU @ 2.60GHz",
      "phys_cores": 4,
      "temperature": {
        "celsius": 42.3125
      },
      "type": 7
    },
    "memory": {
      "memory": 17179869184
    },
    "fans": [
      {
        "actual_speed": {
          "rpm": 2159.0
        },
        "id": 0,
        "maximum_speed": {
          "rpm": 5927.0
        },
        "minimal_speed": {
          "rpm": 2160.0
        },
        "mode": "forced",
        "name": "Left",
        "safe_speed": {
          "rpm": -1.0
        },
        "target_speed": {
          "rpm": 2160.0
        }
      },
      {
        "actual_speed": {
          "rpm": 1994.0
        },
        "id": 1,
        "maximum_speed": {
          "rpm": 5489.0
        },
        "minimal_speed": {
          "rpm": 2000.0
        },
        "mode": "forced",
        "name": "Right",
        "safe_speed": {
          "rpm": -1.0
        },
        "target_speed": {
          "rpm": 2000.0
        }
      }
    ],
    "gpu": {
      "temperature": {
        "celsius": 44.5625
      }
    }
  }
}
```
