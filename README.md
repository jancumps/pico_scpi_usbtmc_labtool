# pico_scpi_usbtmc_labtool
LabVIEW compatible instrument on a Raspberry Pico


Prerequisites:  
Toolchain (and IDE) that can build Pico projects with CMake  
Pico C SDK 1.5  

Clone the repository with its subrepositories, to get the application, the Pico SCPI USBTMC_LabLib (PSL) sources, and the Jan Breuer SCPI library:  
git clone https://github.com/jancumps/pico_scpi_usbtmc_labtool.git  --recurse-submodules  
_If you download the archive from github instead, then also download [Pico SCPI USBTMC_LabLib (PSL)](https://github.com/jancumps/pico_scpi_usbtmc_lablib). Extract its contents into the ./pico_scpi_isbtmc_lablib folder._  


Add this variable to your environment:  

    PICO_SDK_PATH (e.g.: C:/Users/jancu/Documents/Pico/pico-sdk)  

If you use VSCode, you can define them via Preferences -> User -> Extensions -> CMake Tools -> CMake: Configure Environment.  


[documentation](https://github.com/jancumps/pico_scpi_usbtmc_labtool/wiki) on GitHub wiki
