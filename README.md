# CUB3D


##TODO

#MAP Parsing


## HOW THE FUCK DOES RAYCASTING WORK

For every x of the screen (i.e. for every vertical stripe of the screen), send out a ray that starts at the player location and with a direction that depends on both the player's looking direction, and the x-coordinate of the screen.


If it hit a wall, calculate the distance of this hit point to the player, and use this distance to calculate how high this wall has to be drawn on the screen.


For infinite precision with this method, an infinitely small step size, and thus an infinite number of calculations would be needed! That's pretty bad, but luckily, there's a better method that requires only very few calculations and yet will detect every wall: the idea is to check at every side of a wall the ray will encounter. We give each square width 1, so each side of a wall is an integer value and the places in between have a value after the point. Now the step size isn't constant, it depends on the distance to the next side

To rotate a vector, multiply it with the rotation matrix

[ cos(a) -sin(a) ]
[ sin(a)  cos(a) ]

(0 , 0)  (0 , 1) line = dist(a , b) * tan(FOV / 2)


(0 , 0 , 0) * (0 , 0 , 1) -> FOV 90🟡  = (       )