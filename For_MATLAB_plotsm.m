% Captura en temps real de temps i dos percentatges

%% Obertura del port s�rie (COM)

% Elimina previs
delete(instrfind({'Port'},{'/dev/ttyS255'}));
% Crea objecte s�rie
s = serial('/dev/ttyS255','BaudRate',9600,'Terminator','CR/LF');
warning('off','MATLAB:serial:fscanf:unsuccessfulRead');
% Obre el port
fopen(s);

%% Set-up

% Par�metres
t = 15; % Temps en segons que vol representar-se
delta_t = 0.002; % Separaci� en segons entre mostres consecutives
n_samples = round (t / delta_t); % No. de mostres

% Prepara la figura
f = figure('Name','Captura');
a = axes('XLim',[0 t],'YLim',[0 101],'YLim',[0 101]);
l1 = line(nan,nan,'Color','r','LineWidth',2);
l2 = line(nan,nan,'Color','b','LineWidth',2);

xlabel('Temps (s)')
ylabel('Percentatge')
grid on
hold on

%% Bucle
% inicialitzar
x = zeros(1,n_samples);
y1 = zeros(1,n_samples);
y2 = zeros(1,n_samples);
n = 0;

while n < n_samples
    % Lectura del port s�rie
    n = n + 1;
    a = fscanf(s,'%g,%d,%d');
    x(n) = a(1);
    y1(n) = a(2);
    y2(n) = a(3);
    % Representaci� gr�fica
    set(l1,'YData',y1(1:n),'XData',x(1:n));
    set(l2,'YData',y2(1:n),'XData',x(1:n));
    drawnow
end
fprintf('Temps: %g s, separaci� entre mostres consecutives: %g, no. de mostres: %d', t, delta_t, n_samples);

%% Tancament del port

fclose(s);
delete(s);
clear s;

