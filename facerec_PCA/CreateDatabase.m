function []=CreateDatabase
cd TrainDatabase;
while (1==1)
    choice=menu('Create Database',...
                  ' Add  an  Image',...
                  ' Add  a  Folder',...
                  ' Exit');
    if (choice ==1)
        addimage;
    end
    if (choice == 2)
        addfolder;
    end
    if (choice == 3)
        cd ..;
        clc;
        close all;
        return;
    end    
end
end