%Main
close all
clear all
clc
while (1==1)
    choice=menu('Face Attendance System',...
                'Create Database of Faces',...
                'Delete DataBase',...
                'Train System',...
                'Face Recognition',...
                'Exit');
    if (choice ==1)
        CreateDatabase;
    end
    
    if (choice == 2)
        DeleteDatabase;
    end
    
    if (choice ==3)
        [m, A, Eigenfaces]=Trainit;
    end
    if (choice == 4)
        if exist('train.mat');
            load train;
        end
        FaceRec(m, A, Eigenfaces);
    end
   
    if (choice == 5)
        clear all;
        clc;
        close all;
        return;
    end    
    
end
