This is a reconstruction of the older z\_framework that I have for cpp in the past.

I realized that I want to be able to just copy the file to anywhere and it will works.

So instead of putting files into folders, I will put EVERYTHING into a single header file.
The things that are implemented will be grouped by functionality.
The file dependency will be laid out at the top of the files.
The class/method dependency hopefully, will be laid out at the beginning of every methods/class def.
This is to help in deleting the unused method/class from the file if you need to.
       
## zf\_term 
zf\_term is an implementation similar to ncurses, which uses SFML. 
The original idea is to be able to write roguelike games and still support tiles.

## zf\_spritesheet
zf\_spritesheet is a small spritesheet file that allow you to load sprite into a single texture object on the fly.
This is used by zf\_term to manage the ascii characters and the special characters.
