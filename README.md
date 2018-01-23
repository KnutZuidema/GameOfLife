# GameOfLife
Modified version of the classic Game of Life, with 3 "races" fighting each other

## get it

`git clone --recursive https://github.com/KnutZuidema/GameOfLife.git`

## Build

### Prerequisites

*   [cmake](#)
*   [SFML 2.0](https://www.sfml-dev.org/)
*   [Boost.Program-options 1.66](http://www.boost.org/doc/libs/1_66_0/doc/html/program_options.html)

### Compilation

##### GCC 6.1

`g++ -I$(INCLUDEDIR) main.cpp Cell.cpp Grid.cpp -c`

### Linking

##### GCC 6.1

`g++ -o GameOfLife.exe main.o Cell.o Grid.o -L$(LIBDIR) -lsfml-graphics -lsfml-window -lsfml-system -lboost_program_options`

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
