# Heat
Heat is a real time 2D [heat equation](https://en.wikipedia.org/wiki/Heat_equation)
solver. It uses SDL2 to simulate a hypothetical "plate" in a 2D space and the evolution
of its temperature through time.

## Motivations
I recently came across this beautiful [YouTube
playlist](https://www.youtube.com/playlist?list=PLZHQObOWTQDNPOjrT6KVlfJuKtYTftqH6),
where I had the opportunity to learn a little more about differential equations,
so I decided to write this program with the hope of consolidating that knowledge
and to learn some numerical methods for solving
[PDEs](https://en.wikipedia.org/wiki/Partial_differential_equation).
I also decided to use [CUDA](https://developer.nvidia.com/cuda-toolkit) to accelerate
the computations using a GPU.

## Running the program 
You can run the program either by using the [Nix](https://nixos.org/) package
manager (*recommended*) or CMake. It is mandatory that you have a CUDA capable
GPU to run the program with hardware acceleration.

### Nix
If you are already using Nix you should probably already know the drill.  
Simply start `nix-shell` inside the directory and you are done.

### CMake
1. Grab the latest CUDA toolkit available
2. Clone this repository
3. Run `cmake` inside it.

By default, GPU acceleration is ON. You can turn it off with `cmake -DGPU=OFF`.
