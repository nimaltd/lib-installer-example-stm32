# stm32-installer-example

A small library made to try [stm32-installer](https://github.com/nimaltd/stm32-installer) on, and a starting point for making your own library installable.

It does one useful thing. `example_due()` says yes once every `EXAMPLE_PERIOD_MS` milliseconds and never blocks, so a main loop can blink an LED, read a sensor or print a line on a rhythm, without `HAL_Delay()` holding everything else up. Its `uptime` option adds `example_uptime()`, the time since start up in hours, minutes and seconds.

It also has a step for stm32-installer 2.0.0 to run, so you can see one work: `make-id` makes `Core/Inc/example_id.h`, this board's own ID, a random number that `example_id()` returns. The installer shows what it runs and asks first.

---

## Try the installer with it

Install the installer once:

```bash
pip install stm32-installer
```

It needs stm32-installer 2.0.0 or newer. `pip install --upgrade stm32-installer` brings an older one up to date.

Then, from the root of any STM32 project CubeMX made, for STM32CubeIDE, CMake, Keil, IAR or a Makefile:

```bash
stm32-installer nimaltd/stm32-installer-example
```

It asks three things. Press Enter for each, and the library goes into `example/` without its option, and its step runs:

```
Options
  uptime     Uptime in hours, minutes and seconds. Add it? [y/N]:
Folder to install example into [example]:
...
Run
  make-id      Make this board's own ID, Core/Inc/example_id.h
               python scripts/make_id.py Core/Inc/example_id.h
               Run it? [Y/n]:
Made Core/Inc/example_id.h: device 2EA6A6A4.
               done
```

`Core/Inc` is on the include path of every IDE CubeMX makes a project for, which is how `example.c` finds the file.

Then use it in `main.c`, between CubeMX's `USER CODE` lines so CubeMX keeps it:

```c
/* USER CODE BEGIN Includes */
#include "example.h"
/* USER CODE END Includes */
```

```c
  /* USER CODE BEGIN 2 */
  example_t blink;
  example_init(&blink);
  /* USER CODE END 2 */

  while (1)
  {
    /* USER CODE BEGIN 3 */
    if (example_due(&blink))
    {
      HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
    }
    /* USER CODE END 3 */
  }
```

`LD2` is the user LED of a Nucleo board. Use the name CubeMX gave yours. Build and flash, and it blinks every half a second.

### Things to try

**Keep a setting through an update.** Open `example/src/example_config.h` and change the period between its `USER CODE` lines:

```c
/* USER CODE BEGIN EXAMPLE_CONFIGURATION */
#define EXAMPLE_PERIOD_MS           100U
/* USER CODE END EXAMPLE_CONFIGURATION */
```

Run the same install command again. Every file of the library is written again, and the installer says it kept yours:

```
  kept    example/src/example_config.h  your USER CODE EXAMPLE_CONFIGURATION
```

**Its board ID.** `example_id()` returns the number in `Core/Inc/example_id.h`, made for this project alone. Run the install again, and the step is not asked about: `make-id skipped, Core/Inc/example_id.h is already there`, so the ID never changes under a board already in use. Delete the file, and the next install asks again and makes a new one. Answer for it on the command line instead, with `--run make-id` to run it or `--no-run make-id` to leave it, and `--yes` takes every answer offered, for a script. Nobody to answer, and it is not run; then `example_id()` is 0.

```c
uint32_t id = example_id();   /* this board's own, 0 when the step was not run */
```

**Add a part, and take it out.** `--with uptime` adds `example_uptime.h` and `example_uptime.c`, and registers them with your IDE. `--without uptime` takes them out of both again.

```bash
stm32-installer nimaltd/stm32-installer-example --with uptime
```

```c
example_uptime_t up = example_uptime();   /* up.hours, up.minutes, up.seconds */
```

**Uninstall it.** The library leaves every IDE project it was put in, and then its files go. What you changed in `example_config.h` is saved beside it first. `Core/Inc/example_id.h` stays, since it is yours:

```bash
stm32-installer --uninstall example
```

**Without internet.** Download this repository as a zip, from the green **Code** button, **Download ZIP**, and give the installer the zip instead of the name:

```bash
stm32-installer D:/Downloads/stm32-installer-example-main.zip
```

---

## Make your own library installable

Copy [`installer.yml`](installer.yml) to the root of your library's repository, and change what is yours: its name, its description, its repository and its files. Every key the installer reads is in it, with a comment saying what it does; the ones this library has no use for are commented out. Only `name` and `files` are required.

Then anyone installs your library with:

```bash
stm32-installer yourname/yourlibrary
```

A configuration file with `USER CODE BEGIN` and `USER CODE END` lines, like `example_config.h`, keeps the user's settings on every update. `run` lists the steps run after the install, with the script in [`scripts/make_id.py`](scripts/make_id.py). The [stm32-installer README](https://github.com/nimaltd/stm32-installer#for-someone-writing-a-library) has the rest.

---

## API

| Function | What it does |
|---|---|
| `void example_init(example_t *handle)` | Start a period of `EXAMPLE_PERIOD_MS` from now |
| `bool example_due(example_t *handle)` | Whether the period has passed. Returns at once, and starts the next one when it has |
| `uint32_t example_count(const example_t *handle)` | How many times `example_due()` has said yes |
| `uint32_t example_id(void)` | This board's own ID, from `Core/Inc/example_id.h`, or 0 when the step was not run |
| `example_uptime_t example_uptime(void)` | With the `uptime` option: hours, minutes and seconds since start up |

Declare one `example_t` for each thing that repeats on its own rhythm. A main loop that comes back late is caught up, so the rhythm does not drift.

---

## License

Apache License 2.0. See [LICENSE.md](LICENSE.md).
