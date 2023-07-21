% GCR spectrum calculation for Geant4 energy histogram
clear all
close all

meteoriteRadius = 241; % m

mp = 938.27208816; % MeV - rpton rest mass
A = 9.9e8; % m-2 s-1 MeV-1 sr-1
x = @(E) 780*exp(-2.5e-4*E);
phi = 660; % MeV - modulation parameter

J = @(E) A* E*(E + 2*mp)*power(E + x(E) + phi, -2.65)/( (E + phi)*(E + 2*mp + phi) ); % particles/(MeV m2 sr s)

% figure(1)
% fplot(J, 'LineWidth', 2 , 'Color', 'red')
% set(gca, 'LineWidth', 2, 'XMinorTick', 'on', 'YMinorTick', 'on', 'FontSize', 20, 'FontWeight', 'bold')
% xlabel('Energy [MeV]', 'FontSize', 15)
% ylabel('Flux [MeV-1 cm-2 s-1 sr]', 'FontSize', 15)
% set(gca, 'YScale', 'log', 'XScale', 'log')
% set(gca, 'YLim', [10e-4 10e3], 'XLim', [10e-1 10e4])
% grid on
% grid minor
% title('GCR Flux')

energy1 = 1:0.05:10; % MeV
energy2 = 10.5:0.5:100; % MeV
energy3 = 105:5:1000; % MeV
energy4 = 1050:50:5000; % MeV
energy5 = 5500:500:100000; % MeV
energy = [energy1, energy2, energy3, energy4, energy5];

integralFlux = integral(J, 0, inf, ArrayValued=true) % particles/(m2 sr s)
NumberOfParticles = integralFlux*4*pi*pi*meteoriteRadius*meteoriteRadius % particles/s

meanFlux = zeros(length(energy) - 1, 1);

index = 1;
while index <= length(energy) - 1
    meanFlux(index) = integral(J, energy(index), energy(index+1), ArrayValued=true) / ( energy(index+1) - energy(index) ); % particles/(MeV m2 sr s)
    index = index + 1;
end

% index = 1;
% while index <= length(energy) - 1
%     meanFlux(index) = J(energy(index));
%     index = index + 1;
% end

meanFlux = meanFlux';
energy = energy(1:length(energy)-1);
output = [energy; meanFlux];

% figure(2)
% hold on
% fplot(J, 'LineWidth', 2 , 'Color', 'red')
% bar(energy, meanFlux)
% hold off
% set(gca, 'LineWidth', 2, 'XMinorTick', 'on', 'YMinorTick', 'on', 'FontSize', 20, 'FontWeight', 'bold')
% xlabel('Energy [MeV]', 'FontSize', 15)
% ylabel('Flux [MeV-1 cm-2 s-1]', 'FontSize', 15)
% set(gca, 'YScale', 'log', 'XScale', 'log')
% set(gca, 'YLim', [10e-4 10e3], 'XLim', [10e-1 10e4])
% grid on
% grid minor
% title('GCR Flux')

fileID = fopen('spectrum.txt', 'w');
fprintf(fileID,'%6.2f %12.9f\n', output);
fclose(fileID);