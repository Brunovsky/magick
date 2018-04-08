/**
 * Magick++ Project Demo
 * 
 * [Tutorial] To Setup ImageMagick and Magick++ in Windows
 *  and setup a Magick++ Project in Visual Studio 2017:
 * 
 * <----
 * 1.  Download ImageMagick from
 *   https://www.imagemagick.org/script/download.php
 *   by selecting the appropriate dll.exe in the
 *   Windows section.
 *    @ 7 April 2018, ImageMagick's latest version
 *    was 7.0.7-28. So the relevant files were:
 *       ImageMagick-7.0.7-28-Q{X}-{AR}-dll.exe
 *         {X} = 8 or 16, for 8bit or 16bit ImageMagick.
 *        {AR} = x86 or x64
 *
 * 2.  Install ImageMagick.
 *   2.1  Options:
 *       Add application directory to your system path
 *          Yes. This injects all ImageMagick dlls, magick.exe
 *          and ffmpeg.exe into the PATH. If you do not include this
 *          option you won't be able to use magick from the command line
 *          and will have to include a copy of ImageMagick's dlls into
 *          every project.
 *       Install FFmpeg
 *          Yes (unless you've already installed it independently).
 *          This is a command line utility for manipulation and
 *          conversion of media, video and audio file formats.
 *          https://www.ffmpeg.org/
 *       Associate supported file extensions with ImageMagick
 *          ...
 *       Install legacy utilities (e.g. convert)
 *          No (it's deprecated command line syntax).
 *       Install development headers and libraries for C and C++
 *          Yes, this includes MagickCore, MagickWand which are
 *          the C core API, and Magick++ which is the ImageMagick
 *          API for C++.      
 *
 *   Let's presume you installed ImageMagick to directory
 *    C:\Program Files\ImageMagick-7.0.7-Q16\
 *
 *   2.2  Once done to make a quick verification of the installation
 *     run
 *       magick -version
 *       ffmpeg
 *     Also, try to convert an image you already have on your computer,
 *     it is as simple as running e.g.
 *       magick photo.png photo.jpg      (converts png to jpeg)
 *       magick photo.jpg photo.png      (converts jpeg to png)
 *     on the same directory as the photo.
 *
 * 3.  After installation, go to the installation folder and
 *   start a Visual Studio solution directly from within the folder
 *   Magick++_Demo, by opening the solution file Magick_Demo++.dsw.
 *   Visual Studio should prompt you to irreversibly upgrade the files
 *   found there to versions compatible with Visual Studio 2017.
 *   In ImageMagick 7.0.7-28 this solution includes:
 *     8 projects:
 *       demo, button, detrans, flip, gravity, piddle, shapes, zoom
 *     4 images:
 *       smile.miff, model.miff, smile_anim.miff, tile.miff,
 *
 * 4.  We will focus on building project demo. It contains only demo.cpp.
 *   The main() outputs are three files demo_out_0, demo_out_1 and demo_out_2
 *   all inside the directory Magick++_Demo.
 *
 *     Magick++ projected should be built with the Release configuration
 *     and x64 or x86 architecture, based on which version of ImageMagick you got.
 *
 *   4.1  Open Project demo's Project Settings (Right click > Properties)
 *
 *   4.2  At the top of the Panel you should see two combo boxes
 *     titled "Configuration:" and "Platform:". Set the first to
 *     Release (or All Configurations) and the second to x86 or x64
 *     (or All Platforms) according to which ImageMagick version you downloaded.
 *     If you're on x64 Windows and
 *     the option x64 / All Platforms does not show:
 *       https://stackoverflow.com/questions/14188965/visual-studio-will-not-give-me-the-platform-option-of-64-bit-in-configuration-ma
 *
 *   4.3  In VC++ Directories, add the entry
 *       C:\Program Files\ImageMagick-7.0.7-Q16\include
 *     to the Include Directories line. There should be one or more entries
 *     here already by default, so the result would look something like
 *       C:\Program Files\ImageMagick-7.0.7-Q16\include;$(IncludePath)
 *     To make sure you do not overwrite anything, click on the droparrow
 *     on the right of the text entry field and then on <Edit..> and add a
 *     New Line with the text C:\Program Files\ImageMagick-7.0.7-Q16\include
 *
 *     The above grants access to the monolithic header <Magick++.h>,
 *     which itself includes all the other subheaders of Magick++.
 *
 *   4.4  There are three more similar procedures. The second is in
 *     C/C++ > General >> Additional Include Directories, once again
 *     add the text
 *       "C:\Program Files\ImageMagick-7.0.7-Q16\include"
 *
 *   4.5  The third is in Linker > General >> Additional Library Directories,
 *     add the text
 *       "C:\Program Files\ImageMagick-7.0.7-Q16\lib"
 *
 *     The above indicates the location of the dynamic libraries
 *     used by ImageMagick++.
 *
 *   4.6  The last is in Linker > Input >> Additional Dependencies,
 *     here you should add the three individual libraries in the
 *     C:\Program Files\ImageMagick-7.0.7-Q16\lib folder:
 *       CORE_RL_Magick++_.lib
 *       CORE_RL_MagickCore_.lib
 *       CORE_RL_MagickWand_.lib
 *     They should appear ; separated. Some projects might be incorrectly
 *     configured and include other similar libraries; in 7.0.7-28 these
 *     are the ones you want included.
 *
 * 5.  Build (Rebuild) only the project demo at first. No major or complex
 *   build errors should occur. Then run the demo.
 *   If Visual Studio reports no runtime errors and the program
 *   terminates normally you should find the demo_out_*.miff files
 *   in the Magick++_Demo folder.
 *
 *   If ImageMagick cannot read .miff files properly (you open the files but
 *   nothing appears) you should replace every instance of a *.miff file
 *   within the .cpp files with *.jpg or *.png, and convert the 4 images in the
 *   project folder (smile.miff, model.miff, ...) into .jpg or .png
 *   files accordingly. Ironically you can just use magick on cmd to do it.
 *
 *     --> No Windows SDK error. Just set a Windows SDK for the solution
 *      (right click the solution, then Retarget Solution)
 *     .... (I haven't had any other build problems)
 *
 *     If all is good you can repeat #4 for every project one by one,
 *   and experiment them all :-)
 *
 *   Assuming you converted .miff to .jpg files everywhere:
 *   demo outputs demo_out_0.jpg, demo_out_1.jpg, demo_out_2.jpg
 *   button outputs button_out.jpg
 *   ...
 *   
 *
 * 6.  To create your own Magick++ project just replicate step #4.
 *   And then:
 *     #include<Magick++.h>
 *     using namespace Magick;
 * ----!>
 **/

#include <Magick++.h>
#include <iostream>

using namespace Magick;


int main(int argc, char* argv[]) {
	// Initialise Magick with the current directory,
	// do this at the start of any main().
	InitializeMagick(*argv);

    // Load image universe.jpg from img/
	Image univ1jpg("./img/universe.jpg");

    // Save the image in three different formats
	univ1jpg.write("./img/universe.png"); // png
	univ1jpg.write("./img/universe.bmp"); // bitmap
	univ1jpg.write("./img/universe.gif"); // gif

	return 0;
}