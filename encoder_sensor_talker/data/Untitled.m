clc; clear all; close all;

q1 = load('input_q1.txt');
q2 = load('input_q2.txt');
q3 = load('input_q3.txt');
q4 = load('input_q4.txt');
q5 = load('input_q5.txt');
q6 = load('input_q6.txt');

fp = fopen('encoder_data.csv', 'w+');

indx = 1;

while indx <= size(q1, 1)
   
    fprintf(fp, '%3.7f,%3.7f,%3.7f,%3.7f,%3.7f,%3.7f\n', ...
        q1(indx,2), q2(indx,2) + 0.646261, q3(indx,2) - 1.33882, q4(indx,2) + 0.692555, q5(indx,2), q6(indx,2));
    indx = indx + 1;
    disp(indx);
    
end

close('all')