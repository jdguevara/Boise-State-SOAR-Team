# Boise State SOAR Team

This is the repo for the NASA SOAR Team at Boise State. It contains the necessary files for the high-altitude data collection module. Please read through the following sections to learn how to clone the files to your machine, how to compile them, and how to run them. There'll also be sections dedicated to topics that might not be known to all, with links to tutorials/guides on such topics. If you need help, or encounter any problems while following these instructions, feel free to contact the CS team.

## Cloning the Repo

To clone into the repo type the following into your command line

##### HTTPS:
```
git clone https://github.com/jdguevara/Boise-State-SOAR-Team.git
```
##### SSH:

This method is preferred as it is safer and faster than through HTTPS. If you do not have an SSH key, then [this](https://help.github.com/articles/connecting-to-github-with-ssh/) article will help you with both generating an SSH key and adding it to your github account.
```
git clone git@github.com:jdguevara/Boise-State-SOAR-Team.git
```

###### Before cloning into the repo, please make sure to have Jaime Guevara (jdguevara) grant you collaborator permission. This will allow you to clone, as well as push and pull from the repo.

## Downloading the Arduino IDE

Since the module utilizes the Arduino MKRZero board you'll need to use the Arduino IDE in order to interact with the Arduino board and be able to program the module. You can download the IDE [here](https://www.arduino.cc/en/Main/Software), there are links to all the different versions depending on your machine's OS. However, the download link will take you to a page with a large donation banner, but don't worry you don't have to pay for the IDE as the download link is nestled right below the banner.

## Passing the Necessary Libraries to the IDE

<Under construction>

## Setting Up the Correct Board in the IDE

Once you have the files in your machine, and the IDE downloaded you can access the program and link the board in the following manner:
 - Start Arduino IDE
 - Open the desired file
 - Head to the "Tools" menu
   * Open the "Board" drop-down menu
   * Check for Arduino MKRZero
      - If the Arduino MKRZero board is not present select "Boards Manager"
      - Type "SAMD" into the search bar
      - Install the "Arduino SAMD Boards (32-bit ARM Cortex-MO+)
   * Repeat the first three steps, then select the Arduino MKRZero board
 - In the "Tools" menu, check the "Port" drop-down and select the one for the Arduino
 - Under "Sketch" select "Verify/Compile"
 - Go back to "Sketch" and select "Upload" to start the program
 - To see the program in action, go to "Tools" and select "Serial Monitor"

## Creating a Fork/Branch in Git

One of the main purposes of this repo is so that everyone can contribute to the module code, without being dependent upon one person's machine. However, we do not want to make changes to the Master Code unless decided upon by the CS team. So in order for people to be able to work on the code, and not alter the Master, you can create a fork which will copy your work from the Master so you can use it and change it without affecting the Master itself or being dependent on the Master. To learn more about forking you can click [here](https://help.github.com/articles/fork-a-repo/) (for forking the repo) or [here](https://guides.github.com/activities/forking/) (for forking a project).

Another way to separate your own code from that of the main is to create a branch. Branching allows you to separate your work from the Master, but it is still dependent upon the Master itself, so if the Master is erased then the branch goes with it. To learn more about branching you can click [here](https://help.github.com/articles/creating-and-deleting-branches-within-your-repository/). 

###### If you want to learn more about the differences and advantages of forking vs. branching, check [this](https://confluence.atlassian.com/bitbucket/branch-or-fork-your-repository-221450630.html) out.

###### If at any point you need help with any of these steps, or would like access as collaborator to the repo, send a message through Slack to the CS team, or contact Jaime Guevara through email @: jaimeguevara@u.boisestate.edu. 
