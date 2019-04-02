# StoneMask
# Installation Windows
Installation de la SDL 1.2 : <br/>D'abord
 <a href="https://sourceforge.net/projects/codeblocks/files/Binaries/17.12/Windows/codeblocks-17.12mingw-setup.exe/download">CodeBlock</a><br/>
 Ensuite, suivre <a href="https://openclassrooms.com/fr/courses/19980-apprenez-a-programmer-en-c/17117-installation-de-la-sdl">ce</a> tuto <br/>
 Installer SDL_Image à partir <a href="https://www.libsdl.org/projects/SDL_image/release/SDL_image-devel-1.2.12-VC.zip">d'ici</a>
 et suivre <a href="https://openclassrooms.com/fr/courses/19980-apprenez-a-programmer-en-c/17796-afficher-des-images#/id/r-17795">ce</a> tuto <br/>
 
 # Installation Linux
 
 Plus besoin des dll<br/>
 
 sudo apt-get install libsdl1.2-dev <br/>
 sudo apt-get install libsdl-image1.2 libsdl-image1.2-dev<br/> 
 Compiler avec <br/>
 gcc -o main main.c `sdl-config --cflags --libs` -lSDL_image -O3 -Wall

# Installation MacOS

Utilisez Windows ou Linux




