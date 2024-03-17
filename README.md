# EcosisSim

#Grids
idea is to have a self containing grid system that holds an actor on its tiles(named BaseGrid , naming was kind of bad). The crucial thing was to every grid needs to know its neighbors , that way its way more managable to move between grids, using pathfinders or simply for better performance.

#Mammals

i will have a mammal base class that represents every mammal we can put into the game. It will have the base functions such as moving, breeding , dying. Every other mammal can override those functions for spesific things such as moving differently.
Also every mammal will have a age. Mammal manager should manage the spawning and all the information on those mammals.

#Turn based system

to make a turn based system i thought of a Turn manager. At first thought its only job was to manage rounds , but later on i found no usage on the concept of "Rounds" being its own seperate thing. Because of that reason im using it kind of lke a GameManager , where it will manage the game start , creation of grids and the state of the game etc. Right now its kind of blurry so the naming was my fault.
