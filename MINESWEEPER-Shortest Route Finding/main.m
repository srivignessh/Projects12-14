function [v] = main(  )
%snap(); %Function To Take PhotoGraph

[x y x0 y0]=cor_detect(); %Function To Fix Coordinates By Fixing Corners

[checks mine pt]= points(x,y,x0,y0); %Function To Fix The CheckPoints and Mines in Coordinates System
disp('Check Points and Mines Location In Cartesian Coordinates');pt
pause();
[route rte]=pathe(checks,mine); %Function To Set The Order Of Checkpoints To Be Selected To Get The Shortest Route
disp('Order of CheckPoints Travelled To Reach The End');route
pause();
traeck=get_track(route,rte); %Function To Get The Route From On Checkpoint To Another

[track] = get_route(traeck); %Function To Get The Complete Route In Coordinates
disp('Movement Coordinates');track
pause();
[u] = directe(track); %Function To Get In NEWS Direction System

[v] = drect(u); % Function To Get Direction In FBLR System

disp('Movement Direction L-Left,R-Right,F-Forward,B-Rotate Back and Move Forward');
num=solution(v); % Function To Display The Solution
%ser(v,num); % Function To Send The Direction Via USB
end