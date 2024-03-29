Part of a college assignment...

# COVID-19 Model
This program uses Monte Carlo simulation to model the spread of an infectious disease using the
Metropolis algorithm to control people's degree of social distancing on the grid along with survival
probabilities with a constant hazard rate to determine how many days a person has until death given 
that they are currently infected and have survived up to time t.

![Screenshot](graphics/i100_k0_p10000_t0.5.png)

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

![Screenshot](graphics/k_0_timesteps_100.png)

k = 0.5

![Screenshot](graphics/k_0.5_timesteps_100.png)

k = 1

![Screenshot](graphics/k_1_timesteps_100.png)

As illustrated, as k increases, the degree to which this person stays close to "home" increases. This gives us control to
model the spread of an infectious disease for different degrees of social distancing k.

### Survival Probability and Hazard Rates

The hazard rate is the he conditional probability density of an event X happening at x given that it survives to that 
point and is given by:

![Screenshot](equations/hazard_rate.png)

The survival function is thus:

![Screenshot](equations/survival_function.png)

If we assume a constant hazard rate hX(x) = λ then this just becomes:

![Screenshot](equations/survival_function_constant.png)

Or equivalently, we can write:

![Screenshot](equations/survival_function_cum.png)

This is just an exponential distribution. You can invert the equation above and use the inverse transform method to 
map a uniform random variate, y ∈ U(0,1), back to exponentially distributed t

![Screenshot](equations/exponential_t.png)

For the model we will assume a constant hazard rate. When a person is “infected” we will 
randomly assign a days-to-death variable. We will have a fixed time-to-recovery parameter (e.g. 14 days/turns). If the 
days-to-death is greater than the recovery time, then the person will be cured and become immune at 14 days. If their 
randomly assigned days-to-death is say 5, then they will die and be removed after 5 days.

## Requirements

- g++
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
./2d_walk 0 > k_0_timesteps_100.txt
```

To produce graphics for the random walk, run the following commands inside the gnuplot terminal in the project directory:

```shell
set title "k=0, timesteps=100"
set xrange [0:10]
set yrange [0:10]
set grid ytics lt 0 lw 1 lc rgb "#bbbbbb"
set grid xtics lt 0 lw 1 lc rgb "#bbbbbb"
plot 'k_0.5_timesteps_100.txt' with lines title "2d random walk"
```

To produce graphics for the disease simulation, run the following commands inside the gnuplot terminal in the project directory:

```shell
set key outside
set xrange [0:80]
set yrange [0:10000]
set title "set title i=100, k=1, p=10000, t=0.3"
plot '100x100_p10000_i100_k0.5_d0.2_t0.5.txt' using 1:2 with filledcurves x2 title "Didn't Catch" linetype 4, \
'100x100_p10000_i100_k0.5_d0.2_t0.5.txt' using 1:4 with filledcurves x1 title "Dead" linetype 3, \
'100x100_p10000_i100_k0.5_d0.2_t0.5.txt' using 1:3 with filledcurves x1 title "Reovered" linetype 2, \
'100x100_p10000_i100_k0.5_d0.2_t0.5.txt' using 1:2 with filledcurves x1 title "Infected" linetype 1, \
```

Note: I know I can add this to the Makefile as 'make plot' but I prefer to leave the commands here so I can return to them.

## Results

![Screenshot](graphics/i100_k0_p10000_t0.5.png)

![Screenshot](graphics/i100_k1_p10000_t0.5.png)



## Known Issues

None at present.
