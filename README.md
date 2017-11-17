# IDSC Seesaw

**Getting the necessary programming environment System workbench STM32**

- Go to `http://www.openstm32.org/HomePage`
- Create an account on the website and login
- At the end of Step 1 on the homepage, go to the download area `http://www.openstm32.org/Downloading%2Bthe%2BSystem%2BWorkbench%2Bfor%2BSTM32%2Binstaller`

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

Setup steps:
- Open a terminal on your computer
- Navigate to a folder of your choosing where to put the code
- Then type `git clone https://github.com/idsc-frazzoli/IDSC_Seesaw.git` into your terminal

You should now have access to all the code required to set up the Seesaw in a folder of your choosing. 

--------------------------------------------------------------------------
**Running the code**
- Open the *System Workbench* (STM32) where you installed it in the previous steps
- Click: File->Open Projects from file system....  
- Click on "Directory..." and choose the "IDSC_Seesaw" folder on your computer
- Click "Finish"-button at the right bottom. The folder should now be loaded as a project. 
- Delete the file "makefile" in the Seesaw "Debug"-folder (can be done from SystemWorkbench by right clicking the file and choosing "delete")
- Compile the project (Click the brown hammer).
- Connect your Seesaw to your computer via the USB cable. 
- Run the code by either right-clicking your project and choosing "Run As" and the "Ac6 STM32 C/C++ Application" or by clicking the green arrow in the menu and choosing the same option.
