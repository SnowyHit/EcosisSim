# EcosisSim

#Grids
idea is to have a self containing grid system that holds an actor on its tiles(named BaseGrid , naming was kind of bad). The crucial thing was to every grid needs to know its neighbors , that way its way more managable to move between grids, using pathfinders or simply for better performance.

#Mammals

i will have a mammal base class that represents every mammal we can put into the game. It will have the base functions such as moving, breeding , dying. Every other mammal can override those functions for spesific things such as moving differently.
Also every mammal will have a age. Mammal manager should manage the spawning and all the information on those mammals.

#Turn based system

to make a turn based system i thought of a Turn manager. At first thought its only job was to manage rounds , but later on i found no usage on the concept of "Rounds" being its own seperate thing. Because of that reason im using it kind of lke a GameManager , where it will manage the game start , creation of grids and the state of the game etc. Naming is kind of in the wrong but couldnt found a better name.

#Roadmap --

-First things first i made the grids , with correct neighbors and changable size.
![GridGeneration](https://github.com/SnowyHit/EcosisSim/assets/25795916/a7b16da5-5f24-47bd-9368-9083d0a5e51e)

-next on the line was creating the general architecture for my code such as mammal manager , turn manager and mammals. General structure was not really hard , after some work done i managed to get my mammals move as i wanted.

-After checking it correctly moves , i controlled other things , breeding and aging. Also i added cats eating and starving mechanic here. thats why i have seperate mammal and cat&mouse classes.

-Lastly i made sure simulation worked , and get to work on smooth movement - mammal per mammal turn system. I find it easier to handle movement on blueprints so i made some arrangements to communicate between bp and cpp. (in here i added changing colors on their move as a flavor)
![Cat MouseBP](https://github.com/SnowyHit/EcosisSim/assets/25795916/e487b4af-3aeb-4f10-8d0d-d56a1109625e)

-In all parts i was updating my ui.

![UIBP](https://github.com/SnowyHit/EcosisSim/assets/25795916/2806e95e-28d5-4d2b-8140-699dec02193a)




https://github.com/SnowyHit/EcosisSim/assets/25795916/41bbcebd-eec7-47b7-aaec-b4a041e4c90f






#Problems i faced

-First problem was right in the movement part. I thought of every grid having their neighbors but for some reason everytime i call the GetFreeNeighbor() function , Neighbor array smacked me. Some digging and debugging later i found out i wasn't callng the correct grid(i was trying to call a null grid instance). After that function worked movement was smoothly done.

-On breeding and aging , there were some problems on the arrays i put my mammals, because of the nature of arrays it wasn't really pleasant to remove/add them(breed / die) while they are looping inside them. I was trying to move all mammals , then age them and breed them and thing were really getting messy. After figuring out the problem and solving one by one moving-aging-breeding problem , this array management problem kind of solved itself. Only last-minute bug was dying. 
[cat , cat ,cat, mouse ,mouse] -> in a array like this if my iterator comes to the mouse , and cat dies from starvation , the array was changing its indexes , hence creating the problem. Solved this by caching dying mammals after their turn if they are below the iterator and removing them after the turn.

-Smooth movement and turn logic. I did underestimated the turn logic , turns out turn manager could have been more usefull for me if i was looking at it from a different angle. I thought of a turn as the mammals were all one player. and thats why i had a bad time trying to mave them one by one. At the end of the day i did figure out a way to make them wait eachother but its far more dirtier than i wanted.


