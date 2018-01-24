============================================================
% The code is used to determined the controllability of the system
%Produced by Kealeboga Mokonopi
%University of Southern Queens land
% 2006
%====================================================================
function controllabilitymatrix
% System Variables
 M = 0.5;
 m = 0.2;
 b = 0.1;
 i = 0.006;
 g = 9.8;
 l = 0.3;
 p = i*(M+m)+M*m*l^2;
% Production of system amtrices
 A = [0 1 0 0;
 0 -(i+m*l^2)*b/p (m^2*g*l^2)/p 0;
 0 0 0 1;
 0 -(m*l*b)/p m*g*l*(M+m)/p 0];
 B = [0; (i+m*l^2)/p; 0; m*l/p];
 Cm = ctrb(A,B)
Rank = rank(Cm)
==============================================================================================================
============================================================================================================
% The code is used to determined the observability of the system
%Produced by Kealeboga Mokonopi
%University of Southern Queens land
% 2006
%====================================================================
function observabilitymatrix
%system variables and system amtrices
 M = 0.5;
 m = 0.2;
 b = 0.1;
 i = 0.006;
 g = 9.8;
 l = 0.3;
 p = i*(M+m)+M*m*l^2; %denominator
 A = [0 1 0 0;
 0 -(i+m*l^2)*b/p (m^2*g*l^2)/p 0;
 0 0 0 1;
 0 -(m*l*b)/p m*g*l*(M+m)/p 0];
 B = [0; (i+m*l^2)/p; 0; m*l/p];
 C = [1 0 0 0;0 0 1 0];
 Om = obsv(A,C)
Rank = rank(Om) 62
=====================================================================
% The function implements the continous time controller
% using the linear regulator and kalman observer
% Produced by Kealeboga Mokonpi
% USQ, 2006
function lqrcontrl
%====================================================================
% system variables and constants and system matrices
M = .5;
m = 7;
b = 0.1;
i = 0.523;
g = 9.8;
l = 0.25;
p = i*(M+m)+M*m*l^2;
A = [0 1 0 0;
 0 -(i+m*l^2)*b/p (m^2*g*l^2)/p 0;
 0 0 0 1;
 0 -(m*l*b)/p m*g*l*(M+m)/p 0];
B = [ 0;
 (i+m*l^2)/p;
 0;
 m*l/p];
C = eye(4);
D = [0];
ssplant = ss(A,B,C,D);
%======================================================================
set(ssplant, 'InputName', 'Cart Force');
set(ssplant, 'OutputName', {'Cart Pos', 'Cart Vel', 'Pend Angle', 'Pend
Vel'});
set(ssplant, 'StateName', {'Cart Pos', 'Cart Vel', 'Pend Angle', 'Pend
Vel'});
% Design the controller gain
Q = diag([1e9 1e6 1e10 1e5]);
R = 1;
K = lqr(ssplant,Q,R);
%Compute the feedforward gain
Cn=[1 0 0 0];
N=feedforwardG(A,B,Cn,0,K)
cl_sys = feedback(ssplant, -K,+1)
% t_settle = 3;
% damp_ratio = 0.8;
% % Design the observer gain
a = ssplant.a; b = ssplant.b;
c = [1 0 0 0; 0 0 1 0; 0 0 0 1]; d = [0; 0; 0];
QN = 0.1^2;
RN = [0.01^2/12 0 0; 0 0.000017^2/12 0;0 0 0.0873^2/12];63
g = b;
h = d;
obs_plant = ss(a, [b g], c, [d h])
[kest, L] = kalman(obs_plant, QN, RN)
% Create a state space observer-controller
ssobsctrl = ss(a-L*c, [L b-L*d], -K, 0)
% % Augment the plant model to pass the inputs as additional outputs
r = size(b, 2); % Number of inputs
n = size(a, 1); % Number of states
ssplant_aug = ss(a, b, [c; zeros(r, n)], [d; eye(r)]);
% Compute the feedforward gain
Cn=[1 0 0 0];
N=feedforwardG(A,B,Cn,0,K)
% Form the closed loop system with positive feedback
 sscl = N*feedback(ssplant_aug, cl_sys, +1);
 figure
plotpole(sscl, t_settle, damp_ratio);
%Plot the step response
set(sscl,'InputName','r (m)', 'OutputName', {'x(m)', 'theta (rad)',
'angularrate(rad/s)', 'F (N)'});
figure
step(sscl)64
function plot_poles(sscl, t_settle, damp_ratio)
=======================================================================
%PLOT_POLES Plot system pole locations with settling time and damping
ratio constraints.
%
% PLOT_POLES(SSCL, T_SETTLE, DAMP_RATIO)
%
% This function plots the pole locations for the closed loop
% system SSCL along with the settling time constraint
% T_SETTLE (in seconds) and damping ratio DAMP_RATIO.
% By Jim Ledin, 2002.
=======================================================================
plot(pole(sscl), 'o')
axis equal
a = axis;
x_min = a(1); x_max = a(2);
y_min = a(3); y_max = a(4);
settling_pct = 0.01; % If no settling percentage given, use 1%
settling_limit = -log(settling_pct) / t_settle;
if x_max < -settling_limit + 0.1*(x_max - x_min)
 x_max = -settling_limit + 0.1*(x_max - x_min);
 a(2) = x_max;
end
hold on
plot([x_min x_max], [0 0], '--k')
plot([0 0], [y_min y_max], '--k')
plot([-settling_limit -settling_limit], [y_min y_max]);
angle = acos(damp_ratio);
plot([x_min 0 x_min], [x_min*tan(angle) 0 -x_min*tan(angle)])
axis(a)
hold off