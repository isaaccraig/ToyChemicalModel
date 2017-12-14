# CTTR
Chemistry and Transport Toy Research Model

Inputs NetCDF Files containing gridded Boundary Conditions, Emissions, Initial Concentrations, and Deposition Veloctities
to be used in the construction of relevant operators 

Uses  - 3D Crank Nicolson Advection Diffusion Scheme (Implemented, Lacking Wall Boundary Condition at z=0)
      - Steady State Approximation for HO2 and OH (Implemented, Insufficently Tested)
      - Runge-Kutta Wrapped Chemical Derivative ODE Solver (To be modified from PECANS) 
      
