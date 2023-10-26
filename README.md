# 2048_Game_AI_CPP
Functional AI for solving the old mobile game 2048. 

# Run the script
On linux, and after installing the g++ cpp compiler run the two following commands in the terminal

  1) g++ -o main main.cpp
  2) ./main

When requested, input the number of pieces to add and their position (expressed in coords X and Y, with (0,0) being on top left and (4,4) on bottom right)

# Max score
with this naive algorithm the AI can reach up to 80K in score
however in the second version, an optimization was added that increased maximum score all the way to 130k

# Credits
All credits goes to AnasImloul, I have just added user inputs in the program routine
