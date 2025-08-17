# Playlist editor for THPS2 patch
This folder contains everything needed to edit soundtrack in music.db. 
Backup music.db before editing. 

1. If ```sqlite3.exe``` is not present in the folder, download the official ```sqlite3.exe``` command line utility from https://www.sqlite.org/ and copy to this folder.
2. Open ```sql_music_list.csv``` in Notepad or any other text editor, by default it contains original THPS2PC soundtrack entries.
3. Add a few lines in the following format ```<game>,<track_number>,<artist>,<title>,<file>```
4. Save changes and launch ```sql_music_import.bat``` (it will execute SQL queries to import the data)
5. It should create ```music.db``` file and output the new soundtrack table contents in a cmd window.
6. Copy ```music.db``` file to ```patch``` folder.
5. Launch the game to check if it worked.

Keep in mind that this procedure will completely wipe existing soundtrack entries from the database, so you must have every single entry in your CSV.
Keep source CSV file along the database if you plan to edit your soundtrack regularly. Otherwise you can extract existing data using some SQLite editor like SQLiteStudio.

# Audio files
.DAT files found in music folder of the game are just renamed .BIK files in Bink audio format. 
You need to obtain a copy of RAD Game Tools/RAD Video Tools https://www.radgametools.com/bnkdown.htm

More details here: https://github.com/DCxDemo/THPS2-Cumulative-Patch/wiki/Music-editing
