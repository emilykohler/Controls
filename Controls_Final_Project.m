% Controls Final Project

%% Constants
i_o = -1;
x_o = .00254;
m = .004;
G_i = 0.3e-5;
g = 9.81;

%% PID Controller
Kp = 1;
Ki = 0;
Kd = 1;

C = pid(Kp, Ki, Kd);

%% Plant
num = [1];
den = [(-m*x_o^2)/(2*G_i*i_o) 0 i_o/x_o];
sys_ol = tf(num, den);
figure; pzmap(sys_ol)

%% Closed Loop System
sys_cl = 4*feedback(sys_ol, C);
figure; pzmap(sys_cl)
figure; rlocus(sys_cl)


