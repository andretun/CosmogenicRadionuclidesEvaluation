# Source files
In this folder, the source files for the simulation are stored.
An explanation for the files that differ fromm _Hadro06_ example is presented below.

## DetectorConstruciton
In _DetectorConstruction_ the geometry and composition of the detector (or in our case the asteroid) is defined.
The celestial body is described as a spherical object of determined radius and composition.

A series of setter funtion is added in order to be able to dynamically change the default feautres of the asteroid.

## HistoManager
in _HistoManager_, the histograms generated at the end of the simulation are defined, identified by a number and a name.
Moreover, the number of bins and the x-axis span are also defined, but they can be modified with a [macro](https://github.com/Tun98/CosmogenicRadionuclidesEvaluation/tree/main/macro).


## PrimaryGeneratorAction
In _PrimaryGeneratorAction_, the default particle (cosmic ray) generated in the simulation is the proton.
The wanted particle can be declared directly in this source file, or in a [macro](https://github.com/Tun98/CosmogenicRadionuclidesEvaluation/tree/main/macro).

## Tracking actions
In _TrackingAction_, the radionuclides of interest are searched in every particle created in the simulation. Onces an isotope is found, its histogram is updated at the bin depth it was found in.
