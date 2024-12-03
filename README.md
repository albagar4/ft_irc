<div align="center">
    <img src="https://github.com/15Galan/42_project-readmes/blob/master/banners/cursus/projects/ft-irc-light.png?raw=true#gh-light-mode-only" alt="Banner (claro)" />
    <img src="https://github.com/15Galan/42_project-readmes/blob/master/banners/cursus/projects/ft-irc-dark.png?raw=true#gh-dark-mode-only" alt="Banner (oscuro)" />
    <br>
  This project is about recreating your own IRC server. You will use an actual IRC client to connect to your server and test it.
  Internet is ruled by solid standars protocols that allow connected computers to interact with each other.
  It's always a good thing to know.
    <br>
	<table>
	<tr><th>Albagar4 (Authentification, server initialization)</th>
		<td><a href='https://profile.intra.42.fr/users/albagar4' target="_blank">
        <img alt='42 (oscuro)' src='https://img.shields.io/badge/Málaga-black?style=flat&logo=42&logoColor=white'/></td>
	</tr>
	<tr><th>Escastel (Messaging, bonus)</th>
		<td><a href='https://profile.intra.42.fr/users/escastel' target="_blank">
        <img alt='42 (oscuro)' src='https://img.shields.io/badge/Málaga-black?style=flat&logo=42&logoColor=white'/></td>
	</tr>
	<tr><th>Alvega-g (Channels, operator)</th>
		<td><a href='https://profile.intra.42.fr/users/alvega-g' target="_blank">
        <img alt='42 (oscuro)' src='https://img.shields.io/badge/Málaga-black?style=flat&logo=42&logoColor=white'/><br></td>
	</tr>
	</table>    
    <img src="https://img.shields.io/badge/score- 125%20%2F%20100-success?color=%2312bab9&style=flat" />
    </a>
<div>
	<img src="https://i.ibb.co/tQjS65G/Screenshot-from-2024-12-03-13-55-28.png"/>
</div>
</div>

---

# Mandatory part

<table>
  <tr>
    <th>Program name</th>
    <td><em>ircserv</em></td>
  </tr>
  <tr>
    <th>Turn in files</th>
    <td>Makefile, *.{h, hpp}, *.cpp, *.tpp, *.ipp, an optional configuration file</td>
  </tr>
  <tr>
    <th>Makefile</th>
    <td><code>NAME, all, clean, fclean, re, bonus</code></td>
  </tr>
  <tr>
	<th>Arguments</th>
	<td>a map in format <code>*.cub</code></td>
  </tr>
  <tr>
    <th>External functions</th>
    <td><code>open, close, read, write, printf, malloc, free, perror, strerror, exit</code><br>
		All functions of the math library (<code>-lm man man 3 math</code>)<br>
		All functions of the MLX42
	</td>
  </tr>
  <tr>
	<th>Libft authorized</th>
	<td>Yes</td>
  </tr>
  <tr>
    <th>Description</th>
    <td>You must create a “realistic” 3D graphical representation of the inside of a maze from a first-person perspective. You have to create this representation using the Ray-Casting principles mentioned earlier.</td>
  </tr>
</table>

The constraints are as follows:

- You **must** use the **MLX42**. Either the version that is available on the operating system, or from its sources. If you choose to work with the sources, you will need to apply the same rules for your **libft** as those written above in **Common Instructions** part.
- The management of your window must remain smooth: changing to another window, minimizing, etc.
- Display different wall textures (the choice is yours) that vary depending on which side the wall is facing (North, South, East, West).
- Your program must be able to set the floor and ceiling colors to two different ones.
- The program displays the image in a window and respects the following rules:
  - The left and right arrow keys of the keyboard must allow you to look left and right in the maze.
  - The W, A, S, and D keys must allow you to move the point of view through the maze.
  - Pressing **ESC** must close the window and quit the program cleanly.
  - Clicking on the red cross on the window’s frame must close the window and quit the program cleanly.
  - The use of **images** of the **MLX42** is strongly recommended.
- Your program must take as a first argument a scene description file with the **.cub** extension.
  - The map must be composed of only 6 possible characters: **0** for an empty space, **1** for a wall, and **N**,**S**,**E** or **W** for the player’s start position and spawning orientation.
    This is a simple valid map:

```bash
111111
100101
101001
1100N1
111111
```

- The map must be closed/surrounded by walls, if not the program must return an error.
- Except for the map content, each type of element can be separated by one or more empty line(s).
- Except for the map content which always has to be the last, each type of element can be set in any order in the file.
- Except for the map, each type of information from an element can be separated by one or more space(s).
- The map must be parsed as it looks in the file. Spaces are a valid part of the map and are up to you to handle. You must be able to parse any kind of map, as long as it respects the rules of the map.
- Each element (except the map) firsts information is the type identifier (composed by one or two character(s)), followed by all specific informations for each object in a strict order such as :
- North texture:
  - identifier: **NO**
  - path to the north texure

```bash
NO ./path_to_the_north_texture
```

- South texture:
  - identifier: **SO**
  - path to the south texure

```bash
SO ./path_to_the_south_texture
```

- West texture:
  - identifier: **WE**
  - path to the west texure

```bash
WE ./path_to_the_west_texture
```

- East texture:
  - identifier: **EA**
  - path to the east texure

```bash
EA ./path_to_the_east_texture
```

- Floor color:
  - identifier: **F**
  - R,G,B colors in range [0,255]: **0, 255, 255**

```bash
F 220,100,0
```

- Ceiling color:
  - identifier: **C**
  - R,G,B colors in range [0,255]: **0, 255, 255**

```bash
C 225,30,0
```

- Example of the mandatory part with a minimalist **.cub** scene:

```bash
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
F 220,100,0
C 225,30,0
1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

- If any misconfiguration of any kind is encountered in the file, the program must exit properly and return "Error\n" followed by an explicit error message of your choice.

# Bonus part

Bonus list:

- Wall collisions.
- A minimap system.
- Doors which can open and close.
- animated sprite.
- Rotate the point of view with the mouse.

# How to run

Clone this repository and execute it by running the following commands:

```bash
git clone https://github.com/ColmiiK/cub3d.git
cd cub3d
make bonus
./cub3D_bonus maps/subject.cub
```

You can also compile the mandatory part only by running `make` instead of `make bonus`, but remember that the mandatory part doesn't have collisions, mouse movement, a minimap or animated sprites.

You can change the window size by modifying `W_HEIGHT` and `W_WIDTH` in `include/cub3D_bonus.h`.

### For instructions on how to build the dependencies needed, check out [Codam's MLX42](https://github.com/codam-coding-college/MLX42).
