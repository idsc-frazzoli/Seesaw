# IDSC Seesaw

**Getting the necessary programming environment System workbench STM32**

- Go to `http://www.openstm32.org/HomePage`
- Create an account on the website and login
- At the end of Step 1 on the homepage, go to the download area `http://www.openstm32.org/Downloading%2Bthe%2BSystem%2BWorkbench%2Bfor%2BSTM32%2Binstaller`

--------------------------------------------------------------------------
**A note about navigating on your computer using the terminal**

For the Mac and Linux installation is may be necessary to navigate to the folder to which you will have downloaded the programming environment file. If you are using Windows you should be able to bypass the following description.

Common commands to use for this are:
- ls - List all non-hidden files in a directory (same as the command "dir" for Windows)
- cd FOLDERNAME - "change directory", Changes the current directory in which the terminal is open to the one specified in FOLDERNAME. Use "cd .." to go back out of a folder. If necessary, "cd ~" brings you back to "home". 

--------------------------------------------------------------------------
**Mac**
- Scroll to header "Mac" and choose and download file: install_sw4stm32_macos_64bits-v2.2.run
- Move the downloaded file and folder of your choice
- Open the terminal and navigate to the created folder
- type `chmod 777 install_sw4stm32_macos_64bits-v2.2.run` to correct the access rights to the file
- Then run the install by typing `./install_sw4stm32_macos_64bits-v2.2.run` - An install window should appear after a short while
- Click through the install application and install the programming environment in your applications folder (the suggested default)
- The programming environment for the "Seesaw" project should now be successfully installed.

**Windows**
- Scroll to header "Windows" and choose and download file (for 64 bit version): install_sw4stm32_win_64bits-v2.2.exe

**Linux**
- Scroll to header "Linux" and choose and download file: install_sw4stm32_linux_64bits-v2.2.run
- Download the file
- Give the file executable rights
- Install the file (/bin/bash install_sw4stm32_linux_64bits-v2.2.run)

--------------------------------------------------------------------------

**Getting access to existing code**

*Version 1 (easier if not used to git or command line):*
Go to the top of this page and click the green button "Clone or download" on the right side. Download the zip file of the code and unzip it in a place of your choice. 

*Version 2 (from command line):*
Setup steps:
- Open a terminal on your computer
- Navigate to a folder of your choosing where to put the code
- Then type `git clone https://github.com/idsc-frazzoli/Seesaw.git` into your terminal

You should now have access to all the code required to set up the Seesaw in a folder of your choosing. 

--------------------------------------------------------------------------
**Running the code**
- Open the *System Workbench* (STM32) where you installed it in the previous steps
- Click: File->Open Projects from file system....  
- Click on "Directory..." and choose the "Seesaw" folder on your computer
- Click "Finish"-button at the right bottom. The folder should now be loaded as a project. 
- Compile the project (Click the brown hammer). You might have to click more than once. 
- Connect your Seesaw to your computer via the USB cable. 
- Run the code by either right-clicking your project and choosing "Run As" and the "Ac6 STM32 C/C++ Application" or by clicking the green arrow in the menu and choosing the same option.


**Trouble shooting**

- If your Seesaw reacts very strongly at the beginning, try to go to folder "userApps" to file "tControl.c" and lower the motor base spped "uiMotorBaseSpeed" and possibly also the scaling factor of the input commands "dAngleCorrectionConst". 
- If you manage to compile the Seesaw code but cannot run it due to an error similar to "OCD ...", very likely you have to click "Run As..." by right-clicking on your Seesaw project folder and then select the lowest option "Run Configurations". Here it is important that in the tab "Main" the "Target Information" at the bottom is set to: Mcu: "STM32L432KCUx", Board: "NUCLEO-L432KC"
