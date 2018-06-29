% Plots for PRU example
MAXT=100
waveform = linspace(0, MAXT-1, 100);

plot(waveform)

%%
T = 20*(1/50);
Fs = 1000;
dt = 1/Fs;
t = 0:dt:T-dt;
x = 50*sawtooth(2*pi*10*t)+50;

plot(t,x)
title('Sawtooth Waveform')
grid on

%% Solid sawtooth
T = 5*(1/50);
Fs = 200;
dt = 1/Fs;
t = 0:dt:T-dt;
x = 50*sawtooth(2*pi*10*t)+50;

stem(t,x)
title('Sampled Sawtooth Waveform')
grid on
