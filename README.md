# CosmogenicRadionuclidesEvaluation
CosmogenicRadionuclidesEvaluation refers to the Master's Thesis in [this folder](https://github.com/Tun98/CosmogenicRadionuclidesEvaluation/tree/main/docs).
It consists of a Geant4-based model for the evaluation of cosmogenic radionuclide activities in extraterrestrial bodies.

In the following sections, a brief technical descriptio of the model is presented. For more details, please refer to the thesis above mentioned.

## Overview
Cosmogenic radionuclides are the interaction (spallation, neutron capture, etc.) products of the hadronic component of cosmic rays impacting the interstellar matter. 
Celestial bodies are exposed to both SCRs and GCRs, resulting in the production of several cosmogenic isotopes. The production rate of a nuclide depends on the fluxes of primary (cosmic ray) and secondary (product of the interaction of primaries in the matter) particle fluxes. The measurement of cosmogenic radionuclide activities reveals the exposure history of the body during a period of about three half-lives of the radioisotopes.

In this work, a Geant4 model has been develop to evaluate the radionuclide production rates in spherical targets with a determined compositions.


## The code
The code has been developed with the 10.7.03 version of the software and is based on the built-in hadronic example _Hadro06_, which has been modified to meet the physical situation we are interested in.
In order to easily access the different physics lists, the G4PhysicsListFactory class was implemented in the main script instead of the more common PhysicsList header, in which the user declares the physics to be used in the simulation.
In order to represent the CR isotropic flux, the G4ParticleGun class, which allows for generating particles from point sources, was replaced with the G4GeneralParticleSource, which provides different source surface shapes and arbitrary energy and angular spectra for the particles.

The Shielding physics list has been selected to describe the radionuclides production we were interested in for the thesis.


## Radionuclide activity calculations
By assuming the secular equilibrium, such as the balance between production and destruction of the radioisotopes, we can easily determine a nuclide activity by evaluating the production rate related to a certain GCR flux intensity.
For a more detailed description of the method, see chapter 4.4.3 in the [thesis](https://github.com/Tun98/CosmogenicRadionuclidesEvaluation/tree/main/docs).



