function [capcha]= capture(vid)
    capcha=getsnapshot(vid);
    capcha=ycbcr2rgb(capcha);
    capcha=imcrop(capcha,[180,20,280,380]);
    imshow(capcha);
end

