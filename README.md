# NASA-SOAR_BoiseState
This is to store code for the NASA SOAR module created by the Boise State team

### Downloading the Arduino IDE 
While we are using C in order to program our Arduino, it would be best to use the Arduino IDE to better interface with the board. You can use the following download links to install the latest Arduino IDE for your machine.

[Windows](https://www.arduino.cc/download_handler.php?f=/arduino-1.8.3-windows.exe)

[Mac OS (10.7 Lion or newer)](https://www.arduino.cc/download_handler.php?f=/arduino-1.8.3-macosx.zip)

[Linux (64-bit)](https://www.arduino.cc/download_handler.php?f=/arduino-1.8.3-linux64.tar.xz)

###### All other downloads of the IDE can be seen at: https://www.arduino.cc/en/Main/Software

### How to clone into this repo
From you home directory type in the following

	$ mkdir Projects && cd $_

You can type the following commands straight into the bash shell from your directory in order to clone the contents of this repo

##### Using HTTPS:

	$ git clone https://github.com/jdguevara/NASA-SOAR_BoiseState.git
##### Using SSH:

	$ git clone git@github.com:jdguevara/NASA-SOAR_BoiseState.git
Using SSH is a faster and safer way to upload and download changes to and from the repo. If you'd like to learn how to generate an SSH key ,and upload it to GitHub, you can find the article [here](https://help.github.com/articles/connecting-to-github-with-ssh/).

### Compiling and Running the Arduino code and files
Now that you have the correct files in your repo, in order for the Arduino IDE to properly communicate with the board you will need to pass it the following libraries:

- Adafruit_MAX31865 (Temperature sensor library)

From the project directory, that contains these files, move or copy the files to the Arduino library located in 

	~/Documents/Arduino/libraries
Once the files have been passed to the libraries folder, you can do the following to get the code operational:

1. Open the Arduino IDE
	1. Go to _File_, or click the _Open_ icon
	2. Select the Arduino file containing the code desired
2. Go to _Tools_ 
	1. Select _Board:_ 
	2. Select _Board Manager_ from the drop-down list
	3. Type _SAMD_ into the search bar
	4. If the first, and only, package is not already installed then go ahead and install it
3. Go back to _Tools_
	1. Select _Board:_
	2. Select _Arduino MKRZero_ from the drop-down list
4. Go to _Sketch_
	* Select _Verify/Compile_
5. Go back to _Sketch_
	* Select _Upload_

This should successfully get the code running on your machine. 

##### However, the IDE may need to be told which port select in order to communicate with the Arduino. To tell the IDE which port to use, follow these steps:

* Select _Tools_
	* From the drop-down list look for the port that contains a connection to the Arduino board

##### Now repeat step 5 above to get the code running
