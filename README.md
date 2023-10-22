# pico_scpi_usbtmc_labtool
LabVIEW compatible instrument on a Raspberry Pico


Prerequisites:  
Toolchain (and IDE) that can build Pico projects with CMake  
Pico C SDK 1.5  
Jan Breuer [SCPI library](https://github.com/j123b567/scpi-parser)  

Clone the repository with its subrepositories, to get the application and the Pico SCPI USBTMC_LabLib (PSL) sources:  
git clone https://github.com/jancumps/pico_scpi_usbtmc_labtool.git  --recurse-submodules  
_If you download the archive from github instead, then also download [Pico SCPI USBTMC_LabLib (PSL)](https://github.com/jancumps/pico_scpi_usbtmc_lablib). Extract its contents into the ./pico_scpi_isbtmc_lablib folder._  


Add these two variables to your environment:  

    PICO_SDK_PATH (e.g.: C:/Users/jancu/Documents/Pico/pico-sdk)  
    SCPI_LIB_PATH (e.g.: C:/Users/jancu/Documents/elektronica/scpi/scpi-parser/libscpi)

If you use VSCode, you can define them via Preferences -> User -> Extensions -> CMake Tools -> CMake: Configure Environment.  


[documentation](https://github.com/jancumps/pico_scpi_usbtmc_labtool/wiki) on GitHub wiki
