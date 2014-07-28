function [ ] = saveimage(capcha)
SavePath = uigetdir('E:\ufd\TrainDatabase', 'Select Student Folder' );
file_ext='.jpg';
folder_content = dir ([SavePath,'\*',file_ext]);
nface = size (folder_content,1);
str=int2str(nface+1);
str=strcat(str,'.jpg');
saveas=strcat(SavePath,'\',str);
imwrite(capcha,saveas);
disp('Image Sucessfully Saved As ');
disp(str);
end

