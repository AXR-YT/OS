#!/bin/bash
echo "creating directories";

echo "enter directory name: "; 
read dirname;

mkdir "$dirname";

echo "do you want to create a sub-directory (y/n)? ";
read choice;

if [ "$choice" = "y" ]; then
    cd "$dirname";
    echo "enter name of sub directory";
    read subdirname;
    mkdir "$subdirname";
fi

echo "do you want to create a text file (y/n)? ";
read choice2;

if [ "$choice2" = "y" ]; then
    cd "$subdirname";
    echo "enter name of text file";
    read textname;
    cat > "$textname";
fi

echo "do you want to create a copy of the text file and rename it(y/n)? ";
read choice3;
if [ "$choice3" = "y" ]; then
	
    echo "enter name of text file";
    read textname2;

   cp "$textname" "$textname2";
fi


echo "do you want to set r/w/x for owner and r for group/others ";

read choice4;
if [ "$choice4" = "y" ]; then
 chmod 744 "$textname"  
echo "permissions set!";

fi

cd "$subdirname";
echo "Listing files with permissions in $subdirname:";
ls -l;