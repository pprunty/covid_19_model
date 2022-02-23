# COVID-19 Model
This program uses Monte Carlo simulation to model the spread of an infectious disease using the
Metropolis algorithm to control people's degree of social distancing on the grid along with survival
probabilities with a constant hazard rate to determine how many days a person has until death given 
that they are currently infected and have survived up to time t.

![Screenshot](graphics/i100_k0.5_p10000_t0.3.pdf)

## Contents

1. [Overview](#overview)
2. [Requirements](#requirements)
3. [Compilation and Usage](#compilation-and-usage)
4. [Known Issues](#known-issues)

## Overview

### Metropolis Algorithm

A person on the grid's degree of social distancing is controlled by the idea of the Metropolis algorithm. Given the 
current configuration of a system with current energy E1, we can propose an update which would leave the system with 
energy E2. If that update decreases the energy of the system, i.e. E2 < E1, we will accept the update. If it increases 
the energy from E1 to E2 then we will accept the update with probability:

The degree of social distancing is controlled by the variable k. An illustration for different values of k and degree
of social distancing can be seen below:

k = 0

![Screenshot](graphics/K_0.0_TIMESTEPS_100.pdf)

k = 0.5

![Screenshot](graphics/K_0.5_TIMESTEPS_100.pdf)

k = 1

![Screenshot](graphics/K_1.0_TIMESTEPS_100.pdf)

As illustrated, as k increases, the degree to which this person stays close to "home" increases. This gives us control to
model the spread of an infectious disease for different degrees of social distancing k.

### Survival Probability and Hazard Rates

The hazard rate is the he conditional probability density of an event X happening at x given that it survives to that 
point and is given by:


The survival function is thus:



## Requirements

- gcc
- gnuplot (if you would like to produce graphics)

## Compilation and Usage

To compile the code simply run the following command inside a terminal in the project directory:

```shell
make
```

To run the program, simply run the following command inside a terminal in the project directory:

```shell
./main
```

To produce graphics for the 2d walk, run the following commands inside the gnuplot terminal in the project directory:

```shell
./2d_walk 0 > k_0_timesteps_10.txt
```

To produce graphics for the random walk, run the following commands inside the gnuplot terminal in the project directory:

```shell
set title "k=0, timesteps=10"
set grid ytics lt 0 lw 1 lc rgb "#bbbbbb"
set grid xtics lt 0 lw 1 lc rgb "#bbbbbb"
plot 'k_0_timesteps_10.txt' with lines
```

To produce graphics for the disease simulation, run the following commands inside the gnuplot terminal in the project directory:

```shell
set key outside
set xrange [0:100]
set yrange [0:10000]
set title "set title i=100, k=1, p=10000, t=0.3"
plot '100x100_p10000_i100_k0_d0.2_t0.3.txt' using 1:2 with filledcurves x2 title "Didn't Catch" linetype 4, \
'100x100_p10000_i100_k0_d0.2_t0.3.txt' using 1:4 with filledcurves x1 title "Dead" linetype 3, \
'100x100_p10000_i100_k0_d0.2_t0.3.txt' using 1:3 with filledcurves x1 title "Reovered" linetype 2, \
'100x100_p10000_i100_k0_d0.2_t0.3.txt' using 1:2 with filledcurves x1 title "Infected" linetype 1, \
```

Note: I know I can add this to the Makefile as 'make plot' but I prefer to leave the commands here so I can return to them.

## Results




## Known Issues

None at present.
