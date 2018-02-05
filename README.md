# GameOfLife
Modified version of the classic Game of Life, with 3 "races" fighting each other

## get it

If you already have Boost and SFML installed drop the `--recursive`

`git clone --recursive https://github.com/KnutZuidema/GameOfLife.git`

## Build

### Prerequisites

*   [CMake](https://cmake.org/)
*   [SFML](https://www.sfml-dev.org/)
*   [Boost](http://www.boost.org/)

### Building

`build_boost`  
`build_sfml`  
`cmake .`  
`make`

If you have Boost and SFML installed elsewhere you have to pass the `include` and `lib` directories to CMake  
`cmake -DBOOST_INCLUDEDIR=<dir> -DBOOST_LIBRARYDIR=<dir> -DSFML_INCLUDEDIR=<dir> -DSFML_LIBRARYDIR=<dir>`  
You also need to make sure the shared libraries can be found
## Usage

<table>
<tr><th>Argument (=default)</th><th>Description</th></tr>
<tr><td>--help</td><td>produce this help message</td></tr>
<tr><td>-w [ --width ] arg (=400)</td><td>uint, amount of cells horizontally</td></tr>
<tr><td>-h [ --height ] arg (=300)</td><td>uint, amount of cells vertically</td></tr>
<tr><td>-s [ --spawn_chance ] arg (=100)</td><td>uint, chance of a living cell per 1000</td></tr>
<tr><td>-c [ --cell_size ] arg (=3)</td><td>uint, size of the individual cells in pixels</td></tr>
<tr><td>-b [ --border_size ] arg (=30)</td><td>uint, size of the border in pixels</td></tr>
<tr><td>-f [ --frame_rate ] arg (=30)</td><td>uint, max frame rate</td></tr>
</table>

Can also use <code>GameOfLife --help</code> for usage information.
