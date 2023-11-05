clc; clear all; close all;

Fx = load('input_Fx.txt');
Fy = load('input_Fy.txt');
Fz = load('input_Fz.txt');
Mx = load('input_Mx.txt');
My = load('input_My.txt');
Mz = load('input_Mz.txt');

fp = fopen('force_data.csv', 'w+');

indx = 1;

while indx <= size(Fx, 1)
   
    fprintf(fp, '%3.7f,%3.7f,%3.7f,%3.7f,%3.7f,%3.7f\n', ...
        Fx(indx,2), Fy(indx,2), Fz(indx,2), Mx(indx,2), My(indx,2), Mz(indx,2));
    indx = indx + 1;
    disp(indx);
    
end

close('all')