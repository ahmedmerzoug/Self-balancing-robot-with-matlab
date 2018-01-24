%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Calculate the inertias of the vehicle %%
mtot = 0; 
ttot = 0;
%% Wheels
%wheels are not included when calculating
mwheel = 0.03*2; 
mtot = mtot + mwheel;
rwheel = (0.075/2); 
jwheels = ((1/2)*mwheel*rwheel^2); 
%% Motors
mmotor = 0.05528;
mtot = mtot + mmotor;
rmotor = 0.0135; %
Jmotors = ((1/2)*mmotor*rmotor^2)*2; 
% Center of mass calculations
ttot = ttot + mmotor*0;

%% Frame vertical
lframev = 0.50; % Lenght of the frame
dframev = 0.0375;
mframev = 0.6*lframev; % Mass of the frame
mtot = mtot + mframev;
Jframel = (1/12)*mframev*lframev^2 + ...
 mframev*(lframev/2 + dframev)^2; % Ineria of the vertical frame.
% Center of mass calculations
ttot = ttot + mframev*(lframev /2);

%%%% Top part of the frame
lframet = 0.10; % Lenght of the frame
dframet = 0.5485;
mframet = 0.6*lframet; % Mass of the frame
bframet = 0.022; % Height of the frame
cframet = 0.1; % Width of the frame
mtot = mtot + mframet;
Jframe2 = (1/12)*mframet*(bframet^2 + cframet^2) + ...
mframet*dframet^2; % Ineria of the top frame.
%center of mass calculations
ttot = ttot + mframet*dframet;

%% Frame horisontal (steiners law)
lframeh = 0.3; % Length of the frame
mframeh = 0.6*lframeh; % Mass of the frame
mtot = mtot + mframeh;
bframeh = 0.022; % Height of the frame
cframeh = 0.022; % Width of the frame
dframeh = 0.03; % Distance from the rotational axis
Jframe3 = (1/12)*mframeh*(bframeh^2 + cframeh^2) + ...
mframeh*dframeh^2; % Ineria of the horisontal frame.
%center of mass calculations
ttot = ttot + mframeh*dframeh;

%% Box containing all the electronics(steiners law vertical placing)
mbox = 1.5; % mass of the microcontroller
mtot = mtot + mbox;
bbox = 0.039; % height of the microcontroller
cbox = 0.2; % lenght of the microcontroller
dbox = 0.15; % distance from the rotational axis
Jbox = (1/12)*mbox*(bbox^2 + cbox^2) + ...
mbox*dbox^2; % Ineria of the microcontroller.
%center of mass calculations
ttot = ttot + mbox*dbox;

%% Total inertia of the vehicle
mtot;
masscenter = ttot/mtot;
%theels in not included in Jvehicle
Jvehicle = Jmotors + Jframel + Jframe2 +Jframe3 + Jbox;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%% Constants for simulink model for rAFbot %%
%% General constants
g = 9.82;
TS = 0.02;

%% DC—motor constants
N = 30; 
rm = 7.4;
max_omega =200*(2*pi/(60));
max_volt = 12;
stall_torque = 0.49;
kt = (stall_torque*rm)/max_volt;
kv = (stall_torque*rm)/(kt*max_omega);

%% Vehicle constants
Ip = Jvehicle;
Iw = jwheels;
rp = masscenter;
%% center to the centre of gravity
mp = mtot;
rw = rwheel;
mw = mwheel;

%% State feedback controller
alpha = rm*(mp*rp^2+Ip);
beta = rm*(Iw+mp*rw^2+mw*rp^2);
gamma = mp*rp*rm;
A = [0 1 0];
(beta*gamma*g-rw^2*gamma^2)/(alpha*beta-gamma^2*rw^2)  * 2*kt*kv*(gamma*rw+beta)/(alpha*beta-gamma^2*rw^2);
(gamma*rw*alpha-gamma^2*rw*g)/(alpha*beta-gamma^2*rw^2)  2*kt*kv*(-gamma*rw-alpha)/(alpha*beta-gamma^2*rw^2)];
B = [0 2*kt*(-gamma*rw-beta)/(alpha*beta-gamma^2*rw^2)
2*kt*(gamma*rw+alpha)/(alpha*beta^gamma^2*rw^2)]';
C = [1 0 0; 0 1 0; 0 0 l];
D = [0 0 0]';

%% LQ calculations
Q = [200000 0 0; 0 1 0; 0 0 1];
R = 10; %plot simulation
[L,S,P] =lqrd (A,B,Q,R,TS);
Kr = 1/((C*inv(-A+B*L))*B); 

%% Kalman calculations
plant = ss(A,B,[1 0 0; 0 1 0; 0 0 0], 0);
plant_cont = plant;
plant = c2d(plant,Ts);
kalmanQ = 100;
kalmanR = [3 0 0: 0 2 0: 0 0 1];
[kalmf,kalmanL, kalmanP, kalmanM, kalmanZ] = kalman(plant, kalmanQ, kalmanR);








