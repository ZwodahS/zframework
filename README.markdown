This is a reconstruction of the older z\_framework that I have for cpp in the past.
This isn't technically a framework, just bunch of useful code snippet thrown in a place.

The primary reason for redoing the entire codebase is that I realized that I want to be able to just copy the file to anywhere and it will works.
So instead of putting files and individiual classes into folders and files, I will put EVERYTHING into a single header file.
The things that are implemented will be grouped by functionality.
The file dependency will be laid out at the top of the files.
The class/method dependency hopefully, will also be laid out at the beginning of every methods/class def.
These will allow you to detect unused method and delete them appropriately.
       
## zf\_alignment
Defines the basic alignment enum used by various other parts.

## zf\_conversion
Bunch of useful conversion methods 

## zf\_directoin
Defines direction and modifiers.

## zf\_rect
Bunch of useful methods for sf::Rect

## zf\_sprite
Bunch of useful methods for sf::Sprite

## zf\_spritesheet
zf\_spritesheet is a small spritesheet file that allow you to load sprite into a single texture object on the fly.
This is also used by zf\_term and zf\_twindow to manage the ascii characters and the special characters.

## zf\_stringformat
A small and simple implementation for formatting string, similar to boost::format.
I didn't want to rely on boost until necessary. This is usually enough to do the trick.

## zf\_strings
Bunch of useful methods for manipulating strings.

## zf\_term 
zf\_term is an implementation similar to ncurses, which uses SFML. 
The original idea is to be able to write roguelike games and still support tiles.

## zf\_twindow
This is a implementation similar to zf\_term. However, many of the curses like restriction is lifted.
For example, you can create various windows of different cell sizes.
Primarily, it allows you to create a tiled game easier.


The best way to use this codebase, is to treat them like snippets.
Just copy them into your project anywhere you like and include them.
You can remove those that you do not need, or even modify them to suit your needs.

Read the LICENSE for license for the various components.
