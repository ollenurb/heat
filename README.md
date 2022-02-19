# Heat
Heat is a real time [heat equation](https://en.wikipedia.org/wiki/Heat_equation)
solver.  It uses SDL2 to simulate a plate in a 2D space, on which you can apply
heat by using the left click of the mouse.

## Motivations
I recently came across this beautiful [YouTube
playlist](https://www.youtube.com/playlist?list=PLZHQObOWTQDNPOjrT6KVlfJuKtYTftqH6),
where I had the opportunity to learn a little more about differential equations,
so I decided to write this program with the hope of consolidating that knowledge
and to learn some numerical methods for solving
[PDEs](https://en.wikipedia.org/wiki/Partial_differential_equation).

## Running the program 
You can run the program either by using the [Nix](https://nixos.org/) package
manager (*recommended*) or CMake.

### Nix
If you are already using Nix you should probably already know the drill.  
Simply run `nix-shell` inside the directory and you are done.

### CMake
1. Clone this repository
2. Run `cmake` inside it
